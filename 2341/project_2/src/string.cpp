///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: string.cpp
//
// Modifications: 8-Sept-12
//
// Notes- Test class for string.hpp
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <string>
#include "vector.hpp"

#include "string.hpp"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void c_dtor();
void test_at();
void test_add();
void test_clear();
void test_c_str();
void test_size();
void test_add_assign();
void test_assign();
void test_equal();
void test_comparisons();
void test_insertion();

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int main()
{
   c_dtor();
   //test_at();
   //test_add();
   //est_clear();
   //test_c_str();
   //test_size();
   //test_add_assign();
   //test_assign();
   //test_assign();
   //test_equal();
   //test_compairisons();
   //test_insertion();
   
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void c_dtor()
{
   ev4::string<>  _Instance;
   ev4::string<>* _Instance2 = new ev4::string<>();
   delete _Instance2;
}

void test_at()
{
   const char* _Hello = "Hello";
   ev4::string<> _String(_Hello);
   
   for (std::size_t i = 0; i< _String.size(); ++i) std::cout << _String.at(i);

   std::cout << std::endl;
}

void test_add()
{
   const char* _Hello = "Hello";
   const char* _Ld = "ld";
   const char* _E = "!!!!";
   const char* _Space = ' ';
   const char* _Wor = "wor";   

   ev4::string<> _String(_Hello);
   ev4::string<> _String2(_Ld);
   ev4::string<> _String3(_E);

   _String.add(_Space);
   _String.add(_Wor);
   _String.add(_String2.c_str());
   _String.add(_String3);

   std::cout << _String << std::endl;
}

void test_clear()
{
   ev4::string<> _String("YAYAYAYAAYAYAYAYAYAAYYAYAAY");
   //std::cout << _String.clear(); << std::endl;
}

void test_size()
{
   ev4::string<> _String("Hello");
   std::cout << _String.size() << std::endl;
}

void test_add_asign()
{
   ev4::string<> _String("Hello ");
   ev4::string<> _String2("World");

   _String += _String2;

   std::cout << _String << std::endl;
}

void test_assign()
{
   ev4::string<> _String("Jarret");
   ev4::string<> _String2("Nate");

   _String = _String2;

   std::cout << _String << std::endl;
}

void test_equal()
{
   ev4::string<> _String("String 1");
   ev4::string<> _String2("String 2");
   ev4::string<> _String3("String 1");

   std::cout << (_String == _String3) << std::endl;
   std::cout << (_String == _String2) << std::endl;
}

void test_comparisons()
{

   ev4::string<> _String("Jarret");
   ev4::string<> _String2("Nate");
   ev4::string<> _String3("Ali");

   ev4::vector< ev4::string<> > _Vec;

   _Vec.push_back(_String);
   _Vec.push_back(_String2);
   _Vec.push_back(_String3);

   //std::sort(_Vec.begin(), _Vec.end());

   for (std::size_t i = 0; i < _Vec.size(); ++i) std::cout << _Vec[i] << std::endl;
}

void test_insertion()
{
   ev4::string<> _String("HEY");
   std::cout << _String << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
