;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Author: Jarret Shook
;
; Module: bn_tree.asm
;
; Modifications:
;
; 21-April-13: Version 1.0: Last updated 
; 20-April-13: Version 1.0: Created
;
; Timeperiod: ev6
;
; Assembler: nasm -f elf64 bn_tree.asm
; ld -o test bn_tree.asm
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section .data

length         equ   81
const_message  db    'Error: bad_alloc', 0Ah, 0

const_length   equ   $ - const_message

message        db    "Hello", 0
message2       db    " World", 10, 0

_Head          dd    0h, 0h, 0h

section .bss

section .text

global _start                                      ; declared for linker

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;  Procedure: allocate
;
;  Arguements:
;
;     EAX: size in bytes of memory to be allocated
;
;  Returns:
;
;     EAX: returns the pointer to the memory allocated
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

allocate:

         mov   ecx, eax       ; save the args

         mov   eax, 45        ; sys_brk

         xor   ebx, ebx          

         int   80h            ; software interupt

         add   eax, ecx       ; how much memory to reserve

         mov   ebx, eax

         mov   eax, 45        

         int   80h            ; software interupt

         cmp   eax, 0         ; -1 if allocation failed

         je    bad_alloc      ; exit program

         ret

bad_alloc:
      
         mov   ecx, const_message

         mov   edx, const_length

         call  print

         call  _exit_         ; exit..

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;  Procedure: create_node
;
;  Arguements:
;
;     VOID
;  
;  Returns:
;
;     EAX: pointer to the node
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

create_node:

         mov   eax, 32 * 3          ; size of a node
         
         call  allocate             ; call allocate

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;  Procedure: str_cmp_as
;
;  Arguements:
;
;     EBX: offset of a string
;     ECX: offset of a second string
;
;  Returns:
;
;     EAX: -1 EBX is less than ECX
;        :  0 EBX is equal to ECX
;        :  1 EBX is greater than ECX
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

str_cmp_as:

            xor   eax, eax                ; zero out eax

            push  rbx                     ; save the first string

            push  rcx                     ; save the second string

            jmp   cmp_equal

cmp_ret:

            pop   rcx                     ; get the second string back

            pop   rbx                     ; get the first string

            ret

cmp_equal:

            cmpsb [ebx], [ecx]      ; compare the two string

            je    cmp_equal_helper        ; go to a helper "label"

            cmp   byte [ebx], byte [ecx]  ; less than?

            jb    ret_less

            cmp   byte [ebx], byte [ecx]  ; gt?

            ja    ret_greater

cmp_equal_helper:

            cmp   [ebx], byte 0           ; null terminator?
            
            je    cmp_equal_l             ; less than?

            cmp   [ecx], byte 0           ; gt?

            je    cmp_equal_g

            add   ebx, 1                  ; increment ebx

            add   ecx, 1                  ; increment ecx

            jmp    cmp_equal              ; continue?

cmp_equal_l:

            cmp   [ecx], byte 0

            je    ret_equal               ; return equal

            jmp   ret_less                ; else it is less than

cmp_equal_g:

            cmp   [ebx], byte 0

            je    ret_equal               ; return equal

            jmp   ret_greater             ; return greater

ret_equal:

            mov   eax, 0                  ; equal

            jmp   cmp_ret

ret_less:

            mov   eax, -1                 ; less than

            jmp   cmp_ret

ret_greater:

            mov   eax, 1                  ; greater than

            jmp   cmp_ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;  Procedure: str_len_as
;
;  Arguements:
;
;     ECX: offset of string
;
;  Returns:
;
;     EAX: string size
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

str_len_as:

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
;  Procedure: print_tree
;
;  Arguements:
;
;     EAX: tree root
;
;  Returns:
;
;     VOID
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

print_tree:

         mov   ecx, [eax]                 ; pointer to message stored in first memory location

         push  rax

         call  str_len_as

         mov   edx, eax                   ; must be a dword

         pop   rax

         push  rax                        ; avoid overwriting eax

         call  print

         pop   rax

         cmp   [eax + 4], dword 0         ; if left is null

         je    _return_

         mov   eax, [eax + 4]             ; go left

         call  print_tree

         cmp   [eax + 8], dword 0         ; if right is null

         je    _return_

         mov   eax, [eax + 8]             ; go right

         call print_tree

_return_:

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;  Procedure: print
;
;  Arguements:
;  
;     ECX: offset of string to be printed
;     EDX: length of string
;
;  Returns:
;
;     VOID
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

print:

         mov   ebx, 1               ; file descriptor(stdout)
         mov   eax, 4               ; system call number (sys_write)
         int   080h                 ; interupt

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: _exit_
;
; Arguements:
;
;     VOID
;
; Returns
;
;     VOID
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_exit_:

         mov   eax, 1               ; system call number (sys_exit) ... stop printing
                                    ; infinite loop if you do not interupt it
         int   080h                 ; interupt

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 
; Procedure: _start
;
; Arguements:
;
;     VOID
;
;  Returns:
;
;     VOID
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_start:                                      ; entry point

         nop

         mov   [_Head], dword message        ; store the address of message, in the "node"
         
         call create_node                    ; allocate space for a new node

         mov   [eax], dword message2         ; eax stores the address of the node

         mov   [_Head + 4], dword eax        ; 4 bytes (offset for a dword)

         mov   eax, _Head

         call print_tree;

         call _exit_
