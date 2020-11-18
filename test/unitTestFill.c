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
    // This Test is here to ensure that test works as expected.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 20;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // fill all of the empty arayeh with element.
    state = (testCase->fill)(testCase, 0, 1, arayehSize, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check all slots.
    for (size_t i = 0; i < arayehSize; ++i) {
        TEST_ASSERT_EQUAL_INT(element, testCase->_privateProperties.array.pInt[i]);
        TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_ON, testCase->_privateProperties.map[i]);
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(arayehSize, testCase->_privateProperties.used);
    TEST_ASSERT_EQUAL_INT(arayehSize, testCase->_privateProperties.next);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_fill_all_empty_step_two(void)
{
    // Test filling by step 2.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 20;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // fill all of the empty arayeh with element.
    state = (testCase->fill)(testCase, 0, 2, arayehSize, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check for being filled.
    for (size_t i = 0; i < arayehSize; i += 2) {
        TEST_ASSERT_EQUAL_INT(element, testCase->_privateProperties.array.pInt[i]);
        TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_ON, testCase->_privateProperties.map[i]);
    }

    // check for being empty.
    for (size_t i = 1; i < arayehSize; i += 2) {
        TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_OFF, testCase->_privateProperties.map[i]);
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(10, testCase->_privateProperties.used);
    TEST_ASSERT_EQUAL_INT(1, testCase->_privateProperties.next);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_fill_existing_arayeh(void)
{
    // Test filling function on a filled arayeh.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 20;

    // element for filling.
    int existingElement = 1;
    int element         = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // add pre-filling arayeh with data.
    for (size_t i = 0; i < arayehSize; ++i) {
        state = (testCase->add)(testCase, &existingElement);
        // add was successful.
        TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);
    }

    // check for existing element before filling arayeh with new element.
    for (size_t i = 0; i < arayehSize; ++i) {
        TEST_ASSERT_EQUAL_INT(existingElement,
                              testCase->_privateProperties.array.pInt[i]);
    }

    // fill all of the empty arayeh with element.
    state = (testCase->fill)(testCase, 5, 1, 10, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check for being filled.
    for (size_t i = 5; i < 10; ++i) {
        TEST_ASSERT_EQUAL_INT(element, testCase->_privateProperties.array.pInt[i]);
        TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_ON, testCase->_privateProperties.map[i]);
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(arayehSize, testCase->_privateProperties.used);
    TEST_ASSERT_EQUAL_INT(arayehSize, testCase->_privateProperties.next);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_fill_extends_arayeh(void)
{
    // Test dynamic memory space extension.
    // this test is done when starting point is less than the arayeh size and
    // end index is greater than arayeh size.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 20;

    // define end index.
    size_t endIndex = 30;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // fill all of the empty arayeh with element.
    state = (testCase->fill)(testCase, 0, 1, endIndex, &element);

    // check arayeh size increased.
    TEST_ASSERT_GREATER_THAN_size_t(arayehSize, testCase->_privateProperties.size);

    // check fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check all slots.
    for (size_t i = 0; i < endIndex; ++i) {
        TEST_ASSERT_EQUAL_INT(element, testCase->_privateProperties.array.pInt[i]);
        TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_ON, testCase->_privateProperties.map[i]);
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(endIndex, testCase->_privateProperties.used);
    TEST_ASSERT_EQUAL_INT(endIndex, testCase->_privateProperties.next);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_fill_extends_arayeh_start_bigger_than_size(void)
{
    // Test dynamic memory space extension.
    // this test is done when starting point is greater than the arayeh size and
    // end index is greater than the start index. in case of end index < start index
    // and error will occur.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 20;

    // define start index and end index.
    size_t startIndex = 30;
    size_t endIndex   = 50;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // fill all of the empty arayeh with element.
    state = (testCase->fill)(testCase, startIndex, 1, endIndex, &element);

    // check arayeh size increased.
    TEST_ASSERT_GREATER_THAN_size_t(arayehSize, testCase->_privateProperties.size);

    // check fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check all slots.
    for (size_t i = startIndex; i < endIndex; ++i) {
        TEST_ASSERT_EQUAL_INT(element, testCase->_privateProperties.array.pInt[i]);
        TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_ON, testCase->_privateProperties.map[i]);
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(endIndex - startIndex, testCase->_privateProperties.used);
    TEST_ASSERT_EQUAL_INT(0, testCase->_privateProperties.next);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_fill_extends_arayeh_add_insert_off_in_settings(void)
{
    // Test dynamic memory space extension.
    // this test is to make sure that if add or insert memory extent settings are set
    // to 'off', and fill is set to 'on', the memory will be extended if needed by
    // fill function.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 20;

    // define start index and end index.
    size_t startIndex = 0;
    size_t endIndex   = 50;

    // element for filling.
    int element = 5;

    // define new settings.
    arayehSetting newSetting = {AA_ARAYEH_OFF, AA_ARAYEH_OFF, AA_ARAYEH_OFF,
                                AA_ARAYEH_ON, AA_ARAYEH_ON};

    // create new arayeh.
    arayeh *testCase = newArayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // set new settings.
    (testCase->setArayehSettings)(testCase, &newSetting);

    // fill all of the empty arayeh with element.
    state = (testCase->fill)(testCase, startIndex, 1, endIndex, &element);

    // check arayeh size increased.
    TEST_ASSERT_GREATER_THAN_size_t(arayehSize, testCase->_privateProperties.size);

    // check fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // check all slots.
    for (size_t i = startIndex; i < endIndex; ++i) {
        TEST_ASSERT_EQUAL_INT(element, testCase->_privateProperties.array.pInt[i]);
        TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_ON, testCase->_privateProperties.map[i]);
    }

    // assert "used" and "next" pointers.
    TEST_ASSERT_EQUAL_INT(endIndex - startIndex, testCase->_privateProperties.used);
    TEST_ASSERT_EQUAL_INT(50, testCase->_privateProperties.next);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_fill_new_settings_no_extend(void)
{
    // Test new settings for fill to prevent memory extension.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 20;
    // define start index and end index.
    size_t startIndex = 0;
    size_t endIndex   = 50;

    // element for filling.
    int element = 5;

    // define new settings.
    arayehSetting newSetting = {AA_ARAYEH_OFF, AA_ARAYEH_ON, AA_ARAYEH_ON,
                                AA_ARAYEH_OFF, AA_ARAYEH_ON};

    // create new arayeh.
    arayeh *testCase = newArayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // set new settings.
    (testCase->setArayehSettings)(testCase, &newSetting);

    // fill all of the empty arayeh with element.
    state = (testCase->fill)(testCase, startIndex, 1, endIndex, &element);

    // check fill was unsuccessful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_WRONG_INDEX, state);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_fill_error_bad_starting_point(void)
{
    // Test bad arguments as starting and ending points.
    // the error is because starting point will be greater than the ending point.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 20;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // fill with negative starting point.
    state = (testCase->fill)(testCase, -5, 1, 5, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_WRONG_INDEX, state);

    // fill with starting point bigger than ending point.
    state = (testCase->fill)(testCase, 10, 1, 5, &element);

    // fill was successful.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_WRONG_INDEX, state);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_fill_error_wrong_step(void)
{
    // Test wrong step size for filling.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 20;

    // element for filling.
    int element = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // fill all of the empty arayeh with element.
    state = (testCase->fill)(testCase, 0, 0, arayehSize, &element);

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
    RUN_TEST(test_fill_extends_arayeh_start_bigger_than_size);
    RUN_TEST(test_fill_extends_arayeh_add_insert_off_in_settings);
    RUN_TEST(test_fill_new_settings_no_extend);
    RUN_TEST(test_fill_error_bad_starting_point);
    RUN_TEST(test_fill_error_wrong_step);

    return UnityEnd();
}
