/* test/UnitTestInitFree.c
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

#include "unity test framework/unity.h"
#include "../source/arayeh.h"
#include "../source/configurations.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_Init_Free(void) {

    // define default array size.
    size_t arayehSize = 100;

    // create new arrays.
    arayeh *typeChar = newArayeh1D(TYPE_CHAR, arayehSize);
    arayeh *typeSInt = newArayeh1D(TYPE_SINT, arayehSize);
    arayeh *typeInt = newArayeh1D(TYPE_INT, arayehSize);
    arayeh *typeLInt = newArayeh1D(TYPE_LINT, arayehSize);
    arayeh *typeFloat = newArayeh1D(TYPE_FLOAT, arayehSize);
    arayeh *typeDouble = newArayeh1D(TYPE_DOUBLE, arayehSize);

    // test created arayeh pointers.
    TEST_ASSERT_FALSE(typeChar == NULL)
    TEST_ASSERT_FALSE(typeSInt == NULL)
    TEST_ASSERT_FALSE(typeInt == NULL)
    TEST_ASSERT_FALSE(typeLInt == NULL)
    TEST_ASSERT_FALSE(typeFloat == NULL)
    TEST_ASSERT_FALSE(typeDouble == NULL)

    // test array pointers.
    TEST_ASSERT_FALSE(typeChar->_internalProperties.array.pChar == NULL)
    TEST_ASSERT_FALSE(typeSInt->_internalProperties.array.pShortInt == NULL)
    TEST_ASSERT_FALSE(typeInt->_internalProperties.array.pInt == NULL)
    TEST_ASSERT_FALSE(typeLInt->_internalProperties.array.pLongInt == NULL)
    TEST_ASSERT_FALSE(typeFloat->_internalProperties.array.pFloat == NULL)
    TEST_ASSERT_FALSE(typeDouble->_internalProperties.array.pDouble == NULL)

    // test map pointers.
    TEST_ASSERT_FALSE(typeChar->_internalProperties.map == NULL)
    TEST_ASSERT_FALSE(typeSInt->_internalProperties.map == NULL)
    TEST_ASSERT_FALSE(typeInt->_internalProperties.map == NULL)
    TEST_ASSERT_FALSE(typeLInt->_internalProperties.map == NULL)
    TEST_ASSERT_FALSE(typeFloat->_internalProperties.map == NULL)
    TEST_ASSERT_FALSE(typeDouble->_internalProperties.map == NULL)

    // test arayeh "size" attribute.
    TEST_ASSERT_EQUAL_size_t(arayehSize,typeChar->_internalProperties.size);
    TEST_ASSERT_EQUAL_size_t(arayehSize,typeSInt->_internalProperties.size);
    TEST_ASSERT_EQUAL_size_t(arayehSize,typeInt->_internalProperties.size);
    TEST_ASSERT_EQUAL_size_t(arayehSize,typeLInt->_internalProperties.size);
    TEST_ASSERT_EQUAL_size_t(arayehSize,typeFloat->_internalProperties.size);
    TEST_ASSERT_EQUAL_size_t(arayehSize,typeDouble->_internalProperties.size);

    // test arayeh "used" attribute.
    TEST_ASSERT_EQUAL_size_t(0,typeChar->_internalProperties.used);
    TEST_ASSERT_EQUAL_size_t(0,typeSInt->_internalProperties.used);
    TEST_ASSERT_EQUAL_size_t(0,typeInt->_internalProperties.used);
    TEST_ASSERT_EQUAL_size_t(0,typeLInt->_internalProperties.used);
    TEST_ASSERT_EQUAL_size_t(0,typeFloat->_internalProperties.used);
    TEST_ASSERT_EQUAL_size_t(0,typeDouble->_internalProperties.used);

    // test arayeh "next" attribute.
    TEST_ASSERT_EQUAL_size_t(0,typeChar->_internalProperties.next);
    TEST_ASSERT_EQUAL_size_t(0,typeSInt->_internalProperties.next);
    TEST_ASSERT_EQUAL_size_t(0,typeInt->_internalProperties.next);
    TEST_ASSERT_EQUAL_size_t(0,typeLInt->_internalProperties.next);
    TEST_ASSERT_EQUAL_size_t(0,typeFloat->_internalProperties.next);
    TEST_ASSERT_EQUAL_size_t(0,typeDouble->_internalProperties.next);

    // free arrays.
    (typeChar->freeArayeh)(typeChar);
    (typeSInt->freeArayeh)(typeSInt);
    (typeInt->freeArayeh)(typeInt);
    (typeLInt->freeArayeh)(typeLInt);
    (typeFloat->freeArayeh)(typeFloat);
    (typeDouble->freeArayeh)(typeDouble);

    typeChar = NULL;
    typeSInt = NULL;

}

int main(void) {
    UnityBegin("unitTestInitFree.c");

    RUN_TEST(test_Init_Free);

    return UnityEnd();
}
