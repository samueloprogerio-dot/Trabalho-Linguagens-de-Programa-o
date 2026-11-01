@echo off
cd /d "%~dp0funcional_python"

echo Executando o sistema em Python...
echo.
py main.py

if errorlevel 1 (
    echo.
    echo Nao foi possivel executar com o comando "py".
    echo Tentando com o Python do Codex...
    "C:\Users\samue\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe" main.py
)

echo.
pause
