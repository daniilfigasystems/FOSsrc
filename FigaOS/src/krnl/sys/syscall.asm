; File: syscall.asm
; Copyright (c) 2024 Figasystems
; Syscall handler
; Author: Daniil Dunaef
; Date: 21-Nov-2024
; Bugs: No bugs found



extern SCHandler
global SCSyscallHandler
global SCDoSyscall

SCSyscallHandler:
    pushad
    call SCHandler
    popad
    ret

SCDoSyscall:
    popad
    int 0x7f
    ret
