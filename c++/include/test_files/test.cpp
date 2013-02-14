///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: test_file.cpp
//
// Modifications:
//
// 17-Jan-12 : Version 1.0: Created
//
// Timeperiod: ev6
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "array_test.hpp"
#include "avl_tree_test.hpp"
#include "logger_test.hpp"
#include "test_helper_test.hpp"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int main()
{
   ev6::el::test_helper< std::ostream > _Helper("test.cpp");

   try
   {
      _Helper.print_entry(ev6::el::MICROSECONDS);   

      //test_array();
      //test_logger();
      // test_helper_test(); // assumed to work correctly
      test_avl_tree();

      _Helper.print_exit();

   }
   catch (std::exception& _Exception)
   {

      std::cout << "Exception caught.  Terminating the program..." << std::endl;

      _Helper.print_exit(1);

      return 0;

   }

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
