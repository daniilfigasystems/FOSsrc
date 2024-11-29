; File: rand.asm
; Copyright (c) 2024 Figasystems
; Random functions
; Author: Daniil Dunaef
; Date: 18-Nov-2024
; Bugs: No bugs found



extern RNDGetRandom
mov eax, 7     ; set EAX to request function 7
mov ecx, 0     ; set ECX to request subfunction 0
cpuid
shr ebx, 18    ; the result we want is in EBX...
and ebx, 1     ; ...test for the flag of interest...
pushad
call RNDGetRandom
