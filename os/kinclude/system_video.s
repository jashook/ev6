/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/* Author: Jarret Shook                                                       */
/*                                                                            */
/* Module: system_video.s                                                     */
/*                                                                            */
/* Modifications:                                                             */
/*                                                                            */
/* 26-Aug-13: Version 1.0: Last Updated                                       */
/* 26-Aug-13: Version 1.0: Created                                            */
/*                                                                            */
/* Timeperiod: ev7n                                                           */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

#ifndef __SYSTEM_VIDEO_S__
#define __SYSTEM_VIDEO_S__

/* ************************************************************************** */
/* ************************************************************************** */
/* Function: mailbox_read                                                     */
/*                                                                            */
/* Parameters:                                                                */
/*                                                                            */
/*    r0: 4 bits of which mailbox to write to                                 */
/*    r1: address of the mailbox                                              */
/*                                                                            */
/* Returns:                                                                   */
/*                                                                            */
/*    r0: NULL if failed                                                      */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
/* Function: mailbox_write                                                    */
/*                                                                            */
/* Parameters:                                                                */
/*                                                                            */
/*    r0: 28 bits to be written to the GPU mailbox                            */
/*    r1: 4 bits of which mailbox to write to                                 */
/*    r2: address of the mailbox                                              */
/*                                                                            */
/* Returns:                                                                   */
/*                                                                            */
/*    r0: NULL if failed                                                      */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

mailbox_write:

      tst   r0, #0b1111          @ test the last four bits to see if they are 0

      movne r0, #0               @ failed

      movne pc, lr               @ return if true

      cmp   r1, #15              @ see if r1 is greater than 4 bits

      movhi r0, #0               @ failed

      movhi pc, lr               @ return if true

wait_read:

      ldr   r3, [r2, #0x18]      @ status to see if read

      tst   r3, #0x80000000      @ see if the top bit is 0, 8 = 1000

      bne   wait_read

      add   r0, r0, r1           @ make a 32 bit "letter" to send

      str   r0, [r2, #20]        @ write the "letter"

      mov   r0, #1               @ success

      mov   pc, lr

/* ************************************************************************** */
/* ************************************************************************** */
/* Function: video_init                                                       */
/*                                                                            */
/* Parameters:                                                                */
/*                                                                            */
/*    r0: address of the mailbox needed to send information to the GPU        */
/*                                                                            */
/* Returns:                                                                   */
/*                                                                            */
/*    r0: NULL if failed                                                      */
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/*    Receives the frame buffer from the GPU and initializes it               */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

video_init:
                    
         

/* ************************************************************************** */
/* ************************************************************************** */

#endif /* __SYSTEM_VIDEO_S__ */

/* ************************************************************************** */
/* ************************************************************************** */
