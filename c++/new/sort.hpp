////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Author: Jarret Shook
//
// Module: sort.hpp
//
// Modifications:
//
// 19-March-13: Version 1.0: Created
//
// Timeperiod: ev6
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __SORT_HPP__
#define __SORT_HPP__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ev6 {
namespace el {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Input : Three arrays and their sizes.  The destination array should be the size of
//       : the following two arrays.  Array one and two should be in sorted order
// 
// Output: Void return, however, the combined two sorted arrays are stored in the
//       : destionation array
////////////////////////////////////////////////////////////////////////////////

template< typename __Type > void merge_sorted(__Type* _DestinationArray, __Type* _FirstArray, __Type* _SecondArray, int _DestinationSize, int _FirstSize, int _SecondSize)
{
   int _FirstEndIndex = _FirstSize - 1;
   int _SecondEndIndex = _SecondSize - 1;

   for (int _Index = _DestinationSize - 1; _Index >= 0; --_Index)
   {
      ////////////////////////////////////////////////////////////////////////////////
      // Compare to see which is larger
      ////////////////////////////////////////////////////////////////////////////////

      if (_FirstArray[_FirstEndIndex] > _SecondArray[_SecondEndIndex] && _FirstEndIndex >= 0)
      {

         _DestinationArray[_FirstEndIndex + _SecondEndIndex + 1] = _FirstArray[_FirstEndIndex--];

      }
   
      else if (_SecondEndIndex >= 0)
      {

         _DestinationArray[_FirstEndIndex + _SecondEndIndex + 1] = _SecondArray[_SecondEndIndex--];

      }

   }

}   // end of function merge_sorted



template< typename __Type > void merge_sort(__Type* _Array, int _ArraySize)
{
   __Type* _ArrayCopy = new __Type[_ArraySize];
   __Type* _Buffer = new __Type[_ArraySize];

   ////////////////////////////////////////////////////////////////////////////////
   // make a copy of the array
   ////////////////////////////////////////////////////////////////////////////////

   for (std::size_t _Index = 0; _Index < _ArraySize; ++_Index) _ArrayCopy[_Index] = _Array[_Index];

   std::size_t _Size = 1;   // smallest possible size

   while (_Size != _ArraySize)
   {
      bool _SortLastPair = false;;
      std::size_t _Pairs = _ArraySize / _Size;   // the amount of partions in the array

      if (_Pairs % 2 != 0) 
      {
         --_Pairs;   // if not even then ignore the last pair

         _SortLastPair = true;
      }

      for (std::size_t _Index = 1; _Index < _Pairs + 1; ++_Index)
      {

         int _FirstEndIndex = _Index * _Size - 1;
         int _SecondEndIndex = (_Index + 1) * _Size - 1;

         if (_Index == _Pairs) _SecondEndIndex = _Index * _Size;

         int _FirstBeginningIndex = _FirstEndIndex - (_Size - 1);
         int _SecondBeginningIndex = _SecondEndIndex - (_Size - 1);

         std::cout << "_Pairs: " << _Pairs << std::endl;
         std::cout << "_FirstEndIndex: " << _FirstEndIndex << std::endl;
         std::cout << "_SecondEndIndex: " << _SecondEndIndex << std::endl;

         std::cout << "_FirstBeginningIndex: " << _FirstBeginningIndex << std::endl;
         std::cout << "_SecondBeginningIndex: " << _SecondBeginningIndex << std::endl;

         merge_sorted(_Buffer, _ArrayCopy + _FirstBeginningIndex, _ArrayCopy + _SecondBeginningIndex, _Size * 2, _Size, _Size);

      }

      if (_SortLastPair)
      {

         int _EndIndex = (_Pairs + 1) * _Size - 1;
         int _BeginningIndex = (_EndIndex) - (_Size - 1);

         int _PreviousEndingIndex = _Pairs * _Size - 1;
         int _PreviousBeginningIndex = _BeginningIndex - (_Size * 2 - 1);
         
         merge_sorted(_ArrayCopy + _PreviousBeginningIndex, _Buffer + _PreviousBeginningIndex, _Buffer + _BeginningIndex, _Size * 2 + _Size, _Size * 2, _Size);

         for (int _Index = _PreviousBeginningIndex; _Index < _EndIndex; ++_Index) _Buffer[_Index] = _ArrayCopy[_Index];

      }

      __Type* _TempSwapPointer = _ArrayCopy;   // Temporary to help switch _ArrayCopy and _Buffer
   
      _ArrayCopy = _Buffer;

      _Buffer = _TempSwapPointer;

      _Size *= 2;
      
      if (_Size + 1 == _ArraySize) ++_Size;

   }

   for (std::size_t _Index = 0; _Index < _ArraySize; ++_Index) _Array[_Index] = _ArrayCopy[_Index];

   delete [] _ArrayCopy;
   delete [] _Buffer;

} // end of merge_sort function

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}   // end of namespace el
}   // end of namespace ev6

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif // __SORT_HPP__
