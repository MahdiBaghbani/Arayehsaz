# CMake version.
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

# create tests for each unit test file.
set(
        files
        "unitTest_001_InitFree.c"
        "unitTest_002_ResizeMemory.c"
        "unitTest_003_Extend.c"
        "unitTest_006_Duplicate.c"
        "unitTest_007_Add.c"
        "unitTest_008_Insert.c"
        "unitTest_009_Fill.c"
        "unitTest_010_MergeArayeh.c"
        "unitTest_011_MergeArray.c"
        "unitTest_012_Get.c"
)

foreach (file ${files})

    get_filename_component(file_basename ${file} NAME_WE)

    string(REGEX REPLACE "unitTest([^$]+)" "utest\\1" testCase ${file_basename})

    add_executable(${testCase} ${file})

    target_link_libraries(${testCase} PRIVATE arayehsaz unity)

    add_test(NAME ${testCase} COMMAND ${testCase})

endforeach (file ${files})
