/* ///////////////////////////////////////////////////////////////////////// */

#include "linked_list.h"

/* ///////////////////////////////////////////////////////////////////////// */

/* general function for creating and deleting a linked_list struct           */

/* ///////////////////////////////////////////////////////////////////////// */

linked_list* create_linked_list()
{

   linked_list* _List = (linked_list*)malloc(sizeof(linked_list));
   _List->_node = 0;
   _List->_size = 0;

   return _List;

}

void delete_linked_list(linked_list* _List)
{

   clear_list(_List);  
   free(_List);

}

/* ///////////////////////////////////////////////////////////////////////// */

/* General functions for a linked_list struct                                */

/* ///////////////////////////////////////////////////////////////////////// */

void* at_list(linked_list* _List, int _Position)
{

   int _Pos;
   bidirectional_node* _List_ptr = _List->_node;

   for (_Pos = 0; _Pos < _Position; ++_Pos) _List_ptr = _List_ptr->_next;

   return _List_ptr->_data;

}

void* back_list(linked_list* _List)
{

   int _Pos;
   bidirectional_node* _List_ptr = _List->_node;

   for (_Pos = 0; _Pos < _List->_size - 1; ++_Pos) _List_ptr = _List_ptr->_next;

   return _List_ptr->_data;

}

void clear_list(linked_list* _List)
{

   bidirectional_node* _List_ptr = _List->_node;
   bidirectional_node* _List_behind_ptr = _List->_node;

   while(_List_ptr != 0)
   {
      
      _List_ptr = _List_ptr->_next;
      free(_List_behind_ptr);
      _List_behind_ptr = _List_ptr;
   }

   _List->_node = 0;
   _List->_size = 0;

}

int is_list_empty(linked_list* _List)
{
   return _List->_size == 0;
}

void empty_list(linked_list* _List)
{

   clear_list(_List);

}

void* front_list(linked_list* _List)
{

   return _List->_node->_data;

}

void* pop_back_list(linked_list* _List)
{

   int _Position;
   bidirectional_node* _List_ptr = _List->_node;
   void** _Return;

   for (_Position = 0; _Position < _List->_size - 1; ++_Position) _List_ptr = _List_ptr->_next;

   _Return = _List_ptr->_data;

   if (_List->_size == 1)
   {

      free(_List->_node);
      _List->_size = 0;
      _List->_node = 0;
   }

   else
   {
      _List_ptr = _List_ptr->_prev;
      free(_List_ptr->_next);
      _List_ptr->_next = 0;
      --_List->_size;
   }

   return _Return;

}

void push_back_list(linked_list* _List, void* _Data)
{
   
   int _Pos;
   bidirectional_node* _List_ptr = _List->_node;
   
   for (_Pos = 0; _Pos < _List->_size - 1; ++_Pos) _List_ptr = _List_ptr->_next;

   if (_List->_size == 0)
   {
      _List->_node = (bidirectional_node*)malloc(sizeof(linked_list));
      _List->_node->_next = 0;
      _List->_node->_data = _Data;
      ++_List->_size;
   }

   else
   {
      _List_ptr->_next = (bidirectional_node*)malloc(sizeof(linked_list));
      _List_ptr->_next->_next = 0;
      _List_ptr->_next->_prev = _List_ptr;
      _List_ptr->_next->_data = _Data;
      ++_List->_size;
   }

}

void remove_from_list(linked_list* _List, int _Position)
{
 
   int _Pos;
   bidirectional_node* _Next_ptr;
   bidirectional_node* _Prev_ptr;
   bidirectional_node* _List_ptr = _List->_node;

   if (_Position > _List->_size || _List->_size < 0) return;

   for (_Pos = 0; _Pos < _Position; ++_Pos) _List_ptr = _List_ptr->_next;

   if (_List->_size == 1)
   {
      free(_List->_node);
      _List->_node = 0;
      _List->_size = 0;
   }

   else if(_Position == 0)
   {
      _List->_node = _List_ptr->_next;
      free(_List_ptr->_next->_prev);
      --_List->_size;
   }

   else if (_Position == _List->_size - 1)
   {
      _Prev_ptr = _List_ptr->_prev;
      free(_Prev_ptr->_next);
      _Prev_ptr->_next = 0;
      --_List->_size;
   }
 
   else
   {
      _Next_ptr = _List_ptr->_next;
      _Prev_ptr = _List_ptr->_prev;
 
      _Prev_ptr->_next = _Next_ptr;
      free(_Next_ptr->_prev);
      _Next_ptr->_prev = _Prev_ptr;
      
      --_List->_size;
   }

}

int size_of_list(linked_list* _List)
{

   return _List->_size;

}
