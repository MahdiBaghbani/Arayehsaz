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

########################################################################
# Setup compiler
########################################################################

# set C standard.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS OFF)

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
option(ENABLE_TESTING "Enable testing" ON)
option(ENABLE_COMPACT_MAP "Enable compact arayeh map" OFF)
option(BUILD_DOCUMENTATION "Build project documentation" ON)

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
endif (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

########################################################################
# Setup tests
########################################################################

if (ENABLE_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif (ENABLE_TESTING)

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
