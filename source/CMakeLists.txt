# Cmake version.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# create array shared library.
add_library(arayeh arayeh.c arayehInternal.c arayehTypeManager.c arayehTypeManager.h)
target_include_directories(arayeh PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
