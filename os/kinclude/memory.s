/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/* Author: Jarret Shook                                                       */
/*                                                                            */
/* Module: memory.s                                                           */
/*                                                                            */
/* Modifications:                                                             */
/*                                                                            */
/* 13-Aug-13: Version 1.0: Last Updated                                       */
/* 13-Aug-13: Version 1.0: Created                                            */
/*                                                                            */
/* Timeperiod: ev7n                                                           */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

#ifndef __MEMORY_S__
#define __MEMORY_S__

/* ************************************************************************** */
/* ************************************************************************** */

.include "alloc.s"

/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Function: page_init                                                        */
/*                                                                            */
/* Parameters:                                                                */
/*                                                                            */
/*    VOID                                                                    */
/*                                                                            */
/* Returns:                                                                   */
/*                                                                            */
/*    VOID                                                                    */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

page_init:

/* ************************************************************************** */
/* ************************************************************************** */
/* Function: simple_partitioning_init                                         */
/*                                                                            */
/* Parameters:                                                                */
/*                                                                            */
/*    r0: beginning address to start initializing memory                      */
/*    r1: size of memory in MB                                                */
/*                                                                            */
/* Returns:                                                                   */
/*                                                                            */
/*    VOID                                                                    */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

simple_partitioning_init:

         @ Initializes fixed partitions of 4KB each
         @ uses r1 to determine how many partitions

partition_size:   #0x00001000

         mov   r3, r0

         mov   r5, #0            @ zero byte

start_partition:

         mov   r4, #0x00001000   @ 4,096 bytes

continue_partition:

         subs  r4, #1

         strb  r5, [r0], #1   @ r0 = *(r5++)

         bne   continue_partition

         subs  r1, #0x00001000

         bne   start_partition
         
         mov   pc, lr


/* ************************************************************************** */
/* ************************************************************************** */

#endif /* __MEMORY_S__ */

/* ************************************************************************** */
/* ************************************************************************** */