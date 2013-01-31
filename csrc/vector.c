/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */
/*                                                                           */
/* Author: Jarret Shook                                                      */
/*                                                                           */
/* Module: vector.c                                                          */
/*                                                                           */
/* Modifications:                                                            */
/*                                                                           */
/* 29-Dec-12: Version 1.0: Created                                           */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Timeperiod: ev5                                                           */
/*                                                                           */
/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

#include "vector.h"

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

const int BASE_VECTOR_SIZE = 10;

vector* create_vector()
{
   vector* _Vector = (vector*)malloc(sizeof(vector));
   
   _Vector->array = (void**)malloc(sizeof(void*) * BASE_VECTOR_SIZE);
   _Vector->size = 0;
   _Vector->max_size = BASE_VECTOR_SIZE;

   return _Vector;
}

void free_vector(vector* _Vector)
{
   free(_Vector->array);
   free(_Vector);
}

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

void* at_vector(vector* _Vector, int _Position)
{
   return _Vector->array[_Position];
}

void* back_vector(vector* _Vector)
{
   return _Vector->array[_Vector->size - 1];
}

void clear_vector(vector* _Vector)
{
   memset(_Vector->array, 0, sizeof(_Vector->array));
}

void* front_vector(vector* _Vector)
{
   return _Vector->array[0];
}

void insert_vector(vector* _Vector, void* _Data, int _Position)
{
   if (_Position > _Vector->size - 1) return;

   if ( (_Vector->size + 1) >= _Vector->max_size)
   {
      resize_vector(_Vector, _Vector->max_size * 2);
   }
   
   int i;
   void* _Temp;

   for (i = _Position; i < _Vector->size; i++)
   {
      _Temp  = _Vector->array[i + 1];
      
      _Vector->array[i + 1] = _Vector->array[i];
   }

   _Vector->array[_Position] = _Data;
   ++_Vector->size;
   
}

void* pop_back_vector(vector* _Vector)
{
   if (_Vector->size == 0) return 0;

   void* _ReturnValue;
   
   _ReturnValue = _Vector->array[_Vector->size - 1];

   --_Vector->size;

   return _ReturnValue;

}

void push_back_vector(vector* _Vector, void* _Data)
{
   if ( (_Vector->size + 1) >= _Vector->max_size)
   {
      resize_vector(_Vector, _Vector->max_size * 2);
   }

   _Vector->array[_Vector->size] = _Data;
   ++_Vector->size;

}

void remove_vector(vector* _Vector, int _Position)
{
   if (_Position > _Vector->size - 1 || _Vector->size == 0) return;

   int i;
   void* _Temp;

   for (i = _Position; i < _Vector->size - 1; ++i)
   {
      _Vector->array[i] = _Vector->array[i + 1];
   }

   --_Vector->size;
}

void resize_vector(vector* _Vector, int _NewSize)
{
   int i;
   void** _ArrayCopy;

   _ArrayCopy = (void**)malloc(sizeof(void*) * _NewSize);

   for (i = 0; i < _Vector->size; ++i) _ArrayCopy[i] = _Vector->array[i];

   free(_Vector->array);
   _Vector->max_size = _NewSize;
   _Vector->array = _ArrayCopy;
  
}

int size_vector(vector* _Vector)
{
   return _Vector->size;
}
