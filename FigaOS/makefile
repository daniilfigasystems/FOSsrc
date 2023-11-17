nasmargs = -f elf32
gccargs = -m32 -Isrc/krnl/include
all: buildinit buildboot buildstring buildbios buildvga buildgdt link
buildinit:
	wsl gcc $(gccargs) -c src/krnl/init/init.c -o bin/init.o
buildstring:
	wsl gcc $(gccargs) -c src/krnl/include/libs/sources/string.c -o bin/string.o
buildboot:
	wsl nasm $(nasmargs) src/boot/x86/boot.asm -o bin/boot.o
buildbios:
	wsl gcc $(gccargs) -c src/boot/x86/BIOS/bios.c -o bin/bios.o
	wsl nasm $(nasmargs) src/boot/x86/BIOS/bios.asm -o bin/biosasm.o
buildvga:
	wsl gcc $(gccargs) -c src/drivers/vga/vga.c -o bin/vga.o
buildgdt:
	wsl gcc $(gccargs) -c src/krnl/cpu/gdt/gdt.c -o bin/gdt.o
link:
	wsl ld -T link.ld -m elf_i386 -o bin/foskrnl.exe --allow-multiple-definition -nostdlib  bin/boot.o bin/init.o bin/gdt.o
remove: ; del bin\vga.o bin\init.o bin\pit.o bin\dbgprint.o bin\asm.o bin\bugcheck.o