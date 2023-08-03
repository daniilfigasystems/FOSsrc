@echo off
echo                            FOSNT COMPILE DRIVERS
echo                            STARTING NTCOMPILER 
compiler/compile.bat %cd%/PRIVATE/drivers/basevid/vga.c -o bin/vga.o  -nostdlib -nodefaultlibs -Wall -Wimplicit-function-declaration -Wint-conversion -Wbuiltin-declaration-mismatch
compiler/compile.bat %cd%/PRIVATE/drivers/basevid/setmode.c -o bin/setmode.o -nostdlib -nodefaultlibs -Wall -Wimplicit-function-declaration -Wint-conversion -Wbuiltin-declaration-mismatch
gcc bin/setmode.o bin/vga.o -o bin/basevid.sys