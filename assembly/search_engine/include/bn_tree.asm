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

%ifndef __BN_TREE_ASM__
%define __BN_TREE_ASM__

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%include "alloc.asm"
%include "io.asm"
%include "string.asm"
%include "util.asm"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section .data

; nothing to define

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section .bss

; nothing to reserve

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section .text

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

global _start                    ; declared for linker

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: are_balanced
;
; Arguements:
;
;     ECX: first height
;     EDX: second height
;
; Uses
;
;     EBX
;
; Returns:
;
;     EBX: true or false (1 or 0)
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

are_balanced:

         sub   ecx, edx          ; subtrace the first from the second height

         cmp   ecx, 2            ; not balanced?

         je    not_balanced

         cmp   ecx, -2           ; not balanced

         je    not_balanced

         mov   ebx, 1            ; else they are balanced

         ret

not_balanced:

         mov   ebx, 0            ; false

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: create_node
;
; Arguements:
;
;     VOID
;
; Uses:
;
;     EAX
;  
; Returns:
;
;     EAX: pointer to the node
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

create_node:

         mov   eax, 32 * 5       ; size of a node
                                 ; data, leftptr, rightptr, parentptr, height
         
         call  alloc             ; call allocate

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: create_tree
;
; Arguements:
;
;     VOID
;
; Uses:
;
;     EAX
;
; Returns:
;
;     EAX: pointer to a tree structure
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

create_tree:

         mov   eax, 32 * 2       ; struct to hold a head pointer and the size of the tree

         call  alloc

         mov   ebx, eax

         push  rbx

         call  create_node       ; create the head

         pop   rbx

         mov   [eax], dword 0    ; zero out the data

         mov   [eax + 4], dword 0   ; zero out the right pointer

         mov   [eax + 8], dword 0   ; zero out the right pointer

         mov   [eax + 12], dword 0  ; zero out the parent pointer

         mov   [eax + 15], dword 0  ; default height of zero

         mov   [ebx], dword eax  ; head at the first index

         mov   [ebx + 4], dword 0   ; zero out the size

         mov   eax, ebx

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: descend_tree
;
; Arguements:
;
;     EBX: pointer to the head node
;     ECX: string to be inserted
;
; Uses:
;
;     EAX
;     EBX
;     ECX
;     EDX
;
; Returns:
;
;     EBX: pointer to node to be inserted at
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

descend_tree:

         mov   eax, ebx          ; descending pointer = eax = head

         mov   edx, eax          ; descending parent pointer = descending pointer

descend_loop:

         cmp   eax, dword 0      ; is the descending pointer null?

         je    exit_descend_loop ; then exit the loop

         push  rax               ; save the pointer

         mov   ebx, ecx          ; first string

         mov   ecx, [eax]        ; second string

         call  str_cmp

         cmp   eax, 0            ; are the strings equal?

         pop   rax               ; get back the descending pointer

         js    less_than_desc    ; sign flag should be set

         ja    greater_than_desc

         je    equal_to_desc

less_than_desc:

         mov   edx, eax          ; descending parent pointer = descending pointer

         mov   eax, [eax + 4]    ; descending pointer = the left child

         jmp   descend_loop      ; continue descending

greater_than_desc:

         mov   edx, eax          ; descending parent pointer = descending pointer

         mov   eax, [eax + 8]    ; descending pointer = the right child

         jmp   descend_loop      ; continue descending

equal_to_desc:

         mov   edx, eax          ; set the parent pointer to the descending pointer

                                 ; fall through

exit_descend_loop:

         mov   ebx, edx          ; set up to return the parent pointer

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: heights
;
; Arguements:
;
;     EAX: pointer to a node's left child
;     EBX: pointer to a node's right child
;
; Uses:
;
;     EAX
;     EBX
;     ECX
;     EDX
;
; Returns:
;
;     ECX: first height to be returned
;     EDX: second height
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

heights:
   
         xor   ecx, ecx          ; zero out the first return register

         xor   edx, edx          ; zero out the second return register

         cmp   eax, dword 0      ; is it a null pointer?

         je    set_left_special_height

         mov   ecx, dword [eax + 16]   ; else get the height

back_height:

         cmp   ebx, dword 0      ; is it a null pointer?

         je    set_right_special_height

         mov   edx, dword [ebx + 16]   ; else get the node's height

set_left_special_height:

         mov   ecx, dword -1     ; if null then the height is -1

         jmp   back_height

set_right_special_height:

         mov   edx, dword -1     ; if it is null then the height is -1

ret_height:

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: insert_tree
;
; Arguements:
;
;     EAX: pointer to a tree structure
;     ECX: string to be inserted
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

insert_tree:

         push  rbp               ; push the origional base pointer

         mov   rbp, rsp          ; save the stack pointer

         sub   rsp, 4            ; one dword

         mov   [rbp + 4], dword eax    ; save the string

         mov   ebx, dword [eax]  ; move into ebx the pointer to the head node

         cmp   [ebx], dword 0    ; is the data for the head null?

         je    insert_at_head    ; then insert at the head

         push  rax               ; save eax

         push  rcx               ; save ecx

         call  descend_tree      ; descend through the tree if the head is already set

         pop   rcx               ; restore ecx

         pop   rax               ; restore eax

         mov   edx, ebx          ; save the parent pointer

         mov   ebx, ecx          ; first string

         mov   ecx, [edx]        ; second string
 
         push  rax

         call  str_cmp

         cmp   eax, 0            ; are they equal?

         pop   rax

         mov   ecx, ebx          ; move the second string back

         mov   ebx, edx          ; move the parent pointer back
   
         js    insert_left       ; if less than insert at the left

         ja    insert_right      ; else insert at the right

return_insert_tree:

         add   rsp, 4            ; deallocate local storage

         pop   rbp

         ret

insert_at_head:

         mov   [ebx], dword ecx  ; insert the string

         add   [eax + 4], byte 1 ; increment the size

         add   rsp, 4            ; deallocate local storage

         pop   rbp               ; restore rbp

         ret

insert_left:

         push  rax               ; save eax

         push  rbx

         push  rcx

         push  rdx               ; save the registers

         call create_node

         pop   rdx                ; restore the registers

         pop   rcx

         pop   rbx

         mov   [eax], ecx        ; insert the string

         mov   [eax + 4], dword 0      ; zero out the left pointer

         mov   [eax + 8], dword 0      ; zero out the right pointer

         mov   [eax + 12], dword ebx   ; set the parent pointer

         mov   edx, dword [ebx + 16]

         inc   edx               ; store the parent's height then increment it once for the new height

         mov   [eax + 16], dword edx

         mov   [ebx + 4], dword eax ; set the new node to be the left pointer
   
         pop   rax               ; restor eax

         inc   dword [eax + 4]   ; increment the size of the tree

         jmp   return_insert_tree

insert_right:

         push  rax               ; save eax

         push  rbx               ; save the registers

         push  rcx  

         push  rdx

         call create_node

         pop   rdx

         pop   rcx

         pop   rbx               ; restore the registers

         mov   [eax], ecx        ; insert the string

         mov   [eax + 4], dword 0      ; zero out the left pointer

         mov   [eax + 8], dword 0      ; zero out the right pointer

         mov   [eax + 12], dword ebx   ; set the parent pointer

         mov   edx, dword [ebx + 16]

         inc   edx               ; store the parent's height then increment it once for the new height

         mov   [eax + 16], dword edx

         mov   [ebx + 8], dword eax ; set the new node to be the right pointer
   
         pop   rax               ; restore eax

         inc   dword [eax + 4]   ; increment the size of the tree
      
         jmp   return_insert_tree

check_if_balanced:

         push  rax               ; push rax

         mov   eax, ebx          ; last node inserted becomes eax

height_loop:

         mov   ecx, eax          ; save eax
   
         mov   eax, [ecx + 4]    ; left pointer

         mov   ebx, [ecx + 8]    ; right pointer

         push  rcx               ; save the node

         call  heights           ; get their heights

         pop   rbx               ; restore the node

         call  max_heights       ; get the largest height

         push  rbx               ; save ebx

         call  are_balanced      ; is the node balanced?

         cmp   ebx, 1            ; true?

         pop   rbx               ; restore ebx (the node)

         mov   [ebx + 16], dword eax   ; eax contains the largest height

         je    height_loop_help  ; then continue up   

         jmp   balance           ; make an avl_tree !!!!

height_loop_help:

         mov   eax, dword [ebx + 12]   ; go up one parent
         
         cmp   eax, 0            ; null ptr?

         je    break_height

         jmp   height_loop

break_height:

         add   rsp, 4            ; deallocate memory

         pop   rbp               ; restore rbp

balance:

         


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: max_heights
;
; Arguements:
;
;     ECX: first height
;     EDX: second height
;
; Uses:
;
;     EAX
;
; Returns
;
;     EAX: largest of the two heights
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

max_heights:

         cmp   ecx, edx          ; compare the heights

         je    equal_height      ; equal

         js    signed_height     ; is one -1?

         ja    larger_height     ; else larger

smaller_height:

         mov   eax, edx          ; else it is the smaller one

         ret

equal_height:

         mov   eax, ecx          ; equal

         ret

signed_height:

         cmp   ecx, -1           ; is ecx or edx -1

         je    smaller_height    ; if ecx is -1 then it is smaller

         jmp   larger_height     ; else edx is -1 and smaller

larger_height:

         mov   eax, ecx

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;  Procedure: print_tree
;
;  Arguements:
;
;     EAX: pointer to the root of a tree
;
;  Returns:
;
;     VOID
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

print_tree:

         mov   eax, dword [eax]

print_tree_helper:

         cmp   [eax + 4], dword 0         ; if left is null

         je    right

         push  rax                        ; save the current node
         
         mov   eax, [eax + 4]             ; go left

         call  print_tree_helper

         mov   ecx, [eax]                 ; pointer to message stored in first memory location

         push  rax

         call  str_len

         mov   edx, eax                   ; must be a dword

         pop   rax

         push  rax                        ; avoid overwriting eax

         call  print_str

         pop   rax

         pop   rax                        ; after recursion restore the node

         mov   ecx, [eax]                 ; pointer to message stored in first memory location

         push  rax

         call  str_len

         mov   edx, eax                   ; must be a dword

         pop   rax

         push  rax                        ; avoid overwriting eax

         call  print_str

         pop   rax

right:   cmp   [eax + 8], dword 0         ; if right is null

         je    _return_

         push  rax                        ; save the current node

         mov   eax, [eax + 8]             ; go right

         call print_tree_helper

         mov   ecx, [eax]                 ; pointer to message stored in first memory location

         push  rax

         call  str_len

         mov   edx, eax                   ; must be a dword

         pop   rax

         pop   rax                        ; after recursion restore the node

_return_:

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%endif   ; __BN_TREE_ASM__

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
