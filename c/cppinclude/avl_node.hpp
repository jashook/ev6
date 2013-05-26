///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: avl_node.hpp
//
// Modifications:
// 
// 21-Jan-13: Version 1.1: Updated to namespace ev6
// 29-Dec-12: Version 1.0: Created
//
// Timeperiod: ev6
//
// Notes: this class has public member variables
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#ifndef __AVL_NODE_HPP__
#define __AVL_NODE_HPP__

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <functional>

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename __Key, typename __Value = __Key, typename __Compare = std::less<__Value> > class avl_node 
{
   private:   // private member variables
   
      __Compare _m_compare;

   public:   // member variables

      int m_height;
      __Key m_key;
      __Value m_value;
      avl_node< __Key, __Value, __Compare >* m_left_child;
      avl_node< __Key, __Value, __Compare >* m_right_child;
      avl_node< __Key, __Value, __Compare >* m_parent;

   public:   // constructor | destructor

      avl_node() : m_height(0), m_key(0), m_value(0), m_left_child(0), m_right_child(0), m_parent(0), _m_compare() { }
   
      avl_node(__Key& _Key, __Value& _Value) : m_height(0), m_key(_Key), m_value(_Value), m_left_child(0), m_right_child(0), m_parent(0), _m_compare() { }

      avl_node(__Key& _Key, __Value& _Value, __Compare& _Compare) : m_height(0), m_key(_Key), m_value(_Value), m_left_child(0), m_right_child(0), m_parent(0), _m_compare(_Compare) { }

      avl_node(__Key& _Key, __Value& _Value, avl_node* _LeftChild, avl_node* _RightChild, avl_node* _Parent) : m_height(0), m_key(_Key), m_value(_Value), m_left_child(_LeftChild), m_right_child(_RightChild), m_parent(_Parent), _m_compare() { }

   public:   // overloaded operators

      avl_node< __Key, __Value, __Compare >& operator=(const avl_node< __Key, __Value, __Compare>& _Rhs) { if (this != &_Rhs) _assign_node(_Rhs); return *this; }

      bool operator<(const avl_node< __Key, __Value, __Compare >& _Rhs) { return _less_than(_Rhs); }
      bool operator>(const avl_node< __Key, __Value, __Compare >& _Rhs) { return !_less_than(_Rhs); }


   private:   // helper functions

      void _assign_node(const avl_node< __Key, __Value, __Compare >& _Rhs)
      {
         m_height = _Rhs.m_height;
         m_key = _Rhs.m_key;
         m_value = _Rhs.m_value;
         m_left_child = _Rhs.m_left_child;
         m_parent = _Rhs.m_parent;

         _m_compare = _Rhs._m_compare;
      }

      bool _less_than(const avl_node< __Key, __Value, __Compare >& _Rhs)
      {
         return _m_compare(m_value, _Rhs.m_value);
      }

};   // end of class avl_node

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

}   // end of namespace el
}   // end of namespace ev6

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#endif   // __AVL_NODE_HPP__
