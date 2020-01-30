# CMake version.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# include predefined install paths.
include(GNUInstallDirs)
set(install_include_dir ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME})

# set path to header files.
set(include_dir ${PROJECT_SOURCE_DIR}/include)

# create array shared library.
add_library(arayehsaz arayeh.c arayehInternal.c arayehTypeManager.c)

# set public header.
set_target_properties(arayehsaz PROPERTIES PUBLIC_HEADER ${include_dir}/arayeh.h)

# install lib.
install(TARGETS arayehsaz PUBLIC_HEADER DESTINATION ${install_include_dir})
