@echo off
REM FastAPI-C++ Build Script for Windows
REM This script provides easy commands to build and run the FastAPI-C++ test server

setlocal enabledelayedexpansion

if "%1"=="help" goto :help
if "%1"=="-h" goto :help
if "%1"=="--help" goto :help
if "%1"=="" goto :help

if "%1"=="build" goto :build
if "%1"=="run" goto :run
if "%1"=="clean" goto :clean
if "%1"=="test" goto :test

echo [ERROR] Unknown command: %1
echo.
goto :help

:help
echo FastAPI-C++ Build Script for Windows
echo ====================================
echo.
echo Usage: %0 [COMMAND]
echo.
echo Commands:
echo   build       - Build the library and test server
echo   run         - Build and run the test server
echo   clean       - Clean build artifacts
echo   test        - Run quick API tests
echo   help        - Show this help message
echo.
echo Examples:
echo   %0 build    # Build the project
echo   %0 run      # Build and run test server
echo   %0 test     # Test the running server
goto :end

:build
echo [INFO] Building FastAPI-C++...
if not exist "Makefile" (
    echo [ERROR] Makefile not found!
    exit /b 1
)

make clean
make all

if %errorlevel% equ 0 (
    echo [SUCCESS] Build completed successfully!
    echo [INFO] Library: build/libfastapi-cpp.a
    echo [INFO] Test server: build/test_server.exe
) else (
    echo [ERROR] Build failed!
    exit /b 1
)
goto :end

:run
echo [INFO] Building and running test server...
call :build
if %errorlevel% neq 0 exit /b 1

echo [INFO] Starting test server...
echo [INFO] Server will be available at: http://127.0.0.1:8080
echo [INFO] Demo page: http://127.0.0.1:8080/demo
echo [INFO] Health check: http://127.0.0.1:8080/health
echo [INFO] Press Ctrl+C to stop the server
echo.

build/test_server.exe
goto :end

:clean
echo [INFO] Cleaning build artifacts...
if exist "Makefile" make clean
if exist "build" rmdir /s /q build
echo [SUCCESS] Clean completed!
goto :end

:test
echo [INFO] Testing API endpoints...

REM Check if server is running
curl -s http://127.0.0.1:8080/health >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Server is not running. Please start it first with: %0 run
    exit /b 1
)

echo [INFO] Testing health endpoint...
curl -s http://127.0.0.1:8080/health

echo.
echo [INFO] Testing stats endpoint...
curl -s http://127.0.0.1:8080/stats

echo.
echo [INFO] Testing user creation...
curl -s -X POST http://127.0.0.1:8080/users -H "Content-Type: application/json" -d "{\"name\":\"Test User\",\"age\":25,\"email\":\"test@example.com\"}"

echo.
echo [SUCCESS] API tests completed!
goto :end

:end
