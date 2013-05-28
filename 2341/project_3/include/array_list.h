/* ///////////////////////////////////////////////////////////////////////// */
/*                                                                           */
/* Author: Jarret Shook                                                      */
/*                                                                           */
/* Module: array_list.h                                                      */
/*                                                                           */
/* Modifications: 22-Oct-12 - Created                                        */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Timeperiod: EVN4                                                          */
/*                                                                           */
/* Notes: An empty arry_list is defined to be an array_list struct that has  */
/*        a size of 0                                                        */
/*        To Properly use and free memory use the create or delete functions */
/*                                                                           */
/* ///////////////////////////////////////////////////////////////////////// */

#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

/* ///////////////////////////////////////////////////////////////////////// */

#include <stdlib.h>
#include <stdio.h>

/* ///////////////////////////////////////////////////////////////////////// */

// struct type definitions

typedef struct array_list
{
   void** _array;
   int size;
} array_list;

// end of struct type definitions

/* ///////////////////////////////////////////////////////////////////////// */

// functions for creating and deleting a linked_list struct

array_list* create_array_list();

void delete_array_list(array_list*);

/* ///////////////////////////////////////////////////////////////////////// */

// general functions for a linked_list

void* at_array_list(array_list*, int);
void* back_array_list(array_list*);
void clear_array_list(array_list*);
void empty_array_list(array_list*);
void* front_array_list(array_list*);
void insert_array_list(array_list*, int);
void* pop_back_array_list(array_list*);
void push_back_array_list(array_list*, void*);
void remove_array_list(array_list*, int);
int size_array_list(array_list*);

/* ///////////////////////////////////////////////////////////////////////// */

#endif /* __LINKED_LIST_H__ */

/* ///////////////////////////////////////////////////////////////////////// */
