/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/* Author: Jarret Shook                                                       */
/*                                                                            */
/* Module: sleepy.c                                                           */
/*                                                                            */
/* Modifications:                                                             */
/*                                                                            */
/* 11-June-13: Version 1.0: Created                                           */
/*                                                                            */
/* Timeperiod: ev7                                                            */
/*                                                                            */
/* Notes:                                                                     */
/*    Created with the GNU C compiler (Version 4.6.3)                         */
/*    Compiles and runs with the -std=c89 (conforms to the c89 standard)      */
/*                                                                            */
/*    To compile: gcc -std=c89 sleepy.c                                       */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* Function: sleep_run                                                        */
/*                                                                            */
/* Arguements: size_t                                                         */
/*                                                                            */
/* Returns: VOID                                                              */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

void sleep_run(size_t _RunningTime)
{
   int _Count;
   pid_t _ProcessID;

   _ProcessID = getpid(); /* get the process id for the current running process or thread of execution */

   /* the pid is not always the same */

   printf("%i, START\n", (int)_ProcessID);

   for (_Count = 1; _Count < _RunningTime + 1; ++_Count)
   {

      printf("%i, TICK %i\n", (int)_ProcessID, _Count);

      sleep(1); /* suspend the current thread of execution for 1 second */

   }

}

/* ************************************************************************** */
/* ************************************************************************** */
/* Function: main                                                             */
/*                                                                            */
/* Arguements: int, char**                                                    */
/*                                                                            */
/* Returns: int                                                               */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

int main(int argc, char** argv)
{

   if (argc != 2)
   {
      sleep_run(10);
   }

   else
   {
      sleep_run(atoi(argv[1]));
   }

}
