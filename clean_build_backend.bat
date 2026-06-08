@echo off
chcp 65001 > nul
echo ===================================================
echo [WSL] Czyszczenie i kompilacja backendu od zera...
echo ===================================================
echo.

wsl make -C backend clean

wsl make -C backend

echo.
echo ===================================================
echo [Sukces] Backend został pomyślnie skompilowany!
echo Możesz teraz uruchomić frontend (MainFrame.java) z IntelliJ.
echo ===================================================
echo.
pause
