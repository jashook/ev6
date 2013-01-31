////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: rti.hpp (run time information )
//
// Modifications:
//
// 22-Jan-13: Cleaned and changed to namespace ev6
// 19-Dec-12: Changed namespace to ev5 and added to namespace el
// 14-Jun-12: Created
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __RTI_HPP__
#define __RTI_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

   //   Overloaded function to determine if a value is a primative

   template<typename __Type> bool is_primitive() { return false; }
   template<> bool is_primitive<char>() { return true; }
   template<> bool is_primitive<signed char>() { return true; }
   template<> bool is_primitive<short>() { return true; }
   template<> bool is_primitive<int>() { return true; }
   template<> bool is_primitive<long>() { return true; }
   template<> bool is_primitive<unsigned char>() { return true; }
   template<> bool is_primitive<unsigned short>() { return true; }
   template<> bool is_primitive<unsigned int>() { return true; }
   template<> bool is_primitive<unsigned long>() { return true; }
   template<> bool is_primitive<float>() { return true; }
   template<> bool is_primitive<double>() { return true; }
   template<> bool is_primitive<void>() { return true; }

   //   Overloaded templated function to determine if a type is a char
   
   template<typename __Type> bool is_char() { return false; }
   template<> bool is_char<char>() { return true; }

   //   Overloaded templated function to determine if a type is a signed char

   template<typename __Type> bool is_schar() { return false; }
   template<> bool is_schar<signed char>() { return true; }

   //   Overloaded templated function to determine if a type is a short

   template<typename __Type> bool is_short() { return false; }
   template<> bool is_short<short>() { return true; }

   //   Overloaded templated function to determine if a type is an int

   template<typename __Type> bool is_int() { return false; }
   template<> bool is_int<int>() { return true; }

   //   Overloaded templated function to determine if a type is a long
   
   template<typename __Type> bool is_long() { return false; }
   template<> bool is_long<long>() { return true; }

   //   Overloaded templated function to determine if a type is an unsigned char

   template<typename __Type> bool is_uchar() { return false; }
   template<> bool is_uchar<unsigned char>() { return true; }

   //   Overloaded templated function which determines if a type is an unsigned int

   template<typename __Type> bool is_uint() { return false; }
   template<> bool is_uint<unsigned int>() { return true; }

   //   Overloaded templated function which determines if a type is an unsigned long

   template<typename __Type> bool is_ulong() { return false; }
   template<> bool is_ulong<unsigned long>() { return true; }

   //   Overloaded templated function which determines if a type is a float
   
   template<typename __Type> bool is_float() { return false; }
   template<> bool is_float<float>() { return true; }

   //   Overloaded templated function which determines if a type is a double

   template<typename __Type> bool is_double() { return false; }
   template<> bool is_double<double>() { return true; }

   //   Overloaded templated function which determines if a type is void

   template<typename __Type> bool is_void() { return false; }
   template<> bool is_void<void>() { return true; }

   template<typename __Type> int check(bool _Erase = false)
   {
      static int _count = 0;
      ++_count;

      if (_Erase) _count = 0;

      return _count;
   }

   template <typename __Type, typename __Type2> bool are_same_type()
   {
      bool _Result = false;

      check<__Type>();
      int _count = check<__Type2>();
      if(_count == 2) _Result = true;

      check<__Type>(true);
      check<__Type2>(true);

      return _Result;
   }

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace(ev6)
}   // end of namespace(el)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __RTI_HPP__
