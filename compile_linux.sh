#!/bin/bash

# People like colors
YELLOW='\033[1;33m'
GREEN='\033[1;32m'
NC='\033[0m'

COMPILER_FLAGS="-std=c++17"
WARN_FLAGS="-Wall -Wextra -pedantic"

# Exit on error
set -e

echo -e "${YELLOW}Removing old build.${NC}"
rm -rf build

echo -e "${YELLOW}Creating build directory.${NC}"
mkdir build

echo -e "${YELLOW}Compiling executables.${NC}"

g++ -c PrintInfo.cpp \
 $WARN_FLAGS $COMPILER_FLAGS \
 -o build/PrintInfo.o

g++ -c ParseArgv.cpp \
 $WARN_FLAGS $COMPILER_FLAGS \
 -o build/ParseArgv.o

g++ -c TableParse.cpp \
 $WARN_FLAGS $COMPILER_FLAGS \
 -o build/TableParse.o

g++ -c main.cpp \
 $WARN_FLAGS $COMPILER_FLAGS \
 -o build/main.o

echo -e "${YELLOW}Basically linking everything together at this point!${NC}"

cd build
g++ PrintInfo.o ParseArgv.o TableParse.o main.o -o sa_to_binary
cd ../

echo -e "${GREEN}Done!${NC}"

exit
