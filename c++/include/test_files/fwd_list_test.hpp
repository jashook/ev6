///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: fwd_list_test.hpp
//
// Modifications:
//
// 21-March-13 : Version 1.0: Created
//
// Timeperiod: ev6
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#ifndef __FWD_LIST_TEST_HPP__
#define __FWD_LIST_TEST_HPP__

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <stdexcept>

#include "fwd_list.hpp"
#include "test_helper.hpp"

///////////////////////////////////////////////////////////////////////////////
// global functions
///////////////////////////////////////////////////////////////////////////////

void test_fwd_list();

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {
namespace test {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template < typename __Type > class fwd_list_test
{

   private:   // constants

      const static std::size_t SIZE = 1000;

   private:   // member variables

      ev6::el::fwd_list<int>* _m_list;
      ev6::el::test_helper< std::ostream > _m_helper; 

   public:   // Constructor | Destructor

      array_test() : _m_array(0) { }
      ~array_test() { _tidy(); }

   public:   // overloaded operators

      void operator() () { _test(); }

   private:   // helper functions

      void _create_array() 
      {
         _m_list = new ev6::el::fwd_list<int>();

         std::size_t _Size, _SecondSize;

         std::ifstream _File("input.txt");

         _File >> _Size;

         _File.ignore();
         _File >> _SecondSize;
         _File.ignore();

         for (std::size_t i = 0; i < _Size;  ++i) _File >> _m_array->push_back(i); 

         _File.close();

      }

      bool _created() { return _m_list != 0; }

      void _delete_array() { delete _m_list; }

      void _test()
      {
         
         try
         {
            _test_constructor();
            _test_destructor();
            _test_at();
            _test_begin();
            _test_clear();
            _test_end();
            _test_max_size();
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

         _m_helper.set_title("Test array constructors");
         _m_helper.print_entry(ev6::el::MICROSECONDS);

         if (!_created()) _create_array();

         ev6::el::array< int, 3 > _Array = { 0, 1, 2 };

         _Array.at(1) = 3;

         _m_helper.print_exit();

      }

      void _test_destructor() 
      { 
         _m_helper.set_title("Test array destructor");
         _m_helper.print_entry();

         _tidy();

         _m_helper.print_exit();
      }

      void _test_at()
      { 
         if (!_created()) _create_array();

         _m_helper.set_title("Test array at");
         _m_helper.print_entry();

         try 
         {

            for (std::size_t i = 0, _Size = _m_array->size(); i < _Size; ++i) _m_array->at(i);
   
         }

         catch (std::range_error)
         {
            std::cout << "Range error thrown incorrectly" << std::endl;
         }

         try
         {
            _m_array->at(_m_array->size());
         }
         
         catch (std::range_error)
         {
            std::cout << "Range error thrown correctly" << std::endl;
         }

         _m_helper.print_exit();

      }

      void _test_begin() 
      { 
         _m_helper.set_title("Test array begin");
         _m_helper.print_entry(ev6::el::MICROSECONDS);

         std::vector< int > _Vector;

         for (std::size_t i = 0, _Size = _m_array->size(); i < _Size; ++i) _Vector.push_back(_m_array->at(i));

         std::size_t _ErrorCode;

         if (*_Vector.begin() == *(*_m_array).begin()) _ErrorCode = 0;
         else _ErrorCode = 1;

         _m_helper.print_exit(_ErrorCode);

      }

      void _test_clear() 
      {

         if (!_created()) _create_array();

         std::size_t _ErrorCode = 0;

         _m_helper.set_title("Test array clear");
         _m_helper.print_entry();

         _m_array->clear();

         std::cout << "_m_array: " << _m_array->size() << std::endl;

         try 
         {
         
            if (_m_array->at(1) != 0) _ErrorCode = 1;   

         }

         catch (std::range_error)
         {
            std::cout << "Range error thrown incorrectly" << std::endl;
         }

         _m_helper.print_exit(_ErrorCode);

      }

      void _test_end() 
      { 
         
         _m_helper.set_title("Test array end");
         _m_helper.print_entry(ev6::el::MICROSECONDS);

         std::vector< int > _Vector;

         for (std::size_t i = 0, _Size = _m_array->size(); i < _Size; ++i) _Vector.push_back(_m_array->at(i));

         std::size_t _ErrorCode;

         if (*_Vector.end() == *(*_m_array).end()) _ErrorCode = 0;
         else _ErrorCode = 1;

         _m_helper.print_exit(_ErrorCode);

      }

      void _test_max_size() 
      { 

         _m_helper.set_title("Test array max size");
         _m_helper.print_entry();
         
         std::size_t _ErrorCode = 0;
         if (_m_array->size() != 1000) _ErrorCode = 1;

         _m_helper.print_exit(_ErrorCode);

      }

      void _test_to_c_array() 
      {

         _m_helper.set_title("Test array to c array");
         _m_helper.print_entry(ev6::el::MICROSECONDS);

         std::size_t _ErrorCode = 0;

         int* _Array = _m_array->to_c_array();

         _Array[0] = 10;

         _m_helper.print_exit(_ErrorCode);
 
      }

      void _tidy() 
      { 

         if (_created())
         {

            _delete_array();

            _m_array = 0;

         }

      }

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
