arch = i386
Version = 0.002dev
qemuargs = -d pcall,cpu_reset,int -m 8 -no-shutdown -no-reboot
kernelname = foskrnl$(arch).exe
linktargets = bin/boot.o bin/bootasm.o bin/schedule.o bin/pic.o bin/isr.o bin/pit.o bin/init.o bin/kprintf.o bin/regs.o bin/regsasm.o bin/gdt.o bin/idt.o bin/mm.o bin/vga.o bin/vesa.o bin/bugcheck.o bin/string.o bin/keybps2.o bin/irq.o bin/io.o bin/serial.o bin/cmos.o bin/fonts.o bin/bios.o bin/biosasm.o
LOGFILE = build.log
ifeq ($(value arch), i386)
nasmargs = -f elf32
gccargs = -m32 -Isrc/krnl/include -g  -W -ffreestanding -Wformat=0 -fno-PIC
linkeroutput = elf_i386
else ifeq ($(value arch), x64)
nasmargs = -f elf64
gccargs = -m64 -Isrc/krnl/include -g -W -ffreestanding -Wformat=0 -fno-PIC
linkeroutput = elf_x86_64
else ifeq ($(value arch),)
$(info Warning: Architecture not set! Setting to i386)
override arch = i386
override kernelname = foskrnl$(arch).exe
nasmargs = -f elf32
gccargs = -m32 -Isrc/krnl/include -g -W -ffreestanding -Wformat=0 -fno-PIC
linkeroutput = elf_i386
else
$(info Warning: Architecture is wrong! Setting to i386)
override arch = i386
nasmargs = -f elf32
gccargs = -m32 -Isrc/krnl/include -g -W -ffreestanding -Wformat=0 -fno-PIC
linkeroutput = elf_i386
endif
ifeq ($(OS),Windows_NT)
qemu = C:\Program Files\qemu\qemu-system-i386
COLOR = echo
CC = wsl gcc
ASM = wsl nasm
LD = wsl ld
RM = wsl rm
SUM = wsl sha256sum
IMGMAKE = wsl grub-mkrescue
CAT = wsl cat
MV = wsl mv
MKDIR = wsl mkdir
SLEEP = wsl sleep
VER = ver
else
qemu = qemu-system-i386
COLOR = echo
CC = gcc
ASM = nasm
LD = ld
RM = rm
SUM = sha256sum
IMGMAKE = grub-mkrescue
CAT = cat
MV = mv
MKDIR = mkdir
SLEEP = sleep
VER = uname -a
endif
all: setcolor buildinit buildboot buildstring buildpic buildpit buildschedule buildregs buildbios buildkprintf buildmm buildirq buildvga buildkeybps2 buildgdt buildisr buildidt buildserial buildbugcheck buildio buildvbe buildcmos buildfonts link remove
bin:
	$(MKDIR) -p bin
setcolor:
	@$(COLOR) 81
	@echo ######### FigaOS build #########
	@echo ######### Version $(value Version) #########
	@echo ######### Using $(OS) #########
	@echo Preparing Enviroment
	@$(SLEEP) 0.25
	@echo ####### Architecture $(value arch) #######
	@$(VER)
	@$(SLEEP) 0.25
	@echo ## CC VERSION ##
	@$(CC) --version
	@$(SLEEP) 0.25
	@echo ## ASM VERSION ##
	@$(ASM) --version
	@$(SLEEP) 0.25
	@echo ## LD VERSION ##
	@$(LD) --version
	@$(SLEEP) 0.25
	@echo ## IMGMAKE VERSION ##
	@$(IMGMAKE) --version
	@$(SLEEP) 5
buildinit: bin
	@echo Compiling INIT for $(value arch)
	$(CC) $(gccargs) -c src/krnl/init/init.c -o bin/init.o
	@echo INIT object file created 
buildstring: bin
	@echo Compiling STRING for $(value arch)
	$(CC) $(gccargs) -c src/krnl/include/libs/sources/string.c -o bin/string.o
	@echo STRING object file created 
buildkprintf: bin
	@echo Compiling KPRINTF for $(value arch)
	$(CC) $(gccargs) -c src/krnl/misc/kprintf.c -o bin/kprintf.o
	@echo KPRINTF object file created 
buildboot: bin
	@echo Compiling BOOT for $(value arch)
	$(ASM) $(nasmargs) src/boot/x86/boot.asm -o bin/bootasm.o
	$(CC) $(gccargs) -c src/boot/x86/boot.c -o bin/boot.o
	@echo BOOT object file created 
buildregs: bin
	@echo Compiling REGS for $(value arch)
	$(CC) $(gccargs) -c src/krnl/cpu/regs/regs.c -o bin/regs.o
	$(ASM) $(nasmargs) src/krnl/cpu/regs/regs.asm -o bin/regsasm.o
	@echo REGS object file created 
buildbios: bin
	@echo Compiling BIOS for $(value arch)
	$(CC) $(gccargs) -c src/boot/x86/BIOS/bios.c -o bin/bios.o
	$(ASM) $(nasmargs) src/boot/x86/BIOS/bios.asm -o bin/biosasm.o
	@echo BIOS object file created 
buildvga: bin
	@echo Compiling VGA for $(value arch)
	$(CC) $(gccargs) -c src/drivers/vga/vga.c -o bin/vga.o
	@echo VGA object file created 
buildkeybps2: bin
	@echo Compiling KEYBOARD PS2 for $(value arch)
	$(CC) $(gccargs) -c src/drivers/keyboard/keybps2.c -o bin/keybps2.o
	@echo KEYBOARD PS2 object file created 
buildserial: bin
	@echo Compiling SERIAL for $(value arch)
	$(CC) $(gccargs) -c src/krnl/io/serial.c -o bin/serial.o
	@echo SERIAL object file created 
buildpic: bin
	@echo Compiling PIC for $(value arch)
	$(CC) $(gccargs) -c src/drivers/timers/pic/pic.c -o bin/pic.o
	@echo PIC object file created 
buildpit: bin
	@echo Compiling PIT for $(value arch)
	$(CC) $(gccargs) -c src/drivers/timers/pit/pit.c -o bin/pit.o
	@echo PIT object file created 
buildmm: bin
	@echo Compiling MEMORY for $(value arch)
	$(CC) $(gccargs) -c src/krnl/memory/mm.c -o bin/mm.o
	@echo MEMORY object file created 
buildvbe: bin
	@echo Compiling VBE for $(value arch)
	$(CC) $(gccargs) -c src/drivers/vesa/vesa.c -o bin/vesa.o
	@echo VBE object file created 
buildio: bin
	@echo Compiling IO for $(value arch)
	$(CC) $(gccargs) -c src/krnl/io/io.c -o bin/io.o
	@echo IO object file created 
buildschedule: bin
	@echo Compiling SCHEDULE for $(value arch)
	$(CC) $(gccargs) -c src/krnl/multithreading/schedule.c -o bin/schedule.o
	@echo SCHEDULE object file created 
buildgdt: bin
	@echo Compiling GDT for $(value arch)
	$(CC) $(gccargs) -c src/krnl/cpu/gdt/gdt.c -o bin/gdt.o
	@echo GDT object file created
buildidt: bin
	@echo Compiling IDT for $(value arch)
	$(CC) $(gccargs) -c src/krnl/cpu/idt/idt.c -o bin/idt.o
	@echo IDT object file created  
buildirq: bin
	@echo Compiling IRQ for $(value arch)
	$(CC) $(gccargs) -c src/krnl/cpu/irq/irq.c -o bin/irq.o
	@echo IRQ object file created 
buildisr: bin
	@echo Compiling ISR for $(value arch)
	$(CC) $(gccargs) -c src/krnl/cpu/isr/isr.c -o bin/isr.o
	@echo ISR object file created 
buildbugcheck: bin
	@echo Compiling BUGCHECK for $(value arch)
	$(CC) $(gccargs) -c src/krnl/check/bugcheck.c -o bin/bugcheck.o
	@echo BUGCHECK object file created 
buildcmos: bin
	@echo Compiling CMOS for $(value arch)
	$(CC) $(gccargs) -c src/krnl/cpu/CMOS/cmos.c -o bin/cmos.o
	@echo CMOS object file created 
buildfonts: bin
	@echo Compiling FONTS for $(value arch)
	objcopy -O elf32-i386 -B i386 -I binary src/fonts/ter-powerline-v28b.psf bin/fonts.o
	readelf -sW bin/fonts.o
	@echo FONTS object file created 
link: bin
	@echo Linking kernel for $(value arch)
	$(LD) -z max-page-size=0x1000 -no-pie -T link.ld -m $(linkeroutput) -o bin/$(kernelname) -nostdlib $(value linktargets)
	@echo Linked  $(kernelname) kernel
	@echo Checking hash of kernel 
	@$(SUM) bin/$(kernelname)
	@echo Writing hash of kernel to krnlsum.txt
	$(RM) -f krnlsum.txt
	@$(SUM) bin/$(kernelname) >> krnlsum.txt
	@echo Check done
test:
	@$(SLEEP) 5
	@echo Starting $(kernelname) with QEMU arguments: $(value qemuargs)
	$(value qemu) -hda bin/figaOS.iso $(value qemuargs)
	@echo QEMU Shutdown: $(kernelname), bin/figaOS.iso
remove:
	@echo Cleaning up
	$(RM) -f $(value linktargets)
	$(RM) -f *.log
	@echo Cleaned object files $(value linktargets)
	@$(COLOR) 27
	@echo ###### BUILD SUCCESSFUL ######
	@echo ########## SUMMARY ##########
	@echo Operating system: $(OS)
	@echo Architecture: $(arch)
	@echo Linker: $(LD)
	@echo C Compiler: $(CC)
	@echo Assembler Compiler: $(ASM)
	@echo Remove tool: $(RM)
	@echo C Compiler arguments: $(gccargs)
	@echo Assembler Compiler arguments: $(nasmargs)
	@echo Linked objects: $(linktargets)
	@echo Kernel name: $(kernelname)
	@echo Kernel version: $(Version)
	@echo ########## SUMMARY ##########
	@echo Generating log file

	@echo ###### BUILD SUCCESSFUL ###### >> $(LOGFILE)
	@echo ########## SUMMARY ########## >> $(LOGFILE)
	@echo Operating system: $(OS) >> $(LOGFILE)
	@echo Architecture: $(arch) >> $(LOGFILE)
	@echo Linker: $(LD) >> $(LOGFILE)
	@echo C Compiler: $(CC) >> $(LOGFILE)
	@echo Assembler Compiler: $(ASM) >> $(LOGFILE)
	@echo Remove tool: $(RM) >> $(LOGFILE)
	@echo C Compiler arguments: $(gccargs) >> $(LOGFILE)
	@echo Assembler Compiler arguments: $(nasmargs) >> $(LOGFILE)
	@echo Linked objects: $(linktargets) >> $(LOGFILE) 
	@echo Kernel name: $(kernelname) >> $(LOGFILE)
	@echo Kernel version: $(Version) >> $(LOGFILE)
	@echo ########## SUMMARY ########## >> $(LOGFILE)
mkimage: bin
	@echo ISO Boot image creating for $(arch)
	$(MV) bin/$(kernelname) iso/boot/foskrnl.exe
	$(IMGMAKE) -o bin/figaOS.iso iso/
	@echo Removing old kernel image
	$(RM) -f iso/boot/foskrnl.exe
	@echo Removed old kernel image
	@echo Checking hash of image
	@$(SUM) bin/figaOS.iso
	@echo Writing hash of image to isosum.txt
	$(RM) -f isosum.txt
	@$(SUM) bin/figaOS.iso >> isosum.txt
	@echo Check done
	@echo Generating log file
	@echo #### IMAGE CREATION ####>> $(LOGFILE)
	@echo Kernel version: $(Version) >> $(LOGFILE)
	@echo Iso Image: bin/figaOS.iso >> $(LOGFILE)
	@echo Done
	@echo ISO Boot image created
clean:
	@echo Cleaning directories
	$(RM) -f bin/*.o
	$(RM) -f bin/*.exe
	$(RM) -f bin/*.bin
	$(RM) -f bin/*.iso
	$(RM) -f *.log
	$(RM) -f krnlsum.txt
	$(RM) -f isosum.txt
	@echo Cleaning done

	
