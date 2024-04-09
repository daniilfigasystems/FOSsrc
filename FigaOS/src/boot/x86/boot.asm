; File: boot.asm
; Copyright (c) 2023 Figasystems
; Boot procedure
; Author: Daniil Dunaef
; Date: 14-Nov-2023
; Bugs; No current bugs found



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
cli
push ebx
push eax
mov esp, SystemStack
call KernelEntry
jmp $

global isr_0
global isr_1
global isr_2
global isr_3
global isr_4
global isr_5
global isr_6
global isr_7
global isr_8
global isr_9
global isr_10
global isr_11
global isr_12
global isr_13
global isr_14
global isr_15
global isr_16
global isr_17
global isr_18
global isr_19
global isr_20
global isr_21
global isr_22
global isr_23
global isr_24
global isr_25
global isr_26
global isr_27
global isr_28
global isr_29
global isr_30
global isr_31

isr_0:
	cli
	push byte 0
	push byte 0
	jmp isr_stub

isr_1:
	cli
	push byte 0
	push byte 1
	jmp isr_stub

isr_2:
	cli
	push byte 0
	push byte 2
	jmp isr_stub

isr_3:
	cli
	push byte 0
	push byte 3
	jmp isr_stub

isr_4:
	cli
	push byte 0
	push byte 4
	jmp isr_stub

isr_5:
	cli
	push byte 0
	push byte 5
	jmp isr_stub

isr_6:
	cli
	push byte 0
	push byte 6
	jmp isr_stub

isr_7:
	cli
	push byte 0
	push byte 7
	jmp isr_stub

isr_8:
	cli
	push byte 8
	jmp isr_stub

isr_9:
	cli
	push byte 0
	push byte 9
	jmp isr_stub

isr_10:
	cli
	push byte 10
	jmp isr_stub

isr_11:
	cli
	push byte 11
	jmp isr_stub

isr_12:
	cli
	push byte 12
	jmp isr_stub

isr_13:
	cli
	push byte 13
	jmp isr_stub

isr_14:
	cli
	push byte 14
	jmp isr_stub

isr_15:
	cli
	push byte 0
	push byte 15
	jmp isr_stub

isr_16:
	cli
	push byte 0
	push byte 16
	jmp isr_stub

isr_17:
	cli
	push byte 0
	push byte 17
	jmp isr_stub

isr_18:
	cli
	push byte 0
	push byte 18
	jmp isr_stub

isr_19:
	cli
	push byte 0
	push byte 19
	jmp isr_stub

isr_20:
	cli
	push byte 0
	push byte 20
	jmp isr_stub

isr_21:
	cli
	push byte 0
	push byte 21
	jmp isr_stub

isr_22:
	cli
	push byte 0
	push byte 22
	jmp isr_stub

isr_23:
	cli
	push byte 0
	push byte 23
	jmp isr_stub

isr_24:
	cli
	push byte 0
	push byte 24
	jmp isr_stub

isr_25:
	cli
	push byte 0
	push byte 25
	jmp isr_stub

isr_26:
	cli
	push byte 0
	push byte 26
	jmp isr_stub

isr_27:
	cli
	push byte 0
	push byte 27
	jmp isr_stub

isr_28:
	cli
	push byte 0
	push byte 28
	jmp isr_stub

isr_29:
	cli
	push byte 0
	push byte 29
	jmp isr_stub

isr_30:
	cli
	push byte 0
	push byte 30
	jmp isr_stub

isr_31:
	cli
	push byte 0
	push byte 31
	jmp isr_stub

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

global _irq0
global _irq1
global _irq2
global _irq3
global _irq4
global _irq5
global _irq6
global _irq7
global _irq8
global _irq9
global _irq10
global _irq11
global _irq12
global _irq13
global _irq14
global _irq15

_irq0:
        cli
        push byte 0
        push byte 32
        jmp irq_com_stub
_irq1:
        cli
        push byte 0
        push byte 33
        jmp irq_com_stub
_irq2:
        cli
        push byte 0
        push byte 34
        jmp irq_com_stub
_irq3:
        cli
        push byte 0
        push byte 35
        jmp irq_com_stub
_irq4:
        cli
        push byte 0
        push byte 36
        jmp irq_com_stub
_irq5:
        cli
        push byte 0
        push byte 37
        jmp irq_com_stub
_irq6:
        cli
        push byte 0
        push byte 38
        jmp irq_com_stub
_irq7:
        cli
        push byte 0
        push byte 39
        jmp irq_com_stub
_irq8:
        cli
        push byte 0
        push byte 40
        jmp irq_com_stub
_irq9:
        cli
        push byte 0
        push byte 41
        jmp irq_com_stub
_irq10:
        cli
        push byte 0
        push byte 42
        jmp irq_com_stub
_irq11:
        cli
        push byte 0
        push byte 43
        jmp irq_com_stub
_irq12:
        cli
        push byte 0
        push byte 44
        jmp irq_com_stub
_irq13:
        cli
        push byte 0
        push byte 45
        jmp irq_com_stub
_irq14:
        cli
        push byte 0
        push byte 46
        jmp irq_com_stub
_irq15:
        cli
        push byte 0
        push byte 47
        jmp irq_com_stub

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