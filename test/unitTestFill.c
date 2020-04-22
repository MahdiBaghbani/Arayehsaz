/** test/unitTestFill.c
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
#include "unity test framework/unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_fill_all_empty_step_one(void)
{

    // define default arayeh size.
    size_t arayehSize = 20;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(TYPE_INT, arayehSize);

    // fill all of the empty arayeh with element.
    int state = (testCase->fill)(testCase, 0, 1, arayehSize, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check all slots.
    for (size_t i = 0; i < arayehSize; ++i) {
        TEST_ASSERT_EQUAL_INT(element, testCase->_internalProperties.array.pInt[i]);
        TEST_ASSERT_EQUAL_CHAR(IS_FILLED, testCase->_internalProperties.map[i]);
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(arayehSize, testCase->_internalProperties.used);
    TEST_ASSERT_EQUAL_INT(arayehSize, testCase->_internalProperties.next);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_fill_all_empty_step_two(void)
{

    // define default arayeh size.
    size_t arayehSize = 20;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(TYPE_INT, arayehSize);

    // fill all of the empty arayeh with element.
    int state = (testCase->fill)(testCase, 0, 2, arayehSize, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check for being filled.
    for (size_t i = 0; i < arayehSize; i += 2) {
        TEST_ASSERT_EQUAL_INT(element, testCase->_internalProperties.array.pInt[i]);
        TEST_ASSERT_EQUAL_CHAR(IS_FILLED, testCase->_internalProperties.map[i]);
    }

    // check for being empty.
    for (size_t i = 1; i < arayehSize; i += 2) {
        TEST_ASSERT_EQUAL_CHAR(IS_EMPTY, testCase->_internalProperties.map[i]);
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(10, testCase->_internalProperties.used);
    TEST_ASSERT_EQUAL_INT(1, testCase->_internalProperties.next);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_fill_existing_arayeh(void)
{

    // define default arayeh size.
    size_t arayehSize = 20;

    // element for filling.
    int existingElement = 1;
    int element         = 5;
    int state;

    // create new arayeh.
    arayeh *testCase = newArayeh(TYPE_INT, arayehSize);

    // add pre-filling arayeh with data.
    for (size_t i = 0; i < arayehSize; ++i) {
        state = (testCase->add)(testCase, &existingElement);
        // add was successful.
        TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);
    }

    // check for existing element before filling arayeh with new element.
    for (size_t i = 0; i < arayehSize; ++i) {
        TEST_ASSERT_EQUAL_INT(existingElement,
                              testCase->_internalProperties.array.pInt[i]);
    }

    // fill all of the empty arayeh with element.
    state = (testCase->fill)(testCase, 5, 1, 10, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check for being filled.
    for (size_t i = 5; i < 10; ++i) {
        TEST_ASSERT_EQUAL_INT(element, testCase->_internalProperties.array.pInt[i]);
        TEST_ASSERT_EQUAL_CHAR(IS_FILLED, testCase->_internalProperties.map[i]);
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(arayehSize, testCase->_internalProperties.used);
    TEST_ASSERT_EQUAL_INT(arayehSize, testCase->_internalProperties.next);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_fill_extends_arayeh(void)
{

    // define default arayeh size.
    size_t arayehSize = 20;
    size_t fillSize   = 30;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(TYPE_INT, arayehSize);

    // fill all of the empty arayeh with element.
    int state = (testCase->fill)(testCase, 0, 1, fillSize, &element);

    // check arayeh size increased.
    TEST_ASSERT_GREATER_THAN_size_t(arayehSize, testCase->_internalProperties.size);

    // check fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check all slots.
    for (size_t i = 0; i < fillSize; ++i) {
        TEST_ASSERT_EQUAL_INT(element, testCase->_internalProperties.array.pInt[i]);
        TEST_ASSERT_EQUAL_CHAR(IS_FILLED, testCase->_internalProperties.map[i]);
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(fillSize, testCase->_internalProperties.used);
    TEST_ASSERT_EQUAL_INT(fillSize, testCase->_internalProperties.next);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_error_bad_starting_point(void)
{

    // define default arayeh size.
    size_t arayehSize = 20;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(TYPE_INT, arayehSize);

    // fill all of the empty arayeh with element.
    int state = (testCase->fill)(testCase, -5, 1, arayehSize, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_WRONG_INDEX, state);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_error_starting_point_bigger_than_size(void)
{

    // define default arayeh size.
    size_t arayehSize = 20;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(TYPE_INT, arayehSize);

    // fill all of the empty arayeh with element.
    int state = (testCase->fill)(testCase, 21, 1, arayehSize, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_WRONG_INDEX, state);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_error_wrong_step(void)
{

    // define default arayeh size.
    size_t arayehSize = 20;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(TYPE_INT, arayehSize);

    // fill all of the empty arayeh with element.
    int state = (testCase->fill)(testCase, 0, 0, arayehSize, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_WRONG_STEP, state);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

int main(void)
{
    UnityBegin("unitTestFill.c");

    RUN_TEST(test_fill_all_empty_step_one);
    RUN_TEST(test_fill_all_empty_step_two);
    RUN_TEST(test_fill_existing_arayeh);
    RUN_TEST(test_fill_extends_arayeh);
    RUN_TEST(test_error_bad_starting_point);
    RUN_TEST(test_error_starting_point_bigger_than_size);
    RUN_TEST(test_error_wrong_step);

    return UnityEnd();
}
