@echo off
echo                            FIGA NT COMPILER
set arg1 = %1
set arg2 = %2
set args = %3
gcc %1 -o %2 %3

echo         COMPILER LOG %date% %time% >> complogs.log
ver >> complogs.log
echo done >> complogs.log
echo %errorlevel% >> complogs.log
echo         END OF LOG %date% %time% >> complogs.log
