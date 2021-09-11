/** test/perfTest_001_CompactMap.c
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

#include <sys/time.h>

#include "../../include/arayeh.h"

void test_adding(size_t arayeh_type, size_t arayeh_size)
{
    arayeh *case_add = Arayeh(arayeh_type, arayeh_size);

    for (size_t i = 0; i < arayeh_size; i++) {
        case_add->add(case_add, &i);
    }

    case_add->free_arayeh(&case_add);
}

void test_insertion(size_t arayeh_type, size_t arayeh_size)
{
    arayeh *case_insert = Arayeh(arayeh_type, arayeh_size);

    for (size_t i = 0; i < arayeh_size; i++) {
        case_insert->insert(case_insert, arayeh_size - i - 1, &i);
    }

    case_insert->free_arayeh(&case_insert);
}

void test_filling(size_t arayeh_type, size_t arayeh_size)
{
    arayeh *case_fill = Arayeh(arayeh_type, arayeh_size);

    case_fill->fill(case_fill, 0, 1, arayeh_size, &arayeh_type);

    case_fill->free_arayeh(&case_fill);
}

void test_c_array(size_t arayeh_type, size_t arayeh_size)
{
    int *array = (int *) malloc(arayeh_size * sizeof *array);

    for (size_t i = 0; i < arayeh_size; i++) {
        *(array + i) = (int) i;
    }

    free(array);
}

void chronometer(void (*test)(size_t, size_t), size_t arayeh_type, size_t arayeh_size,
                 char *test_module, char *test_name)
{
    struct timeval t0, t1;
    gettimeofday(&t0, NULL);
    test(arayeh_type, arayeh_size);
    gettimeofday(&t1, NULL);
    printf("%s Performance Test: %s\n", test_module, test_name);
    printf("Did %zu calls in %.2g seconds\n\n", arayeh_size,
           t1.tv_sec - t0.tv_sec + 1E-6 * (t1.tv_usec - t0.tv_usec));
}

int main(void)
{
    size_t arayeh_type = AA_ARAYEH_TYPE_INT;
    size_t arayeh_size = 2000000000;
    char *test_module  = "Compact Map";

    chronometer(test_adding, arayeh_type, arayeh_size, test_module, "adding");

    chronometer(test_insertion, arayeh_type, arayeh_size, test_module, "insertion");

    chronometer(test_filling, arayeh_type, arayeh_size, test_module, "filling");

    chronometer(test_c_array, arayeh_type,arayeh_size, test_module, "C array");

    return 0;
}
