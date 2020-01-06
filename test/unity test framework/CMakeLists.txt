# Cmake version.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Unity testing framework library.
add_library(unity unity.c)
target_include_directories(unity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})