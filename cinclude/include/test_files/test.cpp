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

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int main()
{
   try
   {
      
      test_array();

   }

   catch (std::exception& _Exception)
   {

      std::cout << "Exception caught.  Terminating the program..." << std::endl;

      return 0;

   }

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
