////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        file_reader
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __FILE_READER_HPP__
#define __FILE_READER_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <vector>

#include "base.hpp"
#include "iter.hpp"
#include "vector.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class file_reader
{
   public:   // type definitions and constants

      static const std::size_t SIZE = 1024;

   private:   // private type definitions

   private:   // member variables

      const char* _m_file_name;

   public:   // member functions

      vector<char>* read(std::string* _Start = 0, std::string* _Ignore = 0) { return _read(_Start, _Ignore); }
      std::string* read_by_copy() { return _read_by_copy(); }
      vector<std::string*>* read_by_line() { return _read_by_line(); }

      void set_file_name(const char* _FileName) { _set_file_name(_FileName); }

   public:   // constructor | destructor

      file_reader(const char* _FileName) : _m_file_name(_FileName) { _ctor(); }
      file_reader() { }

      ~file_reader() { }

   private:   // helper functions

      void _ctor() 
      { 
         assert(_m_file_name != NULL); 
      }

      void _dtor() { assert(_m_file_name != NULL); }

      vector<char>* _read(std::string* _Start = 0, std::string* _Ignore = 0)
      {
         std::ifstream in(_m_file_name);

         vector<char>* list = new vector<char>(SIZE);

         char temp;

         do
         {
            temp = in.get();
            if (!in.eof()) list->push_back(temp);
         } while (!in.eof());

         return list;
      }

      std::string* _read_by_copy()
      {
         std::ifstream in(_m_file_name);

         std::string* _String = new std::string();

         const char _Delim = EOF;

         std::getline(in, *_String, _Delim);

         return _String;
      }

      vector<std::string*>* _read_by_line()
      {
         std::ifstream in(_m_file_name);

         vector<std::string*>* _List = new vector<std::string*>(SIZE);

         std::string* _Temp;

         do
         {
            _Temp = new std::string();
            std::getline(in, *_Temp, '\n');
            _List->push_back(_Temp);
         } while (!in.eof());

         return _List;
      }

      void _set_file_name(const char* _FileName) { _m_file_name = _FileName; }

};   // end of class file_reader

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __FILE_READER_HPP__