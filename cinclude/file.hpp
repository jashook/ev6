////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Module:        file
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __FILE_HPP__
#define __FILE_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <string>

#include "file_reader.hpp"
#include "vector.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev4 {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class file
{
   private:   // member variables

      std::string _m_path;
      std::string _m_file_name;

   public:   // member functions

      ev4::vector<char>* read(std::string* _Start = 0, std::string* _Ignore = 0) { return _read(_Start, _Ignore); }
      std::string* read_by_copy() { return _read_by_copy(); }
      ev4::vector<std::string*>* read_by_line() { return _read_by_line(); }
      void set_file_name(std::string& _File_Name) { _set_file_name(_File_Name); }
      void set_file_name(const char* _File_Name) { _set_file_name(_File_Name); }
      void set_path(std::string& _Path) { _set_path(_Path); }
      void set_path(const char* _Path) { _set_path(_Path); }

   public:   // constructor | destructor

      file() { }
      file(std::string& _Path, std::string& _File_Name, const std::size_t _Size) : _m_path(_Path), _m_file_name(_File_Name) { }
      file(const char* _Path, const char* _File_Name) { _ctor(_Path, _File_Name); }

      ~file() { }

   private:   // helper functions

      void _ctor(const char* _Path, const char* _File_Name) { _m_file_name = _File_Name; _m_path = _Path; _m_path.append("\\"); _m_path.append(_m_file_name); }
      ev4::vector<char>* _read(std::string* _Start = 0, std::string* _Ignore = 0) { file_reader fr(_m_path.c_str()); return fr.read(_Start, _Ignore); }
      std::string* _read_by_copy() { file_reader fr(_m_path.c_str()); return fr.read_by_copy(); }
      ev4::vector<std::string*>* _read_by_line() { file_reader fr(_m_path.c_str()); return fr.read_by_line(); }
      void _set_file_name(std::string& _File_Name) { _m_file_name = _File_Name; }
      void _set_file_name(const char* _File_Name) { _m_file_name = _File_Name; }
      void _set_path(std::string& _Path) { _m_path = _Path; }
      void _set_path(const char* _Path) { _m_path = _Path; }

};   // end of class file

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end namespace(ev4)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __FILE_HPP__