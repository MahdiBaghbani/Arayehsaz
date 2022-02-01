/** test/unitTest_008_Insert.c
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

void test_insert(void)
{
    // Test that insert method works as expected.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 10;
    int element        = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // insert element.
    state = test_case->insert(test_case, 0, &element);

    // assert successful insertion.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // assert element is inserted in index 0.
    TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[0]);
    TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, 0));
    TEST_ASSERT_EQUAL_INT(1, private_properties->next);

    // insert element.
    state = test_case->insert(test_case, 5, &element);

    // assert successful insertion.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // assert element is inserted in index 0.
    TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[5]);
    TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, 5));
    TEST_ASSERT_EQUAL_INT(1, private_properties->next);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_default_settings_insert_extends_size(void)
{
    // Test that insert will extend memory space when the
    // index for insertion is bigger than the arayeh size
    // with default settings.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 10;
    int element        = 5;
    size_t index       = 1000000;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // insert element at index 1,000,000. arayeh should be extended to the size of 1
    // million or bigger to do this insertion.
    state = test_case->insert(test_case, index, &element);

    // assert successful insertion.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // assert arayeh size to be greater or equal to 1,000,000 and then assert the
    // element insertion.
    TEST_ASSERT_GREATER_THAN_size_t(index, private_properties->size);
    TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[index]);
    TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, index));
    TEST_ASSERT_EQUAL_INT(0, private_properties->next);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_general_size_extension_OFF(void)
{
    // Test arayeh doesn't extend its memory space
    // when general memory extension is set to OFF.
    //
    // an error code will be returned by insert function
    // when the index is not in range of 0 to (arayeh size - 1) when memory extension
    // on insert is disabled, also because the index field of insert function is of
    // type size_t, any negative number in the function call will be converted to
    // unsigned and thus result in an overflow, most of time it will be a very big
    // number that is possibly out of arayeh valid indexes range, but there is a
    // chance that conversion would result in a number inside valid range and corrupt
    // the data inside the arayeh.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 10;
    int element        = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // define new settings.
    arayeh_settings new_settings = {.debug_messages = AA_ARAYEH_OFF,
                                    .extend_size    = AA_ARAYEH_OFF};

    // set new settings.
    test_case->set_settings(test_case, &new_settings);

    // insert element in index 10 (maximum possible index is 9).
    state = test_case->insert(test_case, 10, &element);

    // assert error code.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_NOT_ENOUGH_SPACE, state);

    // ensure arayeh is not affected.
    for (size_t i = 0; i < arayeh_size; i++) {
        TEST_ASSERT_EQUAL_CHAR(0, is_arayeh_map_filled(test_case, i));
    }

    // test a negative index number.
    state = test_case->insert(test_case, -10, &element);

    // assert error code.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_NOT_ENOUGH_SPACE, state);

    // ensure arayeh is not affected.
    for (size_t i = 0; i < arayeh_size; i++) {
        TEST_ASSERT_EQUAL_CHAR(0, is_arayeh_map_filled(test_case, i));
    }

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_general_size_extension_MANUAL(void)
{
    // Test arayeh extend its memory space
    // when general memory extension is set to MANUAL
    // and arayeh will refer to method specific rules
    // for extending its memory size and the default
    // value for insert method is ON.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 10;
    int element        = 5;
    size_t index       = 1000000;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // define new settings.
    arayeh_settings new_settings = {.debug_messages = AA_ARAYEH_OFF,
                                    .extend_size    = AA_ARAYEH_MANUAL};

    // set new settings.
    test_case->set_settings(test_case, &new_settings);

    // insert element at index 1,000,000. arayeh should be extended to the size of 1
    // million or bigger to do this insertion.
    state = test_case->insert(test_case, index, &element);

    // assert successful insertion.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // assert arayeh size to be greater or equal to 1,000,000 and then assert the
    // element insertion.
    TEST_ASSERT_GREATER_THAN_size_t(index, private_properties->size);
    TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[index]);
    TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, index));
    TEST_ASSERT_EQUAL_INT(0, private_properties->next);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_general_ON_method_specific_insert_extension_OFF(void)
{
    // Test arayeh extend its memory space
    // when general extension rule is set to ON and
    // the method specific rule for insert is set to OFF
    // in settings, this means that general rule has
    // higher priority than the method specific rule.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 10;
    size_t index       = 10;
    int element        = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // define new size settings.
    arayeh_size_settings new_size_settings = {.extend_add          = AA_ARAYEH_ON,
                                              .extend_insert       = AA_ARAYEH_OFF,
                                              .extend_fill         = AA_ARAYEH_ON,
                                              .extend_merge_arayeh = AA_ARAYEH_ON,
                                              .extend_merge_array  = AA_ARAYEH_ON};

    // set new size settings.
    test_case->set_size_settings(test_case, &new_size_settings);

    // insert element in index 10 (maximum possible index is 9).
    state = test_case->insert(test_case, index, &element);

    // assert successful insertion.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // assert arayeh size to be greater or equal to 1,000,000 and then assert the
    // element insertion.
    TEST_ASSERT_GREATER_THAN_size_t(index, private_properties->size);
    TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[index]);
    TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, index));
    TEST_ASSERT_EQUAL_INT(0, private_properties->next);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_general_MANUAL_method_specific_insert_extension_OFF(void)
{
    // Test arayeh doesn't extend its memory space
    // when general extension rule is set to MANUAL and
    // the method specific rule for insert is set to OFF.
    //
    // an error code will be returned by insert function
    // when the index is not in range of 0 to (arayeh size - 1) when memory extension
    // on insert is disabled, also because the index field of insert function is of
    // type size_t, any negative number in the function call will be converted to
    // unsigned and thus result in an overflow, most of time it will be a very big
    // number that is possibly out of arayeh valid indexes range, but there is a
    // chance that conversion would result in a number inside valid range and corrupt
    // the data inside the arayeh.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 10;
    int element        = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // define new settings.
    arayeh_settings new_settings = {.debug_messages = AA_ARAYEH_OFF,
                                    .extend_size    = AA_ARAYEH_MANUAL};

    // set new settings.
    test_case->set_settings(test_case, &new_settings);

    // define new size settings.
    arayeh_size_settings new_size_settings = {.extend_add          = AA_ARAYEH_ON,
                                              .extend_insert       = AA_ARAYEH_OFF,
                                              .extend_fill         = AA_ARAYEH_ON,
                                              .extend_merge_arayeh = AA_ARAYEH_ON,
                                              .extend_merge_array  = AA_ARAYEH_ON};

    // set new size settings.
    test_case->set_size_settings(test_case, &new_size_settings);

    // insert element in index 10 (maximum possible index is 9).
    state = test_case->insert(test_case, 10, &element);

    // assert error code.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_NOT_ENOUGH_SPACE, state);

    // ensure arayeh is not affected.
    for (size_t i = 0; i < arayeh_size; i++) {
        TEST_ASSERT_EQUAL_CHAR(0, is_arayeh_map_filled(test_case, i));
    }

    // test a negative index number.
    state = test_case->insert(test_case, -10, &element);

    // assert error code.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_NOT_ENOUGH_SPACE, state);

    // ensure arayeh is not affected.
    for (size_t i = 0; i < arayeh_size; i++) {
        TEST_ASSERT_EQUAL_CHAR(0, is_arayeh_map_filled(test_case, i));
    }

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

int main(void)
{
    UnityBegin("unitTest_008_Insert.c");

    RUN_TEST(test_insert);
    RUN_TEST(test_default_settings_insert_extends_size);
    RUN_TEST(test_general_size_extension_OFF);
    RUN_TEST(test_general_size_extension_MANUAL);
    RUN_TEST(test_general_ON_method_specific_insert_extension_OFF);
    RUN_TEST(test_general_MANUAL_method_specific_insert_extension_OFF);

    return UnityEnd();
}
