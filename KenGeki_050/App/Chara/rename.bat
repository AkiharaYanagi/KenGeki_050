@echo off
setlocal enabledelayedexpansion

set "remove=050"
set "name=%~nx1"
set "newname=!name:%remove%=!"
ren "%~1" "!newname!"
