/** test/unitTest_010_merge_arayeh.c
 *
 * This file is a part of:
 * Azadeh Afzar - Arayehsaz (AA-A).
 *
 * Copyright (C) 2020 - 2021 Azadeh Afzar.
 * Copyright (C) 2020 - 2021 Mohammad Mahdi Baghbani Pourvahid.
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
#include "../../include/functions.h"
#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_merge_arayeh_empty_arayeh_step_1(void)
{
    // Test that merge array method works as expected with step 1.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 5;
    size_t start_index = 0;
    size_t step        = 1;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *source    = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // merge array into source.
    state = source->merge_array(source, 0, 1, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // merge source arayeh into test case arayeh.
    state = test_case->merge_arayeh(test_case, start_index, step, source);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    for (size_t index = start_index; index < arayeh_size; index += step) {
        // assert array is successfully merged into arayeh.
        TEST_ASSERT_EQUAL_INT(cArray[index],
                              private_properties->array.int_pointer[index]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_cell_filled(test_case, index));
    }

    // assert arayeh properties.
    TEST_ASSERT_EQUAL_INT(5, private_properties->next);
    TEST_ASSERT_EQUAL_INT(5, private_properties->used);
    TEST_ASSERT_EQUAL_INT(arayeh_size, private_properties->size);

    // free arayeh.
    source->free_arayeh(&source);
    test_case->free_arayeh(&test_case);
}

void test_merge_arayeh_empty_arayeh_step_5(void)
{
    // Test that merge array method works as expected with step 5.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 21;
    size_t start_index = 0;
    size_t step        = 5;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *source    = Arayeh(AA_ARAYEH_TYPE_INT, 5);
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // merge array into source.
    state = source->merge_array(source, 0, 1, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // merge array.
    state = test_case->merge_arayeh(test_case, start_index, step, source);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    for (size_t arayeh_index = start_index, c_array_index = 0; arayeh_index < arayeh_size;
         arayeh_index += step, c_array_index++) {
        // assert array is successfully merged into arayeh.
        TEST_ASSERT_EQUAL_INT(cArray[c_array_index],
                              private_properties->array.int_pointer[arayeh_index]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_cell_filled(test_case, arayeh_index));
    }

    for (size_t index = start_index; index < arayeh_size; index++) {
        if (index % 5 != 0) {
            // assert that arayeh is empty in this cells.
            TEST_ASSERT_EQUAL_CHAR(0, is_arayeh_cell_filled(test_case, index));
        }
    }

    // assert arayeh properties.
    TEST_ASSERT_EQUAL_INT(1, private_properties->next);
    TEST_ASSERT_EQUAL_INT(5, private_properties->used);
    TEST_ASSERT_EQUAL_INT(arayeh_size, private_properties->size);

    // free arayeh.
    source->free_arayeh(&source);
    test_case->free_arayeh(&test_case);
}

void test_default_settings_merge_arayeh_extends_size(void)
{
    // Test merge array method dynamic memory space extension with default settings.
    // starting point is within arayeh size but the array size to be merged is big
    // enough to force arayeh to extend its memory space.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 5;
    size_t start_index = 4;
    size_t step        = 1;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *source    = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // merge array into source.
    state = source->merge_array(source, 0, 1, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // merge array.
    state = test_case->merge_arayeh(test_case, start_index, step, source);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    for (size_t arayeh_index = start_index, c_array_index = 0;
         arayeh_index < private_properties->size; arayeh_index += step, c_array_index++) {
        // assert array is successfully merged into arayeh.
        TEST_ASSERT_EQUAL_INT(cArray[c_array_index],
                              private_properties->array.int_pointer[arayeh_index]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_cell_filled(test_case, arayeh_index));
    }

    // assert arayeh properties.
    TEST_ASSERT_EQUAL_INT(0, private_properties->next);
    TEST_ASSERT_EQUAL_INT(5, private_properties->used);
    TEST_ASSERT_EQUAL_INT(9, private_properties->size);

    // free arayeh.
    source->free_arayeh(&source);
    test_case->free_arayeh(&test_case);
}

void test_default_settings_merge_arayeh_extends_size_start_bigger_than_size(void)
{
    // Test merge array method dynamic memory space extension with default settings.
    // starting point is within arayeh size but the array size to be merged is big
    // enough to force arayeh to extend its memory space.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 5;
    size_t start_index = 8;
    size_t step        = 1;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *source    = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // merge array into source.
    state = source->merge_array(source, 0, 1, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // merge array.
    state = test_case->merge_arayeh(test_case, start_index, step, source);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    for (size_t arayeh_index = start_index, c_array_index = 0;
         arayeh_index < private_properties->size; arayeh_index += step, c_array_index++) {
        // assert array is successfully merged into arayeh.
        TEST_ASSERT_EQUAL_INT(cArray[c_array_index],
                              private_properties->array.int_pointer[arayeh_index]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_cell_filled(test_case, arayeh_index));
    }

    // assert arayeh properties.
    TEST_ASSERT_EQUAL_INT(0, private_properties->next);
    TEST_ASSERT_EQUAL_INT(5, private_properties->used);
    TEST_ASSERT_EQUAL_INT(13, private_properties->size);

    // free arayeh.
    source->free_arayeh(&source);
    test_case->free_arayeh(&test_case);
}

void test_general_size_extension_OFF(void)
{
    // Test arayeh doesn't extend its memory space
    // when general memory extension is set to OFF.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 5;
    size_t start_index = 4;
    size_t step        = 1;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *source    = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // merge array into source.
    state = source->merge_array(source, 0, 1, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // define new settings.
    arayeh_settings new_settings = {.debug_messages = AA_ARAYEH_OFF,
                                    .extend_size    = AA_ARAYEH_OFF};

    // set new settings.
    test_case->set_settings(test_case, &new_settings);

    // merge array.
    state = test_case->merge_arayeh(test_case, start_index, step, source);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_NOT_ENOUGH_SPACE, state);

    // free arayeh.
    source->free_arayeh(&source);
    test_case->free_arayeh(&test_case);
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
    size_t arayeh_size = 5;
    size_t start_index = 4;
    size_t step        = 1;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *source    = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // merge array into source.
    state = source->merge_array(source, 0, 1, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // define new settings.
    arayeh_settings new_settings = {.debug_messages = AA_ARAYEH_OFF,
                                    .extend_size    = AA_ARAYEH_MANUAL};

    // set new settings.
    test_case->set_settings(test_case, &new_settings);

    // merge array.
    state = test_case->merge_arayeh(test_case, start_index, step, source);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    for (size_t arayeh_index = start_index, c_array_index = 0;
         arayeh_index < private_properties->size; arayeh_index += step, c_array_index++) {
        // assert array is successfully merged into arayeh.
        TEST_ASSERT_EQUAL_INT(cArray[c_array_index],
                              private_properties->array.int_pointer[arayeh_index]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_cell_filled(test_case, arayeh_index));
    }

    // assert arayeh properties.
    TEST_ASSERT_EQUAL_INT(0, private_properties->next);
    TEST_ASSERT_EQUAL_INT(5, private_properties->used);
    TEST_ASSERT_EQUAL_INT(9, private_properties->size);

    // free arayeh.
    source->free_arayeh(&source);
    test_case->free_arayeh(&test_case);
}

void test_general_ON_method_specific_merge_arayeh_extension_OFF(void)
{
    // Test arayeh extend its memory space
    // when general extension rule is set to ON and
    // the method specific rule for merge array is set to OFF
    // in settings, this means that general rule has
    // higher priority than the method specific rule.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 5;
    size_t start_index = 4;
    size_t step        = 1;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *source    = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // merge array into source.
    state = source->merge_array(source, 0, 1, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // define new size settings.
    arayeh_size_settings new_size_settings = {.extend_add          = AA_ARAYEH_ON,
                                              .extend_insert       = AA_ARAYEH_ON,
                                              .extend_fill         = AA_ARAYEH_ON,
                                              .extend_merge_arayeh = AA_ARAYEH_OFF,
                                              .extend_merge_array  = AA_ARAYEH_ON};

    // set new size settings.
    test_case->set_size_settings(test_case, &new_size_settings);

    // merge array.
    state = test_case->merge_arayeh(test_case, start_index, step, source);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    for (size_t arayeh_index = start_index, c_array_index = 0;
         arayeh_index < private_properties->size; arayeh_index += step, c_array_index++) {
        // assert array is successfully merged into arayeh.
        TEST_ASSERT_EQUAL_INT(cArray[c_array_index],
                              private_properties->array.int_pointer[arayeh_index]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_cell_filled(test_case, arayeh_index));
    }

    // assert arayeh properties.
    TEST_ASSERT_EQUAL_INT(0, private_properties->next);
    TEST_ASSERT_EQUAL_INT(5, private_properties->used);
    TEST_ASSERT_EQUAL_INT(9, private_properties->size);

    // free arayeh.
    source->free_arayeh(&source);
    test_case->free_arayeh(&test_case);
}

void test_general_MANUAL_method_specific_merge_arayeh_extension_OFF(void)
{
    // Test arayeh doesn't extend its memory space
    // when general extension rule is set to MANUAL and
    // the method specific rule for fill is set to OFF.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 5;
    size_t start_index = 4;
    size_t step        = 1;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *source    = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // merge array into source.
    state = source->merge_array(source, 0, 1, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // define new settings.
    arayeh_settings new_settings = {.debug_messages = AA_ARAYEH_OFF,
                                    .extend_size    = AA_ARAYEH_MANUAL};

    // set new settings.
    test_case->set_settings(test_case, &new_settings);

    // define new size settings.
    arayeh_size_settings new_size_settings = {.extend_add          = AA_ARAYEH_ON,
                                              .extend_insert       = AA_ARAYEH_ON,
                                              .extend_fill         = AA_ARAYEH_ON,
                                              .extend_merge_arayeh = AA_ARAYEH_OFF,
                                              .extend_merge_array  = AA_ARAYEH_ON};

    // set new size settings.
    test_case->set_size_settings(test_case, &new_size_settings);

    // merge array.
    state = test_case->merge_arayeh(test_case, start_index, step, source);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_NOT_ENOUGH_SPACE, state);

    // free arayeh.
    source->free_arayeh(&source);
    test_case->free_arayeh(&test_case);
}

void test_merge_error_bad_starting_point(void)
{
    // Test bad numbers for starting point.
    // negative starting points would result in a very big starting
    // points once converted to size_t and will result in an overflow.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 5;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *source    = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // merge array into source.
    state = source->merge_array(source, 0, 1, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // merge array.
    state = test_case->merge_arayeh(test_case, -5, 1, source);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_OVERFLOW, state);

    // free arayeh.
    source->free_arayeh(&source);
    test_case->free_arayeh(&test_case);
}

void test_merge_arayeh_error_wrong_step(void)
{
    // Test wrong step size for merging.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 5;

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // create new arayeh.
    arayeh *source    = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // merge array into source.
    state = source->merge_array(source, 0, 1, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // merge array.
    state = test_case->merge_arayeh(test_case, 0, 0, source);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_WRONG_STEP, state);

    // merge array.
    state = test_case->merge_array(test_case, 0, -5, 5, &cArray);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_OVERFLOW, state);

    // free arayeh.
    source->free_arayeh(&source);
    test_case->free_arayeh(&test_case);
}

int main(void)
{
    UnityBegin("unitTest_010_MergeArayeh.c");

    RUN_TEST(test_merge_arayeh_empty_arayeh_step_1);
    RUN_TEST(test_merge_arayeh_empty_arayeh_step_5);
    RUN_TEST(test_default_settings_merge_arayeh_extends_size);
    RUN_TEST(test_default_settings_merge_arayeh_extends_size_start_bigger_than_size);
    RUN_TEST(test_general_size_extension_OFF);
    RUN_TEST(test_general_size_extension_MANUAL);
    RUN_TEST(test_general_ON_method_specific_merge_arayeh_extension_OFF);
    RUN_TEST(test_general_MANUAL_method_specific_merge_arayeh_extension_OFF);
    RUN_TEST(test_merge_error_bad_starting_point);
    RUN_TEST(test_merge_arayeh_error_wrong_step);

    return UnityEnd();
}
