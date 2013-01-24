////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: raw_list.hpp
//
// Modifications:
//
// 22-Jan-13 : Version 3.2: Cleaned and changed to namespace ev6
// 27-Dec-12 : Version 3.1: Updated to ev5
// 14-June-12: Version 1.0: Created
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __RAW_LIST_HPP__
#define __RAW_LIST_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "iter.hpp"
#include "node.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {
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

      typedef bn_node<__Type> _node;

   private:   // member variables

      _node* _m_head;
      _node* _m_tail;

   public:   // member functions

      iterator begin() { return iterator(_m_head->_m_next); }
      iterator end() { return iterator(_m_tail); }
      _node* get_m_head() { return _m_head; }
      _node* get_m_tail() { return _m_tail; }

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

      void _dtor()
      {
         iterator _Begin = begin();
         iterator _End = end();

         iterator _Trail = _Begin;

         while (_Begin != _End)
         {
            ++_Begin;
            delete _Trail.operator->();
            _Trail = _Begin;
         }

         delete _End.operator->();
      }

};   // end of class raw list

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev6)
}   // end namespace(el)
}   // end namespace(mta)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __RAW_LIST_HPP__
