/** test/unitTest_006_Duplicate.c
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
    size_t arayehSize = 5;
    size_t startIndex = 0;
    size_t step       = 1;
    int element;

    // create new arayeh.
    arayeh *sourceCase = Arayeh(AA_ARAYEH_TYPE_INT, arayehSize);

    // define a c array with size 5.
    int cArray[5] = {1, 0, 6, 4, 7};

    // merge array.
    state = sourceCase->mergeArray(sourceCase, startIndex, step, 5, &cArray);

    // assert successful merge.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, state);

    // duplicate arayeh.
    arayeh *duplicateCase = sourceCase->duplicate(sourceCase);

    // shorten names.
    struct privateProperties *sPrivateProperties = &sourceCase->_privateProperties;
    struct privateProperties *dPrivateProperties = &duplicateCase->_privateProperties;

    // get elements from arayeh.
    for (size_t index = startIndex; index < arayehSize; index += step) {
        duplicateCase->get(duplicateCase, index, &element);
        TEST_ASSERT_EQUAL_INT(cArray[index], element);
    }

    // check for same properties.
    TEST_ASSERT_EQUAL_INT(sPrivateProperties->next, dPrivateProperties->next);
    TEST_ASSERT_EQUAL_INT(sPrivateProperties->used, dPrivateProperties->used);
    TEST_ASSERT_EQUAL_INT(sPrivateProperties->size, dPrivateProperties->size);

    // check for same settings.
    TEST_ASSERT_EQUAL_CHAR(sPrivateProperties->settings->debugMessages,
                           dPrivateProperties->settings->debugMessages);
    TEST_ASSERT_EQUAL_CHAR(sPrivateProperties->settings->extendSize,
                           dPrivateProperties->settings->extendSize);

    // check for same size settings.
    TEST_ASSERT_EQUAL_CHAR(sPrivateProperties->settings->methodSize->extendAdd,
                           dPrivateProperties->settings->methodSize->extendAdd);
    TEST_ASSERT_EQUAL_CHAR(sPrivateProperties->settings->methodSize->extendInsert,
                           dPrivateProperties->settings->methodSize->extendInsert);
    TEST_ASSERT_EQUAL_CHAR(sPrivateProperties->settings->methodSize->extendFill,
                           dPrivateProperties->settings->methodSize->extendFill);
    TEST_ASSERT_EQUAL_CHAR(sPrivateProperties->settings->methodSize->extendMergeArayeh,
                           dPrivateProperties->settings->methodSize->extendMergeArayeh);
    TEST_ASSERT_EQUAL_CHAR(sPrivateProperties->settings->methodSize->extendMergeArray,
                           dPrivateProperties->settings->methodSize->extendMergeArray);
    // free arayeh.
    sourceCase->freeArayeh(&sourceCase);
    duplicateCase->freeArayeh(&duplicateCase);
}

int main(void)
{
    UnityBegin("unitTest_006_Duplicate.c");

    RUN_TEST(test_get);

    return UnityEnd();
}
