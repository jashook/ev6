;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Author: Jarret Shook
;
; Module: dynamic_array.asm
;
; Modifications:
;
; 20-May-13: Version 1.0: Last Updated 
; 20-May-13: Version 1.0: Created
;
; Timeperiod: ev6
;
; Assembler: nasm -f elf64 array.asm
; ld -o array.asm
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%ifndef __DYNAMIC_ARRAY_ASM__
%define __DYNAMIC_ARRAY_ASM__

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section .data

; Nothing to define

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section .bss

; Nothing reserved

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section .text

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: create_dynamic_array
;
; Arguements:
;
;     EAX: array size
;
; Uses:
;
;     EAX
;     EBX
;     ECX
;
; Returns:
;
;     EAX: pointer to an array
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

create_dynamic_array:

         mov   ecx, eax          ; save the size

         mul   eax, 32           ; multiply the amount of indexes by the size of a 32 bit pointer

         push  rcx

         call  alloc             ; allocate the memory for the array

         pop   rcx

         mov   ebx, eax          ; save the array

         mov   eax, 32 * 2       ; size of an array structure (data and size)

         push  rbx

         push  rcx

         call  alloc

         pop   rcx

         pop   rbx

         mov   [eax], ebx        ; store the pointer to the array in index 0

         mov   [eax + 4], ecx    ; store the size at index 1

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: resize_dynamic_array
;
; Arguements:
;
;     EAX: pointer to a dynamic_array structure
;
; Uses:
;
;     EAX
;     EBX
;     ECX
;
; Returns:
;
;     VOID
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

resize_dynamic_array:

         mov   ebx, eax          ; save the structure

         mov   edx, [eax]        ; pointer to the array

         mov   eax, [ebx + 4]    ; move the size to eax

         mul   eax, 2            ; double the size of the array

         mov   ecx, eax          ; save the size

         mul   eax, 32           ; multiply the amount of indexes by the size of a 32 bit pointer

         push  rcx

         call  alloc             ; allocate the memory for the array

         pop   rcx

         push  rax

         push  rbx

         push  rcx

         mov   ebx, [ebx]

         mov   edx, ecx

         mov   ecx, eax
  
         call  str_cpy

         pop   rcx

         pop   rbx

         pop   rax

         mov   eax, [ebx]

         mov   [ebx], eax

         mov   [ebx + 4], ecx

         call  free_dynamic_array

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%endif   ; __DYNAMIC_ARRAY_ASM__

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
