SECTIONS {
         . = 0x00000000;
         .text : {
               * (vectors);
               * (.text);
         }
         .rodata : {
               * (.rodata);
         }
         flash_sdata = .;

         . = 0xA0000000;
         ram_sdata = .;
         .data : AT (flash_sdata) {
               * (.data)
         }
         . = 0xA0001000;
         ram_edata = .;
         data_size = ram_edata - ram_sdata;

         sbss = .;
         .bss : {
              * (.bss);
         }
         . = 0xA0002000;
         ebss = .;
         bss_size = ebss - sbss;
}
