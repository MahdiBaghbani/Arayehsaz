# CMake version.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# add unity source directory.
add_subdirectory("unity test framework")

# create tests for each unit test file.
set(files
        unitTestInitFree.c
        unitTestExtend.c
        unitTestAdd.c
        unitTestInsert.c
        unitTestFill.c)

foreach (file ${files})

    get_filename_component(file_basename ${file} NAME_WE)

    string(REGEX REPLACE "unitTest([^$]+)" "test\\1" testCase ${file_basename})

    add_executable(${testCase} ${file})

    target_link_libraries(${testCase} PRIVATE arayehsaz unity)

    add_test(NAME ${testCase} COMMAND ${testCase})

endforeach ()
