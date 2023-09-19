BITS 16  
mov ax, 07C0h
add ax, 288
mov ss, ax
mov sp, 4096
mov ax, 07C0h
mov si, flp
call printfepta
flp db 'Initialization fdd controller', 0
mov si, readingflp
call printfepta
readingflp db 'reading from fdd controller', 0
call flpcontroller
cmp ah, 1
jne error
printfepta:
mov ah, 0Eh
flpcontroller:
mov ah, 2
mov dl, 0
mov dh, 1
mov cl, 0
int 0x16
error:
mov si, errord
call printfepta
errord db 'failed flp sector 0 = NULL', 0