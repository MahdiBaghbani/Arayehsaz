# CMake version.
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

# only build docs for release builds.
if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
    # build the documents only in release builds.

    # check if Doxygen is installed.
    find_package(Doxygen)

    # build.
    if (DOXYGEN_FOUND)
        # set input and output files.
        set(
                DOXYGEN_IN
                ${PROJECT_SOURCE_DIR}/document/Doxyfile.in
        )
        set(
                DOXYGEN_OUT
                ${CMAKE_BINARY_DIR}/document/Doxyfile
        )
        # request to configure the file.
        configure_file(
                ${DOXYGEN_IN}
                ${DOXYGEN_OUT}
                @ONLY
        )

        # note the option ALL which allows to build the docs together with the application.
        message("Doxygen build started")
        add_custom_target(
                document
                ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                COMMENT "Generating API documentation with Doxygen."
                VERBATIM
        )
    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation.")
    endif (DOXYGEN_FOUND)
endif (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
