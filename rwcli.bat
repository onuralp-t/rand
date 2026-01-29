@echo off
set CFLAGS=^
-Wall -Wextra -pedantic ^
-O3 -s

@echo on
gcc %CFLAGS% -o rwcli.exe rwcli.c && .\rwcli.exe
@echo off