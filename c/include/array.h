/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */
/*                                                                           */
/* Author: Jarret Shook                                                      */
/*                                                                           */
/* Module: array.h                                                           */
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

#ifndef __ARRAY_H__
#define __ARRAY_H__

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* type definitions */

typedef struct array
{
   
   void** m_array;
   int m_capacity;
   int m_size;

} array;

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* functions for creating and deleting an array struct */

array* create_array();

void delete_array(array*);

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* general functions for a array */

void* at_array(array*, int);
void* at_array_safe(array*, int);
void* back_array(array*);
void clear_array(array*);
void empty_array(array*);
void* front_array(array*);
void insert_into_array(array*, int, void*);
void* pop_back_array(array*);
void* pop_front_array(array*);
void push_back_array(array*, void*);
void push_front_array(array*, void*);
void remove_from_array(array*, int);
void shift_left_one_array(array*, int);
void shift_right_one_array(array*, int);
int size_of_array(array*);

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

#endif /* __ARRAY_H__ */

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */
