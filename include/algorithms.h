/**
 * @file       include/algorithms.h
 * @author     Mohammad Mahdi Baghbani Pourvahid
 * @date       2020-2022
 * @version    0.1.0
 * @copyright  GNU Affero General Public License.
 * @internal
 *
 * @brief      Algorithms header file for Arayehsaz Library.
 * @details    This header contains algorithmic functions for the Arayehsaz library.
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

#ifndef __AA_A_ALGORITHMS_H__
#define __AA_A_ALGORITHMS_H__

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

/** @cond DO_NOT_DOCUMENT */
__BEGIN_DECLS
/** @endcond */

// this function will calculate the extension size of memory.
size_t growth_factor_python(arayeh *arayeh);

// This function purpose is to update array.next variable to point to next
// empty [available] slot in the array.
void update_next_index(arayeh *self);

/** @cond DO_NOT_DOCUMENT */
__END_DECLS
/** @endcond */

#endif    //__AA_A_ALGORITHMS_H__
