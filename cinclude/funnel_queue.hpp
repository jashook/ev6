////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        funnel_queue
//
// Version:       1.0
//
// Modifications:  Built on top of multiple linked lists
//
// Notes:           funnel_queue will deal with the possibility of having multiple producers, but only a single consumer
//                      FIFO non-supportive
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __FUNNEL_QUEUE_HPP__
#define __FUNNEL_QUEUE_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "node.hpp"
#include "linked_list.hpp"
#include "lock.hpp"
#include "lock_handle.hpp"
#include "utility_ext.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {
namespace mts {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename __Type, std::size_t __Update_Size = 1024> class funnel_queue
{
   public:   // public type definitions and constants

      enum ERROR_CODE
      {
         EC_EMPTY                  = 0,
         EC_SUCCESS                = 1,
         EC_LOCKED                 = 2,
         EC_FINISHED               = 3,
         EC_NOT_FINISHED           = 4,
      };

      typedef __Type value_type;
      typedef std::size_t size_type;
      typedef __Type* pointer;
      typedef __Type& reference;
      typedef const __Type* const_pointer;
      typedef const __Type& const_reference;
      typedef std::ptrdiff_t difference_type;
      typedef bidirectional_list_iterator<__Type> iterator;
      typedef const_bidirectional_list_iterator<__Type> const_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

   private:   // private type definitions and constants

      typedef bidirectional_node<__Type> _node;

   private:   // member variables

      bool                       _m_finished;
      linked_list<__Type>        _m_breaker_list;
      linked_list<__Type>        _m_read_list;
      linked_list_ts<__Type>     _m_write_list;
      lock                       _m_lock;
      std::size_t                _m_update_size;

   public:   // member functions

      iterator begin() { return iterator(_m_read_list.begin()); }
      int can_pop() { return _can_pop(); }
      bool empty() const { return _m_read_list.size() == 0; }
      iterator end() { return iterator(_m_read_list.end()); }
      void finish() { _finish(); }
      int is_finished() { return _is_finished(); }
      __Type pop() throw (ERROR_CODE) { return _read(); }
      int push(const __Type& _Data) { return _write(_Data); }
      std::size_t size() { return _m_read_list.size(); }
      bool try_pop() { return _try_read(); }
      std::size_t update_size() { return _m_update_size; }

   public:   // member operators

      funnel_queue<__Type> operator=(const funnel_queue<__Type>& _Rhs) { if (this != &_Rhs) _ctor(); _copy(const_cast<funnel_queue<__Type>&>(_Rhs)); return *this; }
      bool operator==(const funnel_queue<__Type>& _Rhs) { return this == &_Rhs; }

   public:   // constructor | destructor

      funnel_queue() : _m_update_size(__Update_Size), _m_finished(false) { _ctor(); }
      funnel_queue(const funnel_queue<__Type>& _Rhs) { _ctor(); _copy(const_cast<funnel_queue<__Type>&>(_Rhs)); }

      ~funnel_queue() { _dtor(); }

   private:   // helper functions

      int _can_pop() 
      { 
         
         if (_m_read_list.size() == 0) 
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

      void _finish()
      {

         lock_handle _Locked(_m_lock);

         _set_finished(true);

         _transpher_from_write();

      }

      int _is_finished()
      {

         lock_handle _Locked(_m_lock);

         int _ReturnValue = EC_SUCCESS;

         bool _Finished = _m_finished;

         if (_Finished) _ReturnValue = EC_FINISHED;

         else _ReturnValue = EC_NOT_FINISHED;

         return _ReturnValue;

      }

      __Type _read() throw (ERROR_CODE)
      {
         int _Can_Pop = _can_pop();

         if (_Can_Pop == EC_SUCCESS) 
         {
            return _m_read_list.pop_front();
         }

         else if (_Can_Pop == EC_EMPTY)
         {

            lock_handle _Locked(_m_lock);

            bool _Success = _transpher_to_read();

            if (_Success) { return _m_read_list.pop_front(); }
            
            else { throw EC_EMPTY; }
         }

      }

      void _set_finished(bool _Bool) { _m_finished = _Bool; }

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
         mta::move_from_linked_list_ts(_m_write_list, _m_breaker_list);
      }

      bool _try_read()
      {
         // same as can_pop except will transpher to the read queue if empty
         // then check if it can pop 
         // NOTE: WILL BLOCK if empty

         if (_m_read_list.size() == 0)
         {

            lock_handle _Locked(_m_lock);

            return _transpher_to_read();

         }

         else
         {
            return true;
         }

      }

      int _write(const __Type& _Data)
      {
         int _Return_Value = EC_SUCCESS;

         int _Size = _m_write_list.size();

         if (_Size == _m_update_size)
         {
            lock_handle _Locked(_m_lock);

            _transpher_from_write();
         }

         _Return_Value = _m_write_list.push_back(_Data);

         return _Return_Value;
      }

};   // end of class linked_list

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)
}   // end namespace(mts)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __BROQERED_QUEUE_HPP__