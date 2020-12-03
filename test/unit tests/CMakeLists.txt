# CMake version.
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# create tests for each unit test file.
set(files
        "unitTest_1_InitFree.c"
        "unitTest_2_Extend.c"
        "unitTest_3_Add.c"
        "unitTest_4_Insert.c"
        "unitTest_5_Fill.c")

foreach (file ${files})

    get_filename_component(file_basename ${file} NAME_WE)

    string(REGEX REPLACE "unitTest([^$]+)" "utest\\1" testCase ${file_basename})

    add_executable(${testCase} ${file})

    target_link_libraries(${testCase} PRIVATE arayehsaz unity)

    add_test(NAME ${testCase} COMMAND ${testCase})

endforeach ()
