/**
 * @file       include/types.h
 * @author     Mohammad Mahdi Baghbani Pourvahid
 * @date       2020-2021
 * @version    0.1.0
 * @copyright  GNU Affero General Public License.
 * @internal
 *
 * @brief      Type management header file for Arayehsaz Library.
 * @details    This header contains type specific Arayeh functions.
 */

/*
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

#ifndef __AA_A_TYPES_H__
#define __AA_A_TYPES_H__

#include "arayeh.h"

// To ensure that the names declared in this portion of code have C linkage,
// and thus C++ name mangling is not performed while using this code with C++.
#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
#    define __BEGIN_DECLS extern "C" {
#    define __END_DECLS   }
#else
#    define __BEGIN_DECLS /* empty */
#    define __END_DECLS   /* empty */
#endif

__BEGIN_DECLS

// Initialize arayeh pointer.

int _init_pointer_type_char(arayeh *self, arayeh_types *array, size_t initial_size);

int _init_pointer_type_short_int(arayeh *self, arayeh_types *array, size_t initial_size);

int _init_pointer_type_int(arayeh *self, arayeh_types *array, size_t initial_size);

int _init_pointer_type_long_int(arayeh *self, arayeh_types *array, size_t initial_size);

int _init_pointer_type_float(arayeh *self, arayeh_types *array, size_t initial_size);

int _init_pointer_type_double(arayeh *self, arayeh_types *array, size_t initial_size);

// Allocate memory for arayeh.

int _malloc_type_char(arayeh *self, arayeh_types *array, size_t initial_size);

int _malloc_type_short_int(arayeh *self, arayeh_types *array, size_t initial_size);

int _malloc_type_int(arayeh *self, arayeh_types *array, size_t initial_size);

int _malloc_type_long_int(arayeh *self, arayeh_types *array, size_t initial_size);

int _malloc_type_float(arayeh *self, arayeh_types *array, size_t initial_size);

int _malloc_type_double(arayeh *self, arayeh_types *array, size_t initial_size);

// Re-allocate memory for arayeh.

int _realloc_type_char(arayeh *self, arayeh_types *array, size_t new_size);

int _realloc_type_short_int(arayeh *self, arayeh_types *array, size_t new_size);

int _realloc_type_int(arayeh *self, arayeh_types *array, size_t new_size);

int _realloc_type_long_int(arayeh *self, arayeh_types *array, size_t new_size);

int _realloc_type_float(arayeh *self, arayeh_types *array, size_t new_size);

int _realloc_type_double(arayeh *self, arayeh_types *array, size_t new_size);

// Free arayeh memory.

void _free_type_char(arayeh *self);

void _free_type_short_int(arayeh *self);

void _free_type_int(arayeh *self);

void _free_type_long_int(arayeh *self);

void _free_type_float(arayeh *self);

void _free_type_double(arayeh *self);

// Assign the initialized pointer of an array to the arayeh structs pointer.

void _set_memory_pointer_type_char(arayeh *self, arayeh_types *array);

void _set_memory_pointer_type_short_int(arayeh *self, arayeh_types *array);

void _set_memory_pointer_type_int(arayeh *self, arayeh_types *array);

void _set_memory_pointer_type_long_int(arayeh *self, arayeh_types *array);

void _set_memory_pointer_type_float(arayeh *self, arayeh_types *array);

void _set_memory_pointer_type_double(arayeh *self, arayeh_types *array);

// Add an element of a specific type to the arayeh.

void _add_type_char(arayeh *self, size_t index, void *element);

void _add_type_short_int(arayeh *self, size_t index, void *element);

void _add_type_int(arayeh *self, size_t index, void *element);

void _add_type_long_int(arayeh *self, size_t index, void *element);

void _add_type_float(arayeh *self, size_t index, void *element);

void _add_type_double(arayeh *self, size_t index, void *element);

// Merge an arayeh of a specific type into another arayeh.

int _merge_arayeh_type_char(arayeh *self, size_t start_index, size_t step,
                            arayeh *source);

int _merge_arayeh_type_short_int(arayeh *self, size_t start_index, size_t step,
                                 arayeh *source);

int _merge_arayeh_type_int(arayeh *self, size_t start_index, size_t step, arayeh *source);

int _merge_arayeh_type_long_int(arayeh *self, size_t start_index, size_t step,
                                arayeh *source);

int _merge_arayeh_type_float(arayeh *self, size_t start_index, size_t step,
                             arayeh *source);

int _merge_arayeh_type_double(arayeh *self, size_t start_index, size_t step,
                              arayeh *source);

// Merge a C standard array of a specific type into the arayeh.

int _merge_array_type_char(arayeh *self, size_t start_index, size_t step,
                           size_t array_size, void *array);

int _merge_array_type_short_int(arayeh *self, size_t start_index, size_t step,
                                size_t array_size, void *array);

int _merge_array_type_int(arayeh *self, size_t start_index, size_t step,
                          size_t array_size, void *array);

int _merge_array_type_long_int(arayeh *self, size_t start_index, size_t step,
                               size_t array_size, void *array);

int _merge_array_type_float(arayeh *self, size_t start_index, size_t step,
                            size_t array_size, void *array);

int _merge_array_type_double(arayeh *self, size_t start_index, size_t step,
                             size_t array_size, void *array);

// Get an element from arayeh.

void _get_type_char(arayeh *self, size_t index, void *element);

void _get_type_short_int(arayeh *self, size_t index, void *element);

void _get_type_int(arayeh *self, size_t index, void *element);

void _get_type_long_int(arayeh *self, size_t index, void *element);

void _get_type_float(arayeh *self, size_t index, void *element);

void _get_type_double(arayeh *self, size_t index, void *element);

__END_DECLS

#endif    //__AA_A_TYPES_H__
