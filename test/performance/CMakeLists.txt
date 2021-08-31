# CMake version.
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

# include library targets.
include("cmake/compact_map.cmake")

# add test executable targets.
add_executable(ptest_001_CompactMap "perfTest_001_CompactMap.c")
add_executable(ptest_002_NonCompactMap "perfTest_002_NonCompactMap.c")

target_link_libraries(ptest_001_CompactMap PRIVATE tlib_compact_map)
target_link_libraries(ptest_002_NonCompactMap PRIVATE tlib_non_compact_map)
