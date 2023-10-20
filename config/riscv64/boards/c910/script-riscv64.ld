OUTPUT_ARCH( "riscv" )
ENTRY(_start)

STACK_SIZE = 0x10000;
HEAP_SIZE = 0x10000; 

SECTIONS
{
  . = 0x0;
  .text.init : { *(.text.init) }
  . = ALIGN(0x1000);
  .text : { *(.text) }
  . = ALIGN(0x1000);
  .data : { *(.data) }
  .bss : { *(.bss) }

  .heap_stack :
  {
      . = ALIGN(8);
      PROVIDE ( __heap_start = . );
      . = . + HEAP_SIZE;
      PROVIDE ( __heap_end = . );
      . = ALIGN(8);
      PROVIDE ( __stack_bottom = . );
      . = . + STACK_SIZE;
      PROVIDE ( __stack_top = . );
  }
  _end = .;
}