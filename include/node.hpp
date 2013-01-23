////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        node
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  NODE_H
#define NODE_H

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "free_list.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename _type> struct basic_node
{
   public:   // member variables

      _type _data;

   public:   // constructor | destructor
      
      basic_node(_type _Data) : _data(_Data) { }

};   // end of struct(basic_node)

template <typename __Type> class bidirectional_node
{
   public:   // public member operators

      //void* operator new(std::size_t _Size) { return _get_static()->remove_from_list(); }
      //void operator delete(void* _Ptr) { _get_static()->return_to_list(_Ptr); }

   public:   // Constructor | Destructor

      bidirectional_node(__Type _Data, bidirectional_node* _Next, bidirectional_node* _Prev) : _m_data(_Data), _m_data_ptr(&_m_data), _m_next(_Next), _m_prev(_Prev) { }
      bidirectional_node() : _m_data_ptr(0) { }
      
      // desctructor automatically provided

   public:   // member variables

      bidirectional_node* _m_next;
      bidirectional_node* _m_prev;
      __Type  _m_data;
      __Type* _m_data_ptr;

   public:

      void realloc(__Type& _Data, bidirectional_node* _Next, bidirectional_node* _Prev)
      {
         _m_next = _Next;
         _m_prev = _Prev;
         _m_data = _Data;
         _m_data_ptr = &_m_data;
      }

   private:

      static fl::free_list<bidirectional_node<__Type>>* _get_static() { static fl::free_list<bidirectional_node<__Type>> _Fl; return &_Fl; }

};   // end of struct(bidirectional_node)

template <typename __Key, typename __Type>  struct binary_tree_node
{
   public:   // Constructor | Desctructor

      binary_tree_node() : _m_key(0), _m_data(0), _m_left_child(NULL), _m_right_child(NULL), _m_parent_node(NULL), _m_passed(false) { }
      binary_tree_node(__Key& _key, __Type& _data) : _m_key(_key), _m_data(_data), _m_left_child(NULL), _m_right_child(NULL), _m_parent_node(NULL), _m_passed(false)  { }
      binary_tree_node(__Key& _key, __Type& _data, binary_tree_node* _parent_node, binary_tree_node* _left_child, binary_tree_node* _right_child) : _m_key(_key), _m_data(_data), _m_parent_node(_parent_node), _m_left_child(_left_child), _m_right_child(_right_child), _m_passed(false) { }

      ~binary_tree_node()
      {
         _tidy();   // if deleting a node, but not deleting its children, set the children of the node you are deleting to NULL
      }

   public:   // member variables
      
      __Key _m_key;
      __Type _m_data;
      binary_tree_node* _m_left_child;
      binary_tree_node* _m_right_child;
      binary_tree_node* _m_parent_node;
      bool _m_passed;

   public:   // overloaded operators

      binary_tree_node<__Key, __Type> operator=(const binary_tree_node<__Key, __Type>& _rhs) { return _assign_node(_rhs); }

   private:  // helper functions

      void _assign_node(const binary_tree_node<__Key, __Type>& _rhs)
      {
         _m_key = _rhs._m_key;
         _m_data = _rhs._m_data;
         _m_left_child = _rhs._m_left_child;
         _m_right_child = _rhs._m_right_child;
         _m_parent_node = _rhs._m_parent_node;
         _m_passed = _rhs._m_passed;
      }

      void _tidy()  // recursive delete
      {
         if (_m_left_child != NULL) delete _m_left_child;
         if (_m_right_child != NULL) delete _m_right_child;
      }

};  // end of struct(binary_tree_node)

template <typename __Key, typename __Type = __Key> struct forward_node
{
   public:   // Constructor | Destructor

      forward_node(__Type _Data, forward_node* _Next) : _data(_Data), _next(_Next) { }
      forward_node() { }
      
      // desctructor automatically provided

   public:   // member variables

      forward_node* _next;
      __Key _key;
      __Type _data;
      char init;

};   // end of struct(forward_node)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // NODE_H