@echo off
setlocal enabledelayedexpansion

:: ============================================================
::  Unreal Engine - Clean Project
::  Deletes Binaries & Intermediate from:
::    - Project root
::    - All folders under Plugins\
:: ============================================================

:: Resolve the project root to the folder this .bat lives in
set "PROJECT_ROOT=%~dp0"
:: Strip trailing backslash
if "%PROJECT_ROOT:~-1%"=="\" set "PROJECT_ROOT=%PROJECT_ROOT:~0,-1%"

echo.
echo ============================================================
echo  UE Clean Script
echo  Project Root: %PROJECT_ROOT%
echo ============================================================
echo.
echo  This will DELETE the following folders:
echo    - %PROJECT_ROOT%\Binaries
echo    - %PROJECT_ROOT%\Intermediate
echo    - %PROJECT_ROOT%\Plugins\*\Binaries
echo    - %PROJECT_ROOT%\Plugins\*\Intermediate
echo.
set /p CONFIRM="  Are you sure? (Y/N): "
if /i not "%CONFIRM%"=="Y" (
    echo  Aborted.
    goto :EOF
)

echo.

:: ── Root Binaries ────────────────────────────────────────────
:: Preserve steam_appid.txt before deleting Binaries
set "STEAM_APPID_BAK="
if exist "%PROJECT_ROOT%\Binaries\Win64\steam_appid.txt" (
    copy /y "%PROJECT_ROOT%\Binaries\Win64\steam_appid.txt" "%PROJECT_ROOT%\steam_appid.bak" >nul
    set "STEAM_APPID_BAK=1"
)
call :DeleteFolder "%PROJECT_ROOT%\Binaries"
:: Restore steam_appid.txt after deletion
if defined STEAM_APPID_BAK (
    if not exist "%PROJECT_ROOT%\Binaries\Win64" mkdir "%PROJECT_ROOT%\Binaries\Win64"
    move /y "%PROJECT_ROOT%\steam_appid.bak" "%PROJECT_ROOT%\Binaries\Win64\steam_appid.txt" >nul
    echo  [RESTORE] steam_appid.txt
)

:: ── Root Intermediate ────────────────────────────────────────
call :DeleteFolder "%PROJECT_ROOT%\Intermediate"

:: ── Plugins ──────────────────────────────────────────────────
set "PLUGINS_DIR=%PROJECT_ROOT%\Plugins"

if not exist "%PLUGINS_DIR%" (
    echo  [SKIP] No Plugins folder found.
    goto :Done
)

:: Loop every direct subfolder under Plugins\
for /d %%P in ("%PLUGINS_DIR%\*") do (
    call :DeleteFolder "%%P\Binaries"
    call :DeleteFolder "%%P\Intermediate"
)

:Done
echo.
echo ============================================================
echo  Clean complete. Rebuild the project in Rider / VS.
echo ============================================================
echo.
pause
goto :EOF


:: ── Subroutine ───────────────────────────────────────────────
:DeleteFolder
    if exist "%~1" (
        echo  [DELETE] %~1
        rd /s /q "%~1"
        if exist "%~1" (
            echo  [ERROR]  Failed to delete: %~1
        )
    ) else (
        echo  [SKIP]   Not found: %~1
    )
exit /b