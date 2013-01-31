////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        dynamic_array
//
// Version:       1.0
//
// Modifications:
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//   Old class, use ev4::vector instead.
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "node.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename _type> class dynamic_array
{

   private:   /*   nested classes/structs   */

      template <typename _type> class dynamic_array_iter : public std::iterator<std::random_access_iterator_tag, _type>
      {

         public:   /*   Constructor | Destructor   */
      
            dynamic_array_iter() : _index(NULL) { }
            dynamic_array_iter(const dynamic_array_iter<_type>& _rhs) { _copy(_rhs); }
            dynamic_array_iter(basic_node<_type>** _pointer) : _index(_pointer) { }

            ~dynamic_array_iter() { }

         public:   /*   member operations   */

            dynamic_array_iter<_type> operator+(std::ptrdiff_t _offset) { return _add(_offset); }
            dynamic_array_iter<_type>& operator+=(std::ptrdiff_t _offset) { return _add_assign(_offset); }
            dynamic_array_iter<_type>& operator=(const dynamic_array_iter<_type>& _rhs) { return _assign_iter(_rhs); }
            dynamic_array_iter<_type>& operator--() { return _decrement_prefix(); }
            dynamic_array_iter<_type>& operator--(int) { return _decrement_postfix(); }
            bool operator==(const dynamic_array_iter<_type>& _rhs) const { return _equal(_rhs); }
            bool operator!=(const dynamic_array_iter<_type>& _rhs) const { return !(_equal(_rhs)); }
            dynamic_array_iter<_type>& operator++() { return _increment_prefix(); }
            dynamic_array_iter<_type>& operator++(int) { return _increment_postfix(); }
            _type* operator->() const { return _get_data(); }
            _type& operator*() const { return _get_data(); }
            bool operator<(const dynamic_array_iter<_type>& _rhs) const { return _less_than(_rhs); }
            bool operator>(const dynamic_array_iter<_type>& _rhs) const { return !(_less_than(_rhs)); }
            dynamic_array_iter<_type> operator-(std::ptrdiff_t _offset) const { return _subtract(_offset); }
            std::ptrdiff_t operator-(const dynamic_array_iter<_type>& _rhs) const { return _subtract(_rhs); }
            dynamic_array_iter<_type>& operator-=(std::ptrdiff_t _offset) { return _subtract_assign(_offset); }

         private:   /*   member variables   */
      
            basic_node<_type>** _index;

         private:   /*   helper functions   */

            dynamic_array_iter<_type> _add(std::ptrdiff_t _offset) { dynamic_array_iter<_type> _temp(*this); return _temp += _offset; }
            dynamic_array_iter<_type>& _add_assign(std::ptrdiff_t _offset) { _index += _offset; return *this; }
            dynamic_array_iter<_type>& _assign_iter(const dynamic_array_iter<_type>& _rhs) { if(this != &_rhs) _copy(_rhs); return *this; }
            void _copy(const dynamic_array_iter<_type>& _rhs) { _index = _rhs._index; }
            void _decrement() { --_index; }
            dynamic_array_iter<_type>& _decrement_prefix() { _decrement(); return *this; }
            dynamic_array_iter<_type>& _decrement_postfix() { dynamic_array_iter<_type> _temp(*this); _decrement(); return _temp; }
            bool _equal(const dynamic_array_iter<_type>& _rhs) const { return _index == _rhs._index; }
            void _increment() { ++_index; }
            dynamic_array_iter<_type> _increment_prefix() { _increment(); return *this; }
            dynamic_array_iter<_type> _increment_postfix() { dynamic_array_iter<_type> _temp(*this); _increment(); return _temp; }
            _type& _get_data() const { return (*(*(_index)))._data; }
            bool _less_than(const dynamic_array_iter<_type>& _rhs) const { return _index < _rhs._index; }
            dynamic_array_iter<_type> _subtract(std::ptrdiff_t _offset) const { dynamic_array_iter<_type> _temp(*this); return _temp -= _offset; }
            std::ptrdiff_t _subtract(const dynamic_array_iter<_type>& _rhs) const { return _index - _rhs._index; }
            dynamic_array_iter<_type>& _subtract_assign(std::ptrdiff_t _offset) { _index -= _offset; return *this; }

      };

      template <typename _type> class const_dynamic_array_iter : public std::iterator<std::random_access_iterator_tag, _type>
      {

         public:   /*   Constructor | Destructor   */
      
            const_dynamic_array_iter() : _index(NULL) { }
            const_dynamic_array_iter(const const_dynamic_array_iter<_type>& _rhs) { _copy(_rhs); }
            const_dynamic_array_iter(basic_node<_type>** _pointer) : _index(_pointer) { }

            ~const_dynamic_array_iter() { }

         public:   /*   member operations   */

            const_dynamic_array_iter<_type> operator+(std::ptrdiff_t _offset) { return _add(_offset); }
            const_dynamic_array_iter<_type>& operator+=(std::ptrdiff_t _offset) { return _add_assign(_offset); }
            const_dynamic_array_iter<_type>& operator=(const const_dynamic_array_iter<_type>& _rhs) { return _assign_iter(_rhs); }
            const_dynamic_array_iter<_type>& operator--() { return _decrement_prefix(); }
            const_dynamic_array_iter<_type>& operator--(int) { return _decrement_postfix(); }
            bool operator==(const const_dynamic_array_iter<_type>& _rhs) const { return _equal(_rhs); }
            bool operator!=(const const_dynamic_array_iter<_type>& _rhs) const { return !(_equal(_rhs)); }
            const_dynamic_array_iter<_type>& operator++() { return _increment_prefix(); }
            const_dynamic_array_iter<_type>& operator++(int) { return _increment_postfix(); }
            _type* operator->() const { return _get_data(); }
            _type& operator*() const { return _get_data(); }
            bool operator<(const const_dynamic_array_iter<_type>& _rhs) const { return _less_than(_rhs); }
            bool operator>(const const_dynamic_array_iter<_type>& _rhs) const { return !(_less_than(_rhs)); }
            const_dynamic_array_iter<_type> operator-(std::ptrdiff_t _offset) const { return _subtract(_offset); }
            std::ptrdiff_t operator-(const const_dynamic_array_iter<_type>& _rhs) const { return _subract(_rhs); }
            const_dynamic_array_iter<_type>& operator-=(std::ptrdiff_t _offset) { return _subtract_assign(_offset); }

         private:   /*   member variables   */
      
            basic_node<_type>** _index;

         private:   /*   helper functions   */

            const_dynamic_array_iter<_type> _add(std::ptrdiff_t _offset) { const_dynamic_array_iter<_type> _temp(*this); return _temp += _offset; }
            const_dynamic_array_iter<_type>& _add_assign(std::ptrdiff_t _offset) { _index += _offset; return *this; }
            const_dynamic_array_iter<_type>& _assign_iter(const const_dynamic_array_iter<_type>& _rhs) { if(this != &_rhs) _copy(_rhs); return *this; }
            void _copy(const const_dynamic_array_iter<_type> _rhs) { _index = _rhs._index; }
            void _decrement() { --_index; }
            const_dynamic_array_iter<_type>& _decrement_prefix() { _decrement(); return *this; }
            const_dynamic_array_iter<_type>& _decrement_postfix() { const_dynamic_array_iter<_type> _temp(*this); _decrement(); return _temp; }
            bool _equal(const const_dynamic_array_iter<_type>& _rhs) const { return _index == _rhs._index; }
            void _increment() { --_index; }
            const_dynamic_array_iter<_type> _increment_prefix() { _increment(); return *this; }
            const_dynamic_array_iter<_type> _increment_postfix() { const_dynamic_array_iter<_type> _temp(*this); _increment(); return _temp; }
            const _type _get_data() const { return (*(*(_index)))._data; }
            bool _less_than(const const_dynamic_array_iter<_type>& _rhs) const { return _index < _rhs._less_than; }
            const_dynamic_array_iter<_type> _subtract(std::ptrdiff_t _offset) const { const_dynamic_array_iter<_type> _temp(*this); return _temp -= _offset; }
            std::ptrdiff_t _subtract(const const_dynamic_array_iter<_type>& _rhs) const { return _index - _rhs._index; }
            const_dynamic_array_iter<_type>& _subtract_assign(std::ptrdiff_t _offset) { _index -= _offset; return *this; }

      };

   public:   /*   constants and type definitions   */

      typedef _type value_type;
      typedef std::size_t size_type;
      typedef _type* pointer;
      typedef _type& reference;
      typedef const _type* const_pointer;
      typedef const _type& const_reference;
      typedef std::ptrdiff_t difference_type;
      typedef dynamic_array_iter<_type> iterator;
      typedef const_dynamic_array_iter<_type> const_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

   private:   /*   private constants and type definitions   */
      
      typedef basic_node<_type> _node;

   private:   /*   member variables   */
      _node** _data;
      std::size_t _size;
      std::size_t _capacity;
      const size_type _base_size;

   public:   /*   member functions   */

      reference at(std::size_t _position) { try { return _at_safe(_position); } catch(...) { throw; } }
      const_reference at(size_type _position) const { try { return _at_safe(_position); } catch (...) { throw; } }
      iterator begin() { return iterator(_front()); }
      const_iterator begin() const { return iterator(_front); }
      bool empty() const { return _size == 0; }
      iterator end() { return iterator(_end()); }
      const_iterator end() const { return const_iterator(_end()); }
      size_type max_size() const { return _size; }
      value_type pop_back() { return (_pop_back()); }
      void push_back(value_type _Type) { _push_back(_Type); }
      reverse_iterator rbegin() { return reverse_iterator(end()); }
      const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
      reverse_iterator rend() { return reverse_iterator(begin()); }
      const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
      size_type size() const { return _size; }

   public:   /*   member operators   */

       reference operator[] (size_type _offset) { return _data[_offset]; }
       const_reference operator[] (size_type _offset) const { return _data[_offset]; }

   public:   /*   constructor | destructor   */

      dynamic_array() : _capacity(0), _size(0), _base_size(10) { }
      explicit dynamic_array(std::size_t _Size) : _capacity(_Size), _size(0), _base_size(10)
      {
         if(_capacity != 0) _allocate(_data, _Size);
         else _allocate(_data, _Size);
      }

      ~dynamic_array()
      {
         _tidy(_data);
      }

   public:   /*   helper functions   */
      
      void _allocate(_node**& _temp, size_type _Size)
      {
         _temp = new _node*[_Size];
         for (size_type n = 0; n < _Size; ++n) _temp[n] = NULL;
      }

      bool _at_capacity() { return _size == _capacity; }

      reference _at_safe(size_type _position) throw(std::range_error)
      {
         if (_position >= _size) throw std::range_error("array::at _position is out of range");

         return _data[_position];
      }

      const_reference _at_safe(size_type _position) const throw(std::range_error)
      {
         if (_position >= _size) throw std::range_error("array::at _position is out of range");

         return _data[_position];
      }

      void _copy(_node** _source, _node** _destination)
      {
         for (size_type n = 0; n < _size; ++n) _destination[n] = _source[n];
      }

      void _delete_without_shrinking(_node**& _Data, size_type _start_index)
      {
         while (_start_index < _capacity) 
         { 
            if (_Data[_start_index] != NULL) 
            {
               delete _Data[_start_index];
               _Data[_start_index] = NULL;
            }
            ++_start_index; 
         }
      }

      basic_node<value_type>** _end() { return _data + _size; }
      basic_node<value_type>** _front() { return _data; }

      reference _pop_back() throw(std::range_error)
      {
         if (!(_is_valid())) throw std::range_error("array::at _size is out of range");

         return (_data[_size--])._data;
      }

      void _push_back(value_type _Type)
      {
         if(_at_capacity()) _resize();
         _data[_size++] = new _node(_Type);
      }

      void _resize(size_type _Size = 0)
      {
         if (_capacity != 0)
         {
            if (_Size >= 0) // expand
            {
               _capacity *= 2;
               _node** _data_temp;
               _allocate(_data_temp, _capacity);
               _copy(_data, _data_temp);
               delete [] _data;
               _data = _data_temp;
            }
            else
            {
               if(_size > _Size) _size = _Size;
               _shrink_to_fit(_data, _size - _Size);
            }
         }
         else
         {
            _capacity = 10;
            _allocate(_data, _capacity);
         }
      }

      void _shrink_to_fit(_node** _Data, size_type _start_index)
      {
         _delete_without_shrinking(_Data, _start_index);
         _capacity = _start_index;
         _node** _data_temp;
         _allocate(_data_temp, _capacity);
         _copy(_data, _data_temp);
         delete [] _data;
         _data = _data_temp;
      }

      void _tidy(_node**& _Data)
      {
         _delete_without_shrinking(_Data, 0);
         delete [] _Data;
      }

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   /*   end of namespace(ev4)   */

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   /*   DYNAMIC_ARRY   */
