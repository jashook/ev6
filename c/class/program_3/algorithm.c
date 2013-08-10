/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/* Author: Jarret Shook                                                       */
/*                                                                            */
/* Module: algorith.c                                                         */
/*                                                                            */
/* Modifications:                                                             */
/*                                                                            */
/* 21-June-13: Last Updated                                                   */
/* 14-June-13: Version 1.0: Style change and updated to ev7                   */
/* 21-Feb-13: Version 1.0: Created                                            */
/*                                                                            */
/* Version: 1.0                                                               */
/*                                                                            */
/* Timeperiod: ev7                                                            */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

#include "algorithm.h"

/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Function:                                                                  */
/*                                                                            */
/*    max                                                                     */
/*                                                                            */
/* Arguements:                                                                */
/*                                                                            */
/*    void*: first arguement to be compared                                   */
/*    void*: second arguement to be compared                                  */
/*    int (*)(void*, void*): pointer to a function that compares to types     */
/*                         : passed by pointer and cast to void               */
/*                                                                            */
/* Returns:                                                                   */
/*                                                                            */
/*    void*: the arguement that is larger                                     */
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/*    Generic max function                                                    */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

void* max(void* _First, void* _Second, int (*_Compare)(void*, void*))
{
   /* if _First is less than _Second, return _Second */

   if (_Compare(_First, _Second)) return _Second;

   /* else return _First */
   
   else return _First;
}

/* ************************************************************************** */
/* ************************************************************************** */
/* Function:                                                                  */
/*                                                                            */
/*    merge_sort                                                              */
/*                                                                            */
/* Arguements:                                                                */
/*                                                                            */
/*    void*: array to be sorted                                               */
/*    size_t: size of the array                                               */
/*    size_t: size of the elements in the array                               */
/*    int (*)(void*, void*): pointer to a function that compares to types     */
/*                         : passed by pointer and cast to void               */
/*                                                                            */
/* Returns:                                                                   */
/*                                                                            */
/*    void                                                                    */
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/*    The original array will be overwritten by this function                 */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */


void merge_sort(void* _Array, size_t _ArraySize, size_t _ElementSize, int (*_compare)(void*, void*))
{

   int _Count;

   void* _ArrayCopy = malloc(_ElementSize * _ArraySize);
   void* _Buffer = malloc(_ElementSize * _ArraySize);

   size_t _Size = 1; /* smallest size possible */

   size_t _Pairs = _ArraySize / _Size;

   size_t _Groups = 1;

   size_t _IncrementSize = 1;

   /* ***************************************************** */
   /* Make a copy of the array                              */
   /* ***************************************************** */

   memcpy(_ArrayCopy, _Array, _ArraySize * _ElementSize);

   while (_IncrementSize * 2 <= _ArraySize)
   {
      
      int _SortLastPair = 0;

      void* _TempPointer;

      size_t _Index;

      _Groups = _Pairs / 2;

      _IncrementSize *= 2;
   
      _IncrementSize % 2 == 0 ? _IncrementSize = _IncrementSize : ++_IncrementSize;

      if ((_Groups * _IncrementSize) != _ArraySize)
      {

         _SortLastPair = 1;

      }

      for (_Index = 0; _Index < _ArraySize; _Index += _IncrementSize)
      {

         int _FirstEndIndex = _Index + (_IncrementSize / 2) - 1;
         int _SecondEndIndex = _Index + _IncrementSize - 1;

         int _FirstBeginningIndex = _FirstEndIndex - (_Size - 1);
         int _SecondBeginningIndex = _SecondEndIndex - (_Size - 1);

         if (_SecondEndIndex > _ArraySize - 1) continue;

         char* _ArrayAsBytes = (char*)_ArrayCopy;

         char* _BufferAsBytes = (char*)_Buffer;

         if (_IncrementSize == _Pairs) _SecondEndIndex = _IncrementSize * _Size;

         merge_sorted((void*)(_BufferAsBytes + (_FirstBeginningIndex * _ElementSize)) , (void*)(_ArrayAsBytes + (_FirstBeginningIndex * _ElementSize)), (void*)(_ArrayAsBytes + (_SecondBeginningIndex * _ElementSize)), _Size, _Size, _ElementSize, _compare);

      }

      if (_SortLastPair)
      {

         int _EndIndex = _ArraySize - 1;
         int _BeginningIndex = _EndIndex - (_ArraySize - (_Groups * _IncrementSize)) + 1;

         int _PreviousBeginningIndex = (_IncrementSize * _Groups) - _IncrementSize;
         int _PreviousEndingIndex = _PreviousBeginningIndex + _IncrementSize - 1;

         memcpy((void*)(((char*)_Buffer + (_BeginningIndex * _ElementSize))), (void*)(((char*)_ArrayCopy) + (_BeginningIndex * _ElementSize)), ((_EndIndex - _BeginningIndex) + 1) * _ElementSize);

         merge_sorted((void*)((char*)(_ArrayCopy + (_PreviousBeginningIndex * _ElementSize))), (void*)((char*)(_Buffer + (_PreviousBeginningIndex * _ElementSize))), (void*)((char*)(_Buffer + (_BeginningIndex * _ElementSize))), _IncrementSize, _EndIndex - _BeginningIndex + 1, _ElementSize, _compare);

         memcpy((void*)(((char*)_Buffer + (_PreviousBeginningIndex * _ElementSize))), (void*)(((char*)_ArrayCopy) + (_PreviousBeginningIndex * _ElementSize)), ((_EndIndex - _PreviousBeginningIndex) + 1) * _ElementSize);

      }

      _TempPointer = _ArrayCopy;

      _ArrayCopy = _Buffer;
   
      _Buffer = _TempPointer;

      _Size *= 2;

      /* amount of partitions in the array */
      _Pairs = (_Pairs / 2);

      if (_Size + 1 == _ArraySize) ++_Size;

   }

   memcpy(_Array, _ArrayCopy, _ArraySize * _ElementSize);

   free(_ArrayCopy);
   free(_Buffer);

}

/* ************************************************************************** */
/* ************************************************************************** */
/* Function:                                                                  */
/*                                                                            */
/*    merge_sorted                                                            */
/*                                                                            */
/* Arguements:                                                                */
/*                                                                            */
/*    void*: the destination array to be merged into                          */
/*    void*: the first array to be merged                                     */
/*    void*: the second array to be merged                                    */
/*    size_t: the first array to be merged's size                             */
/*    size_t: the second array to be merged's size                            */
/*    size_t: size of the elements stored in the arrays                       */
/*    int (*)(void*, void*): pointer to a function that compares to types     */
/*                         : passed by pointer and cast to void               */
/*                                                                            */
/* Returns:                                                                   */
/*                                                                            */
/*    void                                                                    */
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/*    Note this will overwrite the contents of the _DestinationArray          */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

void merge_sorted(void* _DestinationArray, void* _FirstArray, void* _SecondArray, size_t _FirstSize, size_t _SecondSize, size_t _ElementSize, int (*_compare)(void*, void*))
{
   
   int _Index;

   int _DestinationSize = _FirstSize + _SecondSize;

   int _FirstEndIndex = _FirstSize - 1;
   int _SecondEndIndex = _SecondSize - 1;

   for (_Index = _DestinationSize - 1; _Index >= 0; --_Index)
   {

      /* ************************************************** */
      /* Compare to see which is larger                     */
      /* ************************************************** */

      if (_FirstEndIndex < 0) 
      {

         char* _DestinationPointer = (char*)_DestinationArray;
         char* _SecondArrayPointer = (char*)_SecondArray;

         memcpy((void*)(_DestinationPointer + ((_Index) * _ElementSize)), (void*)(_SecondArrayPointer + (_SecondEndIndex-- * _ElementSize)), _ElementSize);

         continue;

      }

      if (_SecondEndIndex < 0)
      {

         char* _DestinationPointer = (char*)_DestinationArray;
         char* _FirstArrayPointer = (char*)_FirstArray;

         memcpy((void*)(_DestinationPointer + ((_Index) * _ElementSize)), (void*)(_FirstArrayPointer + (_FirstEndIndex-- * _ElementSize)), _ElementSize);

         continue;
         
      }

      else if (_compare((void*)((char*)(_FirstArray + (_FirstEndIndex * (_ElementSize / sizeof(char))))), (void*)((char*)(_SecondArray + (_SecondEndIndex * (_ElementSize / sizeof(char)))))) > 0)
      {
   
         char* _DestinationPointer = (char*)_DestinationArray;
         char* _FirstArrayPointer = (char*)_FirstArray;

         memcpy((void*)(_DestinationPointer + ((_Index) * _ElementSize)), (void*)(_FirstArrayPointer + (_FirstEndIndex-- * _ElementSize)), _ElementSize);

      }   
   
      else if (_SecondEndIndex >= 0)
      {   

         char* _DestinationPointer = (char*)_DestinationArray;
         char* _SecondArrayPointer = (char*)_SecondArray;

         memcpy((void*)(_DestinationPointer + ((_Index) * (_ElementSize / sizeof(char)))), (void*)(_SecondArrayPointer + (_SecondEndIndex-- * (_ElementSize / sizeof(char)))), _ElementSize);

      }   


   }

}

/* ************************************************************************** */
/* ************************************************************************** */
/* Function:                                                                  */
/*                                                                            */
/*    min                                                                     */
/*                                                                            */
/* Arguements:                                                                */
/*                                                                            */
/*    void*: first arguement to be compared                                   */
/*    void*: second arguement to be compared                                  */
/*    int (*)(void*, void*): pointer to a function that compares to types     */
/*                         : passed by pointer and cast to void               */
/*                                                                            */
/* Returns:                                                                   */
/*                                                                            */
/*    void*: the arguement that is smaller                                    */
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/*    Generic min function                                                    */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

void* min(void* _First, void* _Second, int (*_Compare)(void*, void*))
{
   /* if the max is _First, then return _Second */

   if (max(_First, _Second, _Compare) == _First) return _Second;

   /* else if the max is _Second, return _First */
   
   else return _First;
}

/* ************************************************************************** */
/* ************************************************************************** */
/* Function:                                                                  */
/*                                                                            */
/*    next_power_of_two                                                       */
/*                                                                            */
/* Arguements:                                                                */
/*                                                                            */
/*    unsigned long: integer to be find the next power of to of               */
/*                                                                            */
/* Returns:                                                                   */
/*                                                                            */
/*    unsigned long: the value of the passed integer expressed as the next    */
/*                 : power of two                                             */
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/*    taken from:                                                             */
/*   http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2Float */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

unsigned long next_power_of_two(unsigned long _Integer)
{

   /* 32 bit precision only */

    --_Integer;

    _Integer |= _Integer >> 1;

    _Integer |= _Integer >> 2;

    _Integer |= _Integer >> 4;

    _Integer |= _Integer >> 8;

    _Integer |= _Integer >> 16;

    ++_Integer;

    return _Integer;

}

/* ************************************************************************** */
/* ************************************************************************** */
