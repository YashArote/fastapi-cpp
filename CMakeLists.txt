cmake_minimum_required(VERSION 3.16)
project(FastAPI-CPP VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDEBUG")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/router.cpp
    src/request.cpp
    src/response.cpp
    src/mongo_primitives.cpp
    src/postgres_primitives.cpp
    src/redis_primitives.cpp
)

# Create static library
add_library(fastapi-cpp STATIC ${SOURCES})

# Set library properties
set_target_properties(fastapi-cpp PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER include/server.hpp
)

# Create examples directory
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples)

# Test server executable
add_executable(test_server examples/test_server.cpp)
target_link_libraries(test_server fastapi-cpp pthread)

# Installation
install(TARGETS fastapi-cpp
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/fastapi-cpp
)

install(DIRECTORY include/ DESTINATION include/fastapi-cpp)

# Package configuration
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/FastAPI-CPPConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FastAPI-CPPConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/FastAPI-CPPConfig.cmake"
    INSTALL_DESTINATION lib/cmake/FastAPI-CPP
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/FastAPI-CPPConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/FastAPI-CPPConfigVersion.cmake"
    DESTINATION lib/cmake/FastAPI-CPP
)

# Custom targets
add_custom_target(run_test_server
    COMMAND test_server
    DEPENDS test_server
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running test server"
)

# Print build information
message(STATUS "FastAPI-C++ Build Configuration:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  Install Prefix: ${CMAKE_INSTALL_PREFIX}")
