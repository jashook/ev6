/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/* Author: Jarret Shook                                                       */
/*                                                                            */
/* Module: program_3.c                                                        */
/*                                                                            */
/* Modifications:                                                             */
/*                                                                            */
/* 11-June-13: Version 1.0: Created                                           */
/*                                                                            */
/* Timeperiod: ev7                                                            */
/*                                                                            */
/* Notes:                                                                     */
/*    Created with the GNU C compiler (Version 4.6.3)                         */
/*    Compiles and runs with the -std=c89 (conforms to the c89 standard)      */
/*                                                                            */
/*    To compile: gcc -std=c89 program_3.c                                    */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* struct: array                                                              */
/*                                                                            */
/* variables: size_t*, size_t                                                 */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

typedef struct array
{

   size_t* m_array;
   size_t m_size;

} array;

/* ************************************************************************** */
/* ************************************************************************** */
/* Function: bubble_sort                                                      */
/*                                                                            */
/* Arguements: size_t*, size_t                                                */
/*                                                                            */
/* Returns: VOID                                                              */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

void* bubble_sort(void* _EntryStruct)
{
   array* _ArrayStruct;

   size_t* _Array = _ArrayStruct->m_array;
   size_t _Size = _ArrayStruct->m_size;

   size_t i, j, _Temp;
 
   for (i = (_Size - 1); i > 0; --i)
   {
      for (j = 1; j <= i; ++j)
      {
         if (_Array[j-1] > _Array[j])
         {
            _Temp = _Array[j-1];
            _Array[j-1] = _Array[j];
            _Array[j] = _Temp;
         }
      }
   }

   return (void*) _ArrayStruct;
}

/* ************************************************************************** */
/* ************************************************************************** */
/* Function: initalize_array                                                  */
/*                                                                            */
/* Arguements: size_t*, size_t                                                */
/*                                                                            */
/* Returns: VOID                                                              */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

void initialize_array(size_t* _Array, size_t _ArraySize)
{
   size_t _Count;

   for (_Count = 0; _Count < _ArraySize; ++_Count)
   {

      _Array[_Count] = rand(); /* initialize the first array with random values */

   }
}

/* ************************************************************************** */
/* ************************************************************************** */
/* Function: merge                                                            */
/*                                                                            */
/* Arguements: size_t*, size_t, size_t*, size_t, size_t*                      */
/*                                                                            */
/* Returns: VOID                                                              */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

void merge(size_t* _FirstArray, size_t _FirstArraySize, size_t* _SecondArray, size_t _SecondArraySize, size_t* _ThirdArray)
{

   size_t _Count;

   size_t _First, _Second, _Third;

   _First = _Second = 0;

   for (_Count = 0; _Count < _FirstArraySize + _SecondArraySize; ++_Count)
   {

      if (_FirstArray[_First] < _SecondArray[_Second] && _First < _FirstArraySize)
      {
         *_ThirdArray++ = _First++;
      }

      else if (_FirstArray[_First] > _SecondArray[_Second] && _Second < _SecondArraySize)
      {
         *_ThirdArray++ = _Second++;
      }

      else if (_First < _FirstArraySize)
      {

         *_ThirdArray++ = _First++;

      }

   }

}

/* ************************************************************************** */
/* ************************************************************************** */
/* Function: sort_and_merge_with_threads                                      */
/*                                                                            */
/* Arguements: array*, array*, size_t*                                        */
/*                                                                            */
/* Returns: size_t                                                            */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

size_t sort_and_merge_with_threads(array* _FirstStructArray, array* _SecondStructArray, size_t* _ThirdArray)
{

   size_t* _FirstArray, *_SecondArray;
   size_t _FirstArraySize, _SecondArraySize;

   const size_t _ThreadCount = 2;

   pthread_t _Threads[_ThreadCount]; /* create two p_threads on the stack */

   size_t _ReturnCode;

   void* _Status;

   _ReturnCode = pthread_create(&_Threads[0], NULL, bubble_sort, (void*)_FirstStructArray);

   if (_ReturnCode) exit(-1);

   _ReturnCode = pthread_create(&_Threads[1], NULL, bubble_sort, (void*)_SecondStructArray);

   if (_ReturnCode) exit(-1);

   pthread_join(_Threads[0], &_Status);

   pthread_join(_Threads[1], &_Status);

   _FirstArray = _FirstStructArray->m_array;
   _FirstArraySize = _FirstStructArray->m_size;

   _SecondArray = _SecondStructArray->m_array;
   _SecondArraySize = _SecondStructArray->m_size;
 
   merge(_FirstArray, _FirstArraySize, _SecondArray, _SecondArraySize, _ThirdArray);
   
}

/* ************************************************************************** */
/* ************************************************************************** */
/* Function: main                                                             */
/*                                                                            */
/* Arguements: int, char**                                                    */
/*                                                                            */
/* Returns: int                                                               */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

int main(int argc, char** argv)
{
   size_t _AmountOfElements, _Count;
   size_t* _FirstArray, *_SecondArray, *_ThirdArray, *_FirstCopiedArray, *_SecondCopiedArray, *_LastArray;

   array* _FirstStructArray, *_SecondStructArray;
   
   if (argc != 2)
   {
      _AmountOfElements = 10;
   }

   else
   {
      _AmountOfElements = atoi(argv[1]);
   }

   srand(time(NULL)); /* seed srand to be random */

   _FirstArray = (size_t*)malloc(sizeof(size_t) * _AmountOfElements);

   _SecondArray = (size_t*)malloc(sizeof(size_t) * _AmountOfElements);

   _ThirdArray = (size_t*)malloc(sizeof(size_t) * (_AmountOfElements * 2) );

   _FirstCopiedArray = (size_t*)malloc(sizeof(size_t) * _AmountOfElements);

   _SecondCopiedArray = (size_t*)malloc(sizeof(size_t) * _AmountOfElements);

   _LastArray = (size_t*)malloc(sizeof(size_t) * (_AmountOfElements * 2));

   initialize_array(_FirstArray, _AmountOfElements);

   initialize_array(_SecondArray, _AmountOfElements);

   memcpy(_FirstCopiedArray, _FirstArray, _AmountOfElements);

   memcpy(_SecondCopiedArray, _SecondArray, _AmountOfElements);

   memcpy(_LastArray, _FirstArray, _AmountOfElements);

   memcpy(_LastArray + _AmountOfElements, _SecondArray, _AmountOfElements);

   _FirstStructArray->m_array = _FirstArray;
   _FirstStructArray->m_size = _AmountOfElements;

   _SecondStructArray->m_array = _SecondArray;
   _SecondStructArray->m_size = _AmountOfElements;

   sort_and_merge_with_threads(_FirstStructArray, _SecondStructArray, _ThirdArray);

   /*sort_and_merge(_FirstCopiedArray, _SecondCopiedArray, _ThirdArray);*/

   /*sort_without_merge(_LastArray); */

}
