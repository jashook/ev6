////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        array
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef ARRAY_HPP
#define ARRAY_HPP

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "array_iter.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename __Type, std::size_t __Size> class array
{

   public:   /*   constructor | destructor   */

      //   aggregate type: constructor and destructor provided

   public:   /*   member variables   */

      __Type _data[__Size == 0 ? 1 : __Size]; 

   public:   /*   constants and type definitions   */
      
      typedef __Type value_type;
      typedef std::size_t size_type;
      typedef __Type* pointer;
      typedef __Type& reference;
      typedef const __Type* const_pointer;
      typedef const __Type& const_reference;
      typedef std::ptrdiff_t difference_type;
      typedef array_iter<__Type> iterator;
      typedef const_array_iter<__Type> const_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;


   public:   /*   member functions   */

      reference at(std::size_t _position) { try { return _at_safe(_position); } catch(...) { throw; } }
      const_reference at(size_type _position) const { try { return _at_safe(_position); } catch (...) { throw; } }
      iterator begin() { return iterator(_front()); }
      const_iterator begin() const { return iterator(_front); }
      void clear() { _clear(); }
      bool empty() const { return _size() == 0; }
      iterator end() { return iterator(_end()); }
      const_iterator end() const { return const_iterator(_end()); }
      size_type max_size() const { return _size(); }
      reverse_iterator rbegin() { return reverse_iterator(end()); }
      const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
      reverse_iterator rend() { return reverse_iterator(begin()); }
      const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
      size_type size() const { return _size; }
      __Type* to_c_array() { return _data; }

   public:   /*   member operators   */

       reference operator[] (size_type _offset) { return _data[_offset]; }
       const_reference operator[] (size_type _offset) const { return _data[_offset]; }

   public:   /*   helper functions   */

      reference _at_safe(size_type _position) throw(std::exception)
      {
         if (_position >= _size) throw std::exception("array::at _position is out of range");

         return _data[_position];
      }

      const_reference _at_safe(size_type _position) const throw(std::exception)
      {
         if (_position >= _size) throw std::exception("array::at _position is out of range");

         return _data[_position];
      }

      void _clear() 
      { 
         #if WIN32

          std::memset(_data, 0, sizeof(_data));
          
         #else

          memset(_data, 0, sizeof(_data));
          
         #endif
      }

      pointer _end() { return _data + _size; }
      iterator _front() { return _data; }
      size_type _size() { return _size; }

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   /*   end of namespace(ev4)   */

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif /* ARRAY_HPP */
