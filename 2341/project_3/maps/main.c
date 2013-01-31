#include <stdio.h>
#include "linked_list.h"
#include "array_list.h"

int main()
{
   linked_list* _List = create_linked_list();
   int* _Int = malloc(sizeof(int));
   int* _Int2 = malloc(sizeof(int));

   *_Int2 = 45;
   *_Int = 0;

   push_back_list(_List, _Int);
   push_back_list(_List, _Int2);

   *_Int = 77;

   printf("%d\n", *((int*)at_list(_List, 0)));
   printf("%d\n", *((int*)front_list(_List)));
   printf("%d\n", *((int*)back_list(_List)));  
   printf("%d\n", size_of_list(_List));

   return 0;
}
