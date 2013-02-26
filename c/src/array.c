/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */
/*                                                                           */
/* Author: Jarret Shook                                                      */
/*                                                                           */
/* Module: array.c                                                           */
/*                                                                           */
/* Modifications:                                                            */
/*                                                                           */
/* 16-Feb-13: Version 1.0: Created                                           */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Timeperiod: Ev6                                                           */
/*                                                                           */
/* Notes: An empty array is defined to be a array struct that points to an   */
/*        array struct of size 0.                                            */
/*        To Properly use and free memory use the create or delete functions */
/*                                                                           */
/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

#include "array.h"

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* functions for creating and deleting an array struct */

array* create_array(int _Size)
{
   array* _Array = malloc(sizeof(array));

   _Array->m_array = malloc(sizeof(void*) * _Size);

   #if DEBUG

      memset(_Array->m_array, 0, sizeof(_Array));

   #endif

   _Array->m_size = 0;

   _Array->m_capacity = _Size;
}

void delete_array(array* _Array)
{
   #if DEBUG
   
      memset(_Array->m_array, 0, sizeof(_Array));

   #endif

   free(_Array->m_array);

   free(_Array);
}

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* general functions for a array */

void* at_array(array* _Array, int _Index)
{
   return at_array_safe(_Array, _Index);
}

void* at_array_safe(array* _Array, int _Index)
{
   #if DEBUG

      if (_Index > _Array->capacity - 1) 
      {
         printf("Attempting to read out of bounds.  Exiting the program...\n");
         
         exit(1);
      }

   #endif

   return _Array->m_array[_Index];
}

void* back_array(array* _Array)
{
   return _Array->m_array[_Array->m_size];
}

void clear_array(array* _Array)
{
   memset(_Array->m_array, 0, sizeof(_Array->m_array));
}

void empty_array(array* _Array)
{
   clear_array(_Array);
}

void* front_array(array* _Array)
{
   return _Array->m_array[0];
}

void insert_into_array(array* _Array, int _Index,  void* _Data)
{
   /* Note: Linear time insertion */

   #if DEBUG
   
      if ((_Array->m_capacity == _Array->m_size) || ( _Index >= _Array->m_size) || (_Index < 0))
      {
         printf("Attempting to write out of bounds.  Exiting the program...\n");
         
         exit(1);
      }

   #endif

   shift_right_one_array(_Array, _Index);

   _Array->m_array[_Index] = _Data;

}

void* pop_back_array(array* _Array)
{
   #if DEBUG

      if (_Array->m_size == 0)
      {
         printf("Attempting to read out of bounds.  Exiting the program...\n");
         
         exit(1);
      }
   
   #endif

   return _Array->m_array[_Array->m_size--];
}

void* pop_front_array(array* _Array)
{
   /* Note: Linear time removal */

   #if DEBUG

      if (_Array->m_size == 0)
      {
         printf("Attempting to read out of bounds.  Exiting the program...\n");
         
         exit(1);
      }
   
   #endif

   void* _Return = _Array->m_array[0];

   shift_left_one_array(_Array, 0);
   
   --_Array->m_size;

   return _Return;
}

void push_back_array(array* _Array, void* _Data)
{
   #if DEBUG
   
      if (_Array->m_capacity == _Array->m_size)
      {
         printf("Attempting to write out of bounds.  Exiting the program...\n");
         
         exit(1);
      }

   #endif

   _Array->m_array[_Array->m_size++] = _Data;

}

void push_front_array(array* _Array, void* _Data)
{
   /* Note: Linear time insertion */

   #if DEBUG
   
      if (_Array->m_capacity == _Array->m_size)
      {
         printf("Attempting to write out of bounds.  Exiting the program...\n");
         
         exit(1);
      }

   #endif

   shift_right_one_array(_Array, 0);

   ++_Array->m_size;
   
   _Array->m_array[0] = _Data;

}

void remove_from_array(array* _Array, int _Index)
{
   /* Note: Linear time removal */

   #if DEBUG

      if (_Array->m_size == 0)
      {
         printf("Attempting to read out of bounds.  Exiting the program...\n");
         
         exit(1);
      }
   
   #endif

   shift_left_one_array(_Array, _Index);
   
   --_Array->m_size;
  
}

void shift_left_one_array(array* _Array, int _Index)
{
   #if DEBUG
   
      if (( _Index <= _Array->m_size) || (_Index < 0))
      {
         printf("Attempting to write out of bounds.  Exiting the program...\n");
         
         exit(1);
      }

   #endif

   /* move all pointers down by one */

   int i;

   for (i = _Index; i < _Array->m_size; ++i)
   {
      _Array->m_array[i - 1] = _Array->m_array[i];
   }
}

void shift_right_one_array(array* _Array, int _Index)
{
   #if DEBUG
   
      if (( _Index >= _Array->m_size) || (_Index < 0))
      {
         printf("Attempting to write out of bounds.  Exiting the program...\n");
         
         exit(1);
      }

   #endif

   /* move all pointers down by one */

   int i;

   for (i = _Array->m_size - 1; i > _Index; --i)
   {
      _Array->m_array[i] = _Array->m_array[i - 1];
   }
}

int size_of_array(array* _Array)
{
   return _Array->m_size;
}

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */
