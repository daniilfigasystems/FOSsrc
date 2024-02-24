arch = i386
Version = 0.001dev
qemuargs = -d mmu,pcall,cpu_reset,int
kernelname = foskrnl$(arch).exe
linktargets = bin/boot.o bin/init.o bin/gdt.o bin/mm.o bin/vga.o bin/vesa.o bin/bugcheck.o bin/string.o bin/io.o bin/serial.o bin/cmos.o bin/fonts.o bin/bios.o bin/biosasm.o
LOGFILE = build.log
ifeq ($(value arch), i386)
nasmargs = -f elf32
gccargs = -m32 -Isrc/krnl/include -g  -W -ffreestanding -Wformat=0
linkeroutput = elf_i386
else ifeq ($(value arch), x64)
nasmargs = -f elf64
gccargs = -m64 -Isrc/krnl/include -g -W -ffreestanding -Wformat=0
linkeroutput = elf_x86_64
else ifeq ($(value arch),)
$(info Warning: Architecture not set! Setting to i386)
override arch = i386
override kernelname = foskrnl$(arch).exe
nasmargs = -f elf32
gccargs = -m32 -Isrc/krnl/include -g -W -ffreestanding -Wformat=0
linkeroutput = elf_i386
else
$(info Warning: Architecture is wrong! Setting to i386)
override arch = i386
nasmargs = -f elf32
gccargs = -m32 -Isrc/krnl/include -g -W -ffreestanding -Wformat=0
linkeroutput = elf_i386
endif
ifeq ($(OS),Windows_NT)
qemu = C:\Program Files\qemu\qemu-system-i386
COLOR = color
CC = wsl gcc
ASM = wsl nasm
LD = wsl ld
RM = wsl rm
SUM = wsl sha256sum
IMGMAKE = wsl grub-mkrescue
CAT = wsl cat
MV = wsl mv
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
SLEEP = sleep
VER = uname -a
endif
all: setcolor buildinit buildboot buildstring buildbios buildmm buildvga buildgdt buildserial buildbugcheck buildio buildvbe buildcmos buildfonts link remove
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
buildinit:
	@echo Compiling INIT for $(value arch)
	$(CC) $(gccargs) -c src/krnl/init/init.c -o bin/init.o
	@echo INIT object file created 
buildstring:
	@echo Compiling STRING for $(value arch)
	$(CC) $(gccargs) -c src/krnl/include/libs/sources/string.c -o bin/string.o
	@echo STRING object file created 
buildboot:
	@echo Compiling BOOT for $(value arch)
	$(ASM) $(nasmargs) src/boot/x86/boot.asm -o bin/boot.o
	@echo BOOT object file created 
buildbios:
	@echo Compiling BIOS for $(value arch)
	$(CC) $(gccargs) -c src/boot/x86/BIOS/bios.c -o bin/bios.o
	$(ASM) $(nasmargs) src/boot/x86/BIOS/bios.asm -o bin/biosasm.o
	@echo BIOS object file created 
buildvga:
	@echo Compiling VGA for $(value arch)
	$(CC) $(gccargs) -c src/drivers/vga/vga.c -o bin/vga.o
	@echo VGA object file created 
buildserial:
	@echo Compiling SERIAL for $(value arch)
	$(CC) $(gccargs) -c src/krnl/io/serial.c -o bin/serial.o
	@echo SERIAL object file created 
buildmm:
	@echo Compiling MEMORY for $(value arch)
	$(CC) $(gccargs) -c src/krnl/memory/mm.c -o bin/mm.o
	@echo MEMORY object file created 
buildvbe:
	@echo Compiling VBE for $(value arch)
	$(CC) $(gccargs) -c src/drivers/vesa/vesa.c -o bin/vesa.o
	@echo VBE object file created 
buildio:
	@echo Compiling IO for $(value arch)
	$(CC) $(gccargs) -c src/krnl/io/io.c -o bin/io.o
	@echo IO object file created 
buildgdt:
	@echo Compiling GDT for $(value arch)
	$(CC) $(gccargs) -c src/krnl/cpu/gdt/gdt.c -o bin/gdt.o
	@echo GDT object file created 
buildbugcheck:
	@echo Compiling BUGCHECK for $(value arch)
	$(CC) $(gccargs) -c src/krnl/check/bugcheck.c -o bin/bugcheck.o
	@echo BUGCHECK object file created 
buildcmos:
	@echo Compiling CMOS for $(value arch)
	$(CC) $(gccargs) -c src/krnl/cpu/CMOS/cmos.c -o bin/cmos.o
	@echo CMOS object file created 
buildfonts:
	@echo Compiling FONTS for $(value arch)
	objcopy -O elf32-i386 -B i386 -I binary src/fonts/ter-powerline-v28b.psf bin/fonts.o
	readelf -sW bin/fonts.o
	@echo FONTS object file created 
link:
	@echo Linking kernel for $(value arch)
	$(LD) -z max-page-size=0x1000 -T link.ld -m $(linkeroutput) -o bin/$(kernelname) -nostdlib $(value linktargets)
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
mkimage:
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

	