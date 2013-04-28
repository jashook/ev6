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

         mov   eax, 32 * 3       ; size of a node
         
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

         mov   ebx, eax

         call  create_node       ; create the head

         mov   [eax], dword 0    ; zero out the data

         mov   [eax + 4], dword 0   ; zero out the right pointer

         mov   [eax + 8], dword 0   ; zero out the right pointer

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

         push  eax               ; save the pointer

         mov   ebx, ecx          ; first string

         mov   ecx, [eax]        ; second string

         call  str_cmp

         cmp   eax, 0            ; are the strings equal?

         pop   eax               ; get back the descending pointer

         jb    less_than_desc 

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

         mov   ebx, dword [eax]  ; move into ebx the pointer to the head node

         cmp   [ebx], dword 0    ; is the data for the head null?

         je    insert_at_head    ; then insert at the head

         push  eax               ; save eax

         push  ecx               ; save ecx

         call  descend_tree      ; descend through the tree if the head is already set

         pop   ecx               ; restore ecx

         pop   eax               ; restore eax

         mov   edx, ebx

         mov   ebx, ecx          ; first string

         mov   ecx, edx          ; second string
 
         push  eax

         call  str_cmp

         cmp   eax, 0            ; are they equal?

         pop eax

         mov   ecx, ebx

         mov   ebx, edx
   
         jb    insert_left       ; if less than insert at the left

         ja    insert_right      ; else insert at the right

return_insert_tree:

         ret

insert_at_head:

         mov   [ebx], dword ecx  ; insert the string

         inc   [eax + 4]         ; increment the size

         ret

insert_left:

         push  eax               ; save eax

         pushad                  ; save the registers

         call create_node

         popad                   ; restore the registers

         mov   [eax], ecx        ; insert the string

         mov   [eax + 4], dword 0   ; zero out the left pointer

         mov   [eax + 8], dword 0   ; zero out the right pointer

         mov   [ebx + 4], dword eax ; set the new node to be the left pointer
   
         pop   eax               ; restor eax

         inc   [eax + 4]         ; increment the size of the tree

         jmp   return_insert_tree

insert_right:

         push  eax               ; save eax

         pushad                  ; save the registers

         call create_node

         popad                   ; restore the registers

         mov   [eax], ecx        ; insert the string

         mov   [eax + 4], dword 0   ; zero out the left pointer

         mov   [eax + 8], dword 0   ; zero out the right pointer

         mov   [ebx + 8], dword eax ; set the new node to be the right pointer
   
         pop   eax               ; restor eax

         inc   [eax + 4]         ; increment the size of the tree
      
         jmp   return_insert_tree

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

         mov   ecx, [eax]                 ; pointer to message stored in first memory location

         push  rax

         call  str_len

         mov   edx, eax                   ; must be a dword

         pop   rax

         push  rax                        ; avoid overwriting eax

         call  print_str

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

