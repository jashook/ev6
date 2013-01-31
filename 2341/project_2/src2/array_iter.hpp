////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        iter
//
// Version:       1.0
//
// Modifications: 
//
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef ARRAY_ITER_HPP
#define ARRAY_ITER_HPP

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iterator>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename _type> class array_iter : public std::iterator<std::random_access_iterator_tag, _type>
{

   public:   /*   Constructor | Destructor   */
      
      array_iter() : _m_index(NULL) { }
      array_iter(const array_iter<_type>& _rhs) { _copy(_rhs); }
      array_iter(const _type* _pointer) : _m_index(const_cast<_type*>(_pointer)) {  }

      ~array_iter() { }

   public:   /*   member operations   */

      array_iter<_type> operator+(std::ptrdiff_t _offset) { return _add(_offset); }
      array_iter<_type>& operator+=(std::ptrdiff_t _offset) { return _add_assign(_offset); }
      array_iter<_type>& operator=(const array_iter<_type>& _rhs) { return _assign_iter(_rhs); }
      array_iter<_type>& operator--() { return _decrement_prefix(); }
      array_iter<_type>& operator--(int) { return _decrement_postfix(); }
      bool operator==(const array_iter<_type>& _rhs) const { return _equal(_rhs); }
      bool operator!=(const array_iter<_type>& _rhs) const { return !(_equal(_rhs)); }
      array_iter<_type> operator++() { return _increment_prefix(); }
      array_iter<_type> operator++(int) { return _increment_postfix(); }
      _type* operator->() const { return _get_index(); }
      _type& operator*() const { return *_m_index; }
      bool operator<(const array_iter<_type>& _rhs) const { return _less_than(_rhs); }
      bool operator>(const array_iter<_type>& _rhs) const { return !(_less_than(_rhs)); }
      array_iter<_type> operator-(std::ptrdiff_t _offset) const { return _subtract(_offset); }
      std::ptrdiff_t operator-(const array_iter<_type>& _rhs) const { return _subtract(_rhs); }
      array_iter<_type>& operator-=(std::ptrdiff_t _offset) { return _subtract_assign(_offset); }

   private:   /*   member variables   */
      
      _type* _m_index;

   private:   /*   helper functions   */

      array_iter<_type> _add(std::ptrdiff_t _offset) { array_iter<_type> _temp(*this); return _temp += _offset; }
      array_iter<_type>& _add_assign(std::ptrdiff_t _offset) { _m_index += _offset; return *this; }
      array_iter<_type>& _assign_iter(const array_iter<_type>& _rhs) { if(this != &_rhs) _copy(_rhs); return *this; }
      void _copy(const array_iter<_type>& _rhs) { _m_index = _rhs._m_index; }
      void _decrement() { --_m_index; }
      array_iter<_type>& _decrement_prefix() { _decrement(); return *this; }
      array_iter<_type>& _decrement_postfix() { array_iter<_type> _temp(*this); _decrement(); return _temp; }
      bool _equal(const array_iter<_type>& _rhs) const { return _m_index == _rhs._m_index; }
      void _increment() { ++_m_index; }
      array_iter<_type> _increment_prefix() { _increment(); return *this; }
      array_iter<_type> _increment_postfix() { array_iter<_type> _temp(*this); _increment(); return _temp; }
      _type* _get_index() const { return _m_index; }
      bool _less_than(const array_iter<_type>& _rhs) const { return _m_index < _rhs._m_index; }
      array_iter<_type> _subtract(std::ptrdiff_t _offset) const { array_iter<_type> _temp(*this); return _temp -= _offset; }
      std::ptrdiff_t _subtract(const array_iter<_type>& _rhs) const { return _m_index - _rhs._m_index; }
      array_iter<_type>& _subtract_assign(std::ptrdiff_t _offset) { _m_index -= _offset; return *this; }

};   /*   end of array_iter   */

template <typename _type> class const_array_iter : public std::iterator<std::random_access_iterator_tag, _type>
{

   public:   /*   Constructor | Destructor   */
      
      const_array_iter() : _m_index(NULL) { }
      const_array_iter(const const_array_iter<_type>& _rhs) { _copy(_rhs); }
      const_array_iter(const _type* _pointer) : _m_index(const_cast<_type*>(_pointer)) { assert(_pointer != NULL); }

      ~const_array_iter() { }

   public:   /*   member operations   */

      const_array_iter<_type> operator+(std::ptrdiff_t _offset) { return _add(_offset); }
      const_array_iter<_type>& operator+=(std::ptrdiff_t _offset) { return _add_assign(_offset); }
      const_array_iter<_type>& operator=(const const_array_iter<_type>& _rhs) { return _assign_iter(_rhs); }
      const_array_iter<_type>& operator--() { return _decrement_prefix(); }
      const_array_iter<_type>& operator--(int) { return _decrement_postfix(); }
      bool operator==(const const_array_iter<_type>& _rhs) const { return _equal(_rhs); }
      bool operator!=(const const_array_iter<_type>& _rhs) const { return !(_equal(_rhs)); }
      const_array_iter<_type>& operator++() { return _increment_prefix(); }
      const_array_iter<_type>& operator++(int) { return _increment_postfix(); }
      _type* operator->() const { return _get_index(); }
      _type& operator*() const { return *_m_index; }
      bool operator<(const const_array_iter<_type>& _rhs) const { return _less_than(_rhs); }
      bool operator>(const const_array_iter<_type>& _rhs) const { return !(_less_than(_rhs)); }
      const_array_iter<_type> operator-(std::ptrdiff_t _offset) const { return _subtract(_offset); }
      std::ptrdiff_t operator-(const const_array_iter<_type>& _rhs) const { return _subract(_rhs); }
      const_array_iter<_type>& operator-=(std::ptrdiff_t _offset) { return _subtract_assign(_offset); }

   private:   /*   member variables   */
      
      _type* _m_index;

   private:   /*   helper functions   */

      const_array_iter<_type> _add(std::ptrdiff_t _offset) { const_array_iter<_type> _temp(*this); return _temp += _offset; }
      const_array_iter<_type>& _add_assign(std::ptrdiff_t _offset) { _m_index += _offset; return *this; }
      const_array_iter<_type>& _assign_iter(const const_array_iter<_type>& _rhs) { if(this != &_rhs) _copy(_rhs); return *this; }
      void _copy(const const_array_iter<_type> _rhs) { _m_index = _rhs._m_index; }
      void _decrement() { --_m_index; }
      const_array_iter<_type>& _decrement_prefix() { _decrement(); return *this; }
      const_array_iter<_type>& _decrement_postfix() { const_array_iter<_type> _temp(*this); _decrement(); return _temp; }
      bool _equal(const const_array_iter<_type>& _rhs) const { return _m_index == _rhs._m_index; }
      void _increment() { --_m_index; }
      const_array_iter<_type> _increment_prefix() { _increment(); return *this; }
      const_array_iter<_type> _increment_postfix() { const_array_iter<_type> _temp(*this); _increment(); return _temp; }
      _type* _get_index() const { return _m_index; }
      bool _less_than(const const_array_iter<_type>& _rhs) const { return _m_index < _rhs._less_than; }
      const_array_iter<_type> _subtract(std::ptrdiff_t _offset) const { const_array_iter<_type> _temp(*this); return _temp -= _offset; }
      std::ptrdiff_t _subtract(const const_array_iter<_type>& _rhs) const { return _m_index - _rhs._m_index; }
      const_array_iter<_type>& _subtract_assign(std::ptrdiff_t _offset) { _m_index -= _offset; return *this; }

};   /*   end of const array_iter   */

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   //   end of namespace(ev4)

#endif   //   ARRAY_ITER_HPP
