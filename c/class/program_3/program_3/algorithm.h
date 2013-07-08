/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/* Author: Jarret Shook                                                       */
/*                                                                            */
/* Module: algorith.h                                                         */
/*                                                                            */
/* Modifications:                                                             */
/*                                                                            */
/* 22-June-13: Last Updated                                                   */
/* 14-June-13: Version 1.0: Style change and updated to ev7                   */
/* 21-Feb-13: Version 1.0: Created                                            */
/*                                                                            */
/* Version: 1.0                                                               */
/*                                                                            */
/* Timeperiod: ev7                                                            */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

/* ************************************************************************** */
/* ************************************************************************** */

#ifdef __unix__

   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>

#elif WIN32

   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>

#else

   #include "stdlib.h"
   #include "stdio.h"
   #include "string.h"

#endif

#include <stddef.h>

/* ************************************************************************** */
/* ************************************************************************** */


void* max(void*, void*, int (*)(void*, void*));
void merge_sorted(void*, void*, void*, size_t, size_t, size_t, int (*)(void*, void*));
void mege_sort(void*, size_t, size_t, int (*)(void*, void*));
void* min(void*, void*, int (*)(void*, void*));
unsigned long next_power_of_2(unsigned long);

/* ************************************************************************** */
/* ************************************************************************** */

#endif /* __ALGORITHM_H__ */

/* ************************************************************************** */
/* ************************************************************************** */
