/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */
/*                                                                           */
/* Author: Jarret Shook                                                      */
/*                                                                           */
/* Module: stack.c                                                           */
/*                                                                           */
/* Modifications:                                                            */
/*                                                                           */
/* 16-Feb-13: Version 1.0: Created                                           */
/*                                                                           */
/* Timeperiod: ev6                                                           */
/*                                                                           */
/* Notes: An empty stack is defined to be a stack struct that points to an   */
/*        stack struct of size 0.                                            */
/*        To Properly use and free memory use the create or delete functions */
/*                                                                           */
/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

#include "stack.h"

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* functions for creating and deleting an stack struct */

stack* create_stack()
{
   stack* _Stack = malloc(sizeof(stack));

   _Stack->m_list = create_linked_list();

   _Stack->m_size = 0;

   return _Stack;
}

void delete_stack(stack* _Stack)
{
   delete_linked_list(_Stack->m_list);

   free(_Stack);
}

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* general functions for a stack */

void pop_stack(stack* _Stack)
{
   return pop_back_linked_list(_Stack->m_list);
}

void push_stack(stack* _Stack, void* _Data)
{
   push_back(_Stack->m_list, _Data);
}

int size_stack(stack* _Stack)
{
   return _Stack->m_size;
}

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */
