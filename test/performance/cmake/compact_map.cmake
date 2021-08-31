# CMake version.
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)


# source list for the library.
set(
        sources
        ../../../source/arayeh.c
        ../../../source/types.c
        ../../../source/methods.c
        ../../../source/functions.c
        ../../../source/algorithms.c
)

# target for compact map mode.
add_library(
        tlib_compact_map
        STATIC
        ${sources}
)

# set library public header.
set_target_properties(
        tlib_compact_map
        PROPERTIES
        PUBLIC_HEADER ../../../include/arayeh.h
)

target_include_directories(
        tlib_compact_map
        PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(
        tlib_compact_map
        PUBLIC
        c_std_11
)

target_compile_definitions(
        tlib_compact_map
        PRIVATE
        -DARAYEH_COMPACT_MAP
)

target_include_directories(
        tlib_compact_map
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
)

add_library(
        tlib_non_compact_map
        STATIC
        ${sources}
)

# set library public header.
set_target_properties(
        tlib_non_compact_map
        PROPERTIES
        PUBLIC_HEADER ../../../include/arayeh.h
)

target_include_directories(
        tlib_non_compact_map
        PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(
        tlib_non_compact_map
        PUBLIC
        c_std_11
)

target_include_directories(
        tlib_non_compact_map
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
)
