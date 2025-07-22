cmake_minimum_required(VERSION 3.16)
project(CppProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable precompiled headers support
set(CMAKE_SUPPORTS_PRECOMPILED_HEADERS ON)

# Add the static library
add_library(StaticLib1 STATIC
    StaticLib1.cpp
    pch.cpp
    pch.h
    framework.h
)

# Set up precompiled headers for the static library
target_precompile_headers(StaticLib1 PRIVATE pch.h)

# Add the main executable
add_executable(MainApp
    file.cpp
)

# Link the static library to the main executable
target_link_libraries(MainApp PRIVATE StaticLib1)

# Set up include directories
target_include_directories(StaticLib1 PRIVATE .)
target_include_directories(MainApp PRIVATE .)

# Platform-specific settings
if(WIN32)
    target_compile_definitions(StaticLib1 PRIVATE WIN32_LEAN_AND_MEAN)
    target_compile_definitions(MainApp PRIVATE WIN32_LEAN_AND_MEAN)
endif()

# Debug/Release configurations
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(StaticLib1 PRIVATE _DEBUG)
    target_compile_definitions(MainApp PRIVATE _DEBUG)
else()
    target_compile_definitions(StaticLib1 PRIVATE NDEBUG)
    target_compile_definitions(MainApp PRIVATE NDEBUG)
endif()

# Enable additional warnings
if(MSVC)
    target_compile_options(StaticLib1 PRIVATE /W3)
    target_compile_options(MainApp PRIVATE /W3)
else()
    target_compile_options(StaticLib1 PRIVATE -Wall -Wextra)
    target_compile_options(MainApp PRIVATE -Wall -Wextra)
endif()
