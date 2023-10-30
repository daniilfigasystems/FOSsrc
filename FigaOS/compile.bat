@echo off
echo                            FIGA NT COMPILER
make

echo         COMPILER LOG %date% %time% >> complogs.log
ver >> complogs.log
echo done >> complogs.log
echo %errorlevel% >> complogs.log
echo         END OF LOG %date% %time% >> complogs.log
