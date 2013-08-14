.include "string.s"

.text

         b     start             @ do not execute the data

string:  .asciz "String 1"       @ null terminated string
   
         .equ  null, 0           @ null = 0   


.align

start:
   
         mov   r0, #string

         b     str_len

stop:    b     stop              @ infinite loop
