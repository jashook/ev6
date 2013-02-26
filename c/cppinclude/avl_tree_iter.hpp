///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: avl_tree_iter.hpp
//
// Modifications: 
//
// 21-Jan-13: Version 1.1: Updated to namespace ev6
// 1-Jan-13 : Version 1.0: Created 
//
// Timeperiod: ev6
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#ifndef __AVL_TREE_ITER_HPP__
#define __AVL_TREE_ITER_HPP__

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <functional>
#include <iterator>
#include <iostream>

#include "node.hpp"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template < typename __Key, typename __Value, typename __Compare = std::less<__Value> > class avl_tree_iter : public std::iterator< std::forward_iterator_tag, __Value >
{
   private:   // member variables

      avl_node< __Key, __Value, __Compare >* _m_index;

   public:   // Constructor | Destructor

      avl_tree_iter() : _m_index(0) { }

      avl_tree_iter(const avl_node< __Key, __Value, __Compare >* _Pointer) : _m_index(const_cast< avl_node< __Key, __Value, __Compare >* >(_Pointer)) { }

      avl_tree_iter(const avl_tree_iter< __Key, __Value, __Compare >& _Rhs) { _copy(_Rhs); }

   public:   // overloaded operators

      avl_tree_iter< __Key, __Value, __Compare > operator=(const avl_tree_iter< __Key, __Value, __Compare > _Rhs) { if (this != &_Rhs) _copy(_Rhs); return *this; }
      bool operator==(const avl_tree_iter< __Key, __Value, __Compare >& _Rhs) const { return _equal(_Rhs); }
      bool operator!=(const avl_tree_iter< __Key, __Value, __Compare >& _Rhs) const { return !(_equal(_Rhs)); }
      avl_tree_iter< __Key, __Value, __Compare > operator++() { return _increment_prefix(); }
      avl_tree_iter< __Key, __Value, __Compare > operator++(int) { return _increment_postfix(); }
      avl_node< __Key, __Value, __Compare >* operator->() const { return _get_index(); }
      __Value& operator*() const { return (_m_index->m_value); }
      bool operator<(const avl_tree_iter< __Key, __Value, __Compare>& _Rhs) const { return _less_than(_Rhs); }
      bool operator>(const avl_tree_iter< __Key, __Value, __Compare>& _Rhs) const { return !(_less_than(_Rhs)); }
      
   private:   // helper functions

      void _copy(const avl_tree_iter< __Key, __Value, __Compare >& _Rhs) { _m_index = _Rhs._m_index; }
      bool _equal(const avl_tree_iter< __Key, __Value, __Compare >& _Rhs) const { return _m_index == _Rhs._m_index; }
      void _increment()
      {

         if (_m_index->m_right_child != NULL)
         {
            _m_index = _m_index->m_right_child;
      
            while (_m_index->m_left_child != NULL) _m_index = _m_index->m_left_child;

         }

         else if ( *(_m_index->m_parent) < *_m_index)
         {
            avl_node<__Key, __Value, __Compare>* _Index = _m_index;
   
            while (_m_index->m_parent != NULL)
            {
               _m_index = _m_index->m_parent;

               if (*_m_index > *_Index) break;
            }

            if (_m_index->m_parent == NULL && (*_m_index < *_Index) ) _m_index = NULL;
         }

         else
         {
            _m_index = _m_index->m_parent;
         }

      }

      avl_tree_iter< __Key, __Value, __Compare > _increment_prefix() { _increment(); return *this; }
      avl_tree_iter< __Key, __Value, __Compare > _increment_postfix() { avl_tree_iter< __Key, __Value > _Temp(*this); _increment(); return _Temp; }
      avl_node< __Key, __Value, __Compare >* _get_index() const { return _m_index; }
      bool _less_than(const avl_tree_iter< __Key, __Value, __Compare >& _Rhs) const { return (*_m_index < *_Rhs._m_index); }

};   // end of class avl_tree_iter

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

}   // end of namespace (el)
}   // end of namesapce (ev6)

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#endif   // __AVL_TREE_ITER_HPP__
