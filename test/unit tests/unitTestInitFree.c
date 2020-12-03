/** test/unitTestInitFree.c
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

void test_init_free(void)
{
    // define default arayeh size.
    size_t arayehSize = 100;

    // create new arayehs.
    arayeh *typeChar   = newArayeh(AA_ARAYEH_TYPE_CHAR, arayehSize);
    arayeh *typeSInt   = newArayeh(AA_ARAYEH_TYPE_SINT, arayehSize);
    arayeh *typeInt    = newArayeh(AA_ARAYEH_TYPE_INT, arayehSize);
    arayeh *typeLInt   = newArayeh(AA_ARAYEH_TYPE_LINT, arayehSize);
    arayeh *typeFloat  = newArayeh(AA_ARAYEH_TYPE_FLOAT, arayehSize);
    arayeh *typeDouble = newArayeh(AA_ARAYEH_TYPE_DOUBLE, arayehSize);

    // test arayeh pointers aren't null.
    TEST_ASSERT_NOT_NULL(typeChar)
    TEST_ASSERT_NOT_NULL(typeSInt)
    TEST_ASSERT_NOT_NULL(typeInt)
    TEST_ASSERT_NOT_NULL(typeLInt)
    TEST_ASSERT_NOT_NULL(typeFloat)
    TEST_ASSERT_NOT_NULL(typeDouble)

    // test arayeh pointers.
    TEST_ASSERT_NOT_NULL(typeChar->_privateProperties.array.charPtr)
    TEST_ASSERT_NOT_NULL(typeSInt->_privateProperties.array.shortIntPtr)
    TEST_ASSERT_NOT_NULL(typeInt->_privateProperties.array.intPtr)
    TEST_ASSERT_NOT_NULL(typeLInt->_privateProperties.array.longIntPtr)
    TEST_ASSERT_NOT_NULL(typeFloat->_privateProperties.array.floatPtr)
    TEST_ASSERT_NOT_NULL(typeDouble->_privateProperties.array.doublePtr)

    // test map pointers.
    TEST_ASSERT_NOT_NULL(typeChar->_privateProperties.map)
    TEST_ASSERT_NOT_NULL(typeSInt->_privateProperties.map)
    TEST_ASSERT_NOT_NULL(typeInt->_privateProperties.map)
    TEST_ASSERT_NOT_NULL(typeLInt->_privateProperties.map)
    TEST_ASSERT_NOT_NULL(typeFloat->_privateProperties.map)
    TEST_ASSERT_NOT_NULL(typeDouble->_privateProperties.map)

    // test arayeh "size" attribute.
    TEST_ASSERT_EQUAL_size_t(arayehSize, typeChar->_privateProperties.size);
    TEST_ASSERT_EQUAL_size_t(arayehSize, typeSInt->_privateProperties.size);
    TEST_ASSERT_EQUAL_size_t(arayehSize, typeInt->_privateProperties.size);
    TEST_ASSERT_EQUAL_size_t(arayehSize, typeLInt->_privateProperties.size);
    TEST_ASSERT_EQUAL_size_t(arayehSize, typeFloat->_privateProperties.size);
    TEST_ASSERT_EQUAL_size_t(arayehSize, typeDouble->_privateProperties.size);

    // test arayeh "used" attribute.
    TEST_ASSERT_EQUAL_size_t(0, typeChar->_privateProperties.used);
    TEST_ASSERT_EQUAL_size_t(0, typeSInt->_privateProperties.used);
    TEST_ASSERT_EQUAL_size_t(0, typeInt->_privateProperties.used);
    TEST_ASSERT_EQUAL_size_t(0, typeLInt->_privateProperties.used);
    TEST_ASSERT_EQUAL_size_t(0, typeFloat->_privateProperties.used);
    TEST_ASSERT_EQUAL_size_t(0, typeDouble->_privateProperties.used);

    // test arayeh "next" attribute.
    TEST_ASSERT_EQUAL_size_t(0, typeChar->_privateProperties.next);
    TEST_ASSERT_EQUAL_size_t(0, typeSInt->_privateProperties.next);
    TEST_ASSERT_EQUAL_size_t(0, typeInt->_privateProperties.next);
    TEST_ASSERT_EQUAL_size_t(0, typeLInt->_privateProperties.next);
    TEST_ASSERT_EQUAL_size_t(0, typeFloat->_privateProperties.next);
    TEST_ASSERT_EQUAL_size_t(0, typeDouble->_privateProperties.next);

    // test if free returns success.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, (typeChar->freeArayeh)(&typeChar));
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, (typeSInt->freeArayeh)(&typeSInt));
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, (typeInt->freeArayeh)(&typeInt));
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, (typeLInt->freeArayeh)(&typeLInt));
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, (typeFloat->freeArayeh)(&typeFloat));
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, (typeDouble->freeArayeh)(&typeDouble));

    // test if pointers are nullified after being freed.
    TEST_ASSERT_NULL(typeChar)
    TEST_ASSERT_NULL(typeSInt)
    TEST_ASSERT_NULL(typeInt)
    TEST_ASSERT_NULL(typeLInt)
    TEST_ASSERT_NULL(typeFloat)
    TEST_ASSERT_NULL(typeDouble)
}

int main(void)
{
    UnityBegin("unitTestInitFree.c");

    RUN_TEST(test_init_free);

    return UnityEnd();
}
