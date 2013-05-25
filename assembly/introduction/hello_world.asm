;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Author: Jarret Shook
;
; Module: hello_world.asm
;
; Modifications:
;
; 17-April-13: Version 1.0: Created
;
; Timeperiod: ev6
;
; Notes: prints a message to standard out via a hardware interupt.
;        works only on linux because it is issuing a kernal system call
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section .data

message  db    'Hello!', 0, 0Ah
length   equ   $ - message       ; message's length constant

section .text
global _start                    ; declared for linker

_start:                          ; entry point

         mov   edx, length       ; length
         mov   ecx, message      ; message
         mov   ebx, 1            ; file descriptor(stdout)
         mov   eax, 4            ; system call number (sys_write)
         int   080h               ; interupt
   
         mov   eax, 1            ; system call number (sys_exit)
         int   080h               ; interupt

   
