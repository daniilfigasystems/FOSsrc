@echo off
echo Starting Build
"%qemu%/qemu-system-i386" -hda  bin/figaOS.isobuild.bat %1 && postbuild.bat mkimage %1 && postbuild clean %1 &&
echo Making image

echo Cleaning up

echo Starting qemu
