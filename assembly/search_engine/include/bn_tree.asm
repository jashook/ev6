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

         sub   ecx, edx          ; subtract the first from the second height

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
; Procedure: double_with_left_child
;
; Arguements:
;
;     EAX: pointer to tree struct
;     EBX: parent pointer
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
;     VOID
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

double_with_left_child:

         push  rbx               ; save the origional parent

         mov   ebx, [ebx + 4]    ; parent pointer becomes the left child

         call  rotate_with_right_child

         pop   rbx               ; restore the original parent

         call  rotate_with_left_child

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: double_with_right_child
;
; Arguements:
;
;        EAX: pointer to tree struct
;        EBX: parent pointer
;
; Uses:
;
;        EAX
;        EBX
;        ECX
;        EDX
;
; Returns:
;
;        VOID
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

double_with_right_child:

         push  rbx               ; save the original parent

         mov   ebx, [ebx + 8]    ; parent pointer becomes the right child

         call  rotate_with_left_child

         pop   rbx               ; restore the original parent

         call  rotate_with_right_child

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

         jmp   ret_height

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

         push  rax
      
         push  rcx

         push  rbp               ; push the origional base pointer

         mov   rbp, rsp          ; save the stack pointer

         sub   rsp, 8            ; one dword

         mov   [rbp], dword eax  ; save the struct

         mov   [rbp - 4], dword ecx  ; save the string

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

         add   rsp, 8            ; deallocate local storage

         pop   rbp

         pop   rcx

         pop   rax

         ret

insert_at_head:

         mov   [ebx], dword ecx  ; insert the string

         add   [eax + 4], byte 1 ; increment the size

         add   rsp, 8            ; deallocate local storage

         pop   rbp               ; restore rbp

         pop   rcx

         pop   rax

         ret

insert_left:

         push  rax               ; save eax

         push  rbx

         push  rcx

         push  rdx               ; save the registers

         call create_node

         pop   rdx               ; restore the registers

         pop   rcx

         pop   rbx

         mov   [eax], ecx        ; insert the string

         mov   [eax + 4], dword 0      ; zero out the left pointer

         mov   [eax + 8], dword 0      ; zero out the right pointer

         mov   [eax + 12], dword ebx   ; set the parent pointer

         mov   [eax + 16], dword 0     ; new node has height 0

         mov   [ebx + 4], dword eax ; set the new node to be the left pointer
   
         mov   ebx, eax          ; set the new node to ebx

         pop   rax               ; restore eax

         inc   dword [eax + 4]   ; increment the size of the tree

         jmp   check_if_balanced

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

         mov   [eax + 16], dword 0     ; new node has height 0

         mov   [ebx + 8], dword eax ; set the new node to be the right pointer
   
         mov   ebx, eax          ; set the new node to ebx

         pop   rax               ; restore eax

         inc   dword [eax + 4]   ; increment the size of the tree
      
                                 ; fall through

check_if_balanced:

         mov   eax, ebx

height_loop:

         mov   ecx, eax          ; save eax
   
         mov   eax, [ecx + 4]    ; left pointer

         mov   ebx, [ecx + 8]    ; right pointer

         push  rcx               ; save the node

         call  heights           ; get their heights

         pop   rbx               ; restore the node

         push  rbx
   
         push  rcx

         call  max_heights       ; get the largest height

         pop   rcx

         call  are_balanced      ; is the node balanced?

         mov   rcx, rbx          ; save the true or false value

         pop   rbx               ; restore ebx (the node)

         inc   dword eax         ; increment the largest height

         mov   [ebx + 16], dword eax   ; eax contains the largest height

         cmp   ecx, 1            ; true?

         je    height_loop_help  ; then continue up   

         jmp   balance           ; make an avl_tree !!!!

height_loop_help:

         mov   eax, dword [ebx + 12]   ; go up one parent
         
         cmp   eax, 0            ; null ptr?

         je    break_height

         jmp   height_loop

break_height:

         add   rsp, 8            ; deallocate memory

         pop   rbp               ; restore rbp

         pop   rcx

         pop   rax

         ret

balance:

         mov   ecx, [ebx]        ; get the value

         push  rax               ; save rax

         push  rbx               ; save parent pointer

         mov   ecx, [ebx]        ; second string

         mov   ebx, [rbp - 4]    ; first string

         call  str_cmp           ; call string compare

         cmp   eax, 1            ; greater than?

         js    less_than_balance

         je    greater_than_balance

         pop   rbx

         pop   rax

         jmp   break_height

less_than_balance:

         mov   ecx, ebx          ; save the value

         pop   rbx               ; restore rbx

         mov   eax, dword [ebx + 4]    ; eax has the left child now
         
         push  rbx               ; save the pointer

         mov   ebx, ecx          ; first string

         mov   ecx, dword [eax]        ; get the value

         call  str_cmp

         cmp   eax, 1            ; double with left child

         pop   rbx               ; restore the parent

         pop   rax               ; clean the stack

         mov   eax, [rbp]    ; pass the pointer to the tree struct

         js rot_with_left_child

         call  double_with_left_child

rot_ret_left:

         add   rsp, 8            ; clean up the stack

         pop   rbp

         pop   rcx

         pop   rax

         ret

rot_with_left_child:

         call  rotate_with_left_child

         jmp   rot_ret_left

greater_than_balance:

         mov   ecx, ebx          ; save the value

         pop   rbx               ; restore rbx

         mov   eax, dword [ebx + 8]    ; eax has the right child now
         
         push  rbx               ; save the pointer

         mov   ebx, dword [eax]  ; get the value

         call  str_cmp

         cmp   eax, 1            ; double with right child

         pop   rbx               ; restore the parent

         pop   rax               ; clean the stack

         mov   eax, [rbp - 4]    ; pass the pointer to the tree struct

         js    rot_with_right_child

         call  double_with_right_child

rot_ret_right:

         add   rsp, 8            ; clean up the stack

         pop   rbp

         pop   rcx

         pop   rax

         ret

rot_with_right_child:

         call  rotate_with_right_child

         jmp   rot_ret_right
   
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

         cmp   ecx, -1           ; signed?

         je    signed_height

         cmp   edx, -1           ; signed?

         je    signed_height

         cmp   ecx, edx          ; compare the heights

         je    equal_height      ; equal

         ja    larger_height     ; else larger

                                 ; fall through

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

         cmp   [eax + 4], dword 0         ; if left is null

         mov   ecx, [eax]                 ; pointer to message

         push  rax

         call  str_len

         mov   edx, eax

         pop   rax

         push  rax

         call  print_str

         pop   rax

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
;
; Procedure: rotate_with_left_child
;
; Arguements:
;
;     EAX: pointer to a tree struct
;     EBX: pointer to parent node
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
;     VOID
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

rotate_with_left_child:

         push  rbp               ; push the origional base pointer

         mov   rbp, rsp          ; save the stack pointer

         sub   rsp, 4            ; one dword

         mov   [rbp - 4], dword eax    ; save the pointer to the root

         cmp   ebx, 0            ; null?

         je    ret_rotate_left

         mov   eax, dword [ebx + 4]    ; get the left child

         ; EAX = left_child, EBX = parent

         mov   ecx, dword [eax + 8]    ; get the right child of eax

         mov   [ebx + 4], dword ecx    ; set parent.left = parent.left.right

         cmp   ecx, 0            ; is the right child null?

         jne   set_parent_right  ; if not then update the parent pointer

ret_parent_left:
   
         mov   [eax + 8], ebx    ; parent.left_child.right_child = parent

         push  rax               ; push the left_child

         push  rbx               ; save the parent
         
         mov   eax, dword [ebx + 4]    ; left child of parent

         mov   ebx, dword [ebx + 8]    ; right child of parent

         call  heights           ; get the heights

         call  max_heights       ; get the max height

         inc   dword eax         ; increment the max height by one

         pop   rbx               ; restore the parent to rbx

         mov   [ebx + 16], dword eax   ; save the height

         pop   rax               ; restore the left child to rax

         push  rbx               ; save the parent

         push  rax               ; save the left child

         mov   ebx, dword [eax + 8]    ; right child of left child

         mov   eax, dword [eax + 4]    ; left child of left child

         call  heights

         call  max_heights       ; get the max height

         inc   dword eax

         mov   ebx, eax          ; save the max height

         pop   rax               ; restore the left_child

         mov   [rax + 16], dword ebx   ; save the height

         pop   rbx

         mov   ecx, [eax + 12]   ; left_child.parent

         ; EAX: left_child, EBX: parent, ECX: left_child.parent

         mov   ecx, dword [ebx + 12]   ; left_child.parent = parent.parent

         mov   [ebx + 12], dword eax

         mov   ebx, eax

         cmp   [ebx + 12], dword 0

         jne   continue_left_set_up

         mov   eax, dword [rbp - 4]    ; restore the root node
         
         mov   eax, ebx

         jmp   ret_rotate_left

continue_left_set_up:

         ; EBX: parent

         mov   eax, [ebx + 12]         ; eax is parent.parent

         push  rbx               ; save the parent

         mov   ebx, [ebx]        ; first string

         push  rax               ; save parent.parent

         mov   ecx, [eax]        ; second string

         call  str_cmp

         cmp   eax, -1           ; gt?

         pop   rax               ; restore parent.parent
         
         pop   rbx               ; restore parent
         
         je    less_than_set_up_balance   ; if less than

         mov   [eax + 8], rbx    ; parent.parent.right = parent

         jmp   ret_rotate_left

less_than_set_up_balance:

         mov   [eax + 4], rbx    ; parent.parent.left = parent

         jmp   ret_rotate_left

set_parent_right:

         mov   [ecx + 12], ebx   ; update the parent pointer

         jmp   ret_parent_left

ret_rotate_left:

         add   rsp, 4            ; clean up the stack

         pop   rbp               ; restore the base pointer

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Procedure: rotate_with_right_child
;
; Arguements:
;
;     EAX: pointer to a tree struct
;     EBX: pointer to parent node
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
;     VOID
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

rotate_with_right_child:

         push  rbp               ; push the origional base pointer

         mov   rbp, rsp          ; save the stack pointer

         sub   rsp, 4            ; one dword

         mov   [rbp - 4], dword eax    ; save the pointer to the tree struct

         cmp   ebx, 0            ; null?

         je    ret_rotate_right

         mov   eax, dword [ebx + 8]    ; get the right child

         ; EAX = right_child, EBX = parent

         mov   ecx, dword [eax + 4]    ; get the left child of eax

         mov   [ebx + 8], dword ecx    ; set parent.right = parent.right.left

         cmp   ecx, 0            ; is the right child null?

         jne   set_parent_left  ; if not then update the parent pointer

ret_parent_right:

         mov   [eax + 4], ebx    ; right_child.left_child  = parent

         push  rax               ; push the left_child

         push  rbx               ; save the parent
         
         mov   eax, dword [ebx + 4]    ; left child of parent

         mov   ebx, dword [ebx + 8]    ; right child of parent

         call  heights           ; get the heights

         call  max_heights       ; get the max height

         inc   dword eax         ; increment the max height by one

         pop   rbx               ; restore the parent to rbx

         mov   [ebx + 16], dword eax   ; save the height

         pop   rax               ; restore the left child to rax

         push  rbx               ; save the parent

         push  rax               ; save the right child

         mov   ebx, dword [eax + 8]    ; right child of right child

         mov   eax, dword [eax + 4]    ; left child of right child

         call  heights

         call  max_heights       ; get the max height

         inc   dword eax

         mov   ebx, eax          ; save the max height

         pop   rax               ; restore the right_child

         mov   [rax + 16], dword ebx   ; save the height

         pop   rbx

         mov   ecx, [eax + 12]   ; right_child.parent

         ; EAX: right_child, EBX: parent, ECX: right_child.parent

         mov   ecx, dword [ebx + 12]   ; right_child.parent = parent.parent

         mov   [ebx + 12], dword eax

         mov   ebx, eax

         cmp   [ebx + 12], dword 0

         jne   continue_right_set_up

         mov   eax, dword [rbp - 4]    ; restore the root node
         
         mov   eax, ebx

         jmp   ret_rotate_right

continue_right_set_up:

         ; EBX: parent

         mov   eax, [ebx + 12]   ; eax is parent.parent

         push  rbx               ; save the parent

         mov   ebx, [ebx]        ; first string

         push  rax               ; save parent.parent

         mov   ecx, [eax]        ; second string

         call  str_cmp

         cmp   eax, -1           ; gt?

         pop   rax               ; restore parent.parent
         
         pop   rbx               ; restore parent
         
         je    less_than_set_up_balance_right   ; if less than

         mov   [eax + 8], rbx    ; parent.parent.right = parent

         jmp   ret_rotate_right

less_than_set_up_balance_right:

         mov   [eax + 4], rbx    ; parent.parent.left = parent

         add   rsp, 4            ; clean up the stack

         jmp   ret_rotate_right

set_parent_left:

         mov   [ecx + 12], ebx   ; update the parent pointer

         jmp   ret_parent_right

ret_rotate_right:

         add   rsp, 4

         pop   rbp

         ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



%endif   ; __BN_TREE_ASM__

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
