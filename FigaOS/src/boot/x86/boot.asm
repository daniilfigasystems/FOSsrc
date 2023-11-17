; File: boot.asm
; Copyright (c) 2023 Figasystems
; Boot procedure
; Author: Daniil Dunaef
; Date: 14-Nov-2023
; Bugs; No current bugs found



bits 32
    section .text
    align 4
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002 + 0x00)  
global start
extern k_main
start:
mov eax, cr0
or al, 1
mov cr0, eax
cli
call k_main
hlt
