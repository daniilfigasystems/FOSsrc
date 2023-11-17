OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
{
       .text BLOCK(4K) : ALIGN(4K)
   {
      *(.multiboot)
      *(.text)
   }
    . = 0x100000;
    .text : {*(.text)}
    .data : {*(.data)}
    .bss  : {*(.bss)}
}