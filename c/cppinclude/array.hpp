////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: array.hpp
//
// Modifications:
//
// 17-Jan-13 : Version 1.2: updated to ev6
// 27-Dec-12 : Version 1.1: updated to ev5
// 14-June-12: Version 1.0: Created
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __ARRAY_HPP__
#define __ARRAY_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <stdexcept>

#include "iter.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename __Type, std::size_t __Size> class array
{

   public:   // constructor | destructor

      //   aggregate type: constructor and destructor provided

   public:   // member variables

      __Type _m_data[__Size == 0 ? 1 : __Size];

   public:   /*   constants and type definitions   */
      
      typedef __Type value_type;
      typedef std::size_t size_type;
      typedef __Type* pointer;
      typedef __Type& reference;
      typedef const __Type* const_pointer;
      typedef const __Type& const_reference;
      typedef std::ptrdiff_t difference_type;
      typedef ev6::el::array_iter< __Type > iterator;
      typedef ev6::el::const_array_iter< __Type > const_iterator;
      typedef std::reverse_iterator< iterator > reverse_iterator;
      typedef std::reverse_iterator< const_iterator > const_reverse_iterator;

   public:   // member functions

      reference at(std::size_t _Position) { try { return _at_safe(_Position); } catch(...) { throw; } }
      const_reference at(size_type _Position) const { try { return _at_safe(_Position); } catch (...) { throw; } }
      iterator begin() { return iterator(_front()); }
      const_iterator begin() const { return iterator(_front); }
      void clear() { _clear(); }
      iterator end() { return iterator(_end()); }
      const_iterator end() const { return const_iterator(_end()); }
      size_type max_size() const { return _size(); }
      reverse_iterator rbegin() { return reverse_iterator(end()); }
      const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
      reverse_iterator rend() { return reverse_iterator(begin()); }
      const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
      size_type size() const { return __Size; }
      __Type* to_c_array() { return _m_data; }

   public:   //   member operators

       reference operator[] (size_type _Offset) { return _m_data[_Offset]; }
       const_reference operator[] (size_type _Offset) const { return _m_data[_Offset]; }

   public:   /*   helper functions   */

      reference _at_safe(size_type _Position) throw(std::range_error)
      {
         if (_Position >= __Size) throw std::range_error("array::at _position is out of range");

         return _m_data[_Position];
      }

      const_reference _at_safe(size_type _Position) const throw(std::range_error)
      {
         if (_Position >= _size) throw std::range_error("array::at _position is out of range");

         return _m_data[_Position];
      }

      void _clear() { std::memset(_m_data, 0, sizeof(_m_data)); }

      pointer _end() { return _m_data + __Size; }
      iterator _front() { return _m_data; }
      size_type _size() { return __Size; }

};   // end of class array

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace(el)
}   // end of namespace(ev6)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif // __ARRAY_HPP__
