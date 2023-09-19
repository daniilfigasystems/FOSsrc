@echo off
echo                            FOSNT COMPILE DRIVERS
echo                            STARTING NTCOMPILER 
gcc private/drivers/basevid/vga.c -o bin/basevid.sys -nostdlib