/**
 * @file       source/functions.c
 * @author     Mohammad Mahdi Baghbani Pourvahid
 * @date       2020-2021
 * @version    0.1.0
 * @copyright  GNU Affero General Public License.
 * @internal
 *
 * @brief      Internal functions source file for Arayehsaz Library.
 * @details    This source contains internal Arayeh functions.
 */

/*
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

    // map size should be in bytes, this line calculates the least amount of bytes needed
    // to fit initial_size bits in it.
    size_t map_bytes = initial_size % 8 == 0 ? initial_size / 8 : initial_size / 8 + 1;
    *map_pointer     = (arayeh_map *) malloc(sizeof **map_pointer * map_bytes);

    if (*map_pointer == NULL) {
        state = AA_ARAYEH_FAILURE;
    } else {
        state = AA_ARAYEH_SUCCESS;
    }

    return state;
}

int realloc_arayeh_map(arayeh *self, size_t new_size)
{
    // track error state in the function.
    int state;

    // can we shorten this name? I regret my naming convention :)
    arayeh_map *map_pointer = self->_private_properties.map;

    // map size should be in bytes, this line calculates the least amount of bytes needed
    // to fit new_size bits in it.
    size_t map_bytes = new_size % 8 == 0 ? new_size / 8 : new_size / 8 + 1;

    // first create a new place holder for **map_pointer because It is not guaranteed
    // that pointer returned by the realloc will be same as old pointer passed to
    // realloc and one should not depend on it.
    arayeh_map *new_pointer = NULL;
    new_pointer = (arayeh_map *) realloc(map_pointer, sizeof *map_pointer * map_bytes);

    // check for a possible null pointer in case of reallocation failure.
    if (new_pointer == NULL) {
        state = AA_ARAYEH_FAILURE;
    } else {
        state = AA_ARAYEH_SUCCESS;
        // assign new pointer back to the arayeh map only if its NOT null !!!
        // yeah you have no idea how much pain this block has caused to my mental health.
        self->_private_properties.map = new_pointer;
    }

    return state;
}

int is_arayeh_cell_filled(arayeh *self, size_t index)
{
    // these two lines would find the map byte and the bit in that byte.
    // example: you have an 36 byte map which has 288 bits in total and the index is 46
    // which means you want the 46th bit, so in order to to access it you should first
    // locate the byte that 46th is in it by dividing the index by 8:
    // 46 / 8 = 5.75 , so the 46th bit is in the 5th byte, now you should find the index
    // of 46th bit in the 5th byte, for this you have to find index mod 8:
    // 46 mod 8 = 6
    // so now you know that the 46th bit is in 5th byte at 6th bit! target located :)
    size_t byte_select = index / 8;
    size_t bit_select  = index % 8;

    // get the pointer to the map.
    arayeh_map *map_pointer = self->_private_properties.map;

    // select the byte.
    arayeh_map *map_byte = (map_pointer + byte_select);

    // select bit in the byte.
    switch (bit_select) {
    case 0:
        return map_byte->bit_0;
    case 1:
        return map_byte->bit_1;
    case 2:
        return map_byte->bit_2;
    case 3:
        return map_byte->bit_3;
    case 4:
        return map_byte->bit_4;
    case 5:
        return map_byte->bit_5;
    case 6:
        return map_byte->bit_6;
    case 7:
        return map_byte->bit_7;
    default:
        FATAL_OVERFLOW("is_arayeh_cell_filled", AA_ARAYEH_TRUE);
    }
}

int is_arayeh_cell_empty(arayeh *self, size_t index)
{
    return !is_arayeh_cell_filled(self, index);
}

void insert_to_arayeh_map(arayeh *self, size_t index, unsigned char value)
{
    // these two lines would find the map byte and the bit in that byte.
    // example: you have an 36 byte map which has 288 bits in total and the index is 46
    // which means you want the 46th bit, so in order to to access it you should first
    // locate the byte that 46th is in it by dividing the index by 8:
    // 46 / 8 = 5.75 , so the 46th bit is in the 5th byte, now you should find the index
    // of 46th bit in the 5th byte, for this you have to find index mod 8:
    // 46 mod 8 = 6
    // so now you know that the 46th bit is in 5th byte at 6th bit! target located :)
    size_t byte_select = index / 8;
    size_t bit_select  = index % 8;

    // get the pointer to the map.
    arayeh_map *map_pointer = self->_private_properties.map;

    // select the byte.
    arayeh_map *map_byte = (map_pointer + byte_select);

    // check value to see if it can be ft into 1 bit, if not, change it to 1.
    value = (value > 1) ? 1 : value;

    // select bit in the byte.
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
