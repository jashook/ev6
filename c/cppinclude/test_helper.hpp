////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: test_helper.hpp
//
// Modifications:
//
// 2-Feb-13 : Version 1.0: Created
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __TEST_HELPER_HPP__
#define __TEST_HELPER_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstring>
#include <queue>
#include <string>

#include "hr_timer.hpp"
#include "logger.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

enum TIME_SPECS { NANOSECONDS, MICROSECONDS, MILLISECONDS, SECONDS };

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template< typename __Stream > class test_helper
{
   private:   // member variables

      ev6::el::hr_timer _m_timer;
      ev6::el::logger< __Stream > _m_logger;
      std::queue< std::pair< std::string, std::size_t > > _m_processes;
      std::size_t _m_return_value;
      std::string _m_name;
      TIME_SPECS _m_spec;

   public:   // member functions

      void print_entry(TIME_SPECS _Spec) { _print_entry(0, _Spec); }
      void print_entry(char* _Message = 0, TIME_SPECS _Spec = NANOSECONDS) { _print_entry(_Message, _Spec); }
      void print_entry(const char* _Title, const char* _Message = 0, TIME_SPECS _Spec = NANOSECONDS) { _print_entry(const_cast< char* >(_Message), _Spec); }
      void print_entry(std::string& _Message, TIME_SPECS _Spec = NANOSECONDS) { _print_entry(const_cast< char* >(_Message.c_str()), _Spec); }
      void print_exit(char* _Message = 0) { _print_exit(_Message); }
      void print_exit(std::size_t _ErrorCode) { _print_exit(0, _ErrorCode); }
      void print_exit(const char* _Message) { _print_exit(const_cast< char* >(_Message)); }
      void print_exit(std::string& _Message) { _print_exit(const_cast< char* >(_Message.c_str())); }

      void set_spec(TIME_SPECS _Spec) { _set_spec(_Spec); }

      void set_title(char* _Title) { _set_title(_Title); }
      void set_title(const char* _Title) { _set_title(const_cast< char* >(_Title)); }
      void set_title(std::string& _Title) { _set_title(_Title.c_str()); }

      void set_stream(__Stream& _Stream) { _set_stream(_Stream); }

   public:   // constructor | destructor
   
      test_helper() : _m_name(""), _m_spec(NANOSECONDS) { _ctor(); }
      test_helper(char* _Title) : _m_name(_Title), _m_spec(NANOSECONDS) { _ctor(); }
      test_helper(const char* _Title) : _m_name(const_cast< char* >(_Title)), _m_spec(NANOSECONDS) { _ctor(); }
      test_helper(std::string& _Title) : _m_name(_Title), _m_spec(NANOSECONDS) { _ctor(); }
      test_helper(char* _Title, __Stream& _Stream, TIME_SPECS _Spec = NANOSECONDS) : _m_name(_Title), _m_logger(_Stream), _m_spec(_Spec) { _ctor(); }
      test_helper(const char* _Title, __Stream& _Stream) : _m_name(const_cast< char* >(_Title)), _m_logger(_Stream), _m_spec(NANOSECONDS) { _ctor(); }
      test_helper(std::string& _Title, __Stream& _Stream) : _m_name(_Title), _m_logger(_Stream), _m_spec(NANOSECONDS) { _ctor(); }

      ~test_helper() { _dtor(); }

   private:   // helper functions

      void _ctor()
      {
         _m_return_value = 0;  // default return value is a success
      }

      void _dtor()
      {
         if (_m_name != "") _m_processes.push(std::pair< std::string, std::size_t >(_m_name, _m_return_value)); 

         _m_return_value = 0;

         if (_m_processes.size() != 0)
         {

            _m_logger.endl();

            for (std::size_t i = 0, _Size = _m_processes.size(); i < _Size; ++i)
            {
   
               std::string _Process = _m_processes.front().first;
               std::size_t _ErrorCode = _m_processes.front().second;\

               _m_processes.pop();

               _m_logger << _Process;

               _m_logger << ": ";

               if (_ErrorCode == 0) _m_logger << "Passed";
               else _m_logger << "Failed";

               _m_logger.endl();

            }

            _m_logger.endl(2);
            
         }
      }

      std::pair< long long, std::string > _get_time()
      {

         std::pair < long long, std::string > _Pair;
        
         switch(_m_spec)
         {

            case NANOSECONDS:
      
               _Pair.first = _m_timer.duration_as_nanoseconds();
               _Pair.second = "nanoseconds";
               break;

            case MICROSECONDS:

               _Pair.first = _m_timer.duration_as_microseconds();
               _Pair.second = "microseconds";
               break;

            case MILLISECONDS:

               _Pair.first = _m_timer.duration_as_milliseconds();
               _Pair.second = "milliseconds";
               break;
         
            case SECONDS:

               _Pair.first = _m_timer.duration_as_milliseconds();
               _Pair.second = "seconds";
               break;

         }

         return _Pair;

      }

      void _print_entry(char* _Message = 0, TIME_SPECS _Spec = NANOSECONDS)
      {
         _set_spec(_Spec);

         _m_logger << "////////////////////////////////////////////////////////////////////////////////";
         
         _m_logger.endl();

         _m_logger << "Begin test: ";

         _m_logger << _m_name;

         _m_logger.endl();

         if (_Message != 0) { _m_logger << "Notes: "; _m_logger << _Message; _m_logger.endl(); }

         _m_logger << "////////////////////////////////////////////////////////////////////////////////";
         
         _m_logger.endl(2);

         _m_timer.start();

      }

      void _print_exit(char* _Message = 0, std::size_t _ErrorCode = 0)
      {
         _m_return_value = _ErrorCode;

         _m_timer.stop();

         _m_logger.endl();
   
        _m_logger << "////////////////////////////////////////////////////////////////////////////////";
         
         _m_logger.endl();

         _m_logger << "End test: ";

         _m_logger << _m_name;

         _m_logger.endl();

         if (_Message != 0) { _m_logger << "Notes: "; _m_logger << _Message; _m_logger.endl(); }

         _m_logger.endl();

         if (_ErrorCode == 0) _m_logger << "Passed: ";

         else _m_logger << "Failed: ";

         _m_logger << "Time taken to execute: ";

         long long _Time = _get_time().first;

         std::string _TimeString = _get_time().second;

         _m_logger << _Time;

         _m_logger << " ";

         _m_logger << _TimeString;

         _m_logger.endl();

         _m_logger << "////////////////////////////////////////////////////////////////////////////////";
  
         _m_logger.endl(2);

      }

      void _set_spec(TIME_SPECS _Spec) { _m_spec = _Spec; }
      void _set_stream(__Stream& _Stream) { _m_logger.set_stream(_Stream); }
      void _set_title(char* _Title) 
      {
 
         if (_m_name != "") _m_processes.push(std::pair< std::string, std::size_t >(_m_name, _m_return_value)); 

         _m_name = _Title; 

         _m_return_value = 0; 

      }

};   // end of class test_helper

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace(el)
}   // end of namespace(ev6)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __TEST_HELPER_HPP__
