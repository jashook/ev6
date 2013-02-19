/* ///////////////////////////////////////////////////////////////////////// */
/*                                                                           */
/* Author: Jarret Shook                                                      */
/*                                                                           */
/* Module: test.c                                                            */
/*                                                                           */
/* Modifications: 23-Oct-12 - Created                                        */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Timeperiod: EVN4                                                          */
/*                                                                           */
/* Notes: general library for test functions                                 */
/*                                                                           */
/* ///////////////////////////////////////////////////////////////////////// */

#include "test.h"

/* ///////////////////////////////////////////////////////////////////////// */

/* functions */

void begin(const char* _String)
{
   printf("///////////////////////////////////////////////////////////////////////////////\n");

   printf("START test: ");
   printf(_String);
   printf("\n");  
}

void end(const char* _String)
{
   printf("\n");
   printf("END TEST: ");
   printf(_String);
   printf("\n");
   printf("////////////////////////////////////////////////////////////////////////////////\n");
}

/* ///////////////////////////////////////////////////////////////////////// */

int main()
{

   return 0;

}
