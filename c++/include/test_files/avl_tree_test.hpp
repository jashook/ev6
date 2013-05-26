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
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

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

      void _delete_avl_tree() { delete _m_tree; delete _m_array; }

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

         std::sort(_Vector.begin(), _Vector.end());

         for (std::size_t i = 0, _Size = _m_array->size(); i < _Size; ++i) std::cout << _Vector.at(i) << " ";

         std::size_t _ErrorCode;

         if (*_Vector.begin() == *(*_m_tree).begin()) _ErrorCode = 0;
         else _ErrorCode = 1;

         _m_helper.print_exit(_ErrorCode);

      }

      void _test_end() 
      { 
         
         if (!_created()) _create_avl_tree();
         
         _m_helper.set_title("Test avl_tree end");
         _m_helper.print_entry(ev6::el::MICROSECONDS);

         std::vector<int> _Vector;

         for (std::size_t i = 0; i < _m_array->size(); ++i)
         {

            bool _Found = false;

            for (std::size_t j = 0; j < _Vector.size(); ++j)
            {

               if (_Vector[j] == _m_array->at(i)) 
               {

                  _Found = true;

                  break;

               }

            }

            if (!_Found) _Vector.push_back(_m_array->at(i));

         }

         avl_tree<int>::iterator _Iterator = _m_tree->begin();

         std::size_t _Count = 0, _ErrorCode = 0;

         while (_Iterator != _m_tree->end())
         {
            std::cout << *_Iterator++ << " ";
            ++_Count;
         }

         std::cout << "Size: " << _Count << std::endl;

         if (_Count == _Vector.size()) _ErrorCode = 0;
         else _ErrorCode = 1;

         _m_helper.print_exit(_ErrorCode);

      }

      void _test_contains()
      {   
         if (!_created()) _create_avl_tree();
         
         _m_helper.set_title("Test avl_tree contains");
         _m_helper.print_entry(ev6::el::MICROSECONDS);

         bool _Contains = 0, _ErrorCode = 0;

         if (!_m_tree->contains(_m_array->at(445))) _ErrorCode = 1;

         _m_helper.print_exit(_ErrorCode);
      }

      void _test_insert()
      {

         if (!_created()) _create_avl_tree();
         
         std::size_t _ErrorCode = 0;           

         _m_helper.set_title("Test avl_tree insert");
         _m_helper.print_entry(ev6::el::MICROSECONDS);

         ev6::el::avl_tree< std::string, int > _StringTree;

         std::string _String = "Jar";
         std::string _StringTwo = "El";

         int _Data = 100, _Data2 = 200, _Data3 = 300;

         _StringTree.insert(_String, _Data);
         _StringTree.insert(_StringTwo, 45);

         std::cout << "String Tree: " << std::endl;

         ev6::el::avl_tree< std::string, int >::iterator _It, _End;

         _It = _StringTree.begin();
         _End = _StringTree.end();

         while (_It != _End)
         {
            std::cout << *_It++ << " ";
         }

         std::cout << std::endl;

         ev6::el::avl_tree< int, char* > _CharString;

         char _Arr[80], _Arr2[80];
         std::strcpy(_Arr, "Jarret");
         std::strcpy(_Arr2, "Jarret2");

         const char* _El = "Elena";

         _CharString.insert(45, _Arr);
         _CharString.insert(46, _Arr2);
         _CharString.insert(_Data, _Arr);
         _CharString.insert(_Data2, _Arr2);

         std::cout << "Printing tree of char arrays"  << std::endl;
      
         ev6::el::avl_tree< int, char* >::iterator _It2, _End2;

         _It2 = _CharString.begin();
         _End2 = _CharString.end();

         while (_It2 != _End2)
         {
            std::cout << *_It2++ << " ";
         }

         std::cout << std::endl;

         _m_helper.print_exit(_ErrorCode);

      }
      
      void  _test_print_breadth_first_iteration()
      {

         if (!_created()) _create_avl_tree();
         
         std::size_t _ErrorCode = 0;

         _m_helper.set_title("Test avl_tree print breadth first iteration");
         _m_helper.print_entry(ev6::el::MICROSECONDS);

         _m_tree->print_breadth_first_traversal();
 
         _m_helper.print_exit(_ErrorCode);

      }
      
      void _test_search()
      {

         if (!_created()) _create_avl_tree();
         
         std::size_t _ErrorCode = 0;

         _m_helper.set_title("Test avl_tree search");
         _m_helper.print_entry(ev6::el::MICROSECONDS);

         if (!_m_tree->contains(_m_array->at(445))) _ErrorCode = 1;

         if (!_ErrorCode)
         {
            if (_m_tree->search(_m_array->at(445)) == _m_array->at(445)) 
            {
               _ErrorCode = 0;

               std::cout << "Found: " << _m_tree->search(_m_array->at(445)) << std::endl;

               std::cout << "Key: " << _m_tree->search(_m_array->at(445)) << std::endl;

            }
         }

         _m_helper.print_exit(_ErrorCode);

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
