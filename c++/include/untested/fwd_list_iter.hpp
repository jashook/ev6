////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: fwd_list_iter.hpp
//
// Modifications: 
// 
// 22-Jan-13: Version 2.1: Cleaned and changed to namespace ev6
// 16-Dec-12: Version 2.0: Seperated the iterator into its own header file
// 1-June-12: Version 1.0: Created
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __FWD_LIST_ITER_HPP__
#define __FWD_LIST_ITER_HPP__

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

template <typename __Type> class fwd_list_iterator : public std::iterator<std::forward_iterator_tag, __Type>
{
   public:   // Constructor | Destructor

      fwd_list_iterator(const forward_node<__Type>* _Index) : _m_index(const_cast<forward_node<__Type>*>(_Index)) { }
      fwd_list_iterator(const fwd_list_iterator<__Type>& _rhs) { _copy(const_cast<fwd_list_iterator<__Type>&>(_rhs)); }

      //   Destructor automatically provided

   public:   // member operations

      fwd_list_iterator<__Type> operator=(const fwd_list_iterator<__Type>& _Rhs) { _copy( const_cast< fwd_list_iterator<__Type>& >(_Rhs)); }
      bool operator==(const fwd_list_iterator<__Type>& _Rhs) const { return _equal(_Rhs); }
      bool operator!=(const fwd_list_iterator<__Type>& _Rhs) const { return !(_equal(_Rhs)); }
      forward_node<__Type>* operator->() { return _m_index; }
      __Type& operator*() { return _get_data(); }
      fwd_list_iterator<__Type> operator++() { return _increment_prefix(); }
      fwd_list_iterator<__Type> operator++(int) { return _increment_postfix(); }

   private:   // member variables

      forward_node<__Type>* _m_index;

   private:   // helper functions

      void _copy(fwd_list_iterator<__Type>& _Rhs) { _m_index = _Rhs._m_index; }
      bool _equal(const fwd_list_iterator<__Type>& _Rhs) const { return _m_index == _Rhs._m_index; }
      __Type& _get_data() { return _m_index->_data; }
      void _increment() { _m_index = _m_index->_next; }
      fwd_list_iterator<__Type> _increment_prefix() { _increment(); return *this; }
      fwd_list_iterator<__Type> _increment_postfix() { fwd_list_iterator<__Type> _Temp(*this); _increment(); return _Temp; }
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace(el)
}   // end of namespace(ev6)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __FWD_LIST_ITER_HPP__

