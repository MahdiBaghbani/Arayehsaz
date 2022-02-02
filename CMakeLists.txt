########################################################################
# Setup project
########################################################################

# CMake version.
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

# Project name.
project(
        arayehsaz
        VERSION 0.1.0
        LANGUAGES C
        DESCRIPTION "Easy and almost safe dynamic arrays in C."
)

cmake_host_system_information(RESULT cpu_thread_count QUERY NUMBER_OF_LOGICAL_CORES)
message(STATUS "CMake ${CMAKE_VERSION} using ${cpu_thread_count} threads")
add_definitions(-DAA_ARAYEH_CPU_COUNT=${cpu_thread_count})

########################################################################
# Setup compiler
########################################################################

# set C standard.
if (UNIX AND NOT APPLE)
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED YES)
    set(CMAKE_C_EXTENSIONS OFF)
elseif (WIN32)
    if (MSVC)
        set(CMAKE_C_STANDARD 11)
        set(CMAKE_C_STANDARD_REQUIRED YES)
        set(CMAKE_C_EXTENSIONS OFF)
    elseif (MSYS)
        set(CMAKE_C_STANDARD 11)
        set(CMAKE_C_STANDARD_REQUIRED YES)
        set(CMAKE_C_EXTENSIONS OFF)
    elseif (MINGW)
        set(CMAKE_C_STANDARD 11)
        set(CMAKE_C_STANDARD_REQUIRED YES)
        set(CMAKE_C_EXTENSIONS OFF)
    endif ()
endif ()

# set a default build type.
set(DEFAULT_BUILD_TYPE "Release")

# set compiler flags.
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

add_compile_options(
        -Wall
        -Wextra
        -Werror
        -Wsign-compare
        -Wno-unused
        -Wno-unused-parameter
        -Wno-missing-field-initializers
        -std=c11
        -pedantic
)

# default build options.
option(ENABLE_COMPACT_MAP "Enable compact arayeh map" OFF)
option(ENABLE_MULTI_THREAD "Enable multi threading" OFF)
message(STATUS "Compact Map: ${ENABLE_COMPACT_MAP}, Multi-Threading: ${ENABLE_MULTI_THREAD}")

# other options.
option(ENABLE_TESTING "Enable testing" ON)
option(BUILD_DOCUMENTATION "Build project documentation" ON)
message(STATUS "Testing: ${ENABLE_TESTING}, Documentation: ${BUILD_DOCUMENTATION}")

# enforce shared library format.
if (DEFINED ARAYEHSAZ_SHARED_LIBS)
    set(BUILD_SHARED_LIBS "Build with shared libraries" "${ARAYEHSAZ_SHARED_LIBS}")
endif ()

########################################################################
# Setup build type
########################################################################

# select the release build type by default to get optimization flags
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(
            STATUS
            "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified"
    )
    set(
            CMAKE_BUILD_TYPE
            "${DEFAULT_BUILD_TYPE}"
            CACHE
            STRING
            "Choose type of build."
            FORCE
    )
    # set possible values of build types for cmake-gui.
    set_property(
            CACHE
            CMAKE_BUILD_TYPE
            PROPERTY STRINGS
            "Debug"
            "Release"
            "MinSizeRel"
            "RelWithDebInf"
    )
endif ()

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

########################################################################
# Setup tests
########################################################################

if (ENABLE_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
    if(NOT cpu_thread_count EQUAL 0)
        set(CTEST_BUILD_FLAGS -j${cpu_thread_count})
        set(ctest_test_args ${ctest_test_args} PARALLEL_LEVEL ${cpu_thread_count})
    endif()
endif ()

########################################################################
# Setup documentation
########################################################################

if (BUILD_DOCUMENTATION)
    add_subdirectory(document)
endif ()

########################################################################
# Add subdirectories
########################################################################

# add source directory.
add_subdirectory(include)
add_subdirectory(source)

# if Arayehsaz is the main project, include packaging directory.
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)
option(ARAYEHSAZ_INCLUDE_PACKAGING "Include packaging rules for arayehsaz" "${is_top_level}")
if (ARAYEHSAZ_INCLUDE_PACKAGING)
    add_subdirectory(package)
endif ()
