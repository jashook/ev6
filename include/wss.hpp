////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        wss
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __WSS_HPP__
#define __WSS_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <string>

#include "array.hpp"
#include "vector.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {
namespace wss {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<typename __Container> inline ev4::vector<std::string*>* char_to_string(__Container& _Container, std::size_t _Size)
{
   ev4::vector<std::string*>* _Strings = new ev4::vector<std::string*>();

   std::size_t _Strings_Position = 0;

   std::string* _String = new std::string();

   for (std::size_t i = 0; i < _Size; ++i)
   {
      char _At = _Container[i];

      if (is_valid_char(_At))
      {
         if (!is_space(_At))
         {
            (*_String) += _At;
         }

         else
         {
            _Strings->push_back(_String);
            _String = new std::string();
         }
      }
   }

   _Strings->push_back(_String);

   return _Strings;
}

template<typename __String> inline ev4::vector<__String*>* file_to_strs(__String* _String)
{
   ev4::vector<__String*>* _Strings = new ev4::vector<__String*>();

   __String* _Temp = new __String();

   for (std::size_t i = 0; i < _String->size(); ++i)
   {
      char _At = (*_String).at(i);
      if (is_valid_char(_At))
      {
         if (!is_space(_At))
         {
            (*_Temp) += _At;
         }

         else
         {
            _Strings->push_back(_Temp);
            _Temp = new std::string();
         }
      }
   }

   return _Strings;
}

template< typename __Container> inline ev4::vector<std::string*>* str_line_to_str(__Container* _Container, std::size_t _Size)
{
   ev4::vector<std::string*>* _Strings = new ev4::vector<std::string*>();

   std::string* _String = new std::string();

   for (std::size_t i = 0; i < _Size; ++i)
   {
      const char* _Array = (*(*(*_Container))[i]).c_str();
      for (std::size_t i = 0; i < (*(*(*_Container))[i]).size(); ++i)
      {
         if (is_valid_char(_Array[i]))
         {
            _String->operator+=(_Array[i]);
         }
      }

      _Strings->push_back(_String);
      _String = new std::string();
   }

   _Strings->push_back(_String);

   return _Strings;
}

inline bool is_space(char _Char)
{
   if (static_cast<std::size_t>(_Char) == 32) return true;

   return false;
}

inline bool is_valid_char(char _Char)
{
   if (static_cast<std::size_t>(_Char) >= 32 && static_cast<std::size_t>(_Char) <= 127) return true;

   if (static_cast<std::size_t>(_Char) == 0) return true;

   return false;
}

inline std::size_t to_hash_value(std::string& _String, std::size_t _Size)
{
   std::size_t _Hash = 0;

   std::size_t _Key = 1031;  // Random Number

   for (std::size_t i = 0; i < _Size; ++i)
   {
      _Hash += (static_cast<std::size_t>(_String.at(i)) * _Key);
   }

   return _Hash;
}

inline std::size_t to_hash_value(const char* _String, std::size_t _Size)
{
   std::size_t _Hash = 0;

   for (std::size_t i = 0; i < _Size; ++i)
   {
      _Hash += static_cast<std::size_t>(_String[i]);
   }

   return _Hash;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)
}   // end namespace(wss)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __WSS_HPP__