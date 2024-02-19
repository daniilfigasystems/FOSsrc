@echo off
title FigaOS build
if "%1" == "help" echo build arch - Build for specific architecture && echo Avaible architectures: i386, x64 && echo build help - Prints help && exit /B
setlocal
for /f "tokens=4-5 delims=. " %%i in ('ver') do set VERSION=%%i.%%j
if "%version%" == "10.0" echo Compiling FigaOS using Windows 10
if "%version%" == "6.3" echo Compiling FigaOS using Windows 8.1
if "%version%" == "6.2" echo Compiling FigaOS using Windows 8.
if "%version%" == "6.1" echo Compiling FigaOS using Windows 7.
if "%version%" == "6.0" echo Compiling FigaOS using Windows Vista.
rem etc etc
endlocal 
make arch=%1 --print-directory
if ERRORLEVEL 1 color 47 && echo ##### BUILD FAILED ##### && echo %errorlevel%