/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */
/*                                                                            */
/* Author: Jarret Shook                                                       */
/*                                                                            */
/* Module: avl_tree.h                                                         */
/*                                                                            */
/* Modifications:                                                             */
/*                                                                            */
/* 19-Feb-13: Version 1.0: Created                                            */
/*                                                                            */
/* Timeperiod: ev6                                                            */
/*                                                                            */
/* Notes: An empty avl_tree is defined to be a avl_tree struct that points    */
/*        to an avl_tree struct of size 0.                                    */
/*        To Properly use and free memory use the create or delete functions  */
/*                                                                            */
/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

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

typedef struct avl_node
{

   int m_height;
   void* m_key;
   void* m_value;
   avl_node* m_left_child;
   avl_node* m_right_child;
   avl_node* m_parent;

} avl_node;

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
void clear_avl_tree(avl_tree*);
int contains_avl_tree(avl_tree*, void*);
void empty_avl_tree(avl_tree*);
vector* in_order_traversal(avl_tree*);
void insert_avl_tree(avl_tree*, void*, void*);
void remove_avl_tree(avl_tree*, void*);
void* search(avl_tree*, void*);
int size_avl_tree(avl_tree*);

/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

#endif /* __AVL_TREE_H__ */

/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */
