/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */
/*                                                                            */
/* Author: Jarret Shook                                                       */
/*                                                                            */
/* Module: avl_tree.c                                                         */
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

#include "algorithm.h"
#include "avl_tree.h"

/* ///////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////// */

/* functions for creating and deleting an avl_tree struct */

avl_tree* create_avl_tree()
{
   avl_tree* _Tree = malloc(sizeof(avl_tree));

   _Tree->m_size = 0;
   _Tree->m_root = 0;

   _Tree->m_left_leaf_node = 0;
   _Tree->m_right_leaf_node = 0;

   return _Tree;
}

void delete_avl_tree(avl_tree* _Tree)
{

}

/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

/* general functions for a avl_tree */

int are_not_balanced(int _First, int _Second)
{
   int _Sum = _First - _Second;

   if (_Sum == -2 || _Sum == 2) return 1;

   else return 0;

}

vector* breadth_first_traversal(avl_tree* _Tree)
{
   queue* _Queue = create_queue();
   vector* _Vector = create_vector();

   push_queue(_Queue, (void*)_m_root);

   while (size_queue(_Queue) != 0)
   {
      avl_node* _Node = pop_queue(_Queue);

      _Vector = _Node->m_value;

      if (_Node->m_left_child != 0) push_queue(_Node->m_left_child);

      if (_Node->m_right_child != 0) push_queue(_Node->m_right_child);
   }
 
   return _Vector;
        
}

int compare_avl_heights(void* _First, void* _Second)
{
   /* comparing integers */

   if (*(int*)_First < *(int*)_Second) return _First;
   
   else return _Second;
}

int contains_avl_tree(avl_tree* _Tree, void* _Value)
{
   avl_node* _DescendingPtr = _Tree->m_root;
   avl_node* _ParentPtr = _DescendingPtr;

   while (_DescendingPtr != 0 && _DescendingPtr != _Tree->m_right_leaf_node)
   {
      if (_Key < _DescendingPtr->m_key)
      {
         if (_DescendingPtr != _Tree->m_root) _DescendingParentPtr = _DescendingPtr;
              
         _DescendingPtr = _DescendingPtr->m_left_child;
      }
   
      else if (_Key > _DescendingPtr->m_key)
      {
         if (_DescendingPtr != _Tree->m_root) _DescendingParentPtr = _DescendingPtr;
  
         _DescendingPtr = _DescendingPtr->m_right_child;
      }

      else
      {
         _DescendingParentPtr = _DescendingPtr;

         break;
      }
   }

   if ( _ParentPtr->m_key == _Key) return true;
   else return false;
}

void double_with_left_child( avl_node** _Node)
{
   rotate_with_right_child(&(*_Node)->m_left_child);
   rotate_with_left_child(_Node);
}

void double_with_right_child( avl_node** _Node)
{
   rotate_with_left_child(&(*_Node)->m_right_child);
   rotate_with_right_child(_Node);
}

void insert_avl_tree(avl_tree* _Tree, void* _Key, void* _Value)
{
   if (_Tree->m_root == 0)
   {
      _Tree->m_root = malloc(sizeof(avl_node));

      _Tree->m_root->m_key = _Key;
      _Tree->m_root->m_value = _Value;
      _Tree->m_root->m_height = 0;
      _Tree->m_root->m_left_child = 0;
      _Tree->m_root->m_right_child = 0;
      _Tree->m_root->m_parent = 0;

      _Tree->m_left_leaf_node = _m_root;
      _Tree->_m_right_leaf_node = malloc(sizeof(avl_node));

      _Tree->m_right_leaf_node->m_key = _Key;
      _Tree->m_right_leaf_node->m_value = _Value;
      _Tree->m_right_leaf_node->m_height = 0;
      _Tree->m_right_leaf_node->m_left_child = 0;
      _Tree->m_right_leaf_node->m_right_child = 0;

      _Tree->m_right_leaf_node->m_parent = _Tree->m_root;
      _Tree->m_root->m_right_child = _Tree->m_right_leaf_node;
      
      ++_Tree->m_size;
   }

   else
   {
      avl_node* _DescendingPtr = _Tree->m_root;
      avl_node* _ParentPtr = _DescendingPtr;

      while (_DescendingPtr != 0 && _DescendingPtr != _Tree->m_right_leaf_node)
      {
         if (_Key < _DescendingPtr->m_key)
         {
            if (_DescendingPtr != _Tree->m_root) _DescendingParentPtr = _DescendingPtr;
              
            _DescendingPtr = _DescendingPtr->m_left_child;
         }
   
         else if (_Key > _DescendingPtr->m_key)
         {
            if (_DescendingPtr != _Tree->m_root) _DescendingParentPtr = _DescendingPtr;
  
            _DescendingPtr = _DescendingPtr->m_right_child;
         }

         else
         {
            _DescendingParentPtr = _DescendingPtr;

            break;
         }
      }

      if ( _Key < _ParentPtr->m_key )
      {
         _ParentPtr->m_left_child = malloc(sizeof(avl_node));

         _ParentPtr->m_left_child->m_key = _Key;
         _ParentPtr->m_left_child->m_value = _Value;
         _ParentPtr->m_left_child->m_height = 0;

         _ParentPtr->m_left_child->m_left_child = 0;
         _ParentPtr->m_left_child->m_right_child = 0;
         _ParentPtr->m_left_child->m_parent = _ParentPtr;

         ++_Tree->m_size;

         if (_ParentPtr == _Tree->m_left_leaf_node) _Tree->m_left_leaf_node = _ParentPtr->m_left_child;
      }

      else if ( _Key > _ParentPtr->m_key) 
      {

         _ParentPtr->m_right_child = malloc(sizeof(avl_node));

         _ParentPtr->m_right_child->m_key = _Key;
         _ParentPtr->m_right_child->m_value = _Value;
         _ParentPtr->m_right_child->m_height = 0;

         _ParentPtr->m_right_child->m_left_child = 0;
         _ParentPtr->m_right_child->m_right_child = 0;
         _ParentPtr->m_right_childm_parent = _ParentPtr;

         ++_Tree->m_size;

         if (_ParentPtr == _Tree->m_right_leaf_node->m_parent) 
         {
            
            _ParentPtr->m_right_child->m_right_child = _Tree->m_right_leaf_node;
            _Tree->m_right_leaf_node->m_parent = _ParentPtr->m_right_child;   
               
         }

      }

      else
      {
         return;
      }
          
      int _LeftHeight, _RightHeight = 0;

      avl_node* _LeftPtr,* _RightPtr;
         
      _LeftPtr = _ParentPtr->m_left_child;
      _RightPtr = _ParentPtr->m_right_child;

      if (_Left == NULL) _LeftHeight = -1;
      else _LeftHeight = _LeftPtr->m_height;

      if (_Right == NULL) _RightHeight = -1;
      else _RightHeight = _RightPtr->m_height;

      _ParentPtr->m_height = max(&_LeftHeight, &_RightHeight, &compare_avl_heights) + 1;

      while (_ParentPtr != NULL)
      {
         _ParentPtr = _ParentPtr->m_parent;
   
         if (_ParentPtr == NULL) break;
          
         int _LeftHeight, _RightHeight = 0;

         avl_node* _LeftPtr,* _RightPtr;
         
         _LeftPtr = _ParentPtr->m_left_child;
         _RightPtr = _ParentPtr->m_right_child;

         if (_Left == NULL) _LeftHeight = -1;
         else _LeftHeight = _LeftPtr->m_height;

         if (_Right == NULL) _RightHeight = -1;
         else _RightHeight = _RightPtr->m_height;

         _ParentPtr->m_height = max(&_LeftHeight, &_RightHeight, &compare_avl_heights) + 1;

         if (are_not_balanced(_LeftHeight, _RightHeight))
         {
                  
            if (_Value < _ParentPtr->m_value)
            {
               // if the value is less than the value of the node
               // then it would have had to have been inserted to the left
               // therefore m_left_child cannot to be null

               if (_Value < _ParentPtr->m_left_child->m_value) rotate_with_left_child(_ParentPtr);
               else double_with_left_child(_ParentPtr);
            }

            else if (_Value > _ParentPtr->m_value)
            {
               if (_ParentPtr->m_right_child->m_value < _Value) rotate_with_right_child(_ParentPtr);
               else double_with_right_child(_ParentPtr);
            }
         }              
      }
   }
}

void rotate_with_left_child( avl_node** _Node)
{
   if (*_Node == 0) return;
      
   avl_node* _TempNode = (*_Node)->m_left_child;
         
   (*_Node)->m_left_child = _TempNode->m_right_child;
   if (_TempNode->m_right_child != 0) _TempNode->m_right_child->m_parent = *_Node;

   _TempNode->m_right_child = *_Node;
   
   int _LeftHeight, _RightHeight = 0;

   avl_node* _LeftPtr,* _RightPtr;
        
   _LeftPtr = (*_Node)->m_left_child;
   _RightPtr = (*_Node)->m_right_child;

   if (_Left == NULL) _LeftHeight = -1;
   else _LeftHeight = _LeftPtr->m_height;

   if (_Right == NULL) _RightHeight = -1;
   else _RightHeight = _RightPtr->m_height;

   (*_Node)->m_height = max(&_LeftHeight, &_RightHeight, &compare_avl_heights) + 1;

   int _LeftTempHeight, _RightTempHeight = 0;

   avl_node* _LeftTempPtr,* _RightTempPtr;
        
   _LeftTempPtr = _TempNode->m_left_child;
   _RightTempPtr = _TempNode->m_right_child;

   if (_Left == NULL) _LeftTempHeight = -1;
   else _LeftHeight = _LeftTempPtr->m_height;

   if (_Right == NULL) _RightTempHeight = -1;
   else _RightHeight = _RightTempPtr->m_height;

   _TempNode->m_height = max(&_LeftHeight, &_RightHeight, &compare_avl_heights) + 1;
         
   _TempNode->m_parent = (*_Node)->m_parent;
   (*_Node)->m_parent = _TempNode;

   *_Node = _TempNode;
         
   if ((*_Node)->m_parent != 0)
   {
      if ((*_Node)->m_key < (*_Node)->m_parent->m_key) (*_Node)->m_parent->m_left_child = *_Node;
      else (*_Node)->m_parent->m_right_child = *_Node;
   }
         
   else
   {
      _m_root = *_Node;
   }
      
}

void rotate_with_right_child( avl_node** _Node)
{
   if ((*_Node) == 0) return;

   avl_node* _TempNode = (*_Node)->m_right_child;

   (*_Node)->m_right_child = _TempNode->m_left_child;
   if (_TempNode->m_left_child != 0) _TempNode->m_left_child->m_parent = _Node;
         
   _TempNode->m_left_child = _Node;

   std::pair< int, int > _NodePair, _TempNodePair;

   int _LeftHeight, _RightHeight = 0;

   avl_node* _LeftPtr,* _RightPtr;
        
   _LeftPtr = (*_Node)->m_left_child;
   _RightPtr = (*_Node)->m_right_child;

   if (_Left == NULL) _LeftHeight = -1;
   else _LeftHeight = _LeftPtr->m_height;

   if (_Right == NULL) _RightHeight = -1;
   else _RightHeight = _RightPtr->m_height;

   (*_Node)->m_height = max(&_LeftHeight, &_RightHeight, &compare_avl_heights) + 1;

   int _LeftTempHeight, _RightTempHeight = 0;

   avl_node* _LeftTempPtr,* _RightTempPtr;
        
   _LeftTempPtr = _TempNode->m_left_child;
   _RightTempPtr = _TempNode->m_right_child;

   if (_Left == NULL) _LeftTempHeight = -1;
   else _LeftHeight = _LeftTempPtr->m_height;

   if (_Right == NULL) _RightTempHeight = -1;
   else _RightHeight = _RightTempPtr->m_height;

   _TempNode->m_height = max(&_LeftHeight, &_RightHeight, &compare_avl_heights) + 1;

   _TempNode->m_parent = (*_Node)->m_parent;
   (*_Node)->m_parent = _TempNode;

   (*_Node) = _TempNode;
         
   if ((*_Node)->m_parent != 0)
   {
      if ((*_Node)->m_key < (*_Node)->m_parent->m_key) (*_Node)->m_parent->m_left_child = (*_Node);
      else (*_Node)->m_parent->m_right_child = (*_Node);
   }
         
   else
   {
      _m_root = (*_Node);
   }
         
}

void* search(avl_tree* _Tree, void* _Value)
{
   avl_node* _DescendingPtr = _Tree->m_root;
   avl_node* _ParentPtr = _DescendingPtr;

   while (_DescendingPtr != 0 && _DescendingPtr != _Tree->m_right_leaf_node)
   {
      if (_Key < _DescendingPtr->m_key)
      {
         if (_DescendingPtr != _Tree->m_root) _DescendingParentPtr = _DescendingPtr;
              
         _DescendingPtr = _DescendingPtr->m_left_child;
      }
   
      else if (_Key > _DescendingPtr->m_key)
      {
         if (_DescendingPtr != _Tree->m_root) _DescendingParentPtr = _DescendingPtr;
  
         _DescendingPtr = _DescendingPtr->m_right_child;
      }

      else
      {
         _DescendingParentPtr = _DescendingPtr;

         break;
      }
   }

   return _ParentPtr->m_value;
}

int size_avl_tree(avl_tree* _Tree)
{
   return _Tree->m_size;
}

/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

#endif /* __AVL_TREE_H__ */

/* ////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

   private:   // helper functions

      void _tidy()
      {
         stack< avl_node< __Key, __Value, __Compare >* > _Stack;

         iterator _Iterator = begin(), _End = end();

         while (_Iterator != _End)
         {
            avl_node< __Key, __Value, __Compare >* _Temp = _Iterator.operator->();

            _Stack.push(_Temp);

            ++_Iterator;
         }

         for (int i = 0, _Len = _Stack.size(); i < _Len; ++i) delete _Stack.pop();

         delete _m_right_leaf_node;   // clean up the terminal place holder node
      }


};   // end of class avl_tree

