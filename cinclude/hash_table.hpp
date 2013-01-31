////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        hash_table
//
// Version:       1.0
//
// Modifications: 12-June-12 Created a hash table that uses 1,000,000 elements (approx 16MB of stack space)
//
// Notes:  This hash_table is larger than the default stack size given by windows, to change it use either the link comand /STACK 16000000
//       or change the option found under Linker/SYSTEM/STACK RESERVE for windows VS 2010
//
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "iter.hpp"
#include "array.hpp"
#include "node.hpp"
#include "rti.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<typename __Key, typename bool (*__Hash_Value)(__Key), typename __Type = __Key, size_t __Size = 5000000> class hash_table   //   default __Size = 1,000,000
{
   public:   //   type definitions and constants

      typedef __Type value_type;
      typedef std::size_t size_type;
      typedef __Type* pointer;
      typedef __Type& reference;
      typedef const __Type* const_pointer;
      typedef const __Type& const_reference;
      typedef std::ptrdiff_t difference_type;
      typedef forward_list_iterator<value_type> iterator;
      typedef const_forward_list_iterator<value_type> const_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

   private:   //   private type definitions

      typedef forward_node<__Key, __Type> _node;

   private:   //   member variables 

      array<_node, (__Size < 5000000 ? 5000000 : __Size)> _list;   //   if size < 1,000,000 then set that as the default size
      size_type _m_size;
      size_type _m_capacity;
      size_type _m_collisions;
      _node* _m_first;
      _node* _m_last;

   public:   //   member functions

      iterator begin() { return iterator(*_m_first); }
      size_type capacity() { return _get_capacity(); }
      bool contains(const __Key& _key) { return _contains(const_cast<__Key&>(_key)); }
      iterator end() { return iterator(*_m_last); }
      void insert(const __Key& _key) { if(ev4::are_same_type<__Key, __Type>()) { __Type key = const_cast<__Type&>(_key); _insert(key, key); } }
      void insert(const __Key& _key, const __Type& _data) { _insert(const_cast<__Key>(_key), const_cast<__Type>(_data)); }
      __Type search(const __Key& _key) { return _search(const_cast<__Key&>(_key)); }

      size_type size() { return _get_size(); }

   public:   //   constructor | destructor

      hash_table() : _m_size(0), _m_capacity(__Size), _m_collisions(0), _m_first(NULL), _m_last(NULL) { }

      // destructor automatically provided

   private:   //   helper functions

      bool _contains(__Key& _key)
      {
         if (ev4::is_primitive<__Key>())
         {
            int key;

            if(ev4::is_int<__Key>()) key = const_cast<__Key&>(_key); 

            else key = (int)(const_cast<__Key&>(_key)); 

            size_type hash_value = key;
            unsigned long prime = 131071; // prime number
            hash_value = (prime * (unsigned long)hash_value) % _m_capacity;
            if(_list[hash_value].init == 'T') return true;

            return false;
         }

         else
         {
            size_type hash_value = get_hash_value(_key);
            hash_value = hash_value % _m_capacity;

            if(_list[hash_value].init == 'T') return true;
            
            return false;
         }
      }

      size_type _get_capacity() { return _m_capacity; }
      size_type _get_size() { return _m_size; }

      void _insert(__Key& _key, __Type& _data)
      {
         if (ev4::is_primitive<__Key>())
         {
            int key;

            if(ev4::is_int<__Key>()) key = const_cast<__Key&>(_key); 

            else key = (int)(const_cast<__Key&>(_key)); 

            size_type hash_value = key;
            unsigned long prime = 131071; // prime number
            hash_value = (prime * (unsigned long)hash_value) % _m_capacity;
            _list[hash_value]._key = key;
            _list[hash_value]._data = _data;
            _update(&_list[hash_value]);
         }

         else
         {
            size_type hash_value = get_hash_value(_key);
            hash_value = hash_value % _m_capacity;
            _list[hash_value]._key = _key;
            _list[hash_value]._data = _data;
            _update(&_list[hash_value]);
         }
      }

      __Type _search(__Key& _key)
      {
         if (ev4::is_primitive<__Key>())
         {
            int key;

            if(ev4::is_int<__Key>()) key = const_cast<__Key&>(_key); 

            else key = (int)(const_cast<__Key&>(_key)); 

            size_type hash_value = key;
            unsigned long prime = 131071; // prime number
            hash_value = (prime * (unsigned long)hash_value) % _m_capacity;
            return _list[hash_value]._data;
         }

         else
         {
            size_type hash_value = get_hash_value(_key);
            hash_value = hash_value % _m_capacity;
            return _list[hash_value]._data;
         }
      }

      void _update(_node* _ptr)
      {
         _ptr->init = 'T';
         if (_m_first == NULL) { _m_first = _ptr; _m_last = _ptr; }
         else { _m_last->_next = _ptr; _ptr->_next = NULL; }
      }

};

template<typename __Type> int get_hash_value(__Type& _key) { return __Hash_Value(_key); }

template<> int get_hash_value<int>(int& _key) { return _key; }

template<> int get_hash_value<char>(char& _key) { return _key; }

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   //   End of namespace(ev4)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   //   HASH_TABLE_HPP