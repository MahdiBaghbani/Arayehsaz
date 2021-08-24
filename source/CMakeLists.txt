# CMake version.
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

# source list for the library.
set(
        sources
        arayeh.c
        types.c
        methods.c
        functions.c
        algorithms.c
)

# create object library as base.
add_library(
        arayehsaz
        ${sources}
)

# add alias.
add_library(
        arayehsaz::arayehsaz
        ALIAS
        arayehsaz
)

# set library version, .so symlink version and public header.
set_target_properties(
        arayehsaz
        PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/arayeh.h
)

target_include_directories(
        arayehsaz
        PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(
        arayehsaz
        PUBLIC
        c_std_11
)

target_compile_definitions(
        arayehsaz
        PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:arayehsaz_STATIC_DEFINE>"
)

target_include_directories(
        arayehsaz
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
)
