////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: bidirectional_list_iter.hpp
//
// Modifications: 
//
// 22-Jan-13: Version 2.1: Cleaned and changed to namespace ev6
// 16-Dec-12: Version 2.0: Seperated the iterator into its own header file
// 1-Jun-12 : Version 1.0: Created
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __CONST_BIDIRECTIONAL_LIST_ITERATOR_HPP__
#define __CONST_BIDIRECTIONAL_LIST_ITERATOR_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <cstring>
#include <iterator>

#include "base.hpp"
#include "node.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename __Type> class const_bidirectional_list_iterator : public std::iterator<std::bidirectional_iterator_tag, __Type>
{
   public:   // Constructor | Destructor

      const_bidirectional_list_iterator(const bidirectional_node<__Type>* _Index) : _m_index(const_cast<bidirectional_node<__Type>*>(_Index)) { }
      const_bidirectional_list_iterator(const const_bidirectional_list_iterator<__Type>& _rhs) { _copy(const_cast<const_bidirectional_list_iterator<__Type>&>(_rhs)); }

      //   Destructor automatically provided

   public:   // member operations

      const_bidirectional_list_iterator<__Type> operator=(const const_bidirectional_list_iterator<__Type>& _rhs) { _copy( const_cast<const_bidirectional_list_iterator<__Type>&>(_rhs)); }
      bool operator==(const const_bidirectional_list_iterator<__Type>& _rhs) const { return _equal(_rhs); }
      bool operator!=(const const_bidirectional_list_iterator<__Type>& _rhs) const { return !(_equal(_rhs)); }
      bidirectional_node<__Type>* operator->() { return _m_index; }
      __Type& operator*() { return _get_data(); }
      const_bidirectional_list_iterator<__Type> operator++() { return _increment_prefix(); }
      const_bidirectional_list_iterator<__Type> operator++(int) { return _increment_postfix(); }

   private:   // member variables

      bidirectional_node<__Type>* _m_index;

   private:   // helper functions

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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace(el)
}   // end of namespace(ev6)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __CONST_BIDIRECTIONAL_LIST_ITERATOR_HPP__
