///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: avl_tree.hpp
//
// Modifications:
//
// 13-Feb-13: Version 1.3: Fixed memory leak
// 21-Jan-13: Version 1.2: Updated to namespace ev6
// 4-Jan-13 : Version 1.1: Cleaned and added a little more comments 
// 21-Dec-12: Version 1.0: Created
//
// Version: 1.0
//
// Timeperiod: ev6
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#ifndef __AVL_TREE_HPP__
#define __AVL_TREE_HPP__

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <iostream>
#include <iterator>

#include "iter.hpp"
#include "node.hpp"
#include "queue.hpp"
#include "rti.hpp"
#include "stack.hpp"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename __Key, typename __Value = __Key, typename __Compare = std::less< __Value > > class avl_tree
{
   public:   // type definitions and constants

      typedef __Value value_type;
      typedef std::size_t size_type;
      typedef avl_node< __Key, __Value >* pointer;
      typedef avl_node< __Key, __Value >& reference;
      typedef const __Value* const_pointer;
      typedef const __Value& const_reference;
      typedef std::ptrdiff_t difference_type;
      typedef avl_tree_iter< __Key, __Value > iterator;
      typedef const_avl_tree_iter< __Key, __Value > const_iterator;
      typedef std::reverse_iterator< iterator > reverse_iterator;
      typedef std::reverse_iterator< const_iterator > const_reverse_iterator;

   private:   // member variables

      avl_node< __Key, __Value >* _m_root;
      avl_node< __Key, __Value >* _m_left_leaf_node;
      avl_node< __Key, __Value >* _m_right_leaf_node;
      size_type _m_size;

   public:   // constructor | destructor

      avl_tree() : _m_root(0), _m_left_leaf_node(0), _m_right_leaf_node(0), _m_size(0) { }
      avl_tree( __Key& _Key, __Value& _Data ) : _m_root(0), _m_left_leaf_node(0), _m_right_leaf_node(0), _m_size(0) { _insert(_Key, _Data); }

      ~avl_tree() { _tidy(); }

   public:   // member functions

      iterator begin() { return iterator(_begin()); }
      iterator end() { return iterator(_end()); }
      bool contains(__Key& _Key) { return _contains(_Key); }
      bool contains(const __Key& _Key) { return _contains(const_cast<__Key&>(_Key)); }
      void insert(__Key& _Key, __Value& _Data) { _insert(_Key, _Data); }
      void insert(const __Key& _Key, const __Value& _Data) { _insert(const_cast<__Key&>(_Key), const_cast<__Value&>(_Data)); }
      void insert(const __Key& _Key, __Value& _Data) { _insert(const_cast< __Key& >(_Key), _Data); }
      void insert(__Key& _Key, const __Value& _Data) { _insert(_Key, const_cast< __Value& >(_Data)); }
      void insert(__Key& _Key) { _insert(_Key, _Key); }
      void insert(const __Key& _Key) { _insert(const_cast<__Key&>(_Key), const_cast<__Key&>(_Key)); }
      void print_breadth_first_traversal() { _print_breadth_first_traversal(); }
      __Value& search(__Key& _Key) { return _search(_Key); }
      __Value& search(const __Key& _Key) { return _search(const_cast<__Key&>(_Key)); }

   private:   // helper functions

      bool _are_not_balanced( std::pair< int, int >& _Pair)
      {
         int _Sum = _Pair.first - _Pair.second;

         return (_Sum == -2 || _Sum == 2);
      }

      pointer _begin()
      {
         return _m_left_leaf_node;
      }

      bool _contains(__Key& _Key)
      {
         avl_node<__Key, __Value>* _Parent = _descend(_Key);

         if ( _Parent->m_key == _Key) return true;
         else return false;

      }

      avl_node<__Key, __Value>* _descend(__Key& _Key)
      {
         avl_node<__Key, __Value>* _DescendingPtr = _m_root;
         avl_node<__Key, __Value>* _DescendingParentPtr = _DescendingPtr;

         while (_DescendingPtr != 0 && _DescendingPtr != _m_right_leaf_node)
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

      void _double_with_left_child( avl_node< __Key, __Value, __Compare >*& _Node)
      {
         _rotate_with_right_child(_Node->m_left_child);
         _rotate_with_left_child(_Node);
      }

      void _double_with_right_child( avl_node< __Key, __Value, __Compare >*& _Node)
      {
         _rotate_with_left_child(_Node->m_right_child);
         _rotate_with_right_child(_Node);
      }

      pointer _end()
      {
         return _m_right_leaf_node;
      }

      std::pair<int, int> _height(avl_node< __Key, __Value, __Compare >* _Left, avl_node< __Key, __Value, __Compare >* _Right )
      {
         int _LeftHeight, _RightHeight = 0;

         avl_node< __Key, __Value, __Compare >* _LeftPtr,* _RightPtr;
         
         _LeftPtr = _Left;
         _RightPtr = _Right;

         if (_Left == NULL) _LeftHeight = -1;
         else _LeftHeight = _LeftPtr->m_height;

         if (_Right == NULL) _RightHeight = -1;
         else _RightHeight = _RightPtr->m_height;

         return std::pair< int, int >(_LeftHeight, _RightHeight);
      }

      void _insert(__Key& _Key, __Value& _Value)
      {
         if (_m_root == 0)
         {
            _m_root = new avl_node<__Key, __Value, __Compare>(_Key, _Value);
            _m_left_leaf_node = _m_root;
            _m_right_leaf_node = new avl_node<__Key, __Value, __Compare>(_Key, _Value);
            _m_right_leaf_node->m_parent = _m_root;
            _m_root->m_right_child = _m_right_leaf_node;
            ++_m_size;
         }

         else
         {
            avl_node< __Key, __Value, __Compare >* _ParentPtr = _descend(_Key);

            if ( _Key < _ParentPtr->m_key )
            {
               _ParentPtr->m_left_child = new avl_node< __Key, __Value, __Compare >(_Key, _Value, 0, 0, _ParentPtr);
               ++_m_size;

               if (_ParentPtr == _m_left_leaf_node) _m_left_leaf_node = _ParentPtr->m_left_child;
            }

            else if ( _Key > _ParentPtr->m_key) 
            {
               _ParentPtr->m_right_child = new avl_node< __Key, __Value, __Compare >(_Key, _Value, 0, 0, _ParentPtr);
               ++_m_size;

               if (_ParentPtr == _m_right_leaf_node->m_parent) 
               {
            
                  std::cout << "Changing m_right_child" << std::endl;
                  _ParentPtr->m_right_child->m_right_child = _m_right_leaf_node;
                  _m_right_leaf_node->m_parent = _ParentPtr->m_right_child;   
               
               }

            }

            else
            {
               return;
            }
            
            std::pair< int, int > _Heights = _height(_ParentPtr->m_left_child, _ParentPtr->m_right_child);
            _ParentPtr->m_height = _max(_Heights) + 1;

            while (_ParentPtr != NULL)
            {
                _ParentPtr = _ParentPtr->m_parent;
   
               if (_ParentPtr == NULL) break;
               std::pair< int, int > _Heights = _height(_ParentPtr->m_left_child, _ParentPtr->m_right_child);
 
               _ParentPtr->m_height = _max(_Heights) + 1;

               if (_are_not_balanced(_Heights))
               {
                  
                  if (_Value < _ParentPtr->m_value)
                  {
                     // if the value is less than the value of the node
                     // then it would have had to have been inserted to the left
                     // therefore m_left_child cannot to be null

                     if (_Value < _ParentPtr->m_left_child->m_value) _rotate_with_left_child(_ParentPtr);
                     else _double_with_left_child(_ParentPtr);
                  }

                  else if (_Value > _ParentPtr->m_value)
                  {
                     if (_ParentPtr->m_right_child->m_value < _Value) _rotate_with_right_child(_ParentPtr);
                     else _double_with_right_child(_ParentPtr);
                  }
               }              
            }
         }
      }

      int _max( std::pair< int, int >& _Pair)
      {
         return ( _Pair.first > _Pair.second ? _Pair.first : _Pair.second );
      }

      void _print_breadth_first_traversal()
      {
         mta::queue< avl_node< __Key, __Value, __Compare >* > _Queue;

         avl_node< __Key, __Value, __Compare >* _NewLineNode = new avl_node< __Key, __Value, __Compare >();

         _Queue.push(_m_root);
         _Queue.push(_NewLineNode);

         while (!_Queue.is_empty())
         {
            avl_node< __Key, __Value, __Compare>* _Node = _Queue.pop();

            if (_Node == _NewLineNode) 
            {
               std::cout << std::endl;
               
               if (!_Queue.is_empty()) _Queue.push(_NewLineNode);
            }

            else std::cout << _Node->m_value << " ";

            if (_Node->m_left_child != 0) _Queue.push(_Node->m_left_child);

            if (_Node->m_right_child != 0) _Queue.push(_Node->m_right_child);
         }
         
         delete _NewLineNode;
      }

      void _rotate_with_left_child( avl_node< __Key, __Value, __Compare >*& _Node)
      {
         if (_Node == 0) return;
      
         avl_node< __Key, __Value, __Compare >* _TempNode = _Node->m_left_child;
         
         _Node->m_left_child = _TempNode->m_right_child;
         if (_TempNode->m_right_child != 0) _TempNode->m_right_child->m_parent = _Node;

         _TempNode->m_right_child = _Node;
   
         std::pair< int, int > _NodePair, _TempNodePair;

         _NodePair = _height(_Node->m_left_child, _Node->m_right_child);

         _Node->m_height = _max(_NodePair) + 1;
         
         _TempNodePair = _height(_TempNode->m_left_child, _TempNode->m_right_child);

         _TempNode->m_height = _max(_TempNodePair) + 1;
         
         _TempNode->m_parent = _Node->m_parent;
         _Node->m_parent = _TempNode;

         _Node = _TempNode;
         
         if (_Node->m_parent != 0)
         {
            if (_Node->m_key < _Node->m_parent->m_key) _Node->m_parent->m_left_child = _Node;
            else _Node->m_parent->m_right_child = _Node;
         }
         
         else
         {
            _m_root = _Node;
         }
      
      }

      void _rotate_with_right_child( avl_node< __Key, __Value, __Compare >*& _Node)
      {
         if (_Node == 0) return;

         avl_node< __Key, __Value, __Compare >* _TempNode = _Node->m_right_child;

         _Node->m_right_child = _TempNode->m_left_child;
         if (_TempNode->m_left_child != 0) _TempNode->m_left_child->m_parent = _Node;
         
         _TempNode->m_left_child = _Node;

         std::pair< int, int > _NodePair, _TempNodePair;

         _NodePair = _height(_Node->m_left_child, _Node->m_right_child);

         _Node->m_height = _max(_NodePair) + 1;

         _TempNodePair = _height(_TempNode->m_left_child, _TempNode->m_right_child);
         
         _TempNode->m_height = _max(_TempNodePair) + 1;
         
         _TempNode->m_parent = _Node->m_parent;
         _Node->m_parent = _TempNode;

         _Node = _TempNode;
         
         if (_Node->m_parent != 0)
         {
            if (_Node->m_key < _Node->m_parent->m_key) _Node->m_parent->m_left_child = _Node;
            else _Node->m_parent->m_right_child = _Node;
         }
         
         else
         {
            _m_root = _Node;
         }
         
      }

      __Value& _search(__Key& _Key)
      {
         avl_node<__Key, __Value>* _ParentPtr = _descend(_Key);
      
         return _ParentPtr->m_value;
      }

      void _tidy()
      {
         stack< avl_node< __Key, __Value, __Compare >* > _Stack;

         iterator _Iterator = begin(), _End = end();

         while (_Iterator != _End)
         {
            avl_node< __Key, __Value, __Compare >* _Temp = _Iterator.operator->();

            _Stack.push(_Temp);

            ++_Iterator;
         }

         for (int i = 0, _Len = _Stack.size(); i < _Len; ++i) delete _Stack.pop();

         delete _m_right_leaf_node;   // clean up the terminal place holder node
      }


};   // end of class avl_tree

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

}   // end of namespace el
}   // end of namespace ev6

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#endif   // __AVL_TREE_HPP__
