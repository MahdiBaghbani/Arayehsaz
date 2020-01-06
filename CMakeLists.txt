# Cmake version.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Project name.
project(Arayehsaz VERSION 0.1.0 LANGUAGES C DESCRIPTION "Easy and almost safe array maker in C.")

# C standard.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED YES)

# Library type.
set(BUILD_SHARED_LIBS YES)

# Building options: Release, Debug, RelWithDebInfo, MinRelSize.
set(CMAKE_BUILD_TYPE DEBUG)

# Toolchain options.
set(CMAKE_MAKE_PROGRAM make)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

# add source directory.
add_subdirectory(source)

# include tests in Debug mode.
if (CMAKE_BUILD_TYPE STREQUAL DEBUG)
    include(CTest)
    add_subdirectory(test)
endif ()
