/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */
/*                                                                           */
/* Author: Jarret Shook                                                      */
/*                                                                           */
/* Module: queue.c                                                           */
/*                                                                           */
/* Modifications:                                                            */
/*                                                                           */
/* 16-Feb-13: Version 1.0: Created                                           */
/*                                                                           */
/* Timeperiod: ev6                                                           */
/*                                                                           */
/* Notes: An empty queue is defined to be a queue struct that points to an   */
/*        queue struct of size 0.                                            */
/*        To Properly use and free memory use the create or delete functions */
/*                                                                           */
/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

#include "queue.h"

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* functions for creating and deleting an stack struct */

queue* create_queue()
{
   queue* _Queue = malloc(sizeof(queue));

   _Queue->m_list = create_linked_list();

   _Queue->m_size = 0;

   return _Queue;
}

void delete_stack(queue* _Queue)
{
   delete_linked_list(_Queue->m_list);

   free(_Queue);
}

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* general functions for a stack */

void pop_queue(queue* _Queue)
{
   return pop_back_linked_list(_Queue->m_list);
}

void push_queue(queue* _Queue, void* _Data)
{
   push_back_linked_list(_Queue->m_list, _Data);
}

int size_queue(queue* _Queue)
{
   return _Queue->m_size;
}

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */
