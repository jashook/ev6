////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        bounded_bounded_linked_list
//
// Version:       3.0
//
// Modifications:
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __BOUNDED_bounded_linked_list_HPP__
#define __BOUNDED_bounded_linked_list_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "node.hpp"
#include "iter.hpp"
#include "raw_list.hpp"
#include "free_list.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename __Type, std::size_t __Update_Size = 1024> class bounded_linked_list
{
   public:   // public type definitions and constants

      typedef const __Type*  const_pointer;
      typedef const __Type&  const_reference;
      typedef std::ptrdiff_t difference_type;
      typedef __Type*        pointer;
      typedef __Type&        reference;
      typedef std::size_t    size_type;
      typedef __Type         value_type;

   private:   // private type definitions and constants

      typedef bidirectional_node<__Type> _node;

   private:   // member variables

      fl::free_list< bidirectional_node<__Type>, __Update_Size >* _m_free_list;
      bidirectional_node<__Type>* _m_head;
      bidirectional_node<__Type>* _m_tail;

      std::size_t _m_size;
      std::size_t _m_max_size;

   public:   // member functions

      void append(_node* _Node) { _append(_Node); }
      void append(const bounded_linked_list<__Type>& _Rhs) { _append(_Rhs); }
      bool empty() const { return _m_size == 0; }
      bool full() { return _m_size == __Update_Size; }
      const __Type get(std::size_t _Index) { return _get(_Index); }
      __Type* get_back() { return _get_back(); }
      __Type* get_front() { return _get_front(); }
      std::size_t max_size() { return _m_max_size; }
      void move_back(bounded_linked_list<__Type>& _Rhs) { _move_back(_Rhs); }
      void move_back_to_front(bounded_linked_list<__Type>& _Rhs) { _move_back_to_front(_Rhs); }
      void move_front(bounded_linked_list<__Type>& _Rhs) { _move_front(_Rhs); }
      void move_front_to_back(bounded_linked_list<__Type>& _Rhs) { _move_front_to_back(_Rhs); }
      __Type pop_back() { return _pop_back(); }
      __Type pop_front() { return _pop_front(); }
      int push_back(const __Type& _Data) { return _push_back(const_cast<__Type&>(_Data)); }
      int push_front(const __Type& _Data) { return _push_front(const_cast<__Type&>(_Data)); }
      std::size_t size() { return _m_size; }
      mta::raw_list<__Type>* to_raw_list() { return _to_raw_list(); }
      void swap_with(bounded_linked_list<__Type, __Update_Size>& _Rhs) { _swap_with(_Rhs); }

   public:   // member operators

      bounded_linked_list<__Type>& operator=(const bounded_linked_list<__Type>& _Rhs) { if (this != &_Rhs) _ctor(); _copy(const_cast<bounded_linked_list<__Type>&>(_Rhs)); return *this; }
      bounded_linked_list<__Type>& operator=(const mta::raw_list<__Type>& _Rhs) { if (this != &_Rhs) _ctor(); _assign(); return *this; }
      bool operator==(const bounded_linked_list<__Type>& _Rhs) { return this == &_Rhs; }

   public:   // constructor | destructor

      bounded_linked_list() : _m_size(0), _m_max_size(__Update_Size) { _ctor(); }
      bounded_linked_list(const bounded_linked_list<__Type>& _Rhs) { _ctor(); _copy(const_cast<bounded_linked_list<__Type>&>(_Rhs)); }

      ~bounded_linked_list() { _dtor(); }

   private:   // helper functions

      void _append(_node* _Node) { _push_back(_Node); }

      void _append(const bounded_linked_list<__Type>& _Rhs) { _copy(_Rhs); }

      void assign(const mta::raw_list<__Type>& _Rhs) { _m_head = _Rhs.get_m_head(); _m_tail = _Rhs.get_m_tail(); }

      void _ctor() 
      {

         _m_head = new bidirectional_node<__Type>();
         _m_tail = new bidirectional_node<__Type>();
         _m_free_list = new fl::free_list< bidirectional_node<__Type>, __Update_Size >();

         _m_head->_m_next = _m_tail; 
         _m_head->_m_prev = 0; 
         _m_tail->_m_prev = _m_head; 
         _m_tail->_m_next = 0;
      }

      void _copy(const bounded_linked_list<__Type>& _Rhs)
      {

      }

      void _dtor() 
      { 
         _node* _It = _m_head->_m_next; 

         while (_It != _m_tail) 
         {
            _node* _Temp = _It; 

            _It = _It->_m_next; 

            _m_free_list->return_to_list(_It->_m_prev); 
         } 
      
      }

      __Type* _get_back() { return _m_tail->_m_prev->_m_data; }
      __Type* _get_front() { return _m_head->_m_next->_m_data; }

      __Type _pop_back()
      {
         __Type _Data = _m_tail->_m_prev->_m_data;

         _node* _Temp = _m_tail->_m_prev->_m_prev;

         _Temp->_m_next = _m_tail;
         _m_free_list->return_to_list(_m_tail->_m_prev);

         _m_tail->_m_prev = _Temp;

         --_m_size;

         return _Data;
      }

      __Type _pop_front()
      {
         __Type _Data = _m_head->_m_next->_m_data;

         _node* _Temp = _m_head->_m_next->_m_next;

         _Temp->_m_prev = _m_head;
         _m_free_list->return_to_list(_m_head->_m_next);

         _m_head->_m_next = _Temp;

         --_m_size;

         return _Data;
      }

      int _push_back(__Type& _Data)
      {
         std::size_t _Return_value = 0;

         if (_m_size == 0)
         { 
            _m_tail->_m_prev = static_cast<bidirectional_node<__Type>*>(_m_free_list->remove_from_list());
            _m_tail->_m_prev->realloc(_Data, _m_tail, _m_head);
            _m_head->_m_next = _m_tail->_m_prev; 
            ++_m_size;
         }

         else if (_m_size < __Update_Size || __Update_Size == 0)
         {
            _node* _Temp = _m_tail->_m_prev;
            _m_tail->_m_prev = static_cast<bidirectional_node<__Type>*>(_m_free_list->remove_from_list());
            _m_tail->_m_prev->realloc(_Data, _m_tail, _Temp);
            _Temp->_m_next = _m_tail->_m_prev;
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
            _m_head->_m_next = static_cast<bidirectional_node<__Type>*>(_m_free_list->remove_from_list());
            _m_head->_m_next->realloc(_Data, _m_tail, _m_head);
            _m_tail->_m_prev = _m_head->_m_next; 
            ++_m_size;
         }

         else if (_m_size < __Update_Size || __Update_Size == 0)
         {
            _node* _Temp = _m_head->_m_next;
            _m_head->_m_next = static_cast<bidirectional_node<__Type>*>(_m_free_list->remove_from_list());
            _m_head->_m_next->realloc(_Data, _Temp, _m_head);
            _Temp->_m_prev = _m_head->_m_next;
            ++_m_size;
         }

         else
         {
            _Return_value = 1;
         }

         return _Return_value;
      }

      mta::raw_list<__Type>* _to_raw_list() { return new mta::raw_list<__Type>(_m_head, _m_tail); }

      void _swap_free_lists(bounded_linked_list<__Type, __Update_Size>& _Rhs)
      {
         // swap both allocators

         fl::free_list< bidirectional_node<__Type>, __Update_Size >* _Temp = _Rhs._m_free_list;
         _Rhs._m_free_list = _m_free_list;
         _m_free_list = _Temp;
      }

      void _swap_empty(bounded_linked_list<__Type, __Update_Size>& _Rhs)
      {
         _node* _Last = _m_tail->_m_prev;
         _node* _First = _m_head->_m_next;

         _Rhs._m_head->_m_next = _First;
         _First->_m_prev = _Rhs._m_head;

         _Rhs._m_tail->_m_prev = _Last;
         _Last->_m_next = _Rhs._m_tail;

         _m_head->_m_next = _m_tail;
         _m_head->_m_prev = NULL;

         _m_tail->_m_prev = _m_head;
         _m_tail->_m_next = NULL;

         int _Saved_size = _m_size;
         _m_size = _Rhs.size();
         _Rhs._m_size = _Saved_size;
      }

      void _swap_lists(bounded_linked_list<__Type, __Update_Size>& _Rhs)
      {
         // saved first and last nodes of both lists

         _node* _R_First = _Rhs._m_head->_m_next;
         _node* _R_Last = _Rhs._m_tail->_m_prev;

         _node* _Last = _m_tail->_m_prev;
         _node* _First = _m_head->_m_next;

         _R_Last->_m_next = _m_tail;
         _m_tail->_m_prev = _R_Last;

         // swap both lists

         _R_First->_m_prev = _m_head;
         _m_head->_m_next = _R_First;

         _Rhs._m_head->_m_next = _First;
         _First->_m_prev = _Rhs._m_head;

         _Rhs._m_tail->_m_prev = _Last;
         _Last->_m_next = _Rhs._m_tail;

         // swap sizes

         int _Saved_size = _m_size;
         _m_size += _Rhs.size();
         _Rhs._m_size = _Saved_size;
      }

      void _swap_with(bounded_linked_list<__Type, __Update_Size>& _Rhs)
      {
          _swap_free_lists(_Rhs);


         if (_Rhs.size() == 0) _swap_empty(_Rhs);

         else _swap_lists(_Rhs);
      }


};   // end of class bounded_linked_list

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __bounded_linked_list_HPP__