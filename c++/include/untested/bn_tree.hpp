///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: bn_tree.hpp
//
// Modifications: 
//
// 22-Jan-13 : Version 3.2: Cleaned and changed to namespace ev6
// 19-Dec-12 : Version 3.1: Bug fixes, changed to namespace ev5 and added el
// 1-June-12 : Version 3.0: Completed with
//                        : No support for extending the tree
//                        : Iterative Insert and Delete Functions
//                        : Iterators Supported ( in-order iteration )
// 8-April-12: Version 2.0: Completed with
//                        : Support for extending the tree
// 6-April-12: Version 1.0: Functionality extended and completed
// 2-April-12: Version 1.0: Design Decision: Version 1.0 was resursive
// 2-April-12: Version 1.0: Created
//
// Timeperiod: ev6
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#ifndef __BN_TREE_HPP__
#define __BN_TREE_HPP__

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <iterator>

#include "iter.hpp"
#include "node.hpp"
#include "rti.hpp"
#include "stack.hpp"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template< typename __Key, typename __Value = __Key, typename __Compare = std::less< __Value > >class bn_tree
{
   public:   // type definitions and constants

      typedef __Value value_type;
      typedef std::size_t size_type;
      typedef __Value* pointer;
      typedef __Value& reference;
      typedef const __Value* const_pointer;
      typedef const __Value& const_reference;
      typedef std::ptrdiff_t difference_type;
      typedef bn_tree_iter< __Key, __Value > iterator;
      typedef const_bn_tree_iter< __Key, __Value > const_iterator;
      typedef std::reverse_iterator< iterator > reverse_iterator;
      typedef std::reverse_iterator< const_iterator > const_reverse_iterator;

   private:   // member variables

      bn_node< __Key, __Value, __Compare >* _m_root;
      bn_node< __Key, __Value, __Compare >* _m_left_leaf_node;
      bn_node< __Key, __Value, __Compare >* _m_right_leaf_node;
      size_type _m_size;

   public:   // constructor | destructor

      bn_tree() : _m_root(0), _m_left_leaf_node(0), _m_right_leaf_node(0), _m_size(0) { }
      bn_tree( __Key& _Key, __Value& _Data) : _m_root(0), _m_left_leaf_node(0), _m_right_leaf_node(0), _m_size(0) { _insert(_Key, _Data); }
   
      ~bn_tree() { _tidy(); }

   public:   // member functions

      iterator begin() { return iterator(_m_left_leaf_node); }
      iterator end() { return iterator(_m_right_leaf_node->m_right_child); }
      bool contains(__Key& _Key) { return _contains(_Key); }
      bool contains(const __Key& _Key) { return _contains(const_cast<__Key&>(_Key)); }
      void insert(__Key& _Key, __Value& _Data) { _insert(_Key, _Data); }
      void insert(const __Key& _Key, const __Value& _Data) { _insert(const_cast<__Key&>(_Key), const_cast<__Value&>(_Data)); }
      void insert(__Key& _Key) { _insert(_Key); }
      void insert(const __Key& _Key) { _insert(const_cast<__Key&>(_Key)); }
      __Value& search(__Key& _Key) { return _search(_Key); }
      __Value& search(const __Key& _Key) { return _search(const_cast<__Key&>(_Key)); }

   private:   // helper functions

      bool _contains(__Key& _Key)
      {
         bn_node<__Key, __Value>* _Parent = _descend(_Key);

         if ( _Parent->m_key == _Key) return true;
         else return false;

      }

      bn_node<__Key, __Value>* _descend(__Key& _Key)
      {
         bn_node<__Key, __Value>* _DescendingPtr = _m_root;
         bn_node<__Key, __Value>* _DescendingParentPtr = _DescendingPtr;

         while (_DescendingPtr != 0)
         {
            if (_Key < _DescendingPtr->m_key)
            {
               if (_DescendingPtr != _m_root) _DescendingParentPtr = _DescendingPtr;
               
               _DescendingPtr = _DescendingPtr->m_left_child;
            }
   
            else if (_Key > _DescendingPtr->m_key)
            {
               if (_DescendingPtr != _m_root) _DescendingParentPtr = _DescendingPtr;
  
               _DescendingPtr = _DescendingPtr->m_right_child;
            }

            else
            {
               _DescendingParentPtr = _DescendingPtr;

               break;
            }
         }

         return _DescendingParentPtr;

      }

      void _insert(__Key& _Key, __Value& _Data)
      {
         if (_m_root == 0)
         {
            _m_root = new bn_node<__Key, __Value, __Compare>(_Key, _Data);
            _m_left_leaf_node = _m_root;
            _m_right_leaf_node = _m_root;
            ++_m_size;
         }
         
         else
         {
            bn_node<__Key, __Value, __Compare>* _ParentPtr = _descend(_Key);
            
            if (_ParentPtr == 0) return;

            if (_Key < _ParentPtr->m_key)
            {
               if (_ParentPtr->m_left_child == 0)
               {
                  _ParentPtr->m_left_child = new bn_node<__Key, __Value, __Compare>(_Key, _Data, 0, 0, _ParentPtr);

                  ++_m_size;
                  if (_ParentPtr == _m_left_leaf_node) _m_left_leaf_node = _ParentPtr->m_left_child;
               }
            }

            else
            {
               if (_ParentPtr->m_right_child == 0)
               {
                  _ParentPtr->m_right_child = new bn_node<__Key, __Value, __Compare>(_Key, _Data, 0, 0, _ParentPtr);
                  ++_m_size;
                  if (_ParentPtr == _m_left_leaf_node) _m_left_leaf_node = _ParentPtr->m_right_child;
               }
            }
         }
      }

      void _insert(__Key& _Key)
      {
         if (!are_same_type<__Key, __Value>()) return;

         else
         {
            if (_m_root == NULL)
            {
               _m_root = new bn_node<__Key, __Value, __Compare>(_Key, _Key, 0, 0, 0);
               _m_left_leaf_node = _m_root;
               _m_right_leaf_node = _m_root;
               ++_m_size;
            }

            else
            {
               bn_node<__Key, __Value, __Compare>* _ParentPtr = _descend(_Key);

               if (_ParentPtr == 0) return;

               if (_Key < _ParentPtr->m_key)
               {
                  if (_ParentPtr->m_left_child == 0)
                  {
                     _ParentPtr->m_left_child = new bn_node<__Key, __Value, __Compare>(_Key, _Key, 0, 0, _ParentPtr);

                     ++_m_size;
                     if (_ParentPtr == _m_left_leaf_node) _m_left_leaf_node = _ParentPtr->m_left_child;
                  }
               }

               else
               {
                  if (_ParentPtr->m_right_child == 0)
                  {
                     _ParentPtr->m_right_child = new bn_node<__Key, __Value, __Compare>(_Key, _Key, 0, 0, _ParentPtr);
                     ++_m_size;
                     //if (_ParentPtr == _m_left_leaf_node) _m_left_leaf_node = _ParentPtr->m_right_child;
                  }
               }
            }
         }
      }

      __Value& _search(__Key& _Key)
      {
         bn_node<__Key, __Value, __Compare>* _ParentPtr = _descend(_Key);
      
         return _ParentPtr->m_value;
      }

      void _tidy()
      {
         stack< bn_node<__Key, __Value, __Compare>* > _Stack;

         iterator _Iterator = begin();

         while (_Iterator != 0)
         {

            bn_node< __Key, __Value, __Compare>* _Temp = _Iterator.operator->();
  
            _Stack.push(_Temp);
            
            ++_Iterator;
            std::cout << "Incremented" << std::endl;
         }

         for (int i = 0, _Len = _Stack.size(); i < _Len; ++i) delete _Stack.pop();
      }

};   // end of class bn_tree

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

}   // end of namespace el
}   // end of namespace ev6

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#endif   //__BN_TREE_HPP__
