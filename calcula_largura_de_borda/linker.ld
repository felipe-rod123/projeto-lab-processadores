SECTIONS {
   .text 0x8000 : {
      kernel.o(.text)
      *(.text)
   }

   . = ALIGN(4);

   .data : {
      *(.data)
   }

   . = ALIGN(4);

   .bss : {
      *(.bss)
   }

   . = ALIGN(4);
   . = . + 4K;
   stack_addr = .;
}