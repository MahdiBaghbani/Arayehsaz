# CMake version.
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# set the directory path to install headers in target system.
# would be libdir/arayehsaz.
# example: in my ubuntu it would be installed on ().
set(
        INSTALL_INCLUDE_DIR
        "${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}"
)

if (NOT DEFINED ARAYEHSAZ_INSTALL_CMAKEDIR)
    set(
            ARAYEHSAZ_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
            CACHE STRING "Path to Arayehsaz CMake files"
    )
endif (NOT DEFINED ARAYEHSAZ_INSTALL_CMAKEDIR)

install(
        TARGETS arayehsaz EXPORT arayehsaz_Targets
        RUNTIME COMPONENT arayehsaz_Runtime
        LIBRARY COMPONENT arayehsaz_Runtime
        NAMELINK_COMPONENT arayehsaz_Development
        ARCHIVE COMPONENT arayehsaz_Development
        PUBLIC_HEADER DESTINATION ${INSTALL_INCLUDE_DIR}
)

if (BUILD_SHARED_LIBS)
    set(type shared)
else ()
    set(type static)
endif (BUILD_SHARED_LIBS)

install(
        EXPORT arayehsaz_Targets
        DESTINATION "${ARAYEHSAZ_INSTALL_CMAKEDIR}"
        NAMESPACE arayehsaz::
        FILE arayehsaz-${type}-targets.cmake
        COMPONENT arayehsaz_Development
)

write_basic_package_version_file(
        arayehsazConfigVersion.cmake
        COMPATIBILITY SameMajorVersion
)

install(
        FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/arayehsazConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/arayehsazConfigVersion.cmake"
        DESTINATION "${ARAYEHSAZ_INSTALL_CMAKEDIR}"
        COMPONENT arayehsaz_Development
)

install(
        FILES
        ${PROJECT_SOURCE_DIR}/LICENSE
        ${PROJECT_SOURCE_DIR}/CREDITS
        ${PROJECT_SOURCE_DIR}/README.md
        ${PROJECT_SOURCE_DIR}/CODE_OF_CONDUCT.md
        ${PROJECT_SOURCE_DIR}/CHANGELOG.md
        ${PROJECT_SOURCE_DIR}/SUPPORT.md
        DESTINATION "${CMAKE_INSTALL_DOCDIR}"
)

########################################################################
# Setup project configuration file
########################################################################

# install configure file, allows third-party applications to easily import arayehsaz.
configure_file(
        ${PROJECT_SOURCE_DIR}/arayehsaz.pc.in
        arayehsaz.pc
        @ONLY
)

install(
        FILES
        ${CMAKE_BINARY_DIR}/package/arayehsaz.pc
        DESTINATION
        ${CMAKE_INSTALL_DATAROOTDIR}
)

########################################################################
# Setup uninstall procedure
########################################################################
configure_file(
        ${PROJECT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
        ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake
        IMMEDIATE
        @ONLY
)

add_custom_target(
        uninstall
        ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake
)

# TODO: add additional CPack variables here
include(CPack)
