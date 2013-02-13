///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: avl_tree_test.hpp
//
// Modifications:
//
// 17-Jan-12 : Version 1.0: Created
//
// Timeperiod: ev6
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#ifndef __AVL_TREE_TEST_HPP__
#define __AVL_TREE_TEST_HPP__

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "avl_tree.hpp"
#include "test_helper.hpp"

///////////////////////////////////////////////////////////////////////////////
// global functions
///////////////////////////////////////////////////////////////////////////////

void test_avl_tree();

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {
namespace test {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template < typename __Type > class avl_tree_test
{

   private:   // constants

      const static std::size_t SIZE = 1000;

   private:   // member variables

      ev6::el::array< int, SIZE >* _m_array;
      ev6::el::avl_tree< int >* _m_tree;
      ev6::el::test_helper< std::ostream > _m_helper; 

   public:   // Constructor | Destructor

      avl_tree_test() : _m_tree(0) { }
      ~avl_tree_test() { _tidy(); }

   public:   // overloaded operators

      void operator() () { _test(); }

   private:   // helper functions

      void _create_avl_tree() 
      {
         _m_tree = new ev6::el::avl_tree< int >();
         _m_array = new ev6::el::array< int, SIZE >();

         std::size_t _Size, _SecondSize;

         std::ifstream _File("input.txt");

         _File >> _Size;

         _File.ignore();
         _File >> _SecondSize;
         _File.ignore();

         for (std::size_t i = 0; i < _Size;  ++i)
         {

            std::size_t _Integer;

            _File >> _Integer;

            _m_tree->insert(_Integer);
            _m_array->at(i) = _Integer;

         }

         _File.close();

      }   

      bool _created() { return _m_tree != 0; }

      void _delete_avl_tree() { delete _m_tree; }

      void _test()
      {
         
         try
         {
            _test_constructor();
            _test_destructor();
            _test_begin();
            _test_contains();
            _test_end();
            _test_insert();
            _test_print_breadth_first_iteration();
            _test_search();
         }
         catch( std::exception& _Exception )
         {
            std::cout << "Exception thrown...  Exiting the program." << std::endl;

            return;
         }

      }

      void _test_constructor() 
      {

         _m_helper.set_title("Test avl_tree constructors");
         _m_helper.print_entry(ev6::el::MICROSECONDS);

         if (!_created()) _create_avl_tree();

         ev6::el::avl_tree< int > _Tree;

         _Tree.insert(3);

         _m_helper.print_exit();

      }

      void _test_destructor() 
      { 
         _m_helper.set_title("Test avl_tree destructor");
         _m_helper.print_entry();

         _tidy();

         _m_helper.print_exit();
      }

      void _test_begin() 
      {
   
         if (!_created()) _create_avl_tree();
         
         _m_helper.set_title("Test avl_tree begin");
         _m_helper.print_entry(ev6::el::MICROSECONDS);

         if (!_created()) _create_avl_tree();

         std::vector< int > _Vector;

         for (std::size_t i = 0, _Size = _m_array->size(); i < _Size; ++i) _Vector.push_back(_m_array->at(i));

         std::cout << "End: " << *(_Vector.end()) << std::endl;

         std::sort(_Vector.begin(), _Vector.end());

         for (std::size_t i = 0, _Size = _m_array->size(); i < _Size; ++i) std::cout << _Vector.at(i) << " ";

         std::cout << std::endl;

         std::size_t _ErrorCode;

         std::cout << "End: " << *(_Vector.end()) << std::endl;

         if (*_Vector.begin() == *(*_m_tree).begin()) _ErrorCode = 0;
         else _ErrorCode = 1;

         _m_helper.print_exit(_ErrorCode);

      }

      void _test_end() 
      { 
         
         if (!_created()) _create_avl_tree();
         
         _m_helper.set_title("Test avl_tree end");
         _m_helper.print_entry(ev6::el::MICROSECONDS);

         avl_tree<int>::iterator _Iterator = _m_tree->begin();

         std::size_t _Count = 0, _ErrorCode = 0;

         while (_Iterator != _m_tree->end())
         {
            std::cout << *_Iterator++ << " ";
            ++_Count;
         }

         std::cout << "Size: " << _Count << std::endl;

         if (_Count == SIZE) _ErrorCode = 0;
         else _ErrorCode = 1;

         _m_helper.print_exit(_ErrorCode);

      }

      void _test_contains()
      {

      }

      void _test_insert()
      {

      }
      
      void  _test_print_breadth_first_iteration()
      {

      }
      
      void _test_search()
      {

      }

      void _tidy() 
      { 

         if (_created())
         {

            _delete_avl_tree();

            _m_tree = 0;

         }

      }

};   // end of class avl_tree_test

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

}   // end of namespace test
}   // end of namespace el
}   // end of namespace ev6

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void test_avl_tree() { ev6::el::test::avl_tree_test<int> _Test; _Test(); }

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#endif   // __AVL_TREE_TESTER__
