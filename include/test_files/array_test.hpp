///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: array_test.hpp
//
// Modifications:
//
// 17-Jan-12 : Version 1.0: Created
//
// Timeperiod: ev6
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#ifndef __ARRAY_TEST_HPP__
#define __ARRAY_TEST_HPP__

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <stdexcept>

#include "array.hpp"

///////////////////////////////////////////////////////////////////////////////
// global functions
///////////////////////////////////////////////////////////////////////////////

void test_array();

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {
namespace test {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template < typename __Type > class array_test
{

   private:   // constants

      const static std::size_t SIZE = 1000;

   private:   // member variables

      ev6::el::array< int, SIZE >* _m_array;
 
   public:   // Constructor | Destructor

      array_test() : _m_array(0) { }
      ~array_test() { _tidy(); }

   public:   // overloaded operators

      void operator() () { _test(); }

   private:   // helper functions

      void _create_array() { _m_array = new ev6::el::array< int, SIZE >(); }

      bool _created() { return _m_array != 0; }

      void _delete_array() { delete _m_array; }

      void _test()
      {
         
         try
         {
            _test_constructor();
            _test_destructor();
            _test_at();
            _test_begin();
            _test_clear();
            _test_empty();
            _test_end();
            _test_max_size();
            _test_size();
            _test_to_c_array();
         }
         catch( std::exception& _Exception )
         {
            std::cout << "Exception thrown...  Exiting the program." << std::endl;

            return;
         }

      }

      void _test_constructor() 
      {

         if (!_created()) _create_array();

         ev6::el::array< int, 3 > _Array = { 0, 1, 2 };

      }

      void _test_destructor() { }
      void _test_at() { }
      void _test_begin() { }
      void _test_clear() { }
      void _test_empty() { }
      void _test_end() { }
      void _test_max_size() { }
      void _test_size() { }
      void _test_to_c_array() { }

      void _tidy() { if (_created()) _delete_array(); }

};   // end of class array_test

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

}   // end of namespace test
}   // end of namespace el
}   // end of namespace ev6

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void test_array() { ev6::el::test::array_test<int> _Test; _Test(); }

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#endif   // __ARRAY_TESTER__
