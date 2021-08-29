/** test/unitTest_007_Add.c
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

void test_add(void)
{
    // Test that add method works as expected.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 10;
    int element        = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // add element.
    state = test_case->add(test_case, &element);

    // assert successful adding.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // assert element is added.
    TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[0]);
    TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, 0));
    TEST_ASSERT_EQUAL_INT(1, private_properties->next);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_default_settings_add_extends_size(void)
{
    // Test arayeh extends its memory space
    // when it lacks memory to add new item
    // with default settings.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 1;
    int element        = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // test adding to arayeh for large amount of additions and see how it
    // dynamically extends memory space.
    for (int i = 0; i < 100000; i++) {
        // add element to arayeh.
        state = test_case->add(test_case, &element);
        // assert successful adding.
        TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);
        // assert elements are added.
        TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[i]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, i));
    }

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

// define custom growth function.
size_t growthFactorFunction(arayeh *array)
{
    // this growth function makes space 2x, by returning
    // the array size for extending memory space.
    return array->size;
}

void test_add_extends_size_alternate_growth_function(void)
{
    // Test usage of an alternative growth function instead of default one.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 1;
    int element        = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // shorten names for god's sake.
    struct private_properties *private_properties = &test_case->_private_properties;

    // change growth factor.
    test_case->set_growth_factor(test_case, growthFactorFunction);

    // test adding to arayeh for large amount of additions and see how it
    // dynamically extends memory space.
    for (int i = 0; i < 100000; i++) {
        // add element to arayeh.
        state = test_case->add(test_case, &element);
        // assert successful adding.
        TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);
        // assert elements are added.
        TEST_ASSERT_EQUAL_INT(element, private_properties->array.int_pointer[i]);
        TEST_ASSERT_EQUAL_CHAR(1, is_arayeh_map_filled(test_case, i));
    }

    // assert final size.
    // because size starts at 1 and multiplied by 2 to expand to 100,000 the final
    // size should be 1 * 2^x >= 100,000 which results in x == 17 .
    TEST_ASSERT_EQUAL_INT((1 << 17), private_properties->size);

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
    size_t arayeh_size = 1;
    int element        = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // define new settings.
    arayeh_settings new_settings = {.debug_messages = AA_ARAYEH_OFF,
                                    .extend_size    = AA_ARAYEH_OFF};

    // set new settings.
    test_case->set_settings(test_case, &new_settings);

    // fill the only empty space.
    state = test_case->add(test_case, &element);

    // assert successful addition.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // now fill again to see if the new settings prevents arayeh from extension.
    state = test_case->add(test_case, &element);

    // assert not enough space error.
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
    // value for add method is ON.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 1;
    int element        = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // define new settings.
    arayeh_settings new_settings = {.debug_messages = AA_ARAYEH_OFF,
                                    .extend_size    = AA_ARAYEH_MANUAL};

    // set new settings.
    test_case->set_settings(test_case, &new_settings);

    // fill the only empty space.
    state = test_case->add(test_case, &element);

    // assert successful addition.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // now fill again to see if the new settings allow arayeh to extend its size.
    state = test_case->add(test_case, &element);

    // assert not enough space error.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_general_ON_method_specific_add_extension_OFF(void)
{
    // Test arayeh extend its memory space
    // when general extension rule is set to ON and
    // the method specific rule for add is set to OFF
    // in settings, this means that general rule has
    // higher priority than the method specific rule.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 1;
    int element        = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // define new size settings.
    arayeh_size_settings new_size_settings = {.extend_add          = AA_ARAYEH_OFF,
                                              .extend_insert       = AA_ARAYEH_ON,
                                              .extend_fill         = AA_ARAYEH_ON,
                                              .extend_merge_arayeh = AA_ARAYEH_ON,
                                              .extend_merge_array  = AA_ARAYEH_ON};

    // set new size settings.
    test_case->set_size_settings(test_case, &new_size_settings);

    // fill the only empty space.
    state = test_case->add(test_case, &element);

    // assert successful addition.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // now fill again to see if the new settings allow arayeh to extend its size.
    state = test_case->add(test_case, &element);

    // assert not enough space error.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_general_MANUAL_method_specific_add_extension_OFF(void)
{
    // Test arayeh doesn't extend its memory space
    // when general extension rule is set to MANUAL and
    // the method specific rule for add is set to OFF.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 1;
    int element        = 5;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // define new settings.
    arayeh_settings new_settings = {.debug_messages = AA_ARAYEH_OFF,
                                    .extend_size    = AA_ARAYEH_MANUAL};

    // set new  settings.
    test_case->set_settings(test_case, &new_settings);

    // define new size settings.
    arayeh_size_settings new_size_settings = {.extend_add          = AA_ARAYEH_OFF,
                                              .extend_insert       = AA_ARAYEH_ON,
                                              .extend_fill         = AA_ARAYEH_ON,
                                              .extend_merge_arayeh = AA_ARAYEH_ON,
                                              .extend_merge_array  = AA_ARAYEH_ON};

    // set new size settings.
    test_case->set_size_settings(test_case, &new_size_settings);

    // fill the only empty space.
    state = test_case->add(test_case, &element);

    // assert successful addition.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // now fill again to see if the new settings prevents arayeh from extending its size.
    state = test_case->add(test_case, &element);

    // assert not enough space error.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_NOT_ENOUGH_SPACE, state);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

int main(void)
{
    UnityBegin("unitTest_007_Add.c");

    RUN_TEST(test_add);
    RUN_TEST(test_default_settings_add_extends_size);
    RUN_TEST(test_add_extends_size_alternate_growth_function);
    RUN_TEST(test_general_size_extension_OFF);
    RUN_TEST(test_general_size_extension_MANUAL);
    RUN_TEST(test_general_ON_method_specific_add_extension_OFF);
    RUN_TEST(test_general_MANUAL_method_specific_add_extension_OFF);

    return UnityEnd();
}
