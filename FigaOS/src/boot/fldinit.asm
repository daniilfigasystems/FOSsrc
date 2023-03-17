BITS 32
boot:
mov ax, 07C0h
add ax, 576
mov ss, ax
mov sp, 8192
mov ax, 07C0h
mov ds, ax
mov si, bts1
call bts1
int 0x10
jmp .finit
finit:
pusha
push dx
mov ah, 0x02
mov cl, 0x02
nop
mov al, dh
mov ch, 0x00
mov dh, 0x00
int 0x13
jc io_error
pop dx
cmp al, dh
jne io_read_error
popa
jmp pae
call menu
io_error:
mov bx, disk
call print
call print_nl
mov dh, ah
call print_hex
jmp loop
io_read_error:
mov bx, read_write_error
call print
prints: db "Cannot read files", 0
printa: db "I cant find sectors!", 0
menu: db "Starting FOSKRNL..."
jmp 0000:0500h
times(512-2-($-07C00h)) db 0
db 055h,0AAh
:pae
mov eax, cr4
or eax, 1 << 5
mov cr4, eax