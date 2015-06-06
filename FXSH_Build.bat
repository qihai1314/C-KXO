@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.

if exist debug\*.obj  del debug\*.obj
if exist SDCLSQ.G1A  del SDCLSQ.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"C:\Program Files\CASIO\fx-9860G SDK\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"C:\Program Files\CASIO\fx-9860G SDK\Tools\MakeAddinHeader363.exe" "C:\Users\Administrator\Desktop\2015-06-6交点法转线元推链表\2015-06-4交点法转线元推链表"
if not exist SDCLSQ.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

