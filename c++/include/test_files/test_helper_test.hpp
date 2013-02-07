///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: test_helper_test.hpp
//
// Modifications:
//
// 2-Feb-13 : Version 1.0: Created
//
// Timeperiod: ev6
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#ifndef __TEST_HELPER_TEST_HPP__
#define __TEST_HELPER_TEST_HPP__

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

#include "test_helper.hpp"

///////////////////////////////////////////////////////////////////////////////
// global functions
///////////////////////////////////////////////////////////////////////////////

void test_helper_test();

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {
namespace test {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class test_helper_test
{

   private:   // member variables

      ev6::el::test_helper< std::ostream >* _m_test_helper;
 
   public:   // Constructor | Destructor

      test_helper_test() : _m_test_helper(0) { }
      ~test_helper_test() { _tidy(); }

   public:   // overloaded operators

      void operator() () { _test(); }

   private:   // helper functions

      void _create() { _m_test_helper = new ev6::el::test_helper< std::ostream >(); }

      bool _created() { return _m_test_helper != 0; }

      void _delete() { delete _m_test_helper; _m_test_helper = 0; }

      void _test()
      {
         
         try
         {
            _test_constructor();
            _test_destructor();
            _test_message();
         }

         catch( std::exception& _Exception )
         {
            std::cout << "Exception thrown...  Exiting the program." << std::endl;

            return;
         }

      }

      void _test_constructor() 
      {

         if (!_created()) _create();
         
         _tidy();
         
         _m_test_helper = new ev6::el::test_helper< std::ostream >("Test");
   
         _m_test_helper->print_entry();
         _m_test_helper->print_exit();

         _tidy();

         char _Title[80];

         std::strcpy(_Title, "Test2");

         _m_test_helper = new ev6::el::test_helper< std::ostream >(_Title);
   
         _m_test_helper->print_entry();
         _m_test_helper->print_exit();

         _tidy();

         std::string _String = "Test3";

         _m_test_helper = new ev6::el::test_helper< std::ostream >(_String);
   
         _m_test_helper->print_entry();
         _m_test_helper->print_exit();

         _tidy();

         _m_test_helper = new ev6::el::test_helper< std::ostream >("Test4", std::cout);
   
         _m_test_helper->print_entry();
         _m_test_helper->print_exit();

         _tidy();

         std::strcpy(_Title, "Test5");

         _m_test_helper = new ev6::el::test_helper< std::ostream >(_Title, std::cout);
   
         _m_test_helper->print_entry();
         _m_test_helper->print_exit();

         _tidy();

         _String = "Test6";

         _m_test_helper = new ev6::el::test_helper< std::ostream >(_String, std::cout);
   
         _m_test_helper->print_entry();
         _m_test_helper->print_exit();

         _tidy();

      }

      void _test_destructor() { _tidy(); }

      void _test_message()
      {
         if (!_created()) _create();

         _m_test_helper->set_title("Testing messages");

         char _CString[80];

         std::strcpy(_CString, "Testing c string message");

         std::string _String = "Testing string message";

         _m_test_helper->set_spec(ev6::el::MICROSECONDS);

         _m_test_helper->print_entry("Testing const char* message");
         _m_test_helper->print_exit("Testing const char* message");

         _m_test_helper->set_spec(ev6::el::MILLISECONDS);

         _m_test_helper->print_entry(_CString);
         _m_test_helper->print_exit(_CString);

         _m_test_helper->set_spec(ev6::el::SECONDS);

         _m_test_helper->print_entry(_String);
         _m_test_helper->print_exit(_String);
      }
      
      void _tidy() { if (_created()) _delete(); }

};   // end of class test_helper_test

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

}   // end of namespace test
}   // end of namespace el
}   // end of namespace ev6

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void test_helper_test() { ev6::el::test::test_helper_test _Test; _Test(); }

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#endif   // __TEST_HELPER_TEST_HPP__
