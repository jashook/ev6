////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        vector
//
// Version:       1.0
//
// Modifications: 8-Aug-12: Added support for stack based allocation for speed
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef VECTOR
#define VECTOR

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "array.hpp"
#include "array_iter.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <typename __Type, std::size_t __Size = 1> class vector
{

   public:   //   constants and type definitions

      typedef __Type value_type;
      typedef std::size_t size_type;
      typedef __Type* pointer;
      typedef __Type& reference;
      typedef const __Type* const_pointer;
      typedef const __Type& const_reference;
      typedef std::ptrdiff_t difference_type;
      typedef array_iter<__Type> iterator;
      typedef const_array_iter<__Type> const_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

   private:   //   member variables

      bool _m_set;

      ev4::array<__Type, __Size> _m_array;

      __Type* _m_data;
      std::size_t _m_size;
      std::size_t _m_capacity;
      const size_type _m_base_size;

   public:   //   member functions

      reference at(std::size_t _position) { try { return _at_safe(_position); } catch(...) { throw; } }
      const_reference at(size_type _position) const { try { return _at_safe(_position); } catch (...) { throw; } }
      value_type back() { return _back(); }
      iterator begin() { return iterator(_front()); }
      const_iterator begin() const { return iterator(_front); }
      size_type capacity() const { return _m_capacity; }
      void clear() { if (!_m_set) _delete_without_shrinking(_m_data, 0); else _delete_without_shrinking(_m_array, 0); }
      pointer data() { return __data(); }
      bool empty() const { return _m_size == 0; }
      iterator end() { return iterator(_end()); }
      const_iterator end() const { return const_iterator(_end()); }
      value_type front() { return *(_front()); }
      void insert(size_type _index, value_type _Data) { _insert(_index, _Data); }
      void insert(iterator& _it, value_type _Data) { _insert(_it, _Data); }
      size_type max_size() const { return _m_capacity; }
      value_type pop_back() { return (_pop_back()); }
      void push_back(value_type _Type) { _push_back(_Type); }
      reverse_iterator rbegin() { return reverse_iterator(end()); }
      const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
      void reduce(size_type _new_size) { _reduce(_new_size); }
      reverse_iterator rend() { return reverse_iterator(begin()); }
      void reserve(size_type _new_size) { _reserve(_new_size); }
      const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
      size_type size() const { return _m_size; }

   public:   //   member operators

      void operator+=(const vector<__Type, __Size>& _Rhs) { return _append(_Rhs); }
      bool operator==(const vector& _rhs) { return _equal(_rhs); }
      bool operator!=(const vector& _rhs) { return !(_equal(_rhs)); }
      reference operator[] (size_type _offset) 
      { 
         if (!_m_set) return _m_data[_offset]; 
         return _m_array[_offset];
      }
      const_reference operator[] (size_type _offset) const { if (!_m_set) return _m_data[_offset]; return _m_array[_offset]; }
      vector operator=(const vector& _rhs) { if (this != &_rhs) _initialize(_rhs); return *this; }

   public:   //   constructor | destructor

      vector() : _m_set(true), _m_size(0), _m_base_size(10) 
      {
         if (__Size > 1) _m_capacity = __Size;
         else _m_capacity = 0;
      }

      explicit vector(std::size_t _Size) : _m_set(false), _m_size(0), _m_base_size(10)
      {
         if (__Size > 1) _m_capacity = __Size;
         else _m_capacity = _Size;

         if(_m_capacity != 0 && !_m_set) _allocate(_m_data, _Size);
      }

      vector(iterator& _begin, iterator& _end) : _m_set(false), _m_capacity(__Size), _m_size(0), _m_base_size(10)
      {
         while (_begin != _end) { push_back(*_begin); ++_begin; }
      }

      vector(iterator& _begin, size_type _count) : _m_set(false), _m_capacity(0), _m_size(__Size), _m_base_size(10)
      {
         for (size_type n = 0; n < _count; ++n) { push_back(*_begin); ++_begin; }
      }

      vector(const vector& _rhs) : _m_set(_rhs._m_set), _m_base_size(_rhs._m_base_size) { _initialize(_rhs); }

      ~vector()
      {
         _tidy(_m_data);
      }

   public:   /*   helper functions   */
      
      void _allocate(__Type*& _temp, size_type _Size)
      {
         _m_set = false;
         _temp = new __Type[_Size];
         for (size_type n = 0; n < _Size; ++n) _temp[n] = __Type(0);
      }
      
      void _append(const vector<__Type, __Size>& _Vec)
      {
         for (std::size_t i = 0; i < _Vec.size(); ++i) push_back(_Vec.at(i));
      }

      bool _at_capacity() { return _m_size == _m_capacity; }

      reference _at_safe(size_type _position) throw(std::exception)
      {
         if (_position >= _m_size) throw std::exception("array::at _position is out of range");

         if (!_m_set) return _m_data[_position];
         return _m_array[_position];
      }

      const_reference _at_safe(size_type _position) const throw(std::exception)
      {
         if (_position >= _m_size) throw;

         if (!_m_set) return _m_data[_position];
         return _m_array[_position];
      }

      value_type& _back() { if (!_m_set) return _m_data[_m_size - 1]; return _m_array[_m_size - 1]; }

      void _copy(__Type* _source, __Type* _destination)
      {
         for (size_type n = 0; n < _m_size; ++n) _destination[n] = _source[n];
      }

      void _copy(size_type _start_position)
      {
         if (!_m_set) for (size_type n = _m_size; n >= _start_position; --n) _m_data[n] = _m_data[n - 1];
         for (size_type n = _m_size; n >= _start_position; --n) _m_array[n] = _m_array[n - 1];
      }

      void _copy(iterator& _it)
      {
         iterator last = end();
         while (last != _it) { *last = *(last - 1); --last; }
      }

      pointer __data() { if (!_m_set) return _m_data; }

      void _delete_without_shrinking(__Type*& _Data, size_type _start_index)
      {
         int dec = 0;
         while (_start_index < _m_size) 
         { 
            _Data[_start_index] = __Type(0);
            ++_start_index;
            ++dec;
         }
         _m_size -= dec;
      }

      void _delete_without_shrinking(ev4::array<__Type, __Size>& _Data, size_type _start_index)
      {
         int dec = 0;
         while (_start_index < _m_size) 
         { 
            _Data[_start_index] = __Type(0);
            ++_start_index;
            ++dec;
         }
         _m_size -= dec;
      }

      __Type* _end() { return _m_data + _m_size; }

      bool _equal(const vector& _Vector)
      {
         bool ret = true;

         if (_m_size == _Vector._m_size)
         {
            for (size_type n = 0; n < _m_size; ++n) 
            {
               if (!_m_set) 
               {
                  if (_m_data[n] != _Vector._m_data[n]) { ret = false; break; } 
               }
               
               else 
               {
                  if (_m_data[n] != _Vector._m_data[n]) { ret = false; break; }
               }
            }
         }
         else
         {
            ret = false;
         }

         return ret;
      }

      __Type* _front() { if (!_m_set) return _m_data; return _m_array.begin().operator->();}

      void _initialize(const vector& _rhs)
      {
         _m_capacity = _rhs._m_capacity;
         _m_size = _rhs._m_size;
         if(_m_capacity != 0) {
            _allocate(_m_data, _m_capacity);
            _copy(_rhs._m_data, _m_data);
         }
      }

      void _insert(size_type _index, value_type _Data)
      {
         ++_m_size;
         if(_at_capacity()) _resize();
         _copy(_index);
         if (!_m_set) _m_data[_index] = _Data;
         else _m_array[_index] = _Data;
      }

      void _insert(iterator& _it, value_type _Data)
      {
         ++_m_size;
         if(_at_capacity()) _resize();
         _copy(_it);
         *_it = _Data;
      }

      bool _is_valid()
      {
         if (size() > 0) return true;
         return false;
      }

      reference _pop_back() throw(std::exception)
      {
         if (!(_is_valid())) throw;

         if (!_m_set) return _m_data[--_m_size];
         return _m_array[--_m_size];
      }

      void _push_back(value_type _Type)
      {
         if(_at_capacity()) _resize();
         if (!_m_set) _m_data[_m_size++] = _Type;
         else _m_array[_m_size++] = _Type;
      }

      void _reduce(size_type _new_size)
      {
         if (_m_size > _new_size) { if (!_m_set) { _delete_without_shrinking(_m_data, _new_size); _m_size = _new_size; } else { _delete_without_shrinking(_m_data, _new_size); _m_size = _new_size; } }
         _m_capacity = _new_size;
         __Type* _data_temp;
         _allocate(_data_temp, _m_capacity);
         _copy(_m_data, _data_temp);
         if (!_m_set) delete [] _m_data;
         _m_data = _data_temp;
      }

      void _reserve(size_type _new_size)
      {
         if (_new_size > _m_capacity)
         {
            _m_capacity = _new_size;
            __Type* _data_temp;
            _allocate(_data_temp, _m_capacity);
            _copy(_m_data, _data_temp);
            delete [] _m_data;
            _m_data = _data_temp;
         }
      }

      void _resize(size_type _Size = 0)
      {
         if (_m_capacity != 0 && !_m_set)
         {
            _m_capacity *= 2;
            __Type* _data_temp;
            _allocate(_data_temp, _m_capacity);
            _copy(_m_data, _data_temp);
            delete [] _m_data;
            _m_data = _data_temp;
         }
         else
         {
            _m_capacity = 10;
            _allocate(_m_data, _m_capacity);
         }
      }

      void _shrink_to_fit(__Type* _Data, size_type _start_index)
      {
         _delete_without_shrinking(_Data, _start_index);
         _m_capacity = _start_index;
         __Type* _data_temp;
         if (_m_capacity != 0) {
            __Type* _data_temp;
            allocate(_data_temp, _m_capacity);
            _copy(_m_data, _data_temp);
            delete [] _m_data;
            _m_data = _data_temp;
         }
         else delete [] _m_data;
      }

      void _tidy(__Type*& _Data)
      {
         //if (!_m_set) _delete_without_shrinking(_Data, 0);
         //else _delete_without_shrinking(_m_array, 0);
         if (!_m_set) delete [] _Data;
      }

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   //   end of namespace(ev4)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   /*   VECTOR_   */
