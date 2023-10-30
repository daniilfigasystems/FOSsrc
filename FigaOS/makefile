all: buildbootloader buildfpu buildfpudetect buildsb16 buildcom buildpage buildmalloc buildpageasm buildkeyb buildstr buildpic buildinit buildgdtasm buildgdt buildidt buildidtasm buildpit buildint32 buildvesa buildasm buildvga builddbgprint buildboot buildbsod buildisr buildisrasm buildirq buildirqasm  link remove
notrem: buildinit buildpit buildasm buildvga builddbgprint buildboot buildbsod link
buildinit: PRIVATE/ntos/init/init.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/ntos/init/init.c -o bin/init.o -m32
buildpage: PRIVATE/ntos/mm/page.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/ntos/mm/page.c -o bin/page.o -m32
buildbsod: PRIVATE/ntos/ke/bugcheck.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/ntos/ke/bugcheck.c -o bin/bugcheck.o -m32
buildvga:  PRIVATE/drivers/basevid/vga.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/drivers/basevid/vga.c -o bin/vga.o -m32
buildpit:  PRIVATE/drivers/pit/PIT.c  ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/drivers/pit/PIT.c -o bin/pit.o -m32
buildgdt: PRIVATE/drivers/gdt/gdt.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/drivers/gdt/gdt.c -o bin/gdt.o -m32
builddbgprint: PRIVATE/ntos/kd/dbgprint.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/ntos/kd/dbgprint.c -o bin/dbgprint.o -m32
buildboot: PRIVATE/boot/fldinit.s ; wsl nasm -iPRIVATE/boot/a20check.s -f elf32 PRIVATE/boot/fldinit.s -o bin/krnent.o
buildgdtasm: PRIVATE/drivers/gdt/gdt.s ; wsl nasm -f elf32 PRIVATE/drivers/gdt/gdt.s -o bin/gdtasm.o
buildasm: PRIVATE/ntos/include/asm.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/ntos/include/asm.c -o bin/asm.o -m32
buildidt: PRIVATE/drivers/idt/idt.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/drivers/idt/idt.c -o bin/idt.o -m32
buildidtasm: PRIVATE/drivers/idt/idt.s ; wsl nasm -f elf32 PRIVATE/drivers/idt/idt.s -o bin/idtasm.o
buildstr: PRIVATE/ntos/include/string.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/ntos/include/string.c -o bin/string.o -m32
buildisr: PRIVATE/drivers/isr/isr.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/drivers/isr/isr.c -o bin/isr.o -m32
buildirq: PRIVATE/drivers/irq/irq.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/drivers/irq/irq.c -o bin/irq.o -m32
buildirqasm: PRIVATE/drivers/irq/irq.s ; wsl nasm -f elf32 PRIVATE/drivers/irq/irq.s -o bin/irqasm.o
buildisrasm: PRIVATE/drivers/isr/isr.s ; wsl nasm -f elf32 PRIVATE/drivers/isr/isr.s -o bin/israsm.o
buildint32: PRIVATE/ntos/asm/int32.s ; wsl nasm -f elf32 PRIVATE/ntos/asm/int32.s -o bin/int32.o
buildkeyb: PRIVATE/drivers/keyboard/keyb.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/drivers/keyboard/keyb.c -o bin/keyb.o -m32
buildvesa: PRIVATE/drivers/vesa/vesa.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/drivers/vesa/vesa.c -o bin/vesa.o -m32
buildbootloader: PRIVATE/bootloader/start.s ; wsl nasm -f elf32 PRIVATE/bootloader/start.s -o bin/startboot.o
buildcom: PRIVATE/drivers/serial/serial.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/drivers/serial/serial.c -o bin/serial.o -m32
buildvbeasm: PRIVATE/drivers/vesa/vbe.s ; wsl nasm -f elf32 PRIVATE/drivers/vesa/vbe.s -o bin/vbe.o
buildtssasm: PRIVATE/drivers/vesa/vbe.s ; wsl nasm -f elf32 PRIVATE/drivers/tss/tss.s -o bin/tssasm.o
buildtss: PRIVATE/drivers/irq/irq.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/drivers/tss/tss.c -o bin/tss.o -m32
buildmalloc: PRIVATE/ntos/mm/malloc.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/ntos/mm/malloc.c -o bin/malloc.o -m32
buildpageasm: PRIVATE/ntos/mm/page.s ; wsl nasm -f elf32 PRIVATE/ntos/mm/page.s -o bin/pageasm.o
buildfpu: PRIVATE/ntos/fpu/fpu.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/ntos/fpu/fpu.c -o bin/fpu.o -m32
buildfpudetect: PRIVATE/ntos/fpu/fpudetect.s ; wsl nasm -f elf32 PRIVATE/ntos/fpu/fpudetect.s -o bin/fpucheck.o
buildpic: PRIVATE/drivers/pic/pic.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/drivers/pic/pic.c -o bin/pic.o -m32
builddrivers: PRIVATE/drivers/drivers.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/drivers/drivers.c -o bin/drivers.o -m32
buildsb16: PRIVATE/drivers/sb16/sb16.c ; wsl gcc -IPRIVATE/ntos/include -c PRIVATE/drivers/sb16/sb16.c -o bin/sb16.o -m32
link: bin/init.o bin/vga.o bin/krnent.o bin/asm.o ; wsl ld -T linker.ld -m elf_i386 -o bin/foskrnl.exe --allow-multiple-definition -nostdlib bin/pic.o bin/sb16.o bin/pageasm.o bin/bugcheck.o bin/malloc.o bin/vesa.o bin/init.o bin/vga.o bin/pit.o bin/page.o bin/serial.o bin/krnent.o bin/gdt.o bin/asm.o bin/dbgprint.o bin/gdtasm.o bin/idt.o bin/idtasm.o bin/string.o bin/isr.o bin/israsm.o bin/irq.o bin/irqasm.o bin/keyb.o bin/int32.o bin/fpu.o bin/fpucheck.o
remove: ; del bin\vga.o bin\init.o bin\pit.o bin\dbgprint.o bin\asm.o bin\bugcheck.o