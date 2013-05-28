////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: const_bn_tree_iter.hpp
//
// Modifications: 
// 
// 22-Jan-13: Version 2.1: Cleaned and added to namespace ev6
// 14-Dec-12: Version 2.0: Renamed class from const_tree_iter to const_bn_tree_iter
//                       : Timerperiod changed from ev4 to ev5
//                       : Added the class to namespace el
//                       : Seperated the iterator into its own header file
//                       : Because the passed member variable was removed
//                       : had to find a new way to keep track of passed
//                       : nodes
// 1-June-12: Version 1.0: Created
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __CONST_BN_TREE_ITER_HPP__
#define __CONST_BN_TREE_ITER_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <iterator>

#include "base.hpp"
#include "bn_node.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template< typename __Key, typename __Value, typename __Compare = std::less< __Value > > class const_bn_tree_iter : public std::iterator< std::forward_iterator_tag, __Value >
{
   private:   // private type definitions

      typedef bn_node< __Key, __Value, __Compare > _node;

   private:   // member variables

      _node* _m_index;

   public:   // constructor | destructor

      const_bn_tree_iter() : _m_index(0) { }
   
      const_bn_tree_iter(const _node* _Pointer) : _m_index( const_cast< _node* >(_Pointer) ) { }

      const_bn_tree_iter(const const_bn_tree_iter< __Key, __Value, __Compare >& _Rhs) { _copy(_Rhs); }

   public:   // overloaded operators

      const_bn_tree_iter< __Key, __Value, __Compare > operator=(const const_bn_tree_iter< __Key, __Value, __Compare > _Rhs) { if (this != &_Rhs) _copy(_Rhs); return *this; }

      bool operator==(const const_bn_tree_iter< __Key, __Value, __Compare >& _Rhs) const { return _equal(_Rhs); }
      
      bool operator!=(const const_bn_tree_iter< __Key, __Value, __Compare >& _Rhs) const { return !(_equal(_Rhs)); }

      const_bn_tree_iter< __Key, __Value, __Compare > operator++() { return _increment_prefix(); }
      const_bn_tree_iter< __Key, __Value, __Compare > operator++(int) { return _increment_postfix(); }
      const_bn_tree_iter< __Key, __Value, __Compare > operator->() const { return _get_index(); }
      __Value& operator*() const { return (_m_index->m_value); }
      bool operator<(const const_bn_tree_iter< __Key, __Value, __Compare >& _Rhs) const { return _less_than(_Rhs); }
      bool operator>(const const_bn_tree_iter< __Key, __Value, __Compare >& _Rhs) const { return !(_less_than(_Rhs)); }

   private:   // helper functions

      void _copy(const const_bn_tree_iter< __Key, __Value, __Compare >& _Rhs) { _m_index = _Rhs._m_index; }
      bool _equal(const const_bn_tree_iter< __Key, __Value, __Compare >& _Rhs) const { return _m_index == _Rhs._m_index; }
         
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

               if (_m_index > _Index) break;
            }

            if (_m_index == NULL) _m_index = NULL;
         }

         else
         {
            _m_index = _m_index->m_parent;
         }

      }

      const_bn_tree_iter< __Key, __Value, __Compare > _increment_prefix() { _increment(); return *this; }
      const_bn_tree_iter< __Key, __Value, __Compare > _increment_postfix() { const_bn_tree_iter< __Key, __Value, __Compare > _Temp(*this); _increment(); return _Temp; }
      _node* _get_index() const { return _m_index; }
      bool _less_than(const const_bn_tree_iter< __Key, __Value, __Compare >& _Rhs) const { return (*_m_index < *_Rhs._m_index); }

};   // end of class const_bn_tree_iter

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace (el)
}   // end of namesapce (ev6)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __CONST_BN_TREE_ITER_HPP__
