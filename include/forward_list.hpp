////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        forward_list
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef FORWARD_LIST
#define FORWARD_LIST

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <iterator>

#include "forward_node.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename __Type> class forward_list
{

   private:   // private iterator class


      class forward_list_iterator : public std::iterator<std::forward_iterator_tag, __Type>
      {
         public:   /*   Constructor | Destructor   */

            forward_list_iterator(const fl::forward_node<__Type>* _Index) : _m_index(const_cast<forward_node<__Type>*>(_Index)) { }
            forward_list_iterator(const fl::forward_list_iterator& _rhs) { _copy(const_cast<forward_list_iterator&>(_rhs)); }

            //   Destructor automatically provided
         
         public:   /*   member operations   */
         
            forward_list_iterator operator=(const forward_list_iterator& _rhs) { _copy( const_cast<forward_list_iterator&>(_rhs)); }
            bool operator==(const forward_list_iterator& _rhs) const { return _equal(_rhs); }
            bool operator!=(const forward_list_iterator& _rhs) const { return !(_equal(_rhs)); }
            fl::forward_node<__Type>* operator->() { return _m_index; }
            __Type& operator*() { return _get_data(); }
            forward_list_iterator operator++() { return _increment_prefix(); }
            forward_list_iterator operator++(int) { return _increment_postfix(); }

         private:   //   member variables

            fl::forward_node<__Type>* _m_index;

         private:   //   helper functions

            void _copy(forward_list_iterator& _rhs) { _m_index = _rhs._m_index; }
            bool _equal(const forward_list_iterator& _rhs) const { return _m_index == _rhs._m_index; }
            __Type& _get_data() { return _m_index->_data; }
            void _increment() { _m_index = _m_index->_next; }
            forward_list_iterator _increment_prefix() { _increment(); return *this; }
            forward_list_iterator _increment_postfix() { forward_list_iterator _temp(*this); _increment(); return _temp; }
      };

      class const_forward_list_iterator : public std::iterator<std::forward_iterator_tag, __Type>
      {
         public:   /*   Constructor | Destructor   */

            const_forward_list_iterator(const fl::forward_node<__Type>* _Index) : _m_index(const_cast<fl::forward_node<__Type>*>(_Index)) { }
            const_forward_list_iterator(const const_forward_list_iterator& _rhs) { _copy(const_cast<const_forward_list_iterator&>(_rhs)); }

            //   Destructor automatically provided
         
         public:   /*   member operations   */
         
            const_forward_list_iterator operator=(const const_forward_list_iterator& _rhs) { _copy( const_cast<const_forward_list_iterator&>(_rhs)); }
            bool operator==(const const_forward_list_iterator& _rhs) const { return _equal(_rhs); }
            bool operator!=(const const_forward_list_iterator& _rhs) const { return !(_equal(_rhs)); }
            fl::forward_node<__Type>* operator->() { return _m_index; }
            __Type& operator*() { return _get_data(); }
            const_forward_list_iterator operator++() { return _increment_prefix(); }
            const_forward_list_iterator operator++(int) { return _increment_postfix(); }

         private:   //   member variables

            fl::forward_node<__Type>* _m_index;

         private:   //   helper functions

            void _copy(const_forward_list_iterator& _rhs) { _m_index = _rhs._m_index; }
            bool _equal(const const_forward_list_iterator& _rhs) const { return _m_index == _rhs._m_index; }
            __Type& _get_data() { return _m_index->_data; }
            void _increment() { _m_index = _m_index->_next; }
            const_forward_list_iterator _increment_prefix() { _increment(); return *this; }
            const_forward_list_iterator _increment_postfix() { const_forward_list_iterator _temp(*this); _increment(); return _temp; }
      };

   public:   /*   constants and type definations   */

      typedef __Type value_type;
      typedef std::size_t size_type;
      typedef __Type* pointer;
      typedef __Type& reference;
      typedef const __Type* const_pointer;
      typedef const __Type& const_reference;
      typedef std::ptrdiff_t difference_type;
      typedef forward_list_iterator iterator;
      typedef const_forward_list_iterator const_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

   private:

      typedef fl::forward_node<__Type> _node;

   public:   /*   Constructor | Destructor   */

      forward_list() { _allocate(); }
      forward_list(const forward_list<__Type>& _rhs) { _allocate(); _copy(const_cast<forward_list<__Type>&>(_rhs)); }

      ~forward_list() { _deallocate(); }

   public:   /*   member functions   */

      iterator begin() { return iterator(_head._next); }
      const_iterator begin() const { return const_iterator(_head._next); }
      bool empty() const { return _size == 0; }
      iterator end() { return iterator(&_tail); }
      const_iterator end() const { return const_iterator(_tail); }
      const __Type get(size_type _Index) { return _get(_Index); }
      size_t max_size() const { return _size; }
      __Type pop_back() { return _pop_back(); }
      _node* pop_back_node() 	{ return _pop_back_node(); }
      _node* pop_front_node() { return _pop_front_node(); }
      __Type pop_front() { return _pop_front(); }
      void push_back(__Type _data) { _push_back(_data); }
      void push_back(const __Type _data) const { _const_push_back(_data); }
      void push_back_node(const _node* _Node) { _push_back_node(const_cast<_node*>(_Node)); }
      void push_back_node(const _node* _Node, const __Type& _Data) { _push_back_node(const_cast<_node*>(_Node), const_cast<__Type&>(_Data)); }
      void push_front(__Type _data) { _push_front(_data); }
      void push_front(const __Type _data) const { _const_push_front(_data); }
      void push_front_node(const _node* _Node, const __Type& _Data) { _push_front_node(const_cast<_node*>(_Node), const_cast<__Type&>(_Data)); }
      std::size_t size() const { return _size; }

   public:   //   member operators

      forward_list<__Type> operator=(const forward_list<__Type>& _rhs) { if(this != &_rhs) _allocate(); _copy(const_cast<forward_list<__Type>&>(_rhs)); return *this; }

   private:  //   helper functions

      void _allocate()
      {
         _head._next = &_tail;
         _tail._next = NULL;
         _last = &_head;
         _size = 0;
         _at_last = true;
      }

      void _copy(forward_list<__Type>& _rhs)
      {
         forward_list<__Type>::iterator rhs_iter(_rhs._head._next);
         _node* iter = _head._next;

         while(rhs_iter.operator->() != &_rhs._tail) _push_back(*(rhs_iter++));
         
      }

      void _deallocate()
      {
         _node* iter = _head._next;
         _node* back_iter = iter;
         while (iter != NULL)
         {
            iter = iter->_next;
            if (back_iter == &_tail) break;
            else 
            {
               delete back_iter;
               back_iter = iter;
            }
         }  
      }

      const __Type _get(size_type _Index)
      {
         _node* temp = &_head;
         for (size_type n = 0; n < _Index + 1; temp = temp->_next, ++n) { }
         return temp->_data;
      }

      __Type _pop_back()
      {
         __Type _Temp = _last->_next->_data;
         delete _last->_next;
         _last->_next = &_tail;
         --_size;
         _at_last = true;
         return _Temp;
      }

      _node* _pop_back_node()
      {
         _node* _Node = _last->_next;
         _Node->_next = NULL;
         _last->_next = &_tail;
         --_size;
         _at_last = true;
         return _Node;
      }

      __Type _pop_front()
      {
         __Type _Temp = _head._next->_data;
         _node* _At = _head._next;
         _head._next = _At->_next;
         delete _At;

         if (_size == 1) { _last = &_head; _at_last = true; }

         --_size;
         return _Temp;
      }

      _node* _pop_front_node()
      {
         _node* _Node = _head._next;
         _head._next = _Node->_next;
         _Node->_next = NULL;

         if (_size == 1) { _last = &_head; _at_last = true; }

         --_size;
         return _Node;
      }

      void _push_back(__Type _data)
      {
         if (!_at_last) _last = _last->_next;
         else _at_last = false;
         _last->_next = new _node(_data, &_tail);
         ++_size;
      }

      void _const_push_back(const __Type _data) const
      {
         if (!_at_last) _last = _last->_next;
         else _at_last = false;
         _last->_next_ = new _node(_data, &_tail);
         ++_size;
      }

      void _push_back_node(_node* _Node)
      {
         if (!_at_last) _last = _last->_next;
         else _at_last = false;
         _last->_next = _Node;
         _Node->_next = &_tail;
         ++_size;
      }

      void _push_back_node(_node* _Node, __Type& _Data)
      {
         if (!_at_last) _last = _last->_next;
         else _at_last = false;
         _last->_next = _Node;
         _Node->_data = _Data;
         _Node->_next = &_tail;
         ++_size;
      }

      void _push_front(__Type _data)
      {
         _node* _temp = _head._next;
         _head._next = new _node(_data, _temp);
         ++_size;
      }

      void _const_push_front(const __Type _data) const
      {
         _node* _temp = _head._next;
         _head._next = new _node(_data, _temp);
         ++_size;
      }

      void _push_front_node(_node* _Node)
      {
         _node* _temp = _head._next;
         _head._next = _Node;
         _Node->_next = _temp;
         ++_size;
      }

      void _push_front_node(_node* _Node, __Type& _Data)
      {
         _node* _temp = _head._next;
         _head._next = _Node;
         _Node->_data = _Data;
         _Node->_next = _temp;
         ++_size;
      }
      
   private:   /*   member variables   */
      _node _head;
      _node _tail;
      _node* _last;
      bool _at_last;
      size_type _size;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   /*   end of namespace(ev4)   */

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   /*   FORWARD_LIST   */
