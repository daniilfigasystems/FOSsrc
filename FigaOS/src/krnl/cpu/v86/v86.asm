extern V86GetRegs
global V86Enter

V86Enter:
    db 0xcd
    xor ah, ah
    mov al, 1
    shl al, 17
    lahf
    mov ah, al
    call V86GetRegs
    sahf
    ret