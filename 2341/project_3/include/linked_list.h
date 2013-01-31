/* ///////////////////////////////////////////////////////////////////////// */
/*                                                                           */
/* Author: Jarret Shook                                                      */
/*                                                                           */
/* Module: linked_list.h                                                     */
/*                                                                           */
/* Modifications: 22-Oct-12 - Created                                        */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Timeperiod: EVN4                                                          */
/*                                                                           */
/* Notes: An empty linked_list is defined to be a linked_list struct that    */
/*        points to a linked_list node and has size = 0                      */
/*        To Properly use and free memory use the create or delete functions */
/*                                                                           */
/* ///////////////////////////////////////////////////////////////////////// */

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

/* ///////////////////////////////////////////////////////////////////////// */

#include <stdlib.h>
#include <stdio.h>

/* ///////////////////////////////////////////////////////////////////////// */

// struct type definitions

typedef struct bidirectional_node
{
 
   struct bidirectional_node* _next;
   struct bidirectional_node* _prev;
   void* _data;

} bidirectional_node;

typedef struct linked_list
{
   
   bidirectional_node* _node;
   bidirectional_node* _extremes;
   int _size;

} linked_list;


// end of struct type definitions

/* ///////////////////////////////////////////////////////////////////////// */

// functions for creating and deleting a linked_list struct

linked_list* create_linked_list();

void delete_linked_list(linked_list*);

/* ///////////////////////////////////////////////////////////////////////// */

// general functions for a linked_list

void* at_list(linked_list*, int);
void* back_list(linked_list*);
void clear_list(linked_list*);
void empty_list(linked_list*);
void* front_list(linked_list*);
void insert_into_list(linked_list*, int);
void* pop_back_list(linked_list*);
void* pop_front_list(linked_list*);
void push_back_list(linked_list*, void*);
void push_front_list(linked_list*, void*);
void remove_from_list(linked_list*, int);
int size_of_list(linked_list*);

/* ///////////////////////////////////////////////////////////////////////// */

#endif /* __LINKED_LIST_H__ */
