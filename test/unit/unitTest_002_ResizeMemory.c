/** test/unitTest_002_ResizeMemory.c
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
#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_increase_size(void)
{
    // Test increasing arayeh size when resizing.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 20;
    size_t new_size    = 34;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // test current size.
    TEST_ASSERT_EQUAL_INT(arayeh_size, test_case->_private_properties.size);

    // increase size.
    state = test_case->resize_memory(test_case, new_size);

    // assert successful extension.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // test new size.
    TEST_ASSERT_EQUAL_INT(new_size, test_case->_private_properties.size);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

void test_decrease_size(void)
{
    // Test decreasing arayeh size when resizing.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayeh_size = 50;
    size_t new_size    = 34;

    // create new arayeh.
    arayeh *test_case = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);

    // test current size.
    TEST_ASSERT_EQUAL_INT(arayeh_size, test_case->_private_properties.size);

    // decrease size.
    state = test_case->resize_memory(test_case, new_size);

    // assert successful extension.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // test new size.
    TEST_ASSERT_EQUAL_INT(new_size, test_case->_private_properties.size);

    // free arayeh.
    test_case->free_arayeh(&test_case);
}

int main(void)
{
    UnityBegin("unitTest_002_ResizeMemory.c");

    RUN_TEST(test_increase_size);
    RUN_TEST(test_decrease_size);

    return UnityEnd();
}
