////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: linked_list.hpp
//
// Modifications:
//
// 22-Jan-13: Version 3.2: Cleaned and changed to namespace ev6
// 27-Dec-12: Version 3.1: Updated to ev5
// 
// Timeperiod: ev6
//
// Notes: No modifications recorded before 27-Dec-12
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __LINKED_LIST_HPP__
#define __LINKED_LIST_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "base.hpp"
#include "free_list.hpp"
#include "iter.hpp"
#include "node.hpp"
#include "raw_list.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename __Type, std::size_t __Size = 0> class linked_list
{
   public:   // public type definitions and constants

      typedef __Type value_type;
      typedef std::size_t size_type;
      typedef __Type* pointer;
      typedef __Type& reference;
      typedef const __Type* const_pointer;
      typedef const __Type& const_reference;
      typedef std::ptrdiff_t difference_type;
      typedef bidirectional_list_iterator<__Type> iterator;
      typedef const_bidirectional_list_iterator<__Type> const_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

   private:   // private type definitions and constants

      typedef bidirectional_node<__Type> _node;

   private:   // member variables

      _node*         _m_head;
      _node*         _m_tail;
      std::size_t    _m_size;
      std::size_t    _m_max_size;

   public:   // member functions

      void append(_node* _Node) { _append(_Node); }
      void append(const linked_list<__Type>& _Rhs) { _append(_Rhs); }
      iterator begin() { return iterator(_m_head->m_next); }
      bool empty() const { return _m_size == 0; }
      iterator end() { return iterator(_m_tail); }
      const __Type get(std::size_t _Index) { return _get(_Index); }
      __Type* get_back() { return _get_back(); }
      __Type* get_front() { return _get_front(); }
      std::size_t max_size() { return _m_max_size; }
      void move(linked_list<__Type>& _Rhs) { _move(_Rhs); }
      void move_back(linked_list<__Type>& _Rhs) { _move_back(_Rhs); }
      void move_back_to_front(linked_list<__Type>& _Rhs) { _move_back_to_front(_Rhs); }
      void move_front(linked_list<__Type>& _Rhs) { _move_front(_Rhs); }
      void move_front_to_back(linked_list<__Type>& _Rhs) { _move_front_to_back(_Rhs); }
      __Type pop_back() { return _pop_back(); }
      __Type pop_front() { return _pop_front(); }
      int push_back(const __Type& _Data) { return _push_back(const_cast<__Type&>(_Data)); }
      int push_front(const __Type& _Data) { return _push_front(const_cast<__Type&>(_Data)); }
      std::size_t size() { return _m_size; }
      mta::raw_list<__Type>* to_raw_list() { return _to_raw_list(); }

   public:   // member operators

      linked_list<__Type>& operator=(const linked_list<__Type>& _Rhs) { if (this != &_Rhs) _ctor(); _copy(const_cast<linked_list<__Type>&>(_Rhs)); return *this; }
      linked_list<__Type>& operator=(const mta::raw_list<__Type>& _Rhs) { if (this != &_Rhs) _ctor(); assign(); return *this; }
      bool operator==(const linked_list<__Type>& _Rhs) { return this == &_Rhs; }

   public:   // constructor | destructor

      linked_list() : _m_head(NULL), _m_tail(NULL), _m_size(0), _m_max_size(__Size) { _ctor(); }
      linked_list(const linked_list<__Type>& _Rhs) { _ctor(); _copy(const_cast<linked_list<__Type>&>(_Rhs)); }

      ~linked_list() { _dtor(); }

   private:   // helper functions

      void _append(_node* _Node) { _push_back(_Node); }

      void _append(const linked_list<__Type>& _Rhs) { _copy(_Rhs); }

      void assign(const mta::raw_list<__Type>& _Rhs) { _m_head = _Rhs.get_m_head(); _m_tail = _Rhs.get_m_tail(); }

      void _ctor() 
      { 
         
         _m_head = new _node();  

         _m_tail = new _node(); 

         _m_head->m_next = _m_tail; 

         _m_head->m_prev = NULL; 

         _m_tail->m_prev = _m_head; 

         _m_tail->m_next = NULL; 

      }

      void _copy(const linked_list<__Type>& _Rhs)
      {
         iterator _It(_Rhs.begin());
         iterator _End(_Rhs.end());

         while(_It != _End) { _Rhs.push_back(*_It); ++_It; }
      }

      void _dtor() 
      { 

         _node* _It = _m_head->m_next; 

         while (_It != _m_tail) 
         { 

            _node* _Temp = _It; 

            _It = _It->m_next; 

            delete _Temp; 

         } 

         delete _m_head; 

         delete _m_tail; 

      }
      const __Type _get(std::size_t _Index) { iterator _It = _go_to(_Index); return *_It; }
      __Type* _get_back() { return _m_tail->m_prev->m_data; }
      __Type* _get_front() { return _m_head->m_next->m_data; }
      iterator _go_to(std::size_t _Index) { iterator _It(_m_head->m_next); for (std::size_t i = 0; i < _Index; ++i) ++_It; return _It; }

      void _move(linked_list<__Type>& _Rhs)
      {
         // moves from _Rhs to this

         _node* _R_First = _Rhs._m_head->m_next;
         _node* _R_Last = _Rhs._m_tail->m_prev;

         _node* _Last = _m_tail->m_prev;

         _R_Last->m_next = _m_tail;
         _m_tail->m_prev = _R_Last;

         _R_First->m_prev = _Last;
         _Last->m_next = _R_First;

         _m_size += _Rhs.size();
         _Rhs._m_size = 0;

         _Rhs._m_head->m_next = _Rhs._m_tail;
         _Rhs._m_tail->m_prev = _Rhs._m_head;
      }

      void _move_back(linked_list<__Type>& _Rhs)
      {
         _node* _Temp = _Rhs._m_tail->m_prev;
         _node* _Saved = _Temp->m_prev;

         _Temp->m_prev = _m_tail->m_prev;
         _Temp->m_next = _m_tail;
         _m_tail->m_prev = _Temp;
         _Temp->m_prev->m_next = _Temp;

         _Rhs._m_tail->m_prev = _Saved;
         _Saved->m_next = _Rhs->_m_tail;

         --_Rhs._m_size;
         ++_m_size;
      }

      void _move_back_to_front(linked_list<__Type>& _Rhs)
      {
         _node* _Temp = _Rhs._m_tail->m_prev;
         _node* _Saved = _Temp->m_prev;

         _Temp->m_next = _m_head->m_next;
         _Temp->m_prev = _m_head;
         _m_head->m_next = _Temp;
         _Temp->m_next->m_prev = _Temp;

         _Rhs._m_tail->m_prev = _Saved;
         _Saved->m_next = _Rhs->_m_tail;

         --_Rhs._m_size;
         ++_m_size;
      }

      void _move_front(linked_list<__Type>& _Rhs)
      {
         _node* _Temp = _Rhs._m_head->m_next;
         _node* _Saved = _Temp->m_next;

         _Temp->m_next = _m_head->m_next;
         _Temp->m_prev = _m_head;
         _m_head->m_next = _Temp;
         _Temp->m_next->m_prev = _Temp;

         _Rhs._m_head->m_next = _Saved;
         _Saved->m_prev = _Rhs._m_head;

         --_Rhs._m_size;
         ++_m_size;
      }

      void _move_front_to_back(linked_list<__Type>& _Rhs)
      {
         _node* _Temp = _Rhs._m_head->m_next;
         _node* _Saved = _Temp->m_next;

         _Temp->m_prev = _m_tail->m_prev;
         _Temp->m_next = _m_tail;
         _m_tail->m_prev = _Temp;
         _Temp->m_prev->m_next = _Temp;

         _Rhs._m_head->m_next = _Saved;
         _Saved->m_prev = _Rhs._m_head;

         --_Rhs._m_size;
         ++_m_size;
      }

      __Type _pop_back()
      {
         __Type _Data = _m_tail->m_prev->m_data;

         _node* _Temp = _m_tail->m_prev->m_prev;

         _Temp->m_next = _m_tail;
         delete _m_tail->m_prev;

         _m_tail->m_prev = _Temp;

         --_m_size;

         return _Data;
      }

      __Type _pop_front()
      {
         __Type _Data = _m_head->m_next->_data;

         _node* _Temp = _m_head->m_next->m_next;

         _Temp->m_prev = _m_head;
         delete _m_head->m_next;

         _m_head->m_next = _Temp;

         --_m_size;

         return _Data;
      }

      int _push_back(__Type& _Data)
      {

         std::size_t _Return_value = 0;

         if (_m_size == 0) 
         { 
            _m_head->m_next = new _node(_Data, _m_tail, _m_head); 
            _m_tail->m_prev = _m_head->m_next;
            ++_m_size;
         }

         else if ((_m_size < _m_max_size && _m_max_size != 0) || _m_max_size == 0)
         {
            _node* _Temp = _m_tail->m_prev;
            _Temp->m_next = new _node(_Data, _m_tail, _Temp);
            _m_tail->m_prev = _Temp->m_next;
            ++_m_size;
         }

         else
         {
            _Return_value = 1;
         }

         return _Return_value;
      }

      int _push_front(__Type& _Data)
      {
         std::size_t _Return_value = 0;

         if (_m_size == 0)
         { 
            _m_head->m_next = new _node(_Data, _m_tail, _m_head); 
            _m_tail->m_prev = _m_head->m_next; 
            ++_m_size;
         }

         else if (_m_size < __Size || __Size == 0)
         {
            _node* _Temp = _m_head->m_next;
            _Temp->m_prev = new _node(_Data, _Temp, _m_head);
            _m_head->m_next = _Temp->m_prev;
            ++_m_size;
         }

         else
         {
            _Return_value = 1;
         }

         return _Return_value;
      }

      mta::raw_list<__Type>* _to_raw_list() { return new mta::raw_list<__Type>(_m_head, _m_tail); }


};   // end of class linked_list

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace(el)
}   // end of namespace(ev6)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __LINKED_LIST_HPP__
