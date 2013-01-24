////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: bn_node.hpp
//
// Modifications: 
// 
// 22-Jan-13: Version 2.1: Cleaned and changed to namespace ev6
// 14-Dec-12: Version 2.0: Renamed file from binary_tree_node to bn_node
//                       : Timerperiod changed from ev4 to ev5
//                       : Added the class to namespace el
//                       : Removed _ before the member variables
//                       : Seperated the node class into its own header file
//                       : Fixed overloaded assignment operator
//                       : Changed to return a node by reference instead of by value
// 1-June-12: Version 1.0: Created
//
// Timeperiod: ev6
//
// Notes: Class has public member variables
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __BN_NODE_HPP__
#define __BN_NODE_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <functional>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template< typename __Key, typename __Value = __Key, typename __Compare = std::less<__Value> > class bn_node
{
   private:   // private member variables

      __Compare _m_compare;

   public:   // member variables

      __Key m_key;
      __Value m_value;
      
      bn_node* m_left_child;
      bn_node* m_right_child;
      bn_node* m_parent;

   public:   // constructor | destructor

      bn_node() : _m_compare(), m_key(0), m_value(0), m_left_child(0), m_right_child(0), m_parent(0) { }
      
      bn_node(__Key& _Key, __Value& _Value) : m_key(_Key), m_value(_Value), m_left_child(0), m_right_child(0), m_parent(0) { }
      
      bn_node(__Key& _Key, __Value& _Value, __Compare& _Compare) : _m_compare(_Compare), m_key(_Key), m_value(_Value), m_left_child(0), m_right_child(0), m_parent(0) { }

      bn_node(__Key& _Key, __Value& _Value, bn_node* _LeftChild, bn_node* _RightChild, bn_node* _Parent) : m_key(_Key), m_value(_Value), m_left_child(_LeftChild), m_right_child(_RightChild), m_parent(_Parent) { }

      bn_node(__Key& _Key, __Value& _Value, bn_node* _LeftChild, bn_node* _RightChild, bn_node* _Parent, __Compare& _Compare) : _m_compare(_Compare), m_key(_Key), m_value(_Value), m_left_child(_LeftChild), m_right_child(_RightChild), m_parent(_Parent) { }

   public:   // overloaded operators

      bn_node< __Key, __Value, __Compare >& operator=(const bn_node< __Key, __Value, __Compare >& _Rhs) { _assign_node(_Rhs); return *this; }
      
      bool operator<(const bn_node< __Key, __Value, __Compare >& _Rhs) { return _less_than(_Rhs); }
      bool operator>(const bn_node< __Key, __Value, __Compare >& _Rhs) { return !(_less_than(_Rhs)); }
      
   private:   // helper functions

      void _assign_node(const bn_node< __Key, __Value, __Compare >& _Rhs)
      {
         m_key = _Rhs.m_key;
         m_value = _Rhs.m_value;
         m_left_child = _Rhs.m_left_child;
         m_right_child = _Rhs.m_right_child;
         m_parent = _Rhs.m_parent;

         _m_compare = _Rhs._m_compare;
      }

      bool _less_than(const bn_node< __Key, __Value, __Compare >& _Rhs)
      {
         return _m_compare(m_value, _Rhs.m_value);
      }

};   // end of class bn_node

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace el
}   // end of namespace ev6

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __BN_NODE_HPP__
