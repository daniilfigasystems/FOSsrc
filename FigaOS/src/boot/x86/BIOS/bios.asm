; File: bios.asm
; Copyright (c) 2023 Figasystems
; Bios functions
; Author: Daniil Dunaef
; Date: 15-Nov-2023
; Bugs; No current bugs found



BITS 16
global to_pm, checkA20

to_pm:
;Lets enable A20 line
in al, 0x92
or al, 2
out 0x92, al
cli
;Switch to PM
mov eax, cr0
or al, 1
mov cr0, eax
jmp PM32
BITS 32

PM32:
push ds
push es
push fs
push gs
push ss
push esp
popa
jmp done

done:
pop ds
pop es
pop fs
pop gs
pop ss
pop esp
ret

checkA20:
pushad
mov edi, 0x112345
mov esi, 0x012345
mov [esi], esi
mov [edi], edi
cmpsd
popad
jne A20enabled
ret

A20enabled:
mov esi, 0x00000001
mov edi, 0x000FFFFF
mov [esi], esi
mov [edi], edi
cmpsd
popad
ret