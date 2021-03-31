/** test/unitTest_006_Duplicate.c
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
#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_get(void)
{
    // Test that insert method works as expected.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 5;
    size_t start_index = 0;
    size_t step        = 1;
    int element;

    // create new arayeh.
    arayeh *source_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // define a c array with size 5.
    int c_generic_array[5] = {1, 0, 6, 4, 7};

    // merge array.
    state = source_case->merge_array(source_case, start_index, step, 5, &c_generic_array);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // duplicate arayeh.
    arayeh *duplicate_case = source_case->duplicate(source_case);

    // shorten names.
    struct private_properties *source_private_properties =
        &source_case->_private_properties;
    struct private_properties *duplicate_private_properties =
        &duplicate_case->_private_properties;

    // get elements from arayeh.
    for (size_t index = start_index; index < arayeh_size; index += step) {
        duplicate_case->get(duplicate_case, index, &element);
        TEST_ASSERT_EQUAL_INT(c_generic_array[index], element);
    }

    // check for same properties.
    TEST_ASSERT_EQUAL_INT(source_private_properties->next,
                          duplicate_private_properties->next);
    TEST_ASSERT_EQUAL_INT(source_private_properties->used,
                          duplicate_private_properties->used);
    TEST_ASSERT_EQUAL_INT(source_private_properties->size,
                          duplicate_private_properties->size);

    // check for same settings.
    TEST_ASSERT_EQUAL_CHAR(source_private_properties->settings->debug_messages,
                           duplicate_private_properties->settings->debug_messages);
    TEST_ASSERT_EQUAL_CHAR(source_private_properties->settings->extend_size,
                           duplicate_private_properties->settings->extend_size);

    // check for same size settings.
    TEST_ASSERT_EQUAL_CHAR(
        source_private_properties->settings->method_size->extend_add,
        duplicate_private_properties->settings->method_size->extend_add);
    TEST_ASSERT_EQUAL_CHAR(
        source_private_properties->settings->method_size->extend_insert,
        duplicate_private_properties->settings->method_size->extend_insert);
    TEST_ASSERT_EQUAL_CHAR(
        source_private_properties->settings->method_size->extend_fill,
        duplicate_private_properties->settings->method_size->extend_fill);
    TEST_ASSERT_EQUAL_CHAR(
        source_private_properties->settings->method_size->extend_merge_arayeh,
        duplicate_private_properties->settings->method_size->extend_merge_arayeh);
    TEST_ASSERT_EQUAL_CHAR(
        source_private_properties->settings->method_size->extend_merge_array,
        duplicate_private_properties->settings->method_size->extend_merge_array);
    // free arayeh.
    source_case->free_arayeh(&source_case);
    duplicate_case->free_arayeh(&duplicate_case);
}

int main(void)
{
    UnityBegin("unitTest_006_Duplicate.c");

    RUN_TEST(test_get);

    return UnityEnd();
}
