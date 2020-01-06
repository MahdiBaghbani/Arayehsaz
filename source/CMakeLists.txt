# Cmake version.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# add arrays 1D library.
add_library(array1d arayeh.c arayehInternal.c arayehTypeManager.c arayehTypeManager.h)
target_include_directories(array1d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
