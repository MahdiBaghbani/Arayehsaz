# CMake version.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# create array shared library.
add_library(arayehsaz
        arayeh.c
        types.c
        methods.c
        functions.c
        algorithms.c)

# set library version, so symlink version and public header.
set_target_properties(arayehsaz
        PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        PUBLIC_HEADER ${INCLUDE_DIR}/arayeh.h)

# install lib.
install(TARGETS arayehsaz
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        CONFIGURATIONS Release
        # INSTALL_INCLUDE_DIR is defined in root cmake file.
        PUBLIC_HEADER DESTINATION ${INSTALL_INCLUDE_DIR})
