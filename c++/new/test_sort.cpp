#include <iostream>

#include "sort.hpp"

using namespace ev6;
using namespace el;

int main()
{

   int _Array[8] = { 8, 10, 6, 5, 7, 9, 17, 1 };

   merge_sort(_Array, 8);

   for (std::size_t _Index = 0; _Index < 8; ++_Index)
   {

      std::cout << _Array[_Index] << " ";

   }

   std::cout << std::endl;

}
