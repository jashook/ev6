.include "arm_main.s"
.include "memory.s"

.section "vectors"

reset:   b     start
undef:   b     undef
swi:     b     swi
pabt:    b     pabt
dabt:    b     dabt
         nop
irq:     b     irq
fiq:     b     fiq

.text

memory_start:  #0xA0000000
memory_size:   #0x1E848000

start:
         
         ldr   r0, =memory_start @ beginning of RAM

         ldr   r1, =memory_size

         b     simple_partitioning_init

         @ Copy data into RAM

         ldr   r0, =flash_sdata
         ldr   r1, =ram_sdata
         ldr   r2, =data_size

         @ Handle the case data_size == 0

         cmp   r2, #0
         beq   init_bss

data_copy:

         ldrb  r4, [r0], #1
         strb  r4, [r1], #1
         subs  r2, r2, #1
         bne   data_copy

init_bss:

         @ Initialize .bss

         ldr   r0, =sbss
         ldr   r1, =ebss
         ldr   r2, =bss_size

         @ Handle the case of bss_size == 0

         cmp   r2, #0
         beq   init_stack

         mov   r4, #0

zero_out_stack:

         strb  r4, [r0], #1
         subs  r2, r2, #1
         bne   zero_out_stack

init_stack:

         mov   r4, r0            @ r4 stores the end of .bss and top of the stack
         ldr   sp, =0xA4000000

         bl    arm_main

stop:    b     stop              @ infinite loop if returned
