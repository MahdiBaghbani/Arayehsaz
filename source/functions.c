/** source/functions.c
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

#include "../include/functions.h"

#include "../include/algorithms.h"
#include "../include/fatal.h"
#include "../include/methods.h"
#include "../include/types.h"

int auto_extend_memory(arayeh *self)
{
    /*
     * This function will calculate the extension size of memory and extends arayeh
     * size.
     *
     * ARGUMENTS:
     * self             pointer to the arayeh object.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in configuration.h .
     *
     */

    // shorten names for god's sake.
    struct private_methods *private_methods = &self->_private_methods;

    // track error state in the function.
    int state;

    // calculate the extension memory size using growth factor function.
    size_t extension_size = private_methods->growth_factor(self);

    // extend arayeh size.
    state = self->extend_size(self, extension_size);

    // return error state.
    return state;
}

void set_public_methods(arayeh *self)
{
    /*
     * This function assigns pointers to public functions of an arayeh instance.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     *
     * RETURN:
     * no return, it's void dude.
     *
     */

    self->resize_memory     = _resize_memory;
    self->extend_size       = _extend_size;
    self->free_arayeh       = _free_memory;
    self->duplicate         = _duplicate_arayeh;
    self->add               = _add_to_arayeh;
    self->insert            = _insert_to_arayeh;
    self->fill              = _fill_arayeh;
    self->merge_arayeh      = _merge_from_arayeh;
    self->merge_array       = _merge_from_array;
    self->get               = _get_from_arayeh;
    self->set_settings      = _set_settings;
    self->set_size_settings = _set_size_settings;
    self->set_growth_factor = _set_growth_factor;
}

void set_private_methods(arayeh *self, size_t type)
{
    /*
     * This function assigns pointers to private functions of an arayeh instance.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * type         type of arayeh elements.
     *
     * RETURN:
     * no return, it's void dude.
     *
     */

    // shorten names for god's sake.
    struct private_methods *private_methods = &self->_private_methods;

    // set memory space growth factor function to default.
    private_methods->growth_factor = growth_factor_python;

    // assign based on the arayeh type.
    switch (type) {
    case AA_ARAYEH_TYPE_CHAR:
        private_methods->init_arayeh        = _init_pointer_type_char;
        private_methods->malloc_arayeh      = _malloc_type_char;
        private_methods->realloc_arayeh     = _realloc_type_char;
        private_methods->free_arayeh        = _free_type_char;
        private_methods->set_memory_pointer = _set_memory_pointer_type_char;
        private_methods->add_to_arayeh      = _add_type_char;
        private_methods->merge_from_arayeh  = _merge_arayeh_type_char;
        private_methods->merge_from_array   = _merge_array_type_char;
        private_methods->get_from_arayeh    = _get_type_char;
        break;

    case AA_ARAYEH_TYPE_SINT:
        private_methods->init_arayeh        = _init_pointer_type_short_int;
        private_methods->malloc_arayeh      = _malloc_type_short_int;
        private_methods->realloc_arayeh     = _realloc_type_short_int;
        private_methods->free_arayeh        = _free_type_short_int;
        private_methods->set_memory_pointer = _set_memory_pointer_type_short_int;
        private_methods->add_to_arayeh      = _add_type_short_int;
        private_methods->merge_from_arayeh  = _merge_arayeh_type_short_int;
        private_methods->merge_from_array   = _merge_array_type_short_int;
        private_methods->get_from_arayeh    = _get_type_short_int;
        break;

    case AA_ARAYEH_TYPE_INT:
        private_methods->init_arayeh        = _init_pointer_type_int;
        private_methods->malloc_arayeh      = _malloc_type_int;
        private_methods->realloc_arayeh     = _realloc_type_int;
        private_methods->free_arayeh        = _free_type_int;
        private_methods->set_memory_pointer = _set_memory_pointer_type_int;
        private_methods->add_to_arayeh      = _add_type_int;
        private_methods->merge_from_arayeh  = _merge_arayeh_type_int;
        private_methods->merge_from_array   = _merge_array_type_int;
        private_methods->get_from_arayeh    = _get_type_int;
        break;

    case AA_ARAYEH_TYPE_LINT:
        private_methods->init_arayeh        = _init_pointer_type_long_int;
        private_methods->malloc_arayeh      = _malloc_type_long_int;
        private_methods->realloc_arayeh     = _realloc_type_long_int;
        private_methods->free_arayeh        = _free_type_long_int;
        private_methods->set_memory_pointer = _set_memory_pointer_type_long_int;
        private_methods->add_to_arayeh      = _add_type_long_int;
        private_methods->merge_from_arayeh  = _merge_arayeh_type_long_int;
        private_methods->merge_from_array   = _merge_array_type_long_int;
        private_methods->get_from_arayeh    = _get_type_long_int;
        break;

    case AA_ARAYEH_TYPE_FLOAT:
        private_methods->init_arayeh        = _init_pointer_type_float;
        private_methods->malloc_arayeh      = _malloc_type_float;
        private_methods->realloc_arayeh     = _realloc_type_float;
        private_methods->free_arayeh        = _free_type_float;
        private_methods->set_memory_pointer = _set_memory_pointer_type_float;
        private_methods->add_to_arayeh      = _add_type_float;
        private_methods->merge_from_arayeh  = _merge_arayeh_type_float;
        private_methods->merge_from_array   = _merge_array_type_float;
        private_methods->get_from_arayeh    = _get_type_float;
        break;

    case AA_ARAYEH_TYPE_DOUBLE:
        private_methods->init_arayeh        = _init_pointer_type_double;
        private_methods->malloc_arayeh      = _malloc_type_double;
        private_methods->realloc_arayeh     = _realloc_type_double;
        private_methods->free_arayeh        = _free_type_double;
        private_methods->set_memory_pointer = _set_memory_pointer_type_double;
        private_methods->add_to_arayeh      = _add_type_double;
        private_methods->merge_from_arayeh  = _merge_arayeh_type_double;
        private_methods->merge_from_array   = _merge_array_type_double;
        private_methods->get_from_arayeh    = _get_type_double;
        break;
    default:
        FATAL_WRONG_TYPE("set_private_methods", AA_ARAYEH_TRUE);
    }
}

int malloc_arayeh_map(arayeh_map **map_pointer, size_t initial_size)
{
    // track error state in the function.
    int state;

    size_t map_bytes = initial_size % 8 == 0 ? initial_size / 8 : initial_size / 8 + 1;
    *map_pointer     = (arayeh_map *) malloc(sizeof **map_pointer * map_bytes);

    if (*map_pointer == NULL) {
        free(*map_pointer);
        state = AA_ARAYEH_FAILURE;
    } else {
        state = AA_ARAYEH_SUCCESS;
    }

    return state;
}

int realloc_arayeh_map(arayeh *self, arayeh_map **map_pointer, size_t new_size)
{
    // track error state in the function.
    int state;

    size_t map_bytes = new_size % 8 == 0 ? new_size / 8 : new_size / 8 + 1;
    *map_pointer = (arayeh_map *) realloc(map_pointer, sizeof **map_pointer * map_bytes);

    if (*map_pointer == NULL) {
        free(*map_pointer);
        state = AA_ARAYEH_FAILURE;
    } else {
        state = AA_ARAYEH_SUCCESS;
    }

    return state;
}

int is_arayeh_cell_filled(arayeh *self, size_t index)
{
    int is_filled;

    size_t byte_select = index / 8;
    size_t bit_select  = index % 8;

    arayeh_map *map_pointer = self->_private_properties.map;
    arayeh_map *map_byte    = (map_pointer + byte_select);

    switch (bit_select) {
    case 0:
        is_filled = map_byte->bit_0;
        break;
    case 1:
        is_filled = map_byte->bit_1;
        break;
    case 2:
        is_filled = map_byte->bit_2;
        break;
    case 3:
        is_filled = map_byte->bit_3;
        break;
    case 4:
        is_filled = map_byte->bit_4;
        break;
    case 5:
        is_filled = map_byte->bit_5;
        break;
    case 6:
        is_filled = map_byte->bit_6;
        break;
    case 7:
        is_filled = map_byte->bit_7;
        break;
    default:
        FATAL_OVERFLOW("is_arayeh_cell_filled", AA_ARAYEH_TRUE);
    }

    return is_filled;
}

int is_arayeh_cell_empty(arayeh *self, size_t index)
{
    return !is_arayeh_cell_filled(self, index);
}

void insert_to_arayeh_map(arayeh *self, size_t index, char value)
{
    size_t byte_select = index / 8;
    size_t bit_select  = index % 8;

    arayeh_map *map_pointer = self->_private_properties.map;
    arayeh_map *map_byte    = (map_pointer + byte_select);

    switch (bit_select) {
    case 0:
        map_byte->bit_0 = value;
        break;
    case 1:
        map_byte->bit_1 = value;
        break;
    case 2:
        map_byte->bit_2 = value;
        break;
    case 3:
        map_byte->bit_3 = value;
        break;
    case 4:
        map_byte->bit_4 = value;
        break;
    case 5:
        map_byte->bit_5 = value;
        break;
    case 6:
        map_byte->bit_6 = value;
        break;
    case 7:
        map_byte->bit_7 = value;
        break;
    default:
        FATAL_OVERFLOW("insert_to_arayeh_map", AA_ARAYEH_TRUE);
    }
}

void arayeh_map_cell_state_change_filled(arayeh *self, size_t index)
{
    insert_to_arayeh_map(self, index, 1);
}

void arayeh_map_cell_state_change_empty(arayeh *self, size_t index)
{
    insert_to_arayeh_map(self, index, 0);
}

void arayeh_map_cell_state_set_all_filled(arayeh *self)
{
    for (size_t i = 0; i < self->_private_properties.size; i++) {
        arayeh_map_cell_state_change_filled(self, i);
    }
}

void arayeh_map_cell_state_set_all_empty(arayeh *self)
{
    for (size_t i = 0; i < self->_private_properties.size; i++) {
        arayeh_map_cell_state_change_empty(self, i);
    }
}

void update_used_counter(arayeh *self, size_t change_size_number)
{
    // update both public and private "used" counter.
    self->_private_properties.used += change_size_number;
    self->used = self->_private_properties.used;
}
