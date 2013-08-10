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

#include <stdlib.h>
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

void sleep_run(const char* _Name, size_t _RunningTime)
{
   int _Count;
   pid_t _ProcessID, _ParentProcessID;

   _ProcessID = getpid(); /* get the process id for the current running process or thread of execution */

   _ParentProcessID = getppid(); /* get the parent's process id for the current running process or thread of execution */

   for (_Count = 1; _Count < _RunningTime + 1; ++_Count)
   {

      printf("%s Process with PID: %i and PPID: %i tick %i\n", _Name, (int)_ProcessID, (int)_ParentProcessID, _Count);

      /* sleep(1);  suspend the current thread of execution for 1 second */

      /* With sleep commented out the output of the ticks is not interleaved. */
      /* The output changes every time the program is run so it is fairly     */
      /* non-deterministic.  One possible explination to why this is occuring */
      /* is the two processes are executing on seperate CPUs, one cpu might   */
      /* be scheduled to run more processes then the other, making one of the */
      /* processes work faster than the other                                 */

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
   size_t _AmountOfTicks, _ReturnValue;

   if (argc != 2)
   {
      _AmountOfTicks = 10;
   }

   else
   {
      _AmountOfTicks = atoi(argv[1]);
   }

   _ReturnValue = fork();

   /* if the return value is 0 then the current process in execution is the child */
   if (_ReturnValue == 0)
   {
      sleep_run("Child", _AmountOfTicks);

      exit(0); /* exit the child process when finished */
   }

   /* non zero return value signals then the current process in execurtion is the parent process */
   else
   {

      sleep_run("Original", _AmountOfTicks);

      wait(); /* wait for the forked child process to exit and return to the parent */

   }

}
