@echo off
echo Building...

Rem Building with cmake then deploying dependencies on the client side.
cd build && cmake --build . && cd .. && copy .\build\bin\r-type_client.exe .\ && copy .\build\bin\r-type_server.exe .\

if %ERRORLEVEL% NEQ 0 goto :error

echo.
echo Build Completed !
echo Binaries are located in build\bin\
echo.

:error