////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        bounded_queue
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __BOUNDED_QUEUE_HPP__
#define __BOUNDED_QUEUE_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "array.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<typename __Type, std::size_t __Size = 1024> class bounded_queue
{
   public:   // type definitions and constants

      typedef const __Type*  const_pointer;
      typedef const __Type&  const_reference;
      typedef std::ptrdiff_t difference_type;
      typedef __Type*        pointer;
      typedef __Type&        reference;
      typedef std::size_t    size_type;
      typedef __Type         value_type;

   private:   // nested classes

      template<std::size_t __Size> class position
      {
         public:   // type definitions and constants

         private:   // member variables

            size_type _m_position;

         public:   // member functions

            size_type get_position() const { return _m_position; }

            void set_position(size_type _Value) { _m_position = _Value; }

         public:   // member operators

            size_type operator--() { return _decrement(); }
            size_type operator++() { return _increment(); }

         public:   // constructor | destructor

            position() : _m_position(static_cast<size_type>(0)) { }

            ~position() { }

         private:   // helper functions

            size_type _decrement()
            {
               _m_position == static_cast<size_type>(0) ? _m_position = __Size : --_m_position;

               return _m_position; 
            }

            size_type _increment()
            {
               _m_position >= __Size - static_cast<size_type>(1) ? _m_position = static_cast<size_type>(0) : ++_m_position;

               return _m_position;
            }

      };

   private:   // member variables

      ev4::array<__Type, __Size> _m_array;

      position<__Size> _m_dequeue_position;
      position<__Size> _m_inqueue_position;

      size_type _m_size;

   public:   // member functions

      bool empty() { return _empty(); }
      bool full() { return _full(); }
      __Type pop() { return _pop(); }
      void push(__Type& _Data) { _push(_Data); }
      size_type size() { return _size(); }

   public:   // constructor | destructor

      bounded_queue() : _m_size(0) { }

   private:   // helper functions

      bool _empty() { return _m_size == static_cast<size_type>(0); }
      bool _full() { return _m_size == static_cast<size_type>(__Size); }

      __Type _pop()
      {
         __Type _Temp = _m_array[_m_dequeue_position.get_position()];

         ++_m_dequeue_position;
         --_m_size;

         return _Temp;
      }

      void _push(__Type& _Data)
      {
         _m_array[_m_inqueue_position.get_position()] = _Data;

         ++_m_inqueue_position;
         ++_m_size;
      }

      size_type _size() { return _m_size; }

};   // end of class bounded_queue

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __BOUNDED_QUEUE_HPP__