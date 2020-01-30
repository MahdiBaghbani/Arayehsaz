# CMake version.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# add source directory.
add_subdirectory("unity test framework")

# add tests.
add_executable(testArayehInitFree unitTestInitFree.c)
target_link_libraries(testArayehInitFree PRIVATE arayeh unity)
add_test(unitTestArayehInitFree testArayehInitFree)