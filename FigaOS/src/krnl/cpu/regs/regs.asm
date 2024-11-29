; File: regs.asm
; Copyright (c) 2024 Figasystems
; Registers parsing
; Author: Daniil Dunaef
; Date: 14-Nov-2024
; Bugs: No bugs found



extern __dump_dummy__
global dump
dump:
    pushad
    call __dump_dummy__
    popa
    ret