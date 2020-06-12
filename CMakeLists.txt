########################################################################
# Setup project
########################################################################

# CMake version.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Project name.
project(arayehsaz
        VERSION 0.1.0
        LANGUAGES C
        DESCRIPTION "Easy and almost safe dynamic arrays in C."
        )

# Library type.
set(BUILD_SHARED_LIBS YES)

########################################################################
# Setup compiler
########################################################################

# C standard.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS OFF)

# set flags.
if (("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" MATCHES "Clang") AND NOT WIN32)
    add_definitions(-Wall)
    add_definitions(-Wextra)
    add_definitions(-Wsign-compare)
    add_definitions(-Wno-unused)
    add_definitions(-Wno-unused-parameter)
    add_definitions(-Wno-missing-field-initializers)
    add_definitions(-std=c11)
    add_definitions(-pedantic)
endif ()

if ("${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
    # make sure we don't accidentally copy more than an int
    add_definitions(-Wlarge-by-value-copy=8)
endif ()

########################################################################
# Setup build type
########################################################################

# set a default build type.
set(DEFAULT_BUILD_TYPE "Release")

#select the release build type by default to get optimization flags
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose type of build." FORCE)
    # set possible values of build types for cmake-gui.
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInf")
endif (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)


########################################################################
# Setup include and install paths
########################################################################

# include install default variables.
include(GNUInstallDirs)

# set the directory to install headers.
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME})

# set path to header files.
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

########################################################################
# Setup project configuration file
########################################################################

# install configure file, allows third-party applications to easily import arayehsaz.
configure_file(arayehsaz.pc.in arayehsaz.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/arayehsaz.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR})

########################################################################
# Add subdirectories
########################################################################

# add source directory.
add_subdirectory(include)
add_subdirectory(source)

########################################################################
# Setup tests
########################################################################

# set a default test build option.
set(BUILD_TESTING ON)

if (BUILD_TESTING)
    message(STATUS "Creating test targets.")
    enable_testing()
    add_subdirectory(test)
endif (BUILD_TESTING)

########################################################################
# Setup uninstall procedure
########################################################################
configure_file(
        ${PROJECT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
        IMMEDIATE
        @ONLY)

add_custom_target(uninstall
        ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
        )
