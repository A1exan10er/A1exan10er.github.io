#!/bin/bash

# Cross-compilation script for Windows
# This script compiles the PDF2JPG tool for Windows using MinGW

echo "Building PDF2JPG for Windows..."

# Set up cross-compilation environment
export CXX=x86_64-w64-mingw32-g++
export CC=x86_64-w64-mingw32-gcc
export PKG_CONFIG_PATH=/usr/x86_64-w64-mingw32/lib/pkgconfig

# Note: You'll need to install Windows versions of these libraries:
# - Poppler (poppler-cpp)
# - OpenCV
# These can be obtained from:
# - MSYS2: https://www.msys2.org/
# - vcpkg: https://github.com/Microsoft/vcpkg
# - Pre-built binaries

echo "Note: This requires Windows versions of Poppler and OpenCV libraries."
echo "You can:"
echo "1. Use this script as a template and install the libraries manually"
echo "2. Use a Windows environment with MSYS2 or vcpkg"
echo "3. Use the Docker approach below"

# Example compilation command (requires proper library paths):
# $CXX -std=c++17 -O2 PDF2JPG_Windows.cpp -o PDF2JPG.exe \
#   -lpoppler-cpp -lopencv_core -lopencv_imgproc -lopencv_imgcodecs \
#   -static-libgcc -static-libstdc++

echo "To build on Windows with MSYS2:"
echo "1. Install MSYS2"
echo "2. pacman -S mingw-w64-x86_64-poppler mingw-w64-x86_64-opencv"
echo "3. g++ -std=c++17 -O2 PDF2JPG_Windows.cpp -o PDF2JPG.exe \\"
echo "   \$(pkg-config --cflags --libs poppler-cpp opencv4)"
