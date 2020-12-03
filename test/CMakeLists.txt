# CMake version.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# add unity source directory.
add_subdirectory("unity test framework")

# add test category directories.
add_subdirectory("unit tests")
add_subdirectory("integration tests")
add_subdirectory("performance tests")
