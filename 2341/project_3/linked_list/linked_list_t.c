/* ///////////////////////////////////////////////////////////////////////// */
/*                                                                           */
/* Author: Jarret Shook                                                      */
/*                                                                           */
/* Module: linked_list_t.c                                                   */
/*                                                                           */
/* Modifications: 23-Oct-12 - Created                                        */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Timeperiod: EVN4                                                          */
/*                                                                           */
/* Notes: Test file for linked_list.h and c                                  */
/*                                                                           */
/* ///////////////////////////////////////////////////////////////////////// */

#include "linked_list.h"
#include "test.h"

/* ///////////////////////////////////////////////////////////////////////// */
/* helper functions */

linked_list* create()
{
   linked_list* _List = create_linked_list();
   return _List;
}

void delete(linked_list* _List)
{
   delete_linked_list(_List);
}

void push_back(linked_list* _List, int* _Arr, int _Size)
{
   int i;
   
   for (i = 0; i < _Size; ++i) push_back_list(_List, &_Arr[i]);
}

void contents(linked_list* _List)
{
   int i;

   for (i = 0; i < _List->_size; ++i) printf("%d ", *((int*)at_list(_List,i)));
}

/* ///////////////////////////////////////////////////////////////////////// */

/* test functions */

void create_delete()
{
   begin("create_delete");

   linked_list* _List = create();

   printf("Created\n");

   delete(_List);

   printf("Deleted\n");

   end();
}

void test_push()
{
   int i;

   begin("test_push");

   int arr[] = { 1, 5, 9, 87, 33, 23, 22, 12, 32, 55, 100, 101 };
   
   linked_list* _List = create();

   push_back(_List, arr, 12);
   
   printf("Array Pushed back\n");

   for ( i = 0; i < 2000; ++i)
   {
      int* temp = (int*)malloc(sizeof(int));
      *temp = i;
      push_back_list(_List, temp);
   }

   printf("Pushed back elements");

   end();
}

void test_at()
{
   int i;

   begin("test_at");

   int arr[] = { 1, 5, 9, 87, 33, 23, 22, 12, 32, 55, 100, 101 };
   
   linked_list* _List = create();

   push_back(_List, arr, 12);
   
   printf("Array Pushed back\n");

   for ( i = 0; i < 2000; ++i)
   {
      int* temp = (int*)malloc(sizeof(int));
      *temp = i;
      push_back_list(_List, temp);
   }

   printf("Pushed back elements");

   contents(_List);

   end();
}

void test_clear()
{
   int i;

   begin("test_clear");

   int arr[] = { 1, 5, 9, 87, 33, 23, 22, 12, 32, 55, 100, 101 };
   
   linked_list* _List = create();

   push_back(_List, arr, 12);
   
   printf("Array Pushed back\n");

   for ( i = 0; i < 2000; ++i)
   {
      int* temp = (int*)malloc(sizeof(int));
      *temp = i;
      push_back_list(_List, temp);
   }

   printf("Pushed back elements");

   clear_list(_List);

   end();
}

void test_front()
{
   int i;

   begin("test_front");

   int arr[] = { 1, 5, 9, 87, 33, 23, 22, 12, 32, 55, 100, 101 };
   
   linked_list* _List = create();

   push_back(_List, arr, 12);
   
   printf("Array Pushed back\n");

   for ( i = 0; i < 2000; ++i)
   {
      int* temp = (int*)malloc(sizeof(int));
      *temp = i;
      push_back_list(_List, temp);
   }

   printf("Pushed back elements");

   while (_List->_size != 0)
   {
      printf("%d ", *((int*)front_list(_List)));
      remove_from_list(_List, 0);
   }

   printf("\n");

   end();
}

void test_back()
{
   int i;

   begin("test_back");

   int arr[] = { 1, 5, 9, 87, 33, 23, 22, 12, 32, 55, 100, 101 };
   
   linked_list* _List = create();

   push_back(_List, arr, 12);
   
   printf("Array Pushed back\n");

   for ( i = 0; i < 2000; ++i)
   {
      int* temp = (int*)malloc(sizeof(int));
      *temp = i;
      push_back_list(_List, temp);
   }

   printf("Pushed back elements");

   while (_List->_size != 0)
   {
      printf("%d ", *((int*)back_list(_List)));
      remove_from_list(_List, _List->_size - 1);
   }

   printf("\n");

   end();
}

void test_pop_back()
{
   int i;

   begin("test_pop_back");

   int arr[] = { 1, 5, 9, 87, 33, 23, 22, 12, 32, 55, 100, 101 };
   
   linked_list* _List = create();

   push_back(_List, arr, 12);
   
   printf("Array Pushed back\n");

   for ( i = 0; i < 2000; ++i)
   {
      int* temp = (int*)malloc(sizeof(int));
      *temp = i;
      push_back_list(_List, temp);
   }

   printf("Pushed back elements");

   while (_List->_size != 0)
   {
      printf("%d ", *((int*)pop_back_list(_List)));
   }

   printf("\n");

   end();
}

/* ///////////////////////////////////////////////////////////////////////// */

/* main */

int main()
{

   create_delete();
   test_push();
   test_at();
   test_clear();
   test_front();
   test_back();
   test_pop_back();

   return 0;
}

/* ///////////////////////////////////////////////////////////////////////// */
