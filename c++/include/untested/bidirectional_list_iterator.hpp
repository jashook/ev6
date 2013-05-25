////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: bidirectional_list_iter.hpp
//
// Modifications: 
// 
// 22-Jan-13: Version 2.1: Cleaned and updated
// 16-Dec-12: Version 2.0: Seperated the iterator into its own header file
// 1-Jun-12 : Version 1.0: Created
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __BIDIRECTIONAL_LIST_ITERATOR_HPP__
#define __BIDIRECTIONAL_LIST_ITERATOR_HPP__

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

template <typename __Type> class bidirectional_list_iterator : public std::iterator<std::bidirectional_iterator_tag, __Type>
{
   public:   //  Constructor | Destructor

      bidirectional_list_iterator(const bidirectional_node<__Type>* _Index) : _m_index(const_cast<bidirectional_node<__Type>*>(_Index)) { }
      bidirectional_list_iterator(bidirectional_list_iterator<__Type>& _rhs) { _copy(_rhs); }
      bidirectional_list_iterator() : _m_index(NULL) { }

      //   Destructor automatically provided

   public:   // member operations

      bidirectional_list_iterator<__Type> operator=(bidirectional_list_iterator<__Type>& _rhs) { if (this != &_rhs) _ctor(); _copy(_rhs); return *this; }
      bool operator==(const bidirectional_list_iterator<__Type>& _rhs) const { return _equal(_rhs); }
      bool operator!=(const bidirectional_list_iterator<__Type>& _rhs) const { return !(_equal(_rhs)); }
      bidirectional_node<__Type>* operator->() { return _m_index; }
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


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace(el)
}   // end of namespace(ev6)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __BIDIRECTIONAL_LIST_ITERATOR_HPP__
