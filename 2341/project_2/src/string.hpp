////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        string
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef STRING_HPP
#define STRING_HPP

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <cstring>
#include <iostream>
#include <string>

#include "array_iter.hpp"
#include "vector.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
    
template<typename __Container = ev4::vector<char> > class string
{
   private:   // member variables

      __Container* _m_container;
      std::size_t _m_size;

   public:   // overloaded operators

      void operator+=(const string& _Rhs) { _add(_Rhs); }
      string& operator=(const string& _Rhs) { if (*this != _Rhs)_ctor(); _copy(_Rhs); }     
      bool operator==(const string& _Rhs) { return _equal(_Rhs); }
      bool operator!=(const string& _Rhs) { return !_equal(_Rhs); }
      bool operator<(const string& _Rhs) { return _less_than(_Rhs); }
      bool operator>(const string& _Rhs) { return !_less_than(_Rhs); }

      friend std::ostream&  operator<<(std::ostream& _Out, const string& _Rhs) { return _Rhs._print(_Out); }

   public:   // member functions
   
      char at(std::size_t _Index) const { return _at(_Index); }
      void add(char _Char) { _add(_Char); }
      void add(const char* _String) { _add(_String); }
      void add(char* _String) { _add(static_cast< const char* >(_String)); }
      void add(const string& _String) { _add(_String); }
      void clear() { _clear(); }
      char* c_str() { return _c_str(); }
      std::size_t size() const { return _size(); }

   public:   // constructor | destructor

      string() : _m_size(0), _m_container(0) { _ctor(); }

      string(char* _String) : _m_size(0), _m_container(0) { _ctor(_String); }

      string(const char* _String) : _m_size(0), _m_container(0) { _ctor(const_cast< char* >(_String)); }

      string(std::string _String) : _m_size(0), _m_container(0) { _ctor(_String.c_str()); }

      ~string() { _dtor(); }

   private:   // helper functions

      char _at(std::size_t _Index) const
      {
         return (*_m_container)[_Index];
      }

      void _add(char _Char)
      {
         _m_container->push_back(_Char);
      }

      void _add(const char* _String)
      {
         std::size_t _Index = 0;

         while (_String[_Index] != 0) _m_container->push_back(_String[_Index]);
      }

      void _add(const string& _Rhs)
      {
         _m_size += _Rhs.size();

         *_m_container += *_Rhs._m_container;
      }

      void _clear()
      {
         _m_container->clear();
      }

      char* _c_str()
      {
         return _m_container->data();
      }

      void _copy(const string& _Rhs)
      {
         if (_m_container != 0) *_m_container = *_Rhs._m_container;
         
         _m_size = _Rhs._m_size;
      }

      void _ctor(char* _String = 0) 
      { 
         _m_container = new __Container();

         if (_String == 0) return; // if no string is passed then exit the function

         std::size_t _Len = std::strlen(_String);

         for (std::size_t i = 0; i < _Len; ++i) _m_container->push_back(_String[i]);

      }

      void _dtor(){ delete _m_container; }

      bool _equal(const string& _Rhs)
      {
         bool _Result = true;

         for (std::size_t i = 0; ((i < _m_container->size()) || i < _Rhs.size()); ++i) if ((*_m_container)[i] == _Rhs.at(i)) { _Result = false; break; }
        
         return _Result;

      }

      bool _less_than(const string& _Rhs)
      {
         bool _Result = true;

         for (std::size_t i = 0; ((i < _m_container->size()) || i < _Rhs.size()); ++i) if ((*_m_container)[i] > _Rhs.at(i)) { _Result = false; break; }

         if (_Result == false && _Rhs.size() > size()) return true; // account for one string being smaller than the other

         return _Result;
      }

      std::ostream& _print(std::ostream& _Out) const
      {
         for (std::size_t i = 0; i < _m_container->size(); ++i) _Out << at(i);

	 return _Out;
      }

      std::size_t _size() const { return _m_container->size(); }
};
    
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace(ev4)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif /* STRING_HPP */
