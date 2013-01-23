////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        brokered_queue
//
// Version:       1.0
//
// Modifications:  
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __BROKERED_QUEUE_HPP__
#define __BROKERED_QUEUE_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "node.hpp"
#include "linked_list.hpp"
#include "lock.hpp"
#include "lock_handle.hpp"
#include "utility.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {
namespace mts {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename __Type, std::size_t __Update_Size = 1024> class brokered_queue
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

      linked_list<__Type>  _m_transpher_list;
      linked_list<__Type>  _m_read_list;
      linked_list<__Type>  _m_write_list;

      bool                 _m_finished;
      lock                 _m_lock;
      std::size_t          _m_update_size;

   public:   // member functions

      iterator begin() { return iterator(_m_read_list.begin()); }
      int can_pop() { return _can_pop(); }
      bool empty() { return _m_read_list.size() == 0; }
      iterator end() { return iterator(_m_read_list.end()); }
      void finish() { _finish(); }
      int is_finished() { return _is_finished(); }
      void flush() { _flush(); }
      void flush_read() { _flush_read(); }
      bool full_enqueue() { return _m_write_list.full(); }
      __Type pop() throw (ERROR_CODE) { return _read(); }
      int push(const __Type& _Data) { return _write(_Data); }
      std::size_t size() { return _m_read_list.size(); }
      bool try_pop() { return _try_read(); }
      std::size_t update_size() { return _m_update_size; }

   public:   // member operators

      brokered_queue<__Type> operator=(const brokered_queue<__Type>& _Rhs) { if (this != &_Rhs) _ctor(); _copy(const_cast<brokered_queue<__Type>&>(_Rhs)); return *this; }
      bool operator==(const brokered_queue<__Type>& _Rhs) { return this == &_Rhs; }

   public:   // constructor | destructor

      brokered_queue() : _m_update_size(__Update_Size), _m_finished(false) { _ctor(); }
      brokered_queue(const brokered_queue<__Type>& _Rhs) { _ctor(); _copy(const_cast<brokered_queue<__Type>&>(_Rhs)); }

      ~brokered_queue() { _dtor(); }

   private:   // helper functions

      bool _can_pop()
      {
         return !_m_read_list.empty();
      }

      void _ctor() { }
      void _dtor() { }

      void _finish()
      {

         lock_handle _Locked(_m_lock);

         _set_finished(true);

         _transpher_from_write();

      }

      void _flush()
      {
         bool _Transphered;

            do
            {
               lock_handle _Locked(_m_lock);

               _Transphered = _transpher_from_write();
               if (_Transphered) break;
               else mta::sleep(0);
            } while (!_Transphered);
      }

      void _flush_read()
      {
         lock_handle _Locked(_m_lock);

         _transpher_to_read();
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
         bool _Can_pop = !_m_read_list.empty();

         if (_Can_pop) 
         {
            return _m_read_list.pop_front();
         }

         bool _Transphered;

         do
         {
            lock_handle _Locked(_m_lock);

            _Transphered = _transpher_to_read();

            if (_Transphered) return _m_read_list.pop_front();
            else mta::sleep(0);
         } while (!_Transphered);

      }

      void _set_finished(bool _Bool) { _m_finished = _Bool; }

      bool _transpher_to_read()
      {

         if (!_m_transpher_list.empty()) 
         {

            _m_read_list.move(_m_transpher_list);

            return true;

         }

         else
         {
            return false;
         }

      }

      bool _transpher_from_write()
      {
         if (1) 
         {

            _m_transpher_list.move(_m_write_list);

            return true;

         }

         else
         {
            return false;
         }
      }

      int _write(const __Type& _Data)
      {
         int _Return_Value = EC_SUCCESS;

         int _Size = _m_write_list.size();

         if (_Size == _m_update_size)
         {
            bool _Transphered;

            do
            {
               lock_handle _Locked(_m_lock);

               _Transphered = _transpher_from_write();
               if (_Transphered) break;
               else mta::sleep(0);
            } while (!_Transphered);
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