/** test/unitTestAdd.c
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

#include "../include/arayeh.h"
#include "configurations.h"
#include "unity test framework/unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_add(void)
{

    // define default arayeh size.
    size_t arayehSize = 10;
    int element       = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh1D(TYPE_INT, arayehSize);

    // add element.
    (testCase->add)(testCase, &element);

    // assert element is added.
    TEST_ASSERT_EQUAL_INT(element, testCase->_internalProperties.array.pInt[0]);
    TEST_ASSERT_EQUAL_CHAR(IS_FILLED, testCase->_internalProperties.map[0]);
    TEST_ASSERT_EQUAL_INT(1, testCase->_internalProperties.next);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_add_extend(void)
{

    // define default arayeh size.
    size_t arayehSize = 1;
    int element       = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh1D(TYPE_INT, arayehSize);

    // add 2 times to extend arayeh.
    (testCase->add)(testCase, &element);
    (testCase->add)(testCase, &element);

    // assert size is increased.
    TEST_ASSERT_GREATER_THAN_INT(arayehSize, testCase->_internalProperties.size);

    // assert next pointer is pointing to 2.
    TEST_ASSERT_EQUAL_INT(2, testCase->_internalProperties.next);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

int main(void)
{
    UnityBegin("unitTestAdd.c");

    RUN_TEST(test_add);
    RUN_TEST(test_add_extend);

    return UnityEnd();
}
