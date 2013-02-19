/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */
/*                                                                           */
/* Author: Jarret Shook                                                      */
/*                                                                           */
/* Module: avl_tree.c                                                        */
/*                                                                           */
/* Modifications:                                                            */
/*                                                                           */
/* 19-Feb-13: Version 1.0: Created                                           */
/*                                                                           */
/* Timeperiod: ev6                                                           */
/*                                                                           */
/* Notes: An empty avl_tree is defined to be a stack avl_tree that points    */
/*        to an avl_tree struct of size 0.                                   */
/*        To Properly use and free memory use the create or delete functions */
/*                                                                           */
/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

#include "avl_tree.h"

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* functions for creating and deleting an avl_tree struct */

avl_tree* create_avl_tree()
{
   avl_tree* _Tree = malloc(sizeof(avl_tree));

   _Tree->m_root = 0;
   _Tree->m_left_leaf_node = 0;
   _Tree->m_right_leaf_node = 0;

   _Tree->m_size = 0;

   return _Tree;
}

void delete_avl_tree(avl_tree* _Tree)
{
   if (_Tree->m_root != 0) free(_Tree->m_root);
   if (_Tree->m_right_leaf_node != 0) free(_Tree->m_right_leaf_node);
   
   free(_Tree);
}

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* general functions for a avl_tree */



/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */
