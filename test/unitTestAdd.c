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
#include "unity test framework/unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_add(void)
{
    // This Test is here to ensure that test works as expected.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 10;
    int element       = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // add element.
    state = (testCase->add)(testCase, &element);

    // assert successful adding.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // assert element is added.
    TEST_ASSERT_EQUAL_INT(element, testCase->_internalProperties.array.pInt[0]);
    TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_ON, testCase->_internalProperties.map[0]);
    TEST_ASSERT_EQUAL_INT(1, testCase->_internalProperties.next);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_add_extend(void)
{
    // Ensure arayeh extends its memory space
    // when it lacks memory to add new item.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 1;
    int element       = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // test adding to arayeh for large amount of additions and see how it
    // dynamically extends memory space.
    for (int i = 0; i < 100000; i++) {
        // add element to arayeh.
        state = (testCase->add)(testCase, &element);
        // assert successful adding.
        TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);
        // assert elements are added.
        TEST_ASSERT_EQUAL_INT(element, testCase->_internalProperties.array.pInt[i]);
        TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_ON, testCase->_internalProperties.map[i]);
    }

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

// define custom growth function.
size_t growthFactorFunction(arayeh *array)
{
    // this growth function makes space 2x, by returning
    // the array size for extending memory space.
    return array->_internalProperties.size;
}

void test_add_extend_alternate_growth_function(void)
{
    // Testing using of an alternative growth function instead of default one.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 1;
    int element       = 5;

    // create new arayeh.
    arayeh *testCase = newArayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // change growth factor.
    (testCase->setGrowthFactorFunction)(testCase, growthFactorFunction);

    // test adding to arayeh for large amount of additions and see how it
    // dynamically extends memory space.
    for (int i = 0; i < 100000; i++) {
        // add element to arayeh.
        state = (testCase->add)(testCase, &element);
        // assert successful adding.
        TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);
        // assert elements are added.
        TEST_ASSERT_EQUAL_INT(element, testCase->_internalProperties.array.pInt[i]);
        TEST_ASSERT_EQUAL_CHAR(AA_ARAYEH_ON, testCase->_internalProperties.map[i]);
    }

    // assert final size.
    // because size starts at 1 and multiplied by 2 to expand to 100,000 the final
    // size should be 1 * 2^x >= 100,000 which results in x == 17 .
    TEST_ASSERT_EQUAL_INT((1 << 17), testCase->_internalProperties.size);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

void test_add_setting_extension_off(void)
{
    // Ensure arayeh doesn't extend its memory space
    // when the memory extension on add is disabled in settings.

    // define error state variable.
    int state;

    // define default arayeh size.
    size_t arayehSize = 1;
    int element       = 5;

    // define new settings.
    arayehSetting newSetting = {AA_ARAYEH_OFF, AA_ARAYEH_OFF, AA_ARAYEH_ON,
                                AA_ARAYEH_ON, AA_ARAYEH_ON};

    // create new arayeh.
    arayeh *testCase = newArayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // set new settings.
    (testCase->setArayehSettings)(testCase, &newSetting);

    // fill the only empty space.
    state = (testCase->add)(testCase, &element);

    // assert successful addition.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // now fill again to see if the new settings prevents arayeh from extension.
    state = (testCase->add)(testCase, &element);

    // assert not enough space error.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_NOT_ENOUGH_SPACE, state);

    // free arayeh.
    (testCase->freeArayeh)(&testCase);
}

int main(void)
{
    UnityBegin("unitTestAdd.c");

    RUN_TEST(test_add);
    RUN_TEST(test_add_extend);
    RUN_TEST(test_add_extend_alternate_growth_function);
    RUN_TEST(test_add_setting_extension_off);

    return UnityEnd();
}
