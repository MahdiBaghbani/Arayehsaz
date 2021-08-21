# CMake version.
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

include (CTest)

# add unity source directory.
add_subdirectory("unity test framework")

# add test category directories.
add_subdirectory("unit")
add_subdirectory("integration")
add_subdirectory("performance")
