////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: bn_tree_iter.hpp
//
// Modifications: 
//
// 22-Jan-13: Version 2.1: Cleaned and changed to namespace ev6 
// 14-Dec-12: Version 2.0: Renamed class from tree_iter to bn_tree_iter
//                       : Timerperiod changed from ev4 to ev5
//                       : Added the class to namespace el
//                       : Seperated the iterator into its own header file
//                       : Because the passed member variable was removed
//                       : had to find a new way to keep track of passed
//                       : nodes
//
// 1-June-12: Version 1.0: Created
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __BN_TREE_ITER_HPP__
#define __BN_TREE_ITER_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <iterator>
#include <iostream>

#include "base.hpp"
#include "bn_node.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template < typename __Key, typename __Value, typename __Compare = std::less<__Value> > class bn_tree_iter : public std::iterator< std::forward_iterator_tag, __Value >
{
   private:   // member variables

      bn_node< __Key, __Value, __Compare >* _m_index;
   
   public:   // Constructor | Destructor

      bn_tree_iter() : _m_index(0) { }

      bn_tree_iter(const bn_node< __Key, __Value, __Compare >* _Pointer) : _m_index(const_cast< bn_node< __Key, __Value, __Compare >* >(_Pointer)) { }

      bn_tree_iter(const bn_tree_iter< __Key, __Value, __Compare >& _Rhs) { _copy(_Rhs); }

   public:   // overloaded operators

      bn_tree_iter< __Key, __Value, __Compare > operator=(const bn_tree_iter< __Key, __Value, __Compare > _Rhs) { if (this != &_Rhs) _copy(_Rhs); return *this; }
      bool operator==(const bn_tree_iter< __Key, __Value, __Compare >& _Rhs) const { return _equal(_Rhs); }
      bool operator!=(const bn_tree_iter< __Key, __Value, __Compare >& _Rhs) const { return !(_equal(_Rhs)); }
      bn_tree_iter< __Key, __Value, __Compare > operator++() { return _increment_prefix(); }
      bn_tree_iter< __Key, __Value, __Compare > operator++(int) { return _increment_postfix(); }
      bn_node< __Key, __Value, __Compare >* operator->() const { return _get_index(); }
      __Value& operator*() const { return (_m_index->m_value); }
      bool operator<(const bn_tree_iter< __Key, __Value, __Compare>& _Rhs) const { return _less_than(_Rhs); }
      bool operator>(const bn_tree_iter< __Key, __Value, __Compare>& _Rhs) const { return !(_less_than(_Rhs)); }
      
   private:   // helper functions

      void _copy(const bn_tree_iter< __Key, __Value, __Compare >& _Rhs) { _m_index = _Rhs._m_index; }
      bool _equal(const bn_tree_iter< __Key, __Value, __Compare >& _Rhs) const { return _m_index == _Rhs._m_index; }
      void _increment()
      {

         if (_m_index->m_right_child != NULL)
         {
            _m_index = _m_index->m_right_child;
      
            while (_m_index->m_left_child != NULL) _m_index = _m_index->m_left_child;

         }

         else if ( *(_m_index->m_parent) < *_m_index)
         {
            bn_node<__Key, __Value, __Compare>* _Index = _m_index;
   
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

      bn_tree_iter< __Key, __Value, __Compare > _increment_prefix() { _increment(); return *this; }
      bn_tree_iter< __Key, __Value, __Compare > _increment_postfix() { bn_tree_iter< __Key, __Value > _Temp(*this); _increment(); return _Temp; }
      bn_node< __Key, __Value, __Compare >* _get_index() const { return _m_index; }
      bool _less_than(const bn_tree_iter< __Key, __Value, __Compare >& _Rhs) const { return (*_m_index < *_Rhs._m_index); }

};   // end of class bn_tree_iter

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace (el)
}   // end of namesapce (ev6)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __BN_TREE_ITER_HPP__
