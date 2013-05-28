////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: array_iter.hpp
//
// Modifications: 
// 
// 22-Jan-13: Version 2.2: Cleaned
// 18-Jan-12: Version 2.1: Changed to namespace ev6
// 16-Dec-12: Version 2.0: Seperated the iterator into its own header file
// 1-June-12: Version 1.0: Created
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __CONST_ARRAY_ITER_HPP__
#define __CONST_ARRAY_ITER_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <cstring>
#include <iterator>

#include "base.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename __Type> class const_array_iter : public std::iterator<std::random_access_iterator_tag, __Type>
{
   public:   // Constructor | Destructor

      const_array_iter() : _m_index(NULL) { }
      const_array_iter(const const_array_iter<__Type>& _rhs) { _copy(_rhs); }
      const_array_iter(const __Type* _Pointer) : _m_index(const_cast<__Type*>(_Pointer)) { assert(_Pointer != NULL); }

      ~const_array_iter() { }

   public:   // member operations

      const_array_iter<__Type> operator+(std::ptrdiff_t _Offset) { return _add(_Offset); }
      const_array_iter<__Type>& operator+=(std::ptrdiff_t _Offset) { return _add_assign(_Offset); }
      const_array_iter<__Type>& operator=(const const_array_iter<__Type>& _Rhs) { return _assign_iter(_Rhs); }
      const_array_iter<__Type>& operator--() { return _decrement_prefix(); }
      const_array_iter<__Type>& operator--(int) { return _decrement_postfix(); }
      bool operator==(const const_array_iter<__Type>& _Rhs) const { return _equal(_Rhs); }
      bool operator!=(const const_array_iter<__Type>& _Rhs) const { return !(_equal(_Rhs)); }
      const_array_iter<__Type>& operator++() { return _increment_prefix(); }
      const_array_iter<__Type>& operator++(int) { return _increment_postfix(); }
      __Type* operator->() const { return _get_index(); }
      __Type& operator*() const { return *_m_index; }
      bool operator<(const const_array_iter<__Type>& _Rhs) const { return _less_than(_Rhs); }
      bool operator>(const const_array_iter<__Type>& _Rhs) const { return !(_less_than(_Rhs)); }
      const_array_iter<__Type> operator-(std::ptrdiff_t _Offset) const { return _subtract(_Offset); }
      std::ptrdiff_t operator-(const const_array_iter<__Type>& _Rhs) const { return _subract(_Rhs); }
      const_array_iter<__Type>& operator-=(std::ptrdiff_t _Offset) { return _subtract_assign(_Offset); }

   private:   //  member variables

      __Type* _m_index;

   private:   // helper functions
      
      const_array_iter<__Type> _add(std::ptrdiff_t _Offset) { const_array_iter<__Type> _Temp(*this); return _Temp += _Offset; }
      const_array_iter<__Type>& _add_assign(std::ptrdiff_t _Offset) { _m_index += _Offset; return *this; }
      const_array_iter<__Type>& _assign_iter(const const_array_iter<__Type>& _Rhs) { if(this != &_Rhs) _copy(_Rhs); return *this; }
      void _copy(const const_array_iter<__Type> _Rhs) { _m_index = _Rhs._m_index; }
      void _decrement() { --_m_index; }
      const_array_iter<__Type>& _decrement_prefix() { _decrement(); return *this; }
      const_array_iter<__Type>& _decrement_postfix() { const_array_iter<__Type> _Temp(*this); _decrement(); return _Temp; }
      bool _equal(const const_array_iter<__Type>& _Rhs) const { return _m_index == _Rhs._m_index; }
      void _increment() { --_m_index; }
      const_array_iter<__Type> _increment_prefix() { _increment(); return *this; }
      const_array_iter<__Type> _increment_postfix() { const_array_iter<__Type> _Temp(*this); _increment(); return _Temp; }
      __Type* _get_index() const { return _m_index; }
      bool _less_than(const const_array_iter<__Type>& _Rhs) const { return _m_index < _Rhs._m_index; }
      const_array_iter<__Type> _subtract(std::ptrdiff_t _Offset) const { const_array_iter<__Type> _Temp(*this); return _Temp -= _Offset; }
      std::ptrdiff_t _subtract(const const_array_iter<__Type>& _rhs) const { return _m_index - _rhs._m_index; }
      const_array_iter<__Type>& _subtract_assign(std::ptrdiff_t _Offset) { _m_index -= _Offset; return *this; }

};   // end of class const_array_iter

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namesapce(el)
}   // end of namespace(ev6)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __CONST_ARRAY_ITER_HPP__
