@echo off

set COMPILER_FLAGS=-std=c++17 -O2
set WARN_FLAGS=-Wall -Wextra -pedantic

color 0E

echo Removing old build.
rmdir /S /Q build

echo Creating build directory.
mkdir build || goto :error

echo  Compiling executables.

g++ -c PrintInfo.cpp %WARN_FLAGS% %COMPILER_FLAGS% -o build/PrintInfo.o || goto :error

g++ -c ParseArgv.cpp %WARN_FLAGS% %COMPILER_FLAGS% -o build/ParseArgv.o || goto :error

g++ -c TableParse.cpp %WARN_FLAGS% %COMPILER_FLAGS% -o build/TableParse.o || goto :error

g++ -c main.cpp %WARN_FLAGS% %COMPILER_FLAGS% -o build/main.o || goto :error

echo Basically linking everything together at this point!

cd build || goto :error
g++ PrintInfo.o ParseArgv.o TableParse.o main.o -s -static -o sa_to_binary.exe || goto :error
cd ../ || goto :error

color 02
echo Done!
timeout 2 > NUL
color 0F
goto :end


:error
color 0C
echo error!
timeout 2 > NUL
color 0F

:end