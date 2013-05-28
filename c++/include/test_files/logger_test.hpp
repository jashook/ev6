///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: logger_test.hpp
//
// Modifications:
//
// 24-Jan-12 : Version 1.0: Created
//
// Timeperiod: ev6
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#ifndef __LOGGER_TEST_HPP__
#define __LOGGER_TEST_HPP__

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <stdexcept>

#include "logger.hpp"
#include "test_helper.hpp"

///////////////////////////////////////////////////////////////////////////////
// global functions
///////////////////////////////////////////////////////////////////////////////

void test_logger();

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {
namespace test {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class logger_test
{

   private:   // member variables

      ev6::el::logger< std::ostream >* _m_logger;
      ev6::el::test_helper< std::ostream > _m_helper;
 
   public:   // Constructor | Destructor

      logger_test() : _m_logger(0) { }
      ~logger_test() { _tidy(); }

   public:   // overloaded operators

      void operator() () { _test(); }

   private:   // helper functions

      void _create_logger() { _m_logger = new ev6::el::logger< std::ostream >(std::cout); }

      bool _created() { return _m_logger != 0; }

      void _delete_logger() { delete _m_logger; _m_logger = 0; }

      void _test()
      {
         
         try
         {
            _test_constructor();
            _test_destructor();
            _test_write();
         }

         catch( std::exception& _Exception )
         {
            std::cout << "Exception thrown...  Exiting the program." << std::endl;

            return;
         }

      }

      void _test_constructor() 
      {

         _m_helper.set_title("Test logger constructor");
         _m_helper.print_entry();

         if (!_created()) _create_logger();

         _m_helper.print_exit();

      }

      void _test_destructor()
      { 
   
         _m_helper.set_title("Test logger destructor");
         _m_helper.print_entry();

         _tidy();

         _m_helper.print_exit();

      }
      
      void _test_write() 
      { 

         _m_helper.set_title("Test logger write");
         _m_helper.print_entry(ev6::el::MICROSECONDS);

         if (!_created()) _create_logger();

         (*_m_logger).operator<<("Hello this should log this sentence");

         _m_logger->endl();

         std::ofstream _File("output.txt");

         ev6::el::logger< std::ofstream > _Logger(_File);

         _Logger << "Hello this should log this sentence";

         _Logger.endl();

         _File.close();

         _m_helper.print_exit();

      }
   
      void _tidy() { if (_created()) _delete_logger(); }

};   // end of class logger_test

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

}   // end of namespace test
}   // end of namespace el
}   // end of namespace ev6

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void test_logger() { ev6::el::test::logger_test _Test; _Test(); }

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#endif   // __LOGGER_TEST_HPP__
