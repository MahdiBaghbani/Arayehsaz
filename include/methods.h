/** include/methods.h
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

#ifndef __AA_A_ARAYEHINTERNAL_H__
#define __AA_A_ARAYEHINTERNAL_H__

#include "arayeh.h"
#include "fatal.h"
#include "typeManager.h"

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
int _extendSize(arayeh *self, size_t extendSize);

// this function will free the array and reset its parameters.
int _freeMemory(arayeh **self);

// this function will calculate the extension size of memory.
size_t _defaultGrowthFactor(arayeh *arayeh);

// this function will override the arayehs default growth factor function
// with a new function provided by user.
void _setGrowthFactorFunction(arayeh *self, size_t (*growthFactor)(arayeh *arayeh));

// This function will calculate the extension size of memory and extends arayeh size.
int _calculateAndExtendSize(arayeh *self);

// this function will insert an "element" into array at
// index = self->_privateProperties.next.
int _addToArayeh(arayeh *self, void *element);

// this function will insert an "element" into array at "index".
int _insertToArayeh(arayeh *self, size_t index, void *element);

// this function will fill array with an element from index (inclusive)
// "startIndex" to index (exclusive) "endIndex" with step size "step".
int _fillArayeh(arayeh *self, size_t startIndex, size_t step, size_t endIndex,
                void *element);

// this function will merge a default C array (for example int a[4] = {1, 2, 3, 4};)
// into arayeh, the starting index for merging is "startIndex" and the size of
// C array determines the last index (in the example above the size of C array is 4).
int _mergeToArayeh(arayeh *self, size_t startIndex, size_t listSize, void *array);

// this function copies data in "index" cell of the array to the "destination" memory
// location.
int _getFromArayeh(arayeh *self, size_t index, void *destination);

// this function will override arayeh default settings with new one.
void _setSettings(arayeh *self, arayehSettings *newSettings);

// this function will override arayeh extend size default settings with new one.
void _setSizeSettings(arayeh *self, arayehSizeSettings *newSettings);

// this function assigns pointers to public functions of an arayeh instance.
void _setPublicMethods(arayeh *self);

// this function assigns pointers to public functions of an arayeh instance.
void _setPrivateMethods(arayeh *self, size_t type);

// This function purpose is to update array.next variable to point to next
// empty [available] slot in the array.
void _UpdateNextLocationPointer(arayeh *self);

__END_DECLS

#endif    //__AA_A_ARAYEHINTERNAL_H__
