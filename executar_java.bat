@echo off
cd /d "%~dp0orientado_objetos_java"

echo Compilando o codigo em Java...
if not exist build mkdir build
"C:\Program Files\Eclipse Adoptium\jdk-21.0.11.10-hotspot\bin\javac.exe" -encoding UTF-8 -d build *.java

if errorlevel 1 (
    echo.
    echo Erro ao compilar o codigo em Java.
    pause
    exit /b 1
)

echo.
echo Executando o sistema em Java...
echo.
"C:\Program Files\Eclipse Adoptium\jdk-21.0.11.10-hotspot\bin\java.exe" -cp build Main

echo.
pause
