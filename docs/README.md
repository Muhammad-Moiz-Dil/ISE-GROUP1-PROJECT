# ISE-GROUP1-PROJECT


# Chatbot Project Setup Guide

## Backend Requirements (Windows & Mac)
- C++17 compatible compiler
- CMake 3.15+
- Drogon (C++ web framework)
- JsonCpp (JSON library)

## Windows Setup---🪟
### Choose a Compiler
- Visual Studio 2019+ (with C++ CMake tools)
- OR MinGW-w64 with GCC 8.1+
- OR MSYS2 with Clang/LLVM

### Required Tools
- CMake 3.15+
- vcpkg (recommended)
- Git

### Install Dependencies
vcpkg install drogon:x64-windows
vcpkg install jsoncpp:x64-windows

## Mac Setup---🍏
### Prerequisites
- Xcode Command Line Tools
- Homebrew

### Install Dependencies
xcode-select --install
brew install cmake
brew install drogon
brew install jsoncpp

### Compiler Options
- Xcode Clang (default)
- OR: brew install gcc

## Frontend Requirements (Windows & Mac)
- Browser: Chrome, Firefox, Safari, or Edge
- Python 3.x (built-in on Mac, install from python.org on Windows)

## Build Instructions

### Windows
git clone <repository-url>
cd ISE-GROUP1-PROJECT/backend
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE="[path_to_vcpkg]/scripts/buildsystems/vcpkg.cmake"
cmake --build . --config Release

### Mac
git clone <repository-url>
cd ISE-GROUP1-PROJECT/backend
mkdir -p build
cd build
cmake ..
make

## Running the Project

### Start Backend (Terminal 1)

Windows:
.\build\Release\chatbot.exe

Mac:
./build/chatbot

### Start Frontend (Terminal 2)
cd frontend
python3 -m http.server 8000

### Open in Browser
http://localhost:8000

## Troubleshooting
- Missing dependencies → install required packages
- Wrong architecture → ensure x64/x86 correct version
- Build fails → delete build/ folder and rebuild
- CMake can’t find packages → check toolchain path
- Port conflict → Backend: 18080, Frontend: 8000



## Quick Run Commands

Terminal 1: Backend Server
cd /*path*/backend
mkdir -p build
cd build
cmake ..
make
cd /*path*/backend
./build/chatbot

Terminal 2: Frontend Server
cd /*path*/frontend
python3 -m http.server 8000
