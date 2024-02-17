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

        dd 0
        dd 1024
        dd 768
        dd 32
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
call KernelEntry
hlt
