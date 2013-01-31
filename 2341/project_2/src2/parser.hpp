////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: Parser
//
// Modifications: 6-Sept-12 - Created
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __PARSER_HPP__
#define __PARSER_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>

#include "string.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace LAB {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<void *(__Function)(std::ifstream&)> class parser
{

private:   // member variables

   char* _m_buffer;

   std::ifstream _m_file;

   ev4::string<>* _m_filename;

private: // member operators

   parser& operator=(const parser&);
   bool operator<(const parser&);
   bool operator>(const parser&);
   bool operator==(const parser&);
   bool operator!=(const parser&);

public:   // member functions

   void parse() { _parse(); }

public:   // constructor | destructor

   parser() : _m_filename(0) { _ctor(); }

   parser(ev4::string<>& _FileName, std::size_t _BufferSize = 81) : _m_filename(0) { _ctor(_FileName, _BufferSize); }

   ~parser() { _dtor(); }

private:  // private constructors

   parser(const parser&);

private:   // helper functions

   void ctor()
   {
      _m_buffer = new char[81]; // if buffer length is not supplied then max is 80 characters
   }

   void _ctor(ev4::string<>& _FileName, std::size_t _BufferSize)
   {
      _m_buffer = new char[_BufferSize];
      _m_filename = new ev4::string<>(_FileName);

      _m_file.open(_FileName.c_str());
   }

   void _dtor()
   {
      delete [] _m_buffer;
      if (_m_filename == 0)delete _m_filename;

      // ifstream closes file in destructor
      // implicite close of file
   }

   void _parse()
   {
      __Function(_m_file);
   }

}; // end of class(parser)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} // end of namespace(LAB)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif // __PARSER_HPP__
