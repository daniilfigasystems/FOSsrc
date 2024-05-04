; File: boot.asm
; Copyright (c) 2023 Figasystems
; Boot procedure
; Author: Daniil Dunaef
; Date: 14-Nov-2023
; Bugs; sti bug



MEMINFO     equ  1<<0
BOOTDEVICE  equ  1<<1
CMDLINE     equ  1<<2
MODULECOUNT equ  1<<3
SYMT        equ  48 ; bits 4 & 5
MEMMAP      equ  1<<6
DRIVE       equ  1<<7
CONFIGT     equ  1<<8
BOOTLDNAME  equ  1<<9
APMT        equ  1<<10
VIDEO       equ  1<<11
VIDEO_FRAMEBUF equ  1<<12
FLAGS       equ  MEMINFO | BOOTDEVICE | CMDLINE
MAGIC_HEADER       equ  0x1BADB002
CHECKSUM    equ -(MAGIC_HEADER + FLAGS)

bits 32
section .multiboot
        align 4
        dd 0x1BADB002
        dd FLAGS
        dd -(0x1BADB002 + FLAGS)

        dd 0
        dd 0
        dd 0
        dd 0
        dd 0

        dd 1
        dd 80
        dd 25
        dd 8
fstart:
section .text 
global start
extern KernelEntry
start:
; cmp eax, 0x1badb002
jmp multibootready
hlt
multibootready:
mov eax, cr0
or al, 1
mov cr0, eax
# sti
cli
push ebx
push eax
mov esp, SystemStack
call KernelEntry
jmp $

global isr_stub

%macro ISR_NO_ERRCODE 1
    global isr_%1
    isr_%1:
        cli
        push byte %1
        jmp isr_stub
%endmacro

%macro ISR_ERRCODE 1
    global isr_%1
    isr_%1:
        cli
        push byte %1
        push byte 0
        jmp isr_stub
%endmacro

ISR_NO_ERRCODE 0
ISR_NO_ERRCODE 1
ISR_NO_ERRCODE 2
ISR_NO_ERRCODE 3
ISR_NO_ERRCODE 4
ISR_NO_ERRCODE 5
ISR_NO_ERRCODE 6
ISR_NO_ERRCODE 7

ISR_ERRCODE 8
ISR_ERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_ERRCODE 15
extern ISRHandle

isr_stub:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp
	push eax
	mov eax, ISRHandle
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

%macro irq_handler 1
    global _irq%1
    _irq%1:
        cli
        push byte 0
        push byte %1
        jmp irq_com_stub
%endmacro

irq_handler 0
irq_handler 1
irq_handler 2
irq_handler 3
irq_handler 4
irq_handler 5
irq_handler 6
irq_handler 7
irq_handler 8
irq_handler 9
irq_handler 10
irq_handler 11
irq_handler 12
irq_handler 13
irq_handler 14
irq_handler 15

extern IRQHandler

irq_com_stub:
        pusha
        push es
        push ds
        push fs
        push gs
        mov ax, 0x10
        mov es, ax
        mov ds, ax
        mov fs, ax
        mov gs, ax
        mov eax, esp
        push eax
        mov eax, IRQHandler
        call eax
        pop eax
        pop es
        pop ds
        pop fs
        pop gs
        popa
        add esp, 8
        iret


global GDTi
extern gp
GDTi:
	lgdt [gp]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush_two
flush_two:
	ret

global IDTi
extern idtptr
IDTi:
        lidt [idtptr]
        ret

SECTION .bss
        resb 8192 ; stack
SystemStack:   