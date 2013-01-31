////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        iter
//
// Version:       1.0
//
// Modifications: 
//
// 1-June-12: Version 1.1:  Support for a Tree iterator named tree_iter (forward iterator)
// 14-May-12: Version 1.0:  Complete support for an array iterator named array_iter (random access iterator)
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef ITER_HPP
#define ITER_HPP

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <cstring>
#include <cassert>

#include "node.hpp"

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
      const_array_iter(const _type* _pointer) : _m_index(const_cast<_typ*>(_pointer)) { assert(_pointer != NULL); }

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
      const_array_iter<_type> _subtract(std::ptrdiff_t _offset) const { const_array_iter<_type> _temp(*this); return _temp -= offset; }
      std::ptrdiff_t _subtract(const const_array_iter<_type>& _rhs) const { return _m_index - _rhs._m_index; }
      const_array_iter<_type>& _subtract_assign(std::ptrdiff_t _offset) { _m_index -= _offset; return *this; }

};   /*   end of const array_iter   */

template <typename __Type> class bidirectional_list_iterator : public std::iterator<std::bidirectional_iterator_tag, __Type>
{
   public:   /*   Constructor | Destructor   */

      bidirectional_list_iterator(const bidirectional_node<__Type>* _Index) : _m_index(const_cast<bidirectional_node<__Type>*>(_Index)) { }
      bidirectional_list_iterator(bidirectional_list_iterator<__Type>& _rhs) { _copy(_rhs); }
      bidirectional_list_iterator() : _m_index(NULL) { }

      //   Destructor automatically provided
         
   public:   /*   member operations   */
         
      bidirectional_list_iterator<__Type> operator=(bidirectional_list_iterator<__Type>& _rhs) { if (this != &_rhs) _ctor(); _copy(_rhs); return *this; }
      bool operator==(const bidirectional_list_iterator<__Type>& _rhs) const { return _equal(_rhs); }
      bool operator!=(const bidirectional_list_iterator<__Type>& _rhs) const { return !(_equal(_rhs)); }
      bidirectional_node<__Type>* operator->() { return m_index; }
      __Type& operator*() { return _get_data(); }
      bidirectional_list_iterator<__Type> operator++() { return _increment_prefix(); }
      bidirectional_list_iterator<__Type> operator++(int) { return _increment_postfix(); }

   private:   //   member variables

      bidirectional_node<__Type>* _m_index;

   private:   //   helper functions

      void _ctor() { _m_index = NULL; }
      void _copy(bidirectional_list_iterator<__Type>& _rhs) { _m_index = _rhs._m_index; }
      void _decrement() { _m_index = _m_index->_m_prev; }
      bidirectional_list_iterator<__Type> _decrement_prefix() { _decrement(); return *this; }
      bidirectional_list_iterator<__Type> _decrement_postfix() { bidirectional_list_iterator<__Type> _temp(*this); _decrement(); return _temp; }
      bool _equal(const bidirectional_list_iterator<__Type>& _rhs) const { return _m_index == _rhs._m_index; }
      __Type& _get_data() { return _m_index->_m_data; }
      void _increment() { _m_index = _m_index->_m_next; }
      bidirectional_list_iterator<__Type> _increment_prefix() { _increment(); return *this; }
      bidirectional_list_iterator<__Type> _increment_postfix() { bidirectional_list_iterator<__Type> _temp(*this); _increment(); return _temp; }
};

template <typename __Type> class const_bidirectional_list_iterator : public std::iterator<std::bidirectional_iterator_tag, __Type>
{
   public:   /*   Constructor | Destructor   */

      const_bidirectional_list_iterator(const bidirectional_node<__Type>* _Index) : _m_index(const_cast<bidirectional_node<__Type>*>(_Index)) { }
      const_bidirectional_list_iterator(const const_bidirectional_list_iterator<__Type>& _rhs) { _copy(const_cast<const_bidirectional_list_iterator<__Type>&>(_rhs)); }

      //   Destructor automatically provided
         
   public:   /*   member operations   */
         
      const_bidirectional_list_iterator<__Type> operator=(const const_bidirectional_list_iterator<__Type>& _rhs) { _copy( const_cast<const_bidirectional_list_iterator<__Type>&>(_rhs)); }
      bool operator==(const const_bidirectional_list_iterator<__Type>& _rhs) const { return _equal(_rhs); }
      bool operator!=(const const_bidirectional_list_iterator<__Type>& _rhs) const { return !(_equal(_rhs)); }
      bidirectional_node<__Type>* operator->() { return _m_index; }
      __Type& operator*() { return _get_data(); }
      const_bidirectional_list_iterator<__Type> operator++() { return _increment_prefix(); }
      const_bidirectional_list_iterator<__Type> operator++(int) { return _increment_postfix(); }

   private:   //   member variables

      bidirectional_node<__Type>* _m_index;

   private:   //   helper functions

      void _copy(const_bidirectional_list_iterator<__Type>& _rhs) { _m_index = _rhs._m_index; }
      void _decrement() { _m_index = _m_index->_m_prev; }
      const_bidirectional_list_iterator<__Type> _decrement_prefix() { _decrement(); return *this; }
      const_bidirectional_list_iterator<__Type> _decrement_postfix() { const_bidirectional_list_iterator<__Type> _temp(*this); _decrement(); return _temp; }
      bool _equal(const const_bidirectional_list_iterator<__Type>& _rhs) const { return _m_index == _rhs._m_index; }
      __Type& _get_data() { return _m_index->_m_data; }
      void _increment() { _m_index = _m_index->_m_next; }
      const_bidirectional_list_iterator<__Type> _increment_prefix() { _increment(); return *this; }
      const_bidirectional_list_iterator<__Type> _increment_postfix() { const_bidirectional_list_iterator<__Type> _temp(*this); _increment(); return _temp; }
};

template <typename __Type> class forward_list_iterator : public std::iterator<std::forward_iterator_tag, __Type>
{
   public:   /*   Constructor | Destructor   */

      forward_list_iterator(const forward_node<__Type>* _Index) : _m_index(const_cast<forward_node<__Type>*>(_Index)) { }
      forward_list_iterator(const forward_list_iterator<__Type>& _rhs) { _copy(const_cast<forward_list_iterator<__Type>&>(_rhs)); }

      //   Destructor automatically provided
         
   public:   /*   member operations   */
         
      forward_list_iterator<__Type> operator=(const forward_list_iterator<__Type>& _rhs) { _copy( const_cast<forward_list_iterator<__Type>&>(_rhs)); }
      bool operator==(const forward_list_iterator<__Type>& _rhs) const { return _equal(_rhs); }
      bool operator!=(const forward_list_iterator<__Type>& _rhs) const { return !(_equal(_rhs)); }
      forward_node<__Type>* operator->() { return _m_index; }
      __Type& operator*() { return _get_data(); }
      forward_list_iterator<__Type> operator++() { return _increment_prefix(); }
      forward_list_iterator<__Type> operator++(int) { return _increment_postfix(); }

   private:   //   member variables

      forward_node<__Type>* _m_index;

   private:   //   helper functions

      void _copy(forward_list_iterator<__Type>& _rhs) { _m_index = _rhs._m_index; }
      bool _equal(const forward_list_iterator<__Type>& _rhs) const { return _m_index == _rhs._m_index; }
      __Type& _get_data() { return _m_index->_data; }
      void _increment() { _m_index = _m_index->_next; }
      forward_list_iterator<__Type> _increment_prefix() { _increment(); return *this; }
      forward_list_iterator<__Type> _increment_postfix() { forward_list_iterator<__Type> _temp(*this); _increment(); return _temp; }
};

template <typename __Type> class const_forward_list_iterator : public std::iterator<std::forward_iterator_tag, __Type>
{
   public:   /*   Constructor | Destructor   */

      const_forward_list_iterator(const forward_node<__Type>* _Index) : _m_index(const_cast<forward_node<__Type>*>(_Index)) { }
      const_forward_list_iterator(const const_forward_list_iterator<__Type>& _rhs) { _copy(const_cast<const_forward_list_iterator<__Type>&>(_rhs)); }

      //   Destructor automatically provided
         
   public:   /*   member operations   */
         
      const_forward_list_iterator<__Type> operator=(const const_forward_list_iterator<__Type>& _rhs) { _copy( const_cast<const_forward_list_iterator<__Type>&>(_rhs)); }
      bool operator==(const const_forward_list_iterator<__Type>& _rhs) const { return _equal(_rhs); }
      bool operator!=(const const_forward_list_iterator<__Type>& _rhs) const { return !(_equal(_rhs)); }
      forward_node<__Type>* operator->() { return _m_index; }
      __Type& operator*() { return _get_data(); }
      const_forward_list_iterator<__Type> operator++() { return _increment_prefix(); }
      const_forward_list_iterator<__Type> operator++(int) { return _increment_postfix(); }

   private:   //   member variables

      forward_node<__Type>* _m_index;

   private:   //   helper functions

      void _copy(const_forward_list_iterator<__Type>& _rhs) { _m_index = _rhs._m_index; }
      bool _equal(const const_forward_list_iterator<__Type>& _rhs) const { return _m_index == _rhs._m_index; }
      __Type& _get_data() { return _m_index->_data; }
      void _increment() { _m_index = _m_index->_next; }
      const_forward_list_iterator<__Type> _increment_prefix() { _increment(); return *this; }
      const_forward_list_iterator<__Type> _increment_postfix() { const_forward_list_iterator<__Type> _temp(*this); _increment(); return _temp; }
};

template <typename __Key, typename __Type> class tree_iter : public std::iterator<std::forward_iterator_tag, __Type>
{

   public:   //   Constructor | Destructor
      
      tree_iter() : _m_index(NULL) { }
      tree_iter(const tree_iter<__Key, __Type>& _rhs) { _copy(_rhs); }
      tree_iter(const binary_tree_node<__Key, __Type>* _pointer) : _m_index(const_cast<binary_tree_node<__Key, __Type>*>(_pointer)) {  }

      ~tree_iter() { }

   public:   //   member operations

      tree_iter<__Key, __Type> operator=(const tree_iter<__Key, __Type>& _rhs) { return _assign_iter(_rhs); }
      bool operator==(const tree_iter<__Key, __Type>& _rhs) const { return _equal(_rhs); }
      bool operator!=(const tree_iter<__Key, __Type>& _rhs) const { return !(_equal(_rhs)); }
      tree_iter<__Key, __Type> operator++() { return _increment_prefix(); }
      tree_iter<__Key, __Type> operator++(int) { return _increment_postfix(); }
      binary_tree_node<__Key, __Type>* operator->() const { return _get_index(); }
      __Type& operator*() const { return (_m_index->_m_data); }
      bool operator<(const tree_iter<__Key, __Type>& _rhs) const { return _less_than(_rhs); }
      bool operator>(const tree_iter<__Key, __Type>& _rhs) const { return !(_less_than(_rhs)); }
      
   private:   //   member variables
      
      binary_tree_node<__Key, __Type>* _m_index;

   private:   //   helper functions

      tree_iter<__Key, __Type> _assign_iter(const tree_iter<__Key, __Type>& _rhs) { if(this != &_rhs) _copy(_rhs); return *this; }
      void _copy(const tree_iter<__Key, __Type>& _rhs) { _m_index = _rhs._m_index; }
      bool _equal(const tree_iter<__Key, __Type>& _rhs) const { return _m_index == _rhs._m_index; }

      void _increment()
      { 

         _m_index->_m_passed = true;

         if (_m_index->_m_right_child != NULL)
         {

            _m_index = _m_index ->_m_right_child;

            while (_m_index->_m_left_child != NULL) _m_index = _m_index->_m_left_child;

            _m_index->_m_passed = true;

         }
         
         else
         {

            binary_tree_node<__Key, __Type>* temp = _m_index;

            while (_m_index->_m_passed == true) 
            {
               _m_index->_m_passed = false;

               if (_m_index->_m_parent_node == NULL) { _m_index = temp->_m_right_child; break; }

               _m_index = _m_index->_m_parent_node;
            }

         }

      }

      tree_iter<__Key, __Type> _increment_prefix() { _increment(); return *this; }
      tree_iter<__Key, __Type> _increment_postfix() { tree_iter<__Key, __Type> _temp(*this); _increment(); return _temp; }
      binary_tree_node<__Key, __Type>* _get_index() const { return _m_index; }
      bool _less_than(const tree_iter<__Key, __Type>& _rhs) const { assert(_m_index != NULL); return  }
      
};   //   end of tree_iter

template <typename __Key, typename __Type> class const_tree_iter : public std::iterator<std::forward_iterator_tag, __Type>
{

   public:   //   Constructor | Destructor
      
      const_tree_iter() : _m_index(NULL) { }
      const_tree_iter(const const_tree_iter<__Key, __Type>& _rhs) { _copy(_rhs); }
      const_tree_iter(const binary_tree_node<__Key, __Type>* _pointer) : _m_index(const_cast<binary_tree_node<__Key, __Type>*>(_pointer)) {  }

      ~const_tree_iter() { }

   public:   //   member operations

      const_tree_iter<__Key, __Type> operator=(const const_tree_iter<__Key, __Type>& _rhs) { return _assign_iter(_rhs); }
      bool operator==(const const_tree_iter<__Key, __Type>& _rhs) const { return _equal(_rhs); }
      bool operator!=(const const_tree_iter<__Key, __Type>& _rhs) const { return !(_equal(_rhs)); }
      const_tree_iter<__Key, __Type> operator++() { return _increment_prefix(); }
      const_tree_iter<__Key, __Type> operator++(int) { return _increment_postfix(); }
      binary_tree_node<__Key, __Type>* operator->() const { return _get_index(); }
      __Type& operator*() const { return (_m_index->_m_data); }
      bool operator<(const const_tree_iter<__Key, __Type>& _rhs) const { return _less_than(_rhs); }
      bool operator>(const const_tree_iter<__Key, __Type>& _rhs) const { return !(_less_than(_rhs)); }
      
   private:   //   member variables
      
      binary_tree_node<__Key, __Type>* _m_index;

   private:   //   helper functions

      const_tree_iter<__Key, __Type> _assign_iter(const const_tree_iter<__Key, __Type>& _rhs) { if(this != &_rhs) _copy(_rhs); return *this; }
      void _copy(const const_tree_iter<__Key, __Type>& _rhs) { _m_index = _rhs._m_index; }
      bool _equal(const const_tree_iter<__Key, __Type>& _rhs) const { return _m_index == _rhs._m_index; }

      void _increment()
      { 

         _m_index->_m_passed = true;

         if (_m_index->_m_right_child != NULL)
         {

            _m_index = _m_index ->_m_right_child;

            while (_m_index->_m_left_child != NULL) _m_index = _m_index->_m_left_child;

            _m_index->_m_passed = true;

         }
         
         else
         {

            binary_tree_node<__Key, __Type>* temp = _m_index;

            while (_m_index->_m_passed == true) 
            {
               _m_index->_m_passed = false;

               if (_m_index->_m_parent_node == NULL) { _m_index = temp->_m_right_child; break; }

               _m_index = _m_index->_m_parent_node;
            }

         }

      }

      const_tree_iter<__Key, __Type> _increment_prefix() { _increment(); return *this; }
      const_tree_iter<__Key, __Type> _increment_postfix() { const_tree_iter<__Key, __Type> _temp(*this); _increment(); return _temp; }
      binary_tree_node<__Key, __Type>* _get_index() const { return _m_index; }
      bool _less_than(const const_tree_iter<__Key, __Type>& _rhs) const { assert(_m_index != NULL); return  }
      
};   //   end of const_tree_iter

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   //   end of namespace(ev4)

#endif   //   ITER_HPP
