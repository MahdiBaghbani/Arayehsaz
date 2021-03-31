/** include/methods.h
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

#ifndef __AA_A_METHODS_H__
#define __AA_A_METHODS_H__

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

// this function will reallocate memory to the array and its map.
int _resize_memory(arayeh *self, size_t new_size);

// this function will reallocate memory to the array and its map.
// the reallocation with this function increases size of the arayeh.
int _extend_size(arayeh *self, size_t extend_size);

// this function will free the array and reset its parameters.
int _free_memory(arayeh **self);

// this function will create an exact copy of "self" arayeh.
arayeh *_duplicate_arayeh(arayeh *self);

// this function will insert an "element" into array at
// index = self->_private_properties.next.
int _add_to_arayeh(arayeh *self, void *element);

// this function will insert an "element" into array at "index".
int _insert_to_arayeh(arayeh *self, size_t index, void *element);

// this function will fill array with an element from index (inclusive)
// "start_index" to index (exclusive) "end_index" with step size "step".
int _fill_arayeh(arayeh *self, size_t start_index, size_t step, size_t end_index,
                 void *element);

// this function will merge an arayeh (source) into current arayeh (self), with
// specified step from the specified start index of (self) arayeh.
int _merge_from_arayeh(arayeh *self, size_t start_index, size_t step, arayeh *source);

// this function will merge a default C array
// (for example int a[4] = {1, 2, 3, 4};) into the arayeh with step, the starting
// index for merging is "start_index" and the size of C array and step determines
// the last index (in the example above the size of C arayeh is 4 with step 1).
int _merge_from_array(arayeh *self, size_t start_index, size_t step, size_t array_size,
                      void *array);

// this function copies data in "index" cell of the array to the "destination" memory
// location.
int _get_from_arayeh(arayeh *self, size_t index, void *destination);

// this function will override arayeh default settings with new one.
void _set_settings(arayeh *self, arayeh_settings *new_settings);

// this function will override arayeh extend size default settings with new one.
void _set_size_settings(arayeh *self, arayeh_size_settings *new_settings);

// this function will override the arayehs default growth factor function
// with a new function provided by user.
void _set_growth_factor(arayeh *self, size_t (*growth_factor)(arayeh *));

__END_DECLS

#endif    //__AA_A_METHODS_H__
