;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Author: Jarret Shook
;
; Module: string.asm
;
; Modifications:
;
; 26-April-13: Version 1.0: Last Updated
; 26-April-13: Version 1.0: Created
;
; Timeperiod: ev6
;
; Assembler: nasm -f elf64 string.asm
; ld -o string string.asm
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section .data

; Nothing to allocate

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section .bss

; Nothing to reserve

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section .text

global str_cmp
global str_cpy
global str_len
global mem_set

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; External Procedures
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: str_cmp
;
; Arguements:
;
;     EBX: pointer to an array of characters (c-string)
;     ECX: pointer to a second array of characters
;
; Uses:
;
;     EAX
;     EBX
;     ECX
;
; Returns:
;
;     EAX: -1 EBX is less than ECX
;        :  0 EBX is equal to ECX
;        :  1 EBX is greater than ECX
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

str_cmp:

         xor   eax, eax          ; zero out eax

         push  rbx               ; save the first string

         push  rcx               ; save the second strng

         jmp   cmp_equal

cmp_ret:

         pop   rcx               ; get the origional string
   
         pop   rbx               ; get the second origional string

         ret

cmp_equal:

         mov   al, byte [ebx]    ; store the first character at location ebx

         cmp   al, byte [ecx]    ; compare the two characters

         je    cmp_equal_helper

         jb    ret_less          ; if ebx < ecx then return less than

         ja    ret_greater       ; else return greater

cmp_equal_helper:

         cmp   [ebx], byte 0     ; null terminator?

         je    cmp_equal_l       ; if so then is it also less than ebx

         cmp   [ecx], byte 0     ; null terminator?

         je    cmp_equal_g       ; if so then is it also greater than ebx?

         add   ebx, 1            ; increment ebx

         add   ecx, 1            ; increment ecx

         jmp   cmp_equal

cmp_equal_l:

         cmp   [ecx], byte 0

         je    ret_equal         ; if they are both null then they are equal

         jmp   ret_less          ; else then ebx is smaller than ecx

cmp_equal_g:

         cmp   [ebx], byte 0

         je    ret_equal         ; return equal if both are null

         jmp   ret_greater       ; else ebx is larger than ecx therefore return greater

ret_equal:

         mov   eax, 0            ; equal

         jmp   cmp_ret

ret_less:

         mov   eax, -1           ; less than

         jmp   cmp_ret

ret_greater:

         mov   eax, 1            ; greater than

         jmp   cmp_ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: str_cpy
;
; Arguements:
;
;     EBX: offset of a string
;     ECX: memory location to be copied into
;
; Uses:
;
;     AL
;     EBX
;     ECX
;
; Returns:
;
;     VOID
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


str_cpy:

         jmp   cpy_init          ; entry point 

cpy_ln:  cmp   [ebx], byte 0     ; null terminator?

         je    ret_cpy           ; if equal then return

         mov   al, [ebx]         ; copy the character into a register

         mov   [ecx], al         ; copy it to the memory location

         add   ebx, 1            ; increment the pointer

         add   ecx, 1            ; increment the second pointer

         jmp   str_cpy           ; continue   

cpy_init:

         push  rbx               ; save the string

         push  rcx               ; save the memory location

         jmp   cpy_ln            ; jump back

ret_cpy:

         pop   rbx               ; pop rbx back

         pop   rcx               ; pop rcx back

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: str_len
;
; Arguements:
;
;     ECX: offset of a string
;
; Uses:
;
;     EAX
;
; Returns:
;
;     EAX: string length
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

str_len:

         xor   eax, eax                   ; zero out eax

         push  rcx                        ; store the origional string

begin_str_len_loop:

         cmp   [ecx], byte 0
             
         je    end_str_len_loop           ; break if null

         add   eax, 1                     ; increment eax if not null
 
         add   ecx, 1                     ; increment the pointer
  
         jmp   begin_str_len_loop         ; repeat

end_str_len_loop:

         add   eax, 1                     ; plus null terminator

         pop   rcx                        ; restore the origional string

         ret                              ; if null terminator is reached return


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: mem_set
;
; Arguements:
;
;     EAX: value to set the memory to
;     EBX: size (in bytes) of memory to set
;     ECX: start of memory
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

mem_set:

         cmp   ebx, 0            ; reached end?
         
         je    mem_ret           ; then return

         sub   ebx, 1            ; subtract 1 from ebx

         mov   [ecx], eax        ; copy the value

         add   ecx, 1            ; increment ecx

         jmp   mem_set           ; repeat

mem_ret: ret
