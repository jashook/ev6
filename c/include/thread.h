/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */
/*                                                                            */
/* Author: Jarret Shook                                                       */
/*                                                                            */
/* Module: thread.h                                                           */
/*                                                                            */
/* Modifications:                                                             */
/*                                                                            */
/* 10-June-13: Version 1.0: Created                                           */
/*                                                                            */
/* Timeperiod: ev6                                                            */
/*                                                                            */
/* Notes:                                                                     */
/*        To Properly use and free memory use the create or delete functions  */
/*                                                                            */
/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

#ifndef __THREAD_H__
#define __THREAD_H__

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

#include "queue.h"
#include "stack.h"
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* type definitions */

typedef struct thread
{

   int m_exit_code;
   int m_is_active ;
   int m_is_alive;
   size_t m_id;
   char* m_name;
   lock* m_lock;
   tid_t m_tid;

} thread;

typedef struct avl_tree
{
   avl_node* m_root;
   avl_node* m_left_leaf_node;
   avl_node* m_right_leaf_node;
   int m_size;

} avl_tree;

/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

/* functions for creating and deleting an avl_tree struct */

avl_tree* create_avl_tree();

void delete_avl_tree(avl_tree*);

/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

/* general functions for a avl_tree */

vector* breadth_first_traversal(avl_tree*);
int compare(void*, void*);
int contains_avl_tree(avl_tree*, void*);
void insert_avl_tree(avl_tree*, void*, void*);
void remove_avl_tree(avl_tree*, void*);
void* search(avl_tree*, void*);
int size_avl_tree(avl_tree*);

/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

#endif /* __AVL_TREE_H__ */

/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */
