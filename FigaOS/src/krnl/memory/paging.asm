; File: paging.asm
; Copyright (c) 2024 Figasystems
; Paging
; Author: Daniil Dunaef
; Date: 14-Aug-2024
; Bugs no Bugs



global PGInstallPageDirectory
global PGEnablePaging

PGInstallPageDirectory:
    mov eax, [esp + 4]
    mov cr3, eax
    ret

PGEnablePaging:
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    ret