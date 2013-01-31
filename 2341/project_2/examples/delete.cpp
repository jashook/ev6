///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: delete
//
// Modifications: 27-Aug-12
//
// Version - 1.0
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define SIZE 100

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void do_another_thing(char*);
void do_something(char*);
void do_something_weird(char*);

int main()
{
   char* _Ptr = new char[SIZE];
   std::cin >> _Ptr;
   do_something(_Ptr);
   do_another_thing(_Ptr);
   do_something_weird(_Ptr);   

   delete _Ptr;

   return 0;
}

void do_something(char* _Ptr)
{
   std::cout << _Ptr << std::endl;
}

void do_another_thing(char* _Ptr)
{
   delete _Ptr; 
}

void do_something_weird(char* _Ptr)
{

   _Ptr[SIZE / 2] = '?';

   for (std::size_t i = 0; i < SIZE; ++i)
   {
      std::cout << *(_Ptr + i);
   }

   std::cout << std::endl;

}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////