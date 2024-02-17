ENTRY(start)
SECTIONS
{
    . = 0x100000;
    .multiboot : {*(.multiboot*)}
    .rodata : {*(.rodata*)}
    .text : {*(.text*)}
    .data : {*(.data*)}
    .bss  : {*(.bss*)}
}