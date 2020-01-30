########################################################################
# Project setup
########################################################################

# CMake version.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Project name.
project(Arayehsaz VERSION 0.1.0 LANGUAGES C DESCRIPTION "Easy and almost safe array maker in C.")

########################################################################
# Compiler specific setup
########################################################################

# C standard.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS OFF)

# set flags.
if(("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" MATCHES "Clang") AND NOT WIN32)
    ADD_DEFINITIONS(-Wall)
    ADD_DEFINITIONS(-Wextra)
    ADD_DEFINITIONS(-Wsign-compare)
    ADD_DEFINITIONS(-Wno-unused)
    ADD_DEFINITIONS(-Wno-unused-parameter)
    ADD_DEFINITIONS(-Wno-missing-field-initializers)
    ADD_DEFINITIONS(-std=c11)
    ADD_DEFINITIONS(-pedantic)
endif()

########################################################################
# Setup the library type and include and linker paths
########################################################################
# Library type.
set(BUILD_SHARED_LIBS YES)

include_directories(
        BEFORE
        ${PROJECT_SOURCE_DIR}/include
)

########################################################################
# Build tests
########################################################################
include(CTest) # note: this adds a BUILD_TESTING which defaults to ON

########################################################################
# Add subdirectories
########################################################################

# add source directory.
add_subdirectory(include)
add_subdirectory(source)

if(BUILD_TESTING)
    add_subdirectory(test)
endif(BUILD_TESTING)
