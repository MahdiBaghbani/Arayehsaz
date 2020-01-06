# Cmake version.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# add source directory.
add_subdirectory("unity test framework")

# add tests.
add_executable(testArayeh unitTestInitFree.c)
target_link_libraries(testArayeh PRIVATE libarayeh unity)
add_test(unitTestArayeh testArayeh)