/** test/unitTest_011_mergeArray.c
 *
 * This file is a part of:
 * Azadeh Afzar - Arayehsaz (AA-A).
 *
 * Copyright (C) 2020 Mohammad Mahdi Baghbani Pourvahid.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgement in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "../../include/arayeh.h"
#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_merge_array_empty_arayeh_step_1(void)
{
    // Test that merge array method works as expected with step 1.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 5;
    size_t startIndex = 0;
    size_t step       = 1;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *testCase = Arayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // shorten names for god's sake.
    struct privateProperties *privateProperties = &testCase->_privateProperties;

    // merge array.
    state = testCase->mergeArray(testCase, startIndex, step, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    for (size_t index = startIndex; index < arayehSize; index += step) {
        // assert array is successfully merged into arayeh.
        TEST_ASSERT_EQUAL_INT(cArray[index], privateProperties->array.intPtr[index]);
        TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_ON, privateProperties->map[index]);
    }

    // assert arayeh properties.
    TEST_ASSERT_EQUAL_INT(5, privateProperties->next);
    TEST_ASSERT_EQUAL_INT(5, privateProperties->used);
    TEST_ASSERT_EQUAL_INT(arayehSize, privateProperties->size);

    // free arayeh.
    testCase->freeArayeh(&testCase);
}

void test_merge_array_empty_arayeh_step_5(void)
{
    // Test that merge array method works as expected with step 5.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 21;
    size_t startIndex = 0;
    size_t step       = 5;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *testCase = Arayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // shorten names for god's sake.
    struct privateProperties *privateProperties = &testCase->_privateProperties;

    // merge array.
    state = testCase->mergeArray(testCase, startIndex, step, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    for (size_t aIndex = startIndex, cIndex = 0; aIndex < arayehSize;
         aIndex += step, cIndex++) {
        // assert array is successfully merged into arayeh.
        TEST_ASSERT_EQUAL_INT(cArray[cIndex], privateProperties->array.intPtr[aIndex]);
        TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_ON, privateProperties->map[aIndex]);
    }

    for (size_t index = startIndex; index < arayehSize; index++) {
        if (index % 5 != 0) {
            // assert that arayeh is empty in this cells.
            TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_OFF, privateProperties->map[index]);
        }
    }

    // assert arayeh properties.
    TEST_ASSERT_EQUAL_INT(1, privateProperties->next);
    TEST_ASSERT_EQUAL_INT(5, privateProperties->used);
    TEST_ASSERT_EQUAL_INT(arayehSize, privateProperties->size);

    // free arayeh.
    testCase->freeArayeh(&testCase);
}

void test_default_settings_merge_array_extends_size(void)
{
    // Test merge array method dynamic memory space extension with default settings.
    // starting point is within arayeh size but the array size to be merged is big
    // enough to force arayeh to extend its memory space.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 5;
    size_t startIndex = 4;
    size_t step       = 1;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *testCase = Arayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // shorten names for god's sake.
    struct privateProperties *privateProperties = &testCase->_privateProperties;

    // merge array.
    state = testCase->mergeArray(testCase, startIndex, step, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    for (size_t aIndex = startIndex, cIndex = 0; aIndex < privateProperties->size;
         aIndex += step, cIndex++) {
        // assert array is successfully merged into arayeh.
        TEST_ASSERT_EQUAL_INT(cArray[cIndex], privateProperties->array.intPtr[aIndex]);
        TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_ON, privateProperties->map[aIndex]);
    }

    // assert arayeh properties.
    TEST_ASSERT_EQUAL_INT(0, privateProperties->next);
    TEST_ASSERT_EQUAL_INT(5, privateProperties->used);
    TEST_ASSERT_EQUAL_INT(9, privateProperties->size);

    // free arayeh.
    testCase->freeArayeh(&testCase);
}

void test_default_settings_merge_array_extends_size_start_bigger_than_size(void)
{
    // Test merge array method dynamic memory space extension with default settings.
    // starting point is within arayeh size but the array size to be merged is big
    // enough to force arayeh to extend its memory space.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 5;
    size_t startIndex = 8;
    size_t step       = 1;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *testCase = Arayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // shorten names for god's sake.
    struct privateProperties *privateProperties = &testCase->_privateProperties;

    // merge array.
    state = testCase->mergeArray(testCase, startIndex, step, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    for (size_t aIndex = startIndex, cIndex = 0; aIndex < privateProperties->size;
         aIndex += step, cIndex++) {
        // assert array is successfully merged into arayeh.
        TEST_ASSERT_EQUAL_INT(cArray[cIndex], privateProperties->array.intPtr[aIndex]);
        TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_ON, privateProperties->map[aIndex]);
    }

    // assert arayeh properties.
    TEST_ASSERT_EQUAL_INT(0, privateProperties->next);
    TEST_ASSERT_EQUAL_INT(5, privateProperties->used);
    TEST_ASSERT_EQUAL_INT(13, privateProperties->size);

    // free arayeh.
    testCase->freeArayeh(&testCase);
}

void test_general_size_extension_OFF(void)
{
    // Test arayeh doesn't extend its memory space
    // when general memory extension is set to OFF.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 5;
    size_t startIndex = 4;
    size_t step       = 1;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *testCase = Arayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // define new settings.
    arayehSettings newSetting = {.debugMessages = AA_ARAYEH_OFF,
                                 .extendSize    = AA_ARAYEH_OFF};

    // set new settings.
    testCase->setSettings(testCase, &newSetting);

    // merge array.
    state = testCase->mergeArray(testCase, startIndex, step, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_NOT_ENOUGH_SPACE, state);

    // free arayeh.
    testCase->freeArayeh(&testCase);
}

void test_general_size_extension_MANUAL(void)
{
    // Test arayeh extend its memory space
    // when general memory extension is set to MANUAL
    // and arayeh will refer to method specific rules
    // for extending its memory size and the default
    // value for merge array method is ON.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 5;
    size_t startIndex = 4;
    size_t step       = 1;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *testCase = Arayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // shorten names for god's sake.
    struct privateProperties *privateProperties = &testCase->_privateProperties;

    // define new settings.
    arayehSettings newSetting = {.debugMessages = AA_ARAYEH_OFF,
                                 .extendSize    = AA_ARAYEH_MANUAL};

    // set new settings.
    testCase->setSettings(testCase, &newSetting);

    // merge array.
    state = testCase->mergeArray(testCase, startIndex, step, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    for (size_t aIndex = startIndex, cIndex = 0; aIndex < privateProperties->size;
         aIndex += step, cIndex++) {
        // assert array is successfully merged into arayeh.
        TEST_ASSERT_EQUAL_INT(cArray[cIndex], privateProperties->array.intPtr[aIndex]);
        TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_ON, privateProperties->map[aIndex]);
    }

    // assert arayeh properties.
    TEST_ASSERT_EQUAL_INT(0, privateProperties->next);
    TEST_ASSERT_EQUAL_INT(5, privateProperties->used);
    TEST_ASSERT_EQUAL_INT(9, privateProperties->size);

    // free arayeh.
    testCase->freeArayeh(&testCase);
}

void test_general_ON_method_specific_merge_array_extension_OFF(void)
{
    // Test arayeh extend its memory space
    // when general extension rule is set to ON and
    // the method specific rule for merge array is set to OFF
    // in settings, this means that general rule has
    // higher priority than the method specific rule.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 5;
    size_t startIndex = 4;
    size_t step       = 1;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *testCase = Arayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // shorten names for god's sake.
    struct privateProperties *privateProperties = &testCase->_privateProperties;

    // define new size settings.
    arayehSizeSettings newSizeSettings = {.extendAdd         = AA_ARAYEH_ON,
                                          .extendInsert      = AA_ARAYEH_ON,
                                          .extendFill        = AA_ARAYEH_ON,
                                          .extendMergeArayeh = AA_ARAYEH_ON,
                                          .extendMergeArray  = AA_ARAYEH_OFF};

    // set new size settings.
    testCase->setSizeSettings(testCase, &newSizeSettings);

    // merge array.
    state = testCase->mergeArray(testCase, startIndex, step, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    for (size_t aIndex = startIndex, cIndex = 0; aIndex < privateProperties->size;
         aIndex += step, cIndex++) {
        // assert array is successfully merged into arayeh.
        TEST_ASSERT_EQUAL_INT(cArray[cIndex], privateProperties->array.intPtr[aIndex]);
        TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_ON, privateProperties->map[aIndex]);
    }

    // assert arayeh properties.
    TEST_ASSERT_EQUAL_INT(0, privateProperties->next);
    TEST_ASSERT_EQUAL_INT(5, privateProperties->used);
    TEST_ASSERT_EQUAL_INT(9, privateProperties->size);

    // free arayeh.
    testCase->freeArayeh(&testCase);
}

void test_general_MANUAL_method_specific_merge_array_extension_OFF(void)
{
    // Test arayeh doesn't extend its memory space
    // when general extension rule is set to MANUAL and
    // the method specific rule for fill is set to OFF.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 5;
    size_t startIndex = 4;
    size_t step       = 1;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *testCase = Arayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // define new settings.
    arayehSettings newSetting = {.debugMessages = AA_ARAYEH_OFF,
                                 .extendSize    = AA_ARAYEH_MANUAL};

    // set new settings.
    testCase->setSettings(testCase, &newSetting);

    // define new size settings.
    arayehSizeSettings newSizeSettings = {.extendAdd         = AA_ARAYEH_ON,
                                          .extendInsert      = AA_ARAYEH_ON,
                                          .extendFill        = AA_ARAYEH_ON,
                                          .extendMergeArayeh = AA_ARAYEH_ON,
                                          .extendMergeArray  = AA_ARAYEH_OFF};

    // set new size settings.
    testCase->setSizeSettings(testCase, &newSizeSettings);

    // merge array.
    state = testCase->mergeArray(testCase, startIndex, step, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_NOT_ENOUGH_SPACE, state);

    // free arayeh.
    testCase->freeArayeh(&testCase);
}

void test_merge_error_bad_starting_point(void)
{
    // Test bad numbers for starting point.
    // negative starting points would result in a very big starting
    // points once converted to size_t and will result in an overflow.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 5;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *testCase = Arayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // merge array.
    state = testCase->mergeArray(testCase, -5, 1, 5, &cArray);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_OVERFLOW, state);

    // free arayeh.
    testCase->freeArayeh(&testCase);
}

void test_merge_array_error_wrong_step(void)
{
    // Test wrong step size for merging.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 5;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *testCase = Arayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // merge array.
    state = testCase->mergeArray(testCase, 0, 0, 5, &cArray);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_WRONG_STEP, state);

    // merge array.
    state = testCase->mergeArray(testCase, 0, -5, 5, &cArray);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_OVERFLOW, state);

    // free arayeh.
    testCase->freeArayeh(&testCase);
}

int main(void)
{
    UnityBegin("unitTest_011_MergeArray.c");

    RUN_TEST(test_merge_array_empty_arayeh_step_1);
    RUN_TEST(test_merge_array_empty_arayeh_step_5);
    RUN_TEST(test_default_settings_merge_array_extends_size);
    RUN_TEST(test_default_settings_merge_array_extends_size_start_bigger_than_size);
    RUN_TEST(test_general_size_extension_OFF);
    RUN_TEST(test_general_size_extension_MANUAL);
    RUN_TEST(test_general_ON_method_specific_merge_array_extension_OFF);
    RUN_TEST(test_general_MANUAL_method_specific_merge_array_extension_OFF);
    RUN_TEST(test_merge_error_bad_starting_point);
    RUN_TEST(test_merge_array_error_wrong_step);

    return UnityEnd();
}
