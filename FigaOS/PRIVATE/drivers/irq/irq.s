global irq0
global irq1
global irq13 
global irq14            ; You complete the rest!
global irq15

; 32: IRQ0
irq0:
    cli
    push byte 0    ; Note that these don't push an error code on the stack:
                   ; We need to push a dummy error code
    push byte 32
    jmp irq_common_stub

            ; You need to fill in the rest!
irq1:
    cli
    push byte 0 ; Note that these don't push an error code on the stack
    push byte 33
    jmp irq_common_stub
irq10:
    cli
    push byte 0
    push byte 42
    jmp irq_common_stub
irq13:
    cli
    push byte 0
    push byte 45
    jmp irq_common_stub
irq14:
    cliirq_common_stub
    push byte 0
    push byte 46
    jmp irq_common_stub
; 47: IRQ15
irq15:
    cli
    push byte 0
    push byte 47
    jmp irq_common_stub

extern irq_handler

; This is a stub that we have created for IRQ based ISRs. This calls
; '_irq_handler' in our C code. We need to create this in an 'irq.c'
irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret
	