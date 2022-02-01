/** test/unitTest_009_Fill.c
 *
 * This file is a part of:
 * Azadeh Afzar - Arayehsaz (AA-A).
 *
 * Copyright (C) 2020 - 2022 Azadeh Afzar.
 * Copyright (C) 2020 - 2022 Mohammad Mahdi Baghbani Pourvahid.
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

void test_fill_all_empty_step_one(void)
{
    // Test that fill method works as expected.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t start       = 0;
    size_t step        = 1;
    size_t arayeh_size = 20;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // fill all of the empty arayeh with element.
    state = test_case->fill(test_case, start, step, arayeh_size, &element);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check all slots.
    for (size_t i = start; i < arayeh_size; i += step) {
        TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[i]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, i));
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(arayeh_size, private_properties->used);
    TEST_ASSERT_EQUAL_INT(arayeh_size, private_properties->next);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_fill_all_empty_step_two(void)
{
    // Test filling by step 2.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t start       = 0;
    size_t step        = 2;
    size_t arayeh_size = 20;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // fill all of the empty arayeh with element.
    state = test_case->fill(test_case, start, step, arayeh_size, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check for being filled.
    for (size_t i = start; i < arayeh_size; i += step) {
        TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[i]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, i));
    }

    // check for being empty.
    for (size_t i = start + 1; i < arayeh_size; i += step) {
        TEST_ASSERT_EQUAL_CHAR(0, is_arayeh_map_filled(test_case, i));
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(10, private_properties->used);
    TEST_ASSERT_EQUAL_INT(1, private_properties->next);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_fill_existing_arayeh(void)
{
    // Test filling method on an already filled arayeh.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 20;

    // element for filling.
    int existingElement = 1;
    int element         = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // fill arayeh with data.
    for (size_t i = 0; i < arayeh_size; ++i) {
        state = test_case->add(test_case, &existingElement);
        // add was successful.
        TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);
    }

    // check for existing element before filling arayeh with new element.
    for (size_t i = 0; i < arayeh_size; ++i) {
        TEST_ASSERT_EQUAL_INT(existingElement, private_properties->array.int_pointer[i]);
    }

    // fill all of the empty arayeh with element.
    state = test_case->fill(test_case, 5, 1, 10, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check for being filled.
    for (size_t i = 5; i < 10; ++i) {
        TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[i]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, i));
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(arayeh_size, private_properties->used);
    TEST_ASSERT_EQUAL_INT(arayeh_size, private_properties->next);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_default_settings_fill_extends_size(void)
{
    // Test fill method dynamic memory space extension with default settings.
    // starting point is within arayeh size but the end index is big
    // enough to force arayeh to extend its memory space.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 20;

    // define end index.
    size_t end_index = 30;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // fill all of the empty arayeh with element.
    state = test_case->fill(test_case, 0, 1, end_index, &element);

    // check arayeh size increased.
    TEST_ASSERT_GREATER_THAN_size_t(arayeh_size, private_properties->size);

    // check fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check all slots.
    for (size_t i = 0; i < end_index; ++i) {
        TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[i]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, i));
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(end_index, private_properties->used);
    TEST_ASSERT_EQUAL_INT(end_index, private_properties->next);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_default_settings_fill_extends_size_start_bigger_than_size(void)
{
    // Test when starting point is greater than the arayeh size and
    // end index is greater than the start index, arayeh will extend
    // its memory size. in case of end index < start index
    // and error will occur.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 20;

    // define start index and end index.
    size_t start_index = 30;
    size_t end_index   = 50;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // fill all of the empty arayeh with element.
    state = test_case->fill(test_case, start_index, 1, end_index, &element);

    // check arayeh size increased.
    TEST_ASSERT_GREATER_THAN_size_t(arayeh_size, private_properties->size);

    // check fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check all slots.
    for (size_t i = start_index; i < end_index; ++i) {
        TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[i]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, i));
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(end_index - start_index, private_properties->used);
    TEST_ASSERT_EQUAL_INT(0, private_properties->next);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_general_size_extension_OFF(void)
{
    // Test arayeh doesn't extend its memory space
    // when general memory extension is set to OFF.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 20;
    // define start index and end index.
    size_t start_index = 0;
    size_t end_index   = 50;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // define new settings.
    arayeh_settings new_settings = {.debug_messages = AA_ARAYEH_OFF,
                                    .extend_size    = AA_ARAYEH_OFF};

    // set new settings.
    test_case->set_settings(test_case, &new_settings);

    // fill all of the empty arayeh with element.
    state = test_case->fill(test_case, start_index, 1, end_index, &element);

    // check fill was unsuccessful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_NOT_ENOUGH_SPACE, state);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_general_size_extension_MANUAL(void)
{
    // Test arayeh extend its memory space
    // when general memory extension is set to MANUAL
    // and arayeh will refer to method specific rules
    // for extending its memory size and the default
    // value for fill method is ON.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 20;

    // define end index.
    size_t end_index = 30;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // define new settings.
    arayeh_settings new_settings = {.debug_messages = AA_ARAYEH_OFF,
                                    .extend_size    = AA_ARAYEH_MANUAL};

    // set new settings.
    test_case->set_settings(test_case, &new_settings);

    // fill all of the empty arayeh with element.
    state = test_case->fill(test_case, 0, 1, end_index, &element);

    // check arayeh size increased.
    TEST_ASSERT_GREATER_THAN_size_t(arayeh_size, private_properties->size);

    // check fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check all slots.
    for (size_t i = 0; i < end_index; ++i) {
        TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[i]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, i));
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(end_index, private_properties->used);
    TEST_ASSERT_EQUAL_INT(end_index, private_properties->next);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_general_ON_method_specific_fill_extension_OFF(void)
{
    // Test arayeh extend its memory space
    // when general extension rule is set to ON and
    // the method specific rule for fill is set to OFF
    // in settings, this means that general rule has
    // higher priority than the method specific rule.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 20;

    // define end index.
    size_t end_index = 30;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // define new size settings.
    arayeh_size_settings new_size_settings = {.extend_add          = AA_ARAYEH_ON,
                                              .extend_insert       = AA_ARAYEH_ON,
                                              .extend_fill         = AA_ARAYEH_OFF,
                                              .extend_merge_arayeh = AA_ARAYEH_ON,
                                              .extend_merge_array  = AA_ARAYEH_ON};

    // set new size settings.
    test_case->set_size_settings(test_case, &new_size_settings);

    // fill all of the empty arayeh with element.
    state = test_case->fill(test_case, 0, 1, end_index, &element);

    // check arayeh size increased.
    TEST_ASSERT_GREATER_THAN_size_t(arayeh_size, private_properties->size);

    // check fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check all slots.
    for (size_t i = 0; i < end_index; ++i) {
        TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[i]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, i));
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(end_index, private_properties->used);
    TEST_ASSERT_EQUAL_INT(end_index, private_properties->next);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_general_MANUAL_method_specific_fill_extension_OFF(void)
{
    // Test arayeh doesn't extend its memory space
    // when general extension rule is set to MANUAL and
    // the method specific rule for fill is set to OFF.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 20;
    // define start index and end index.
    size_t start_index = 0;
    size_t end_index   = 50;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // define new settings.
    arayeh_settings new_settings = {.debug_messages = AA_ARAYEH_OFF,
                                    .extend_size    = AA_ARAYEH_MANUAL};

    // set new settings.
    test_case->set_settings(test_case, &new_settings);

    // define new size settings.
    arayeh_size_settings new_size_settings = {.extend_add          = AA_ARAYEH_ON,
                                              .extend_insert       = AA_ARAYEH_ON,
                                              .extend_fill         = AA_ARAYEH_OFF,
                                              .extend_merge_arayeh = AA_ARAYEH_ON,
                                              .extend_merge_array  = AA_ARAYEH_ON};

    // set new size settings.
    test_case->set_size_settings(test_case, &new_size_settings);

    // fill all of the empty arayeh with element.
    state = test_case->fill(test_case, start_index, 1, end_index, &element);

    // check fill was unsuccessful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_NOT_ENOUGH_SPACE, state);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_general_size_extension_MANUAL_add_insert_OFF_fill_ON(void)
{
    // Test that if add or insert memory extent settings
    // are set to 'off', and fill is set to 'on', the memory
    // will be extended if needed by fill function.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 20;

    // define start index and end index.
    size_t start_index = 0;
    size_t end_index   = 50;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // define new settings.
    arayeh_settings new_settings = {.debug_messages = AA_ARAYEH_OFF,
                                    .extend_size    = AA_ARAYEH_MANUAL};

    // set new settings.
    test_case->set_settings(test_case, &new_settings);

    // define new size settings.
    arayeh_size_settings new_size_settings = {.extend_add          = AA_ARAYEH_OFF,
                                              .extend_insert       = AA_ARAYEH_OFF,
                                              .extend_fill         = AA_ARAYEH_ON,
                                              .extend_merge_arayeh = AA_ARAYEH_ON,
                                              .extend_merge_array  = AA_ARAYEH_ON};

    // set new size settings.
    test_case->set_size_settings(test_case, &new_size_settings);

    // fill all of the empty arayeh with element.
    state = test_case->fill(test_case, start_index, 1, end_index, &element);

    // check arayeh size increased.
    TEST_ASSERT_GREATER_THAN_size_t(arayeh_size, private_properties->size);

    // check fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check all slots.
    for (size_t i = start_index; i < end_index; ++i) {
        TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[i]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, i));
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(end_index - start_index, private_properties->used);
    TEST_ASSERT_EQUAL_INT(50, private_properties->next);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_fill_error_bad_starting_point(void)
{
    // Test bad arguments as starting and ending points.
    // the error is because starting point will be greater than the ending point.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 20;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // fill with negative starting point.
    state = test_case->fill(test_case, -5, 1, 5, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_WRONG_INDEX, state);

    // fill with starting point bigger than ending point.
    state = test_case->fill(test_case, 10, 1, 5, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_WRONG_INDEX, state);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_fill_error_wrong_step(void)
{
    // Test wrong step size for filling.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 20;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // fill all of the empty arayeh with element.
    state = test_case->fill(test_case, 0, 0, arayeh_size, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_WRONG_STEP, state);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

int main(void)
{
    UnityBegin("unitTest_009_Fill.c");

    RUN_TEST(test_fill_all_empty_step_one);
    RUN_TEST(test_fill_all_empty_step_two);
    RUN_TEST(test_fill_existing_arayeh);
    RUN_TEST(test_default_settings_fill_extends_size);
    RUN_TEST(test_default_settings_fill_extends_size_start_bigger_than_size);
    RUN_TEST(test_general_size_extension_OFF);
    RUN_TEST(test_general_size_extension_MANUAL);
    RUN_TEST(test_general_ON_method_specific_fill_extension_OFF);
    RUN_TEST(test_general_MANUAL_method_specific_fill_extension_OFF);
    RUN_TEST(test_general_size_extension_MANUAL_add_insert_OFF_fill_ON);
    RUN_TEST(test_fill_error_bad_starting_point);
    RUN_TEST(test_fill_error_wrong_step);

    return UnityEnd();
}
