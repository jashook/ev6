////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: logger.hpp
//
// Modifications: 
//
// 24-Jan-13: Version 2.0: Cleaned and changed to different streams
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef  __LOGGER_HPP__
#define __LOGGER_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template< typename __Stream > class logger
{
   private: // member variables

      __Stream& _m_output_stream;

   public:   // member functions

      void endl() { _endl(); }

   public:   // member operators

      template <typename __Type> void operator<<(__Type& _Input) { _m_output_stream << _Input; }

   public:   // constructor | destructor
 
      logger(__Stream& _Stream) : _m_output_stream(_Stream) { }

      ~logger() { _dtor(); }

   private:   // helper functions

      void _ctor()
      {

      }

      void _dtor()
      {

      }

      void _endl() { _m_output_stream << std::endl; }

};   // end of class logger

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace(el)
}   // end of namespace(ev6)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __LOGGER_HPP__
