# CMake version.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# include predefined install paths.
include(GNUInstallDirs)
set(install_include_dir ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME})

########################################################################
# Install public header files
########################################################################

install(FILES configurations.h DESTINATION ${install_include_dir})
