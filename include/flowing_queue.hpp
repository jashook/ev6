////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        flowing_queue
//
// Version:       1.0
//
// Modifications:  
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __FLOWING_QUEUE_HPP__
#define __FLOWING_QUEUE_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "brokered_queue.hpp"
#include "linked_list_ts.hpp"
#include "node.hpp"
#include "iter.hpp"
#include "lock.hpp"
#include "lock_handle.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {
namespace mts {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename __Type, std::size_t __Update_Size = 1024> class flowing_queue
{
   private:   // private type definitions and constants

      typedef mts::brokered_queue<__Type, __Update_Size> _queue;
      typedef mts::linked_list_ts<_queue*> _list;

   public:   // public type definitions and constants

      enum ERROR_CODE
      {
         EC_SUCCESS                = 0,
         EC_LOCKED                 = 1,
         EC_EMPTY                  = 2,
         EC_FINISHED               = 3,
         EC_NOT_FINISHED           = 4,
         EC_CANNOT_JOIN            = 5,
         EC_CANNOT_READ            = 6,
      };

      typedef __Type value_type;
      typedef std::size_t size_type;
      typedef __Type* pointer;
      typedef __Type& reference;
      typedef const __Type* const_pointer;
      typedef const __Type& const_reference;
      typedef std::ptrdiff_t difference_type;
      typedef bidirectional_list_iterator<_queue*> iterator;
      typedef const_bidirectional_list_iterator<_queue*> const_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

   private:   // member variables

      bool           _m_finished;
      lock           _m_lock;
      std::size_t    _m_update_size;
      _list          _m_queue_list;
      _list          _m_non_read_list;
      _queue         _m_list;

   public:   // member functions

      int can_pop(iterator _It) { return _can_pop(_It); }
      bool empty(iterator _It) const { return _get_size( _It) == 0; }
      void finish(iterator _It) { _finish(_It); }
      int is_finished(iterator _It) { return _is_finished(_It); }
      iterator join_write() { return _join_write(); }
      __Type pop(iterator _It) throw (ERROR_CODE) { return _read(_It); }
      int push(iterator _It, const __Type& _Data) { return _write(_It, _Data); } 
      std::size_t size(iterator _It) { return _get_size(_It); }
      bool try_pop() { return _try_read(); }
      std::size_t update_size() { return _m_update_size; }

   public:   // member operators

   private:   // private member operators

      flowing_queue operator=(const flowing_queue<__Type>& _Rhs) { }
      bool operator==(const flowing_queue<__Type>& _Rhs) { return this == &_Rhs; }

      flowing_queue(const flowing_queue<__Type>& _Rhs) { }

   public:   // constructor | destructor

      flowing_queue() : _m_update_size(__Update_Size), _m_finished(false) { _ctor(); }

      ~flowing_queue() { _dtor(); }

   private:   // helper functions

      int _can_pop(iterator _It) 
      { 
         
         if ((*_It).size() == 0) 
         {
            return EC_EMPTY; 
         }
         
         else 
         { 
            return EC_SUCCESS; 
         } 

      }

      void _ctor() { }
      void _dtor() { }

      void _finish(iterator _It)
      {

         (*_It)->finish();

      }

      int _is_finished(iterator _It)
      {

         (*_It)->is_finished();

      }

      iterator _join_write()
      {
         lock_handle _Lock(_m_lock);
         _m_queue_list.push_back(new _queue());

         iterator _It = _m_queue_list.last();
         return _It;
      }

      __Type _read(iterator _It) throw (ERROR_CODE)
      {
         return *(_It)->pop();

      }

      /*void _set_finished(bool _Bool) { _m_finished = _Bool; }

      bool _transpher_to_read()
      {

         if (_m_breaker_list.size() > 0) 
         {

            _m_read_list.move(_m_breaker_list);

            return true;

         }

         else
         {
            return false;
         }

      }

      void _transpher_from_write()
      {
         _m_breaker_list.move(_m_write_list);
      }

      */

      bool _try_read(iterator _It)
      {
         // same as can_pop except will transpher to the read queue if empty
         // then check if it can pop 
         // NOTE: WILL BLOCK if empty

         return (*_It)->try_pop();

      }

      int _write(iterator _It, const __Type& _Data)
      {
         
         return (*_It)->push(_Data);

      }

};   // end of class linked_list

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)
}   // end namespace(mts)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __BROQERED_QUEUE_HPP__