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
        arayehsaz_object
        OBJECT
        ${sources}
)

# shared libraries need PIC (POSITION_INDEPENDENT_CODE).
set_property(TARGET arayehsaz_object PROPERTY POSITION_INDEPENDENT_CODE 1)

# add shared and static libraries from the base object library.
add_library(arayehsaz SHARED $<TARGET_OBJECTS:arayehsaz_object>)
add_library(arayehsaz_static STATIC $<TARGET_OBJECTS:arayehsaz_object>)

# set library version, .so symlink version and public header.
set_target_properties(
        arayehsaz
        PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        PUBLIC_HEADER ${INCLUDE_DIR}/arayeh.h
)

# set library version, .so symlink version and public header.
set_target_properties(
        arayehsaz
        PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        PUBLIC_HEADER ${INCLUDE_DIR}/arayeh.h
)

# install library.
install(
        TARGETS arayehsaz
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        CONFIGURATIONS Release
        # INSTALL_INCLUDE_DIR is defined in root cmake file.
        PUBLIC_HEADER DESTINATION ${INSTALL_INCLUDE_DIR}
)
