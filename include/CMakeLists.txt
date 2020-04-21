# CMake version.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# include predefined install paths.
include(GNUInstallDirs)
set(install_include_dir ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME})

########################################################################
# Install general public header files manually
########################################################################

# use template below.

# install(FILES name_of_header DESTINATION ${install_include_dir})
