/**
 * @file       include/functions.h
 * @author     Mohammad Mahdi Baghbani Pourvahid
 * @date       2020-2022
 * @version    0.1.0
 * @copyright  GNU Affero General Public License.
 * @internal
 *
 * @brief      Internal functions header file for Arayehsaz Library.
 * @details    This header contains internal Arayeh functions.
 */

/*
 * Azadeh Afzar - Arayehsaz (AA-A).
 *
 * Copyright (C) 2020 - 2022 Azadeh Afzar.
 * Copyright (C) 2020 - 2022 Mohammad Mahdi Baghbani Pourvahid.
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

#ifndef __AA_A_FUNCTIONS_H__
#define __AA_A_FUNCTIONS_H__

#include "arayeh.h"

// To ensure that the names declared in this portion of code have C linkage,
// and thus C++ name mangling is not performed while using this code with C++.
/** @cond DO_NOT_DOCUMENT */
#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
#    define __BEGIN_DECLS extern "C" {
#    define __END_DECLS   }
#else
#    define __BEGIN_DECLS /* empty */
#    define __END_DECLS   /* empty */
#endif
/** @endcond */

#define ADD 1
#define SUB 2

/** @cond DO_NOT_DOCUMENT */
__BEGIN_DECLS
/** @endcond */

/**
 * @private
 * @brief This function will calculate the extension size of memory and extends arayeh
 * size.
 *
 * @param[in] self              pointer to the arayeh object.
 *
 * @return a code that indicates successful operation or an error code defined in
 * arayeh.h .
 */
int auto_extend_memory(arayeh *self);

/**
 * @private
 * @brief This function assigns pointers to public functions of an arayeh instance.
 *
 * @param[in] self              pointer to the arayeh object.
 */
void set_public_methods(arayeh *self);

/**
 * @private
 * @brief This function assigns pointers to private functions of an arayeh instance.
 *
 * @param[in] self              pointer to the arayeh object.
 */
void set_private_methods(arayeh *self, size_t type);

/**
 * @private
 * @brief this function creates new arayeh map array.
 *
 * @param[in] map_pointer       pointer to pointer to an arayeh_map.
 * @param[in] initial_size      initial size of map.
 *
 * @return a code that indicates successful operation or an error code defined in
 * arayeh.h .
 */
int arayeh_map_malloc(arayeh_map **map_pointer, size_t initial_size);

/**
 * @private
 * @brief this function reallocates memory to an arayeh map array.
 *
 * @param[in] self              pointer to the arayeh object.
 * @param[in] map_pointer       pointer to pointer to an arayeh_map.
 * @param[in] initial_size      initial size of map.
 *
 * @return a code that indicates successful operation or an error code defined in
 * arayeh.h .
 */
int arayeh_map_realloc(arayeh *self, size_t new_size);

/**
 * @private
 * @brief this function checks a cell specified by index for being filled.
 *
 * @param[in] self              pointer to the arayeh object.
 * @param[in] index             index of the map cell for checking.
 *
 * @return if cell is filled returns 1 and if not returns 0.
 */
int is_arayeh_map_filled(arayeh *self, size_t index);

/**
 * @private
 * @brief this function checks a cell specified by index for being empty.
 *
 * @param[in] self              pointer to the arayeh object.
 * @param[in] index             index of the map cell for checking.
 *
 * @return if cell is empty returns 1 and if not returns 0.
 */
int is_arayeh_map_empty(arayeh *self, size_t index);

/**
 * @private
 * @brief this function inserts data into arayeh map.
 *
 * @param[in] self              pointer to the arayeh object.
 * @param[in] index             index of the map cell for insertion.
 * @param[in] value             data to be inserted.
 *
 * @return if cell is empty returns 1 and if not returns 0.
 */
void arayeh_map_insert(arayeh *self, size_t index, unsigned char value);

/**
 * @private
 * @brief this function flips bit at index.
 *
 * @param[in] self              pointer to the arayeh object.
 * @param[in] index             index of the map cell for flipping.
 *
 */
void arayeh_map_flip(arayeh *self, size_t index);

/**
 * @private
 * @brief this function set a cell state in arayeh map to 1.
 *
 * @param[in] self              pointer to the arayeh object.
 * @param[in] index             index of the map cell for changing.
 *
 */
void arayeh_map_cell_state_change_filled(arayeh *self, size_t index);

/**
 * @private
 * @brief this function set a cell state in arayeh map to 0.
 *
 * @param[in] self              pointer to the arayeh object.
 * @param[in] index             index of the map cell for changing.
 *
 */
void arayeh_map_cell_state_change_empty(arayeh *self, size_t index);

/**
 * @private
 * @brief this function set all cell states in arayeh map to 1.
 *
 * @param[in] self              pointer to the arayeh object.
 *
 */
void arayeh_map_cell_state_set_all_filled(arayeh *self);

/**
 * @private
 * @brief this function set all cell states in arayeh map to 0.
 *
 * @param[in] self              pointer to the arayeh object.
 *
 */
void arayeh_map_cell_state_set_all_empty(arayeh *self);

/**
 * @private
 * @brief this function updates used value.
 *
 * @param[in] self                  pointer to the arayeh object.
 * @param[in] operator              type of the operator to be used. ex: ADD, SUB, ...
 * @param[in] change_size_number    size of the change.
 *
 */
void update_used_counter(arayeh *self, uint8_t operator, size_t change_size_number);

/** @cond DO_NOT_DOCUMENT */
__END_DECLS
/** @endcond */

#endif    //__AA_A_FUNCTIONS_H__
