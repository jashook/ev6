////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        write_handle
//
// Version:       1.0
//
// Modifications:  
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __WRITE_HANDLE_HPP__
#define __WRITE_HANDLE_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <cassert>

#include "brokered_queue.hpp"
#include "flowing_queue.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {
namespace mts {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<typename __Type, std::size_t __Update_Size = 1024> class write_handle
{
   private:   // private type definitions

      typedef mts::brokered_queue<__Type, __Update_Size> _queue;

   private:   // member variables

      bidirectional_list_iterator<_queue*> _m_iterator;
      flowing_queue<__Type, __Update_Size>* _m_queue;

   public:   // member functions

      void finish() { _finish(); }
      int join_write() { return _join_write(); }
      int push(const __Type& _Data) { return _push(_Data); }
      std::size_t update_size() { return __Update_Size; }

   public:   // constructor | destructor

      write_handle() : _m_iterator(NULL) { }
      write_handle(flowing_queue<__Type, __Update_Size>* _Queue) : _m_iterator(NULL), _m_queue(_Queue) { }

      ~write_handle() { _dtor() }

   private:   // helper functions

      void _ctor()
      {
         assert(_m_queue != NULL);

         _m_queue = new flowing_queue<__Type, __Update_Size>();

      }

      void _dtor()
      {

         if (_m_iterator != NULL) delete _m_iterator;
         if (_m_queue != NULL) delete _m_queue;

      }

      void _finish()
      {

         if (_m_iterator != NULL)
         {
            _m_queue->finish(_m_iterator);
         }

      }

      int _join_write()
      {
         int _ExitValue = 0;

         if (_m_iterator == NULL)
         {
            
            if (_m_queue == NULL) _ctor();

            _m_iterator = _m_queue->join_write();

         }

         else
         {

            _ExitValue = 1;

         }

         return _ExitValue;

      }

      int _push(const __Type& _Data)
      {
         int _ReturnValue = 0;

         if (_m_queue != NULL && _m_iterator != NULL)
         {
            _ReturnValue = _m_queue->push(_m_iterator, _Data);
         }
         
         else
         {
            _ReturnValue = 1;
         }

         return _ReturnValue;

      }

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)
}   // end namespace(mts)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __WRITE_HANDLE_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////