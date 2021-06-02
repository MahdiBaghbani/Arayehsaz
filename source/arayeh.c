/** @file       source/arayeh.c
 *  @author     Mohammad Mahdi Baghbani Pourvahid
 *  @date       2020-2021
 *  @copyright  GNU AFFERO GENERAL PUBLIC LICENSE.
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

#include "../include/arayeh.h"

#include "../include/fatal.h"
#include "../include/functions.h"

arayeh *Arayeh(size_t type, size_t initial_size)
{

    // check arayeh type.
    if (type < AA_ARAYEH_TYPE_CHAR || AA_ARAYEH_TYPE_DOUBLE < type) {
        // wrong arayeh type.
        FATAL_WRONG_TYPE("Arayeh()", AA_ARAYEH_TRUE);
    }

    // initialize a pointer and allocate memory.
    arayeh *self = (arayeh *) malloc(sizeof *self);

    // shorten names for god's sake.
    struct private_methods *private_methods       = &self->_private_methods;
    struct private_properties *private_properties = &self->_private_properties;

    // assign public methods.
    set_public_methods(self);

    // assign private methods based on arayeh type.
    set_private_methods(self, type);

    // initialize variables for allocating memory.
    arayeh_map *map_pointer = NULL;
    arayeh_types array_pointer;

    /* Overflow happens when the arayeh initial size is bigger than the
     * max allowed size (defined as MAX_SIZE in size_type) divided by the
     * length of desired data type.
     *
     * for example MAX_SIZE in my machine is 18446744073709551615 and length of
     * an int data type is 4, so if arayeh initial size is bigger than
     * 18446744073709551615 / 4 = 4611686018427387904, then an overflow occurs.
     *
     * the formula to determine if overflow happens or not is defined below:
     * (initial_size > (size_t) SIZE_MAX / sizeof datatype)
     *
     */

    // this function identifies the right pointer for arayeh type and sets it to point
    // to NULL and also checks for possible overflow in size_t initial_size.
    int state = private_methods->init_arayeh(self, &array_pointer, initial_size);

    // check for possible size_t overflow.
    if (state == AA_ARAYEH_FAILURE) {
        // free self.
        free(self);
        // overflow detected.
        FATAL_OVERFLOW("Arayeh()", AA_ARAYEH_TRUE);
    }

    // allocate memory to map and array.
    int map_state    = malloc_arayeh_map(&map_pointer, initial_size);
    int arayeh_state = private_methods->malloc_arayeh(self, &array_pointer, initial_size);

    // check if memory allocated or not.
    if (arayeh_state == AA_ARAYEH_FAILURE || map_state == AA_ARAYEH_FAILURE) {
        // free map, array and self pointers.
        free(map_pointer);
        private_methods->free_arayeh(self);
        free(self);
        return NULL;
    }

    // set pointers to memory locations.
    private_methods->set_memory_pointer(self, &array_pointer);
    private_properties->map = map_pointer;

    // set arayeh parameters.
    self->type               = type;
    self->next               = 0;
    self->used               = 0;
    self->size               = initial_size;
    private_properties->type = type;
    private_properties->next = 0;
    private_properties->used = 0;
    private_properties->size = initial_size;

    // set all map cell states to empty.
    arayeh_map_cell_state_set_all_empty(self);

    // create arayeh default setting holder.
    arayeh_settings *default_settings =
        (arayeh_settings *) malloc(sizeof *default_settings);

    // set default setting.
    default_settings->debug_messages = AA_ARAYEH_OFF;
    default_settings->extend_size    = AA_ARAYEH_ON;
    default_settings->method_size    = NULL;

    // assign setting pointer to the arayeh private properties.
    private_properties->settings = default_settings;

    // create arayeh default method specific size extension setting holder.
    arayeh_size_settings *method_size =
        (arayeh_size_settings *) malloc(sizeof *method_size);

    // set default settings.
    method_size->extend_add          = AA_ARAYEH_ON;
    method_size->extend_insert       = AA_ARAYEH_ON;
    method_size->extend_fill         = AA_ARAYEH_ON;
    method_size->extend_merge_arayeh = AA_ARAYEH_ON;
    method_size->extend_merge_array  = AA_ARAYEH_ON;

    // assign setting pointer to the arayeh private properties.
    private_properties->settings->method_size = method_size;

    return self;
}
