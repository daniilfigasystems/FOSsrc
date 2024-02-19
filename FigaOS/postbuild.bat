@echo off
title FigaOS PostBuild
if "%1" == "run" echo Starting QEMU && make test arch=%2
if "%1" == "mkimage" echo Making ISO file && make mkimage arch=%2
if "%1" == "clean" echo Cleaning && make clean arch=%2
if "%1" == "" echo Print postbuild help to get help && exit /b 0
if "%1" == "help" echo Usage: && echo postbuild run - Runs QEMU && echo postbuild mkimage - Make GRUB image && echo postbuild clean - Clean directories && echo postbuild help - Print help && exit /b 0
if ERRORLEVEL 1 color 47 && echo Failed