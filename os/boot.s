.include "string.s"

.text

         b     start             @ do not execute the data

string:  .asciz "Hello world"    @ null terminated string
   
         .equ  null, 0           @ null = 0   


.align

start:
   
         mov   r0, #100

         str   sp, [r0]

         mov   r0, #0

         ldr   sp, r0

stop:    b     stop              @ infinite loop
