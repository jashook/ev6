/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/* Author: Jarret Shook                                                       */
/*                                                                            */
/* Module: program_4.c                                                        */
/*                                                                            */
/* Modifications:                                                             */
/*                                                                            */
/* 30-June-13: Version 1.0: Last Updated                                      */
/* 30-June-13: Version 1.0: Created                                           */
/*                                                                            */
/* Timeperiod: ev6n                                                           */
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/*    To compile: gcc *.c -pthread                                            */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pair.h"

/* ************************************************************************** */
/* ************************************************************************** */

typedef struct philosopher
{
   size_t m_id;

} philosopher;

/* ************************************************************************** */
/* ************************************************************************** */

/* static functions local to this file */

static tuple* init_semaphores(int _Size, int _Destroy)
{

   static tuple* _Tuple = 0;

   static pthread_mutex_t _Lock = PTHREAD_MUTEX_INITIALIZER;

   if (_Tuple == 0)
   {

      pthread_mutex_lock(&_Lock);

      if (_Tuple != 0)
      {
   
         pthread_mutex_unlock(&_Lock); /* make sure the lock is released even if returning early */

         return _Tuple; /* guarentee that the first thead to initialize the _Tuple is the only one to initialize it */

      }

      int _Index;

      _Tuple = malloc(sizeof(tuple));

      tuple_create(_Tuple, _Size);

      sem_t* _Semaphores = malloc(sizeof(sem_t) * _Size);

      for (_Index = 0; _Index < _Size; ++_Index) 
      {

         sem_init(_Semaphores + _Index, 0, 1);

         tuple_set(_Tuple, _Index, _Semaphores + _Index);

      }

      pthread_mutex_unlock(&_Lock);

   }

   if (_Destroy && _Tuple)
   {

      pthread_mutex_lock(&_Lock);
      
      if (!_Tuple)
      {

         pthread_mutex_unlock(&_Lock);

          return _Tuple; /* guarentee that the first thread to destroy the _Tuple is the only one to destroy it */

      }

      int _Index;

      for (_Index = 0; _Index < _Size; ++_Index) sem_destroy(tuple_get(_Tuple, _Index));

      free(tuple_get(_Tuple, 0));

      tuple_free(_Tuple);

      free(_Tuple);

      _Tuple = 0;

      pthread_mutex_unlock(&_Lock);

   }

   return _Tuple;

}

static sem_t* init_room_semaphore(int _Size, int _Destroy)
{

   static sem_t* _Sem = 0;

   static pthread_mutex_t _Lock = PTHREAD_MUTEX_INITIALIZER;

   if (_Sem == 0)
   {

      pthread_mutex_lock(&_Lock);

      if (_Sem != 0) return _Sem; /* guarentee that the first thead to initialize the _Tuple is the only one to initialize it */

      _Sem = malloc(sizeof(sem_t));

      sem_init(_Sem, 0, _Size);

      pthread_mutex_unlock(&_Lock);

   }

   if (_Destroy && _Sem)
   {

      pthread_mutex_lock(&_Lock);
      
      if (!_Sem)
      {

         pthread_mutex_unlock(&_Lock);

          return _Sem; /* guarentee that the first thread to destroy the _Tuple is the only one to destroy it */

      }

      int _Index;

      sem_destroy(_Sem);

      free(_Sem);

      _Sem = 0;

      pthread_mutex_unlock(&_Lock);

   }

   return _Sem;

}

/* ************************************************************************** */
/* ************************************************************************** */

/* function declarations */

void eat(int);
void* run_philosophers(void*);
void start_philosophers(int);
void think(int);

/* ************************************************************************** */
/* ************************************************************************** */

int main(int _Argc, char** _Argv)
{

   size_t _PhilosopherAmount;

   srand(time(NULL));

   if (_Argc < 2) _PhilosopherAmount = 5;

   else _PhilosopherAmount = atoi(_Argv[1]);

   start_philosophers(_PhilosopherAmount);

   return 0;

}

/* ************************************************************************** */
/* ************************************************************************** */

void eat(int _Index)
{

   int _EatTime = rand() % 3 + 1;

   printf("Philosopher %d has started eating\n", _Index);

   sleep(_EatTime);

   printf("Philosopher %d has stopped eating\n", _Index);

}

void* run_philosophers(void* _Args)
{

   int _Count = 1;

   size_t _Size = *(int*)((pair*)_Args)->m_first;
   size_t _Index = *(int*)((pair*)_Args)->m_second;
   
   /* first (_Size) semaphores are the forks, last (_Size - 1) semaphores are the rooms */

   tuple* _Tuple = init_semaphores(_Size, 0);

   sem_t* _RoomSem = init_room_semaphore(_Size, 0);

   while(_Count--)
   {

      think(_Index);
      
      sem_wait(_RoomSem);

      sem_wait(tuple_get(_Tuple, _Index));

      sem_wait(tuple_get(_Tuple, (_Index + 1) % _Size));

      eat(_Index);

      sem_post(tuple_get(_Tuple, (_Index + 1) % _Size));

      sem_post(tuple_get(_Tuple, _Index));

      sem_post(_RoomSem);

   }

}

void start_philosophers(int _Number)
{

   _Number = _Number > 2 ? _Number : 2; /* make sure there are at least two threads */

   pthread_t* _Threads = malloc(sizeof(pthread_t) * _Number);

   pair* _Args = malloc(sizeof(pair) * _Number);

   size_t _ReturnCode;

   void* _Status;

   int _Index;
   

   for (_Index = 0; _Index < _Number; ++_Index) 
   {

      int* _NumberCopy = malloc(sizeof(int));

      *_NumberCopy = _Number;

      _Args[_Index].m_first = _NumberCopy;

      int* _IndexCopy = malloc(sizeof(int));

      *_IndexCopy = _Index;

      _Args[_Index].m_second = _IndexCopy;

      pthread_create(_Threads + _Index, 0, run_philosophers, _Args + _Index);

   }

   for (_Index = 0; _Index < _Number; ++_Index) pthread_join(_Threads[_Index], &_Status);

   init_semaphores(0, 1);

   init_room_semaphore(0, 1);

   for (_Index = 0; _Index < _Number; ++_Index)
   {

      free(_Args[_Index].m_first); 

      free(_Args[_Index].m_second);

   }

   free(_Threads);
   free(_Args);

}

void think(int _Index)
{

   int _ThinkTime = rand() % 5 + 3;

   printf("Philosopher %d has started thinking\n", _Index);

   sleep(_ThinkTime);

   printf("Philosopher %d has stopped thinking\n", _Index);

}

