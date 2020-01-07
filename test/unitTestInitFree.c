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

    // create new arrays
    arayeh *typeChar = newArayeh1D(TYPE_CHAR, 100);
    arayeh *typeSInt = newArayeh1D(TYPE_SINT, 100);
    arayeh *typeInt = newArayeh1D(TYPE_INT, 100);
    arayeh *typeLInt = newArayeh1D(TYPE_LINT, 100);
    arayeh *typeFloat = newArayeh1D(TYPE_FLOAT, 100);
    arayeh *typeDouble = newArayeh1D(TYPE_DOUBLE, 100);

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

    // freeArayeh arrays.
    (typeChar->freeArayeh)(typeChar);
    (typeSInt->freeArayeh)(typeSInt);
    (typeInt->freeArayeh)(typeInt);
    (typeLInt->freeArayeh)(typeLInt);
    (typeFloat->freeArayeh)(typeFloat);
    (typeDouble->freeArayeh)(typeDouble);
}

void test_Fill(void) {

    // create new arrays
    arayeh *typeChar = newArayeh1D(TYPE_CHAR, 10);
    arayeh *typeSInt = newArayeh1D(TYPE_SINT, 10);
    arayeh *typeInt = newArayeh1D(TYPE_INT, 10);
    arayeh *typeLInt = newArayeh1D(TYPE_LINT, 10);
    arayeh *typeFloat = newArayeh1D(TYPE_FLOAT, 10);
    arayeh *typeDouble = newArayeh1D(TYPE_DOUBLE, 10);

    // declare variables
    char varChar        = 'a';
    short int varSInt   = 12345;
    int varInt          = 123456789;
    long int varLInt    = 123456789123456789;
    float varFloat      = 12345.1234;
    double varDouble    = 123456789.123456789;

    (typeChar->fill)(typeChar, 0, 1, 10, &varChar);
    (typeSInt->fill)(typeSInt, 0, 1, 10, &varSInt);
    (typeInt->fill)(typeInt, 0, 1, 10, &varInt);
    (typeLInt->fill)(typeLInt, 0, 1, 10, &varLInt);
    (typeFloat->fill)(typeFloat, 0, 1, 10, &varFloat);
    (typeDouble->fill)(typeDouble, 0, 1, 10, &varDouble);

    // test array
    TEST_ASSERT_EQUAL(varChar, typeChar->_internalProperties.array.pChar[5]);
    TEST_ASSERT_EQUAL(varSInt, typeSInt->_internalProperties.array.pShortInt[0]);
    TEST_ASSERT_EQUAL(varInt, typeInt->_internalProperties.array.pInt[1]);
    TEST_ASSERT_EQUAL(varLInt, typeLInt->_internalProperties.array.pLongInt[2]);
    TEST_ASSERT_EQUAL(varFloat, typeFloat->_internalProperties.array.pFloat[3]);
    TEST_ASSERT_EQUAL(varDouble, typeDouble->_internalProperties.array.pDouble[4]);

    // test map
    TEST_ASSERT_EQUAL(IS_FILLED, typeChar->_internalProperties.map[5]);
    TEST_ASSERT_EQUAL(IS_FILLED, typeSInt->_internalProperties.map[7]);
    TEST_ASSERT_EQUAL(IS_FILLED, typeInt->_internalProperties.map[6]);
    TEST_ASSERT_EQUAL(IS_FILLED, typeLInt->_internalProperties.map[8]);
    TEST_ASSERT_EQUAL(IS_FILLED, typeFloat->_internalProperties.map[9]);
    TEST_ASSERT_EQUAL(IS_FILLED, typeDouble->_internalProperties.map[0]);

    // test array parameters
    TEST_ASSERT_EQUAL(10, typeChar->_internalProperties.size);
    TEST_ASSERT_EQUAL(10, typeSInt->_internalProperties.size);
    TEST_ASSERT_EQUAL(10, typeInt->_internalProperties.size);
    TEST_ASSERT_EQUAL(10, typeLInt->_internalProperties.size);
    TEST_ASSERT_EQUAL(10, typeFloat->_internalProperties.size);
    TEST_ASSERT_EQUAL(10, typeDouble->_internalProperties.size);

    TEST_ASSERT_EQUAL(10, typeChar->_internalProperties.used);
    TEST_ASSERT_EQUAL(10, typeSInt->_internalProperties.used);
    TEST_ASSERT_EQUAL(10, typeInt->_internalProperties.used);
    TEST_ASSERT_EQUAL(10, typeLInt->_internalProperties.used);
    TEST_ASSERT_EQUAL(10, typeFloat->_internalProperties.used);
    TEST_ASSERT_EQUAL(10, typeDouble->_internalProperties.used);

    TEST_ASSERT_EQUAL(10, typeChar->_internalProperties.next);
    TEST_ASSERT_EQUAL(10, typeSInt->_internalProperties.next);
    TEST_ASSERT_EQUAL(10, typeInt->_internalProperties.next);
    TEST_ASSERT_EQUAL(10, typeLInt->_internalProperties.next);
    TEST_ASSERT_EQUAL(10, typeFloat->_internalProperties.next);
    TEST_ASSERT_EQUAL(10, typeDouble->_internalProperties.next);

    // freeArayeh arrays
    (typeChar->freeArayeh)(typeChar);
    (typeSInt->freeArayeh)(typeSInt);
    (typeInt->freeArayeh)(typeInt);
    (typeLInt->freeArayeh)(typeLInt);
    (typeFloat->freeArayeh)(typeFloat);
    (typeDouble->freeArayeh)(typeDouble);
}

void test_extend(void) {

    // create new arrays
    arayeh *typeChar = newArayeh1D(TYPE_CHAR, 10);
    arayeh *typeSInt = newArayeh1D(TYPE_SINT, 10);
    arayeh *typeInt = newArayeh1D(TYPE_INT, 10);
    arayeh *typeLInt = newArayeh1D(TYPE_LINT, 10);
    arayeh *typeFloat = newArayeh1D(TYPE_FLOAT, 10);
    arayeh *typeDouble = newArayeh1D(TYPE_DOUBLE, 10);

    // declare variables
    char varChar        = 'a';
    short int varSInt   = 12345;
    int varInt          = 123456789;
    long int varLInt    = 123456789123456789;
    float varFloat      = 12345.12345;
    double varDouble    = 123456789.123456789;

    (typeChar->fill)(typeChar, 0, 1, 10, &varChar);
    (typeSInt->fill)(typeSInt, 0, 1, 10, &varSInt);
    (typeInt->fill)(typeInt, 0, 1, 10, &varInt);
    (typeLInt->fill)(typeLInt, 0, 1, 10, &varLInt);
    (typeFloat->fill)(typeFloat, 0, 1, 10, &varFloat);
    (typeDouble->fill)(typeDouble, 0, 1, 10, &varDouble);

    // freeArayeh arrays
    (typeChar->freeArayeh)(typeChar);
    (typeSInt->freeArayeh)(typeSInt);
    (typeInt->freeArayeh)(typeInt);
    (typeLInt->freeArayeh)(typeLInt);
    (typeFloat->freeArayeh)(typeFloat);
    (typeDouble->freeArayeh)(typeDouble);
}


int main(void) {
    UnityBegin("unitTestInitFree.c");

    RUN_TEST(test_Init_Free);
    RUN_TEST(test_Fill);
    RUN_TEST(test_extend);

    return UnityEnd();
}