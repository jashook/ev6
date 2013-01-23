////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        raw_list
//
// Version:       3.0
//
// Modifications:
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __RAW_LIST_HPP__
#define __RAW_LIST_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "node.hpp"
#include "iter.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {
namespace mta {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<typename __Type> class raw_list
{
   public:   // type definitions and constants

      typedef __Type value_type;
      typedef std::size_t size_type;
      typedef __Type* pointer;
      typedef __Type& reference;
      typedef const __Type* const_pointer;
      typedef const __Type& const_reference;
      typedef std::ptrdiff_t difference_type;
      typedef bidirectional_list_iterator<value_type> iterator;
      typedef const_bidirectional_list_iterator<value_type> const_iterator;

   private:   // private type definitions

      typedef bidirectional_node<__Type> _node;

   private:   // member variables

      _node* _m_head;
      _node* _m_tail;

   public:   // member functions

      iterator begin() { return iterator(_m_head->_m_next); }
      bool empty() const { return _m_size == 0; }
      iterator end() { return iterator(_m_tail); }
      _node* get_m_head() { return _m_head; }
      _node* get_m_tail() { return _m_tail; }
      std::size_t size() { return _m_size; }

   public:   // member operators

      //void operator+=(const raw_list<__Type>& _Rhs) { _add(_Rhs); }

   public:   // constructor | destructor

      raw_list() : _m_head(NULL), _m_tail(NULL) { }
      raw_list(_node* _Head, _node* _Tail) : _m_head(_Head), _m_tail(_Tail) { }
      raw_list(const raw_list& _Rhs) { _copy(_Rhs); }

      ~raw_list() { _dtor(); }

   private:   // helper functions

      void _add(const raw_list<__Type>& _Rhs)
      {
         _node* _Last = _m_tail->_m_prev;
         _Last->_m_next = _Rhs._m_head->_m_next;
         _Rhs._m_head = NULL;
         _m_tail->_m_prev = _Rhs._m_tail->_m_prev;
         _Rhs._m_tail = NULL;
      }

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)
}   // end namespace(mta)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __RAW_LIST_HPP__