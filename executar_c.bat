@echo off
cd /d "%~dp0estruturado_c"

echo Compilando o codigo em C...
"C:\Users\samue\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin\gcc.exe" main.c -o sistema_notas.exe

if errorlevel 1 (
    echo.
    echo Erro ao compilar o codigo em C.
    pause
    exit /b 1
)

echo.
echo Executando o sistema em C...
echo.
sistema_notas.exe

echo.
pause
