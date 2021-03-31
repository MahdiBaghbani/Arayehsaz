/** test/unitTest_001_InitFree.c
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

void test_init_free(void)
{

    // define default arayeh size.
    size_t arayeh_size = 100;

    // create new arayehs.
    arayeh *type_char      = Arayeh(AA_ARAYEH_TYPE_CHAR, arayeh_size);
    arayeh *type_short_int = Arayeh(AA_ARAYEH_TYPE_SINT, arayeh_size);
    arayeh *type_int       = Arayeh(AA_ARAYEH_TYPE_INT, arayeh_size);
    arayeh *type_long_int  = Arayeh(AA_ARAYEH_TYPE_LINT, arayeh_size);
    arayeh *type_float     = Arayeh(AA_ARAYEH_TYPE_FLOAT, arayeh_size);
    arayeh *type_double    = Arayeh(AA_ARAYEH_TYPE_DOUBLE, arayeh_size);

    // test arayeh pointers aren't null.
    TEST_ASSERT_NOT_NULL(type_char)
    TEST_ASSERT_NOT_NULL(type_short_int)
    TEST_ASSERT_NOT_NULL(type_int)
    TEST_ASSERT_NOT_NULL(type_long_int)
    TEST_ASSERT_NOT_NULL(type_float)
    TEST_ASSERT_NOT_NULL(type_double)

    // test arayeh pointers.
    TEST_ASSERT_NOT_NULL(type_char->_private_properties.array.char_pointer)
    TEST_ASSERT_NOT_NULL(type_short_int->_private_properties.array.short_int_pointer)
    TEST_ASSERT_NOT_NULL(type_int->_private_properties.array.int_pointer)
    TEST_ASSERT_NOT_NULL(type_long_int->_private_properties.array.long_int_pointer)
    TEST_ASSERT_NOT_NULL(type_float->_private_properties.array.float_pointer)
    TEST_ASSERT_NOT_NULL(type_double->_private_properties.array.double_pointer)

    // test map pointers.
    TEST_ASSERT_NOT_NULL(type_char->_private_properties.map)
    TEST_ASSERT_NOT_NULL(type_short_int->_private_properties.map)
    TEST_ASSERT_NOT_NULL(type_int->_private_properties.map)
    TEST_ASSERT_NOT_NULL(type_long_int->_private_properties.map)
    TEST_ASSERT_NOT_NULL(type_float->_private_properties.map)
    TEST_ASSERT_NOT_NULL(type_double->_private_properties.map)

    // test arayeh "size" attribute.
    TEST_ASSERT_EQUAL_size_t(arayeh_size, type_char->_private_properties.size);
    TEST_ASSERT_EQUAL_size_t(arayeh_size, type_short_int->_private_properties.size);
    TEST_ASSERT_EQUAL_size_t(arayeh_size, type_int->_private_properties.size);
    TEST_ASSERT_EQUAL_size_t(arayeh_size, type_long_int->_private_properties.size);
    TEST_ASSERT_EQUAL_size_t(arayeh_size, type_float->_private_properties.size);
    TEST_ASSERT_EQUAL_size_t(arayeh_size, type_double->_private_properties.size);

    // test arayeh "used" attribute.
    TEST_ASSERT_EQUAL_size_t(0, type_char->_private_properties.used);
    TEST_ASSERT_EQUAL_size_t(0, type_short_int->_private_properties.used);
    TEST_ASSERT_EQUAL_size_t(0, type_int->_private_properties.used);
    TEST_ASSERT_EQUAL_size_t(0, type_long_int->_private_properties.used);
    TEST_ASSERT_EQUAL_size_t(0, type_float->_private_properties.used);
    TEST_ASSERT_EQUAL_size_t(0, type_double->_private_properties.used);

    // test arayeh "next" attribute.
    TEST_ASSERT_EQUAL_size_t(0, type_char->_private_properties.next);
    TEST_ASSERT_EQUAL_size_t(0, type_short_int->_private_properties.next);
    TEST_ASSERT_EQUAL_size_t(0, type_int->_private_properties.next);
    TEST_ASSERT_EQUAL_size_t(0, type_long_int->_private_properties.next);
    TEST_ASSERT_EQUAL_size_t(0, type_float->_private_properties.next);
    TEST_ASSERT_EQUAL_size_t(0, type_double->_private_properties.next);

    // test if free returns success.
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, type_char->free_arayeh(&type_char));
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS,
                          type_short_int->free_arayeh(&type_short_int));
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, type_int->free_arayeh(&type_int));
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, type_long_int->free_arayeh(&type_long_int));
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, type_float->free_arayeh(&type_float));
    TEST_ASSERT_EQUAL_INT(AA_ARAYEH_SUCCESS, type_double->free_arayeh(&type_double));

    // test if pointers are nullified after being freed.
    TEST_ASSERT_NULL(type_char)
    TEST_ASSERT_NULL(type_short_int)
    TEST_ASSERT_NULL(type_int)
    TEST_ASSERT_NULL(type_long_int)
    TEST_ASSERT_NULL(type_float)
    TEST_ASSERT_NULL(type_double)
}

int main(void)
{
    UnityBegin("unitTest_001_InitFree.c");

    RUN_TEST(test_init_free);

    return UnityEnd();
}
