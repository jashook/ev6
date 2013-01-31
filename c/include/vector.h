/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */
/*                                                                           */
/* Author: Jarret Shook                                                      */
/*                                                                           */
/* Module: vector.h                                                          */
/*                                                                           */
/* Modifications:                                                            */
/*                                                                           */
/* 27-Dec-12: Version 1.1: Renamed from ArrayList to vector                  */
/* 22-Oct-12: Version 1.0: Created                                           */
/*                                                                           */
/* Version: 1.1                                                              */
/*                                                                           */
/* Timeperiod: ev5                                                           */
/*                                                                           */
/* Notes: An empty vector is defined to be a vector struct that has size 0   */
/*        To properly allocate and free memory, use the create and delete    */
/*        functions                                                          */
/*                                                                           */
/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

#ifndef __VECTOR_H__
#define __VECTOR_H__

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* type definitions */

typedef struct vector
{
   void** array;
   int size;
   int max_size;

} vector;

extern const int BASE_VECTOR_SIZE;

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* functions for creating and delete a vector */

vector* create_vector();
void free_vector(vector*);

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* general functions for a vector */

void* at_vector(vector*, int);
void* back_vector(vector*);
void clear_vector(vector*);
void* front_vector(vector*);
void insert_vector(vector*, void*, int);
void* pop_back_vector(vector*);
void push_back_vector(vector*, void*);
void remove_vector(vector*, int);
void resize_vector(vector*, int);
int size_vector(vector*);

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

#endif   /* __VECTOR_H__ */

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */
