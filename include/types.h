/** include/types.h
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

int _initPtrTypeChar(arayeh *self, arayehType *array, size_t initialSize);

int _initPtrTypeSInt(arayeh *self, arayehType *array, size_t initialSize);

int _initPtrTypeInt(arayeh *self, arayehType *array, size_t initialSize);

int _initPtrTypeLInt(arayeh *self, arayehType *array, size_t initialSize);

int _initPtrTypeFloat(arayeh *self, arayehType *array, size_t initialSize);

int _initPtrTypeDouble(arayeh *self, arayehType *array, size_t initialSize);

// Allocate memory for arayeh.

int _mallocTypeChar(arayeh *self, arayehType *array, size_t initialSize);

int _mallocTypeSInt(arayeh *self, arayehType *array, size_t initialSize);

int _mallocTypeInt(arayeh *self, arayehType *array, size_t initialSize);

int _mallocTypeLInt(arayeh *self, arayehType *array, size_t initialSize);

int _mallocTypeFloat(arayeh *self, arayehType *array, size_t initialSize);

int _mallocTypeDouble(arayeh *self, arayehType *array, size_t initialSize);

// Re-allocate memory for arayeh.

int _reallocTypeChar(arayeh *self, arayehType *array, size_t newSize);

int _reallocTypeSInt(arayeh *self, arayehType *array, size_t newSize);

int _reallocTypeInt(arayeh *self, arayehType *array, size_t newSize);

int _reallocTypeLInt(arayeh *self, arayehType *array, size_t newSize);

int _reallocTypeFloat(arayeh *self, arayehType *array, size_t newSize);

int _reallocTypeDouble(arayeh *self, arayehType *array, size_t newSize);

// Free arayeh memory.

void _freeTypeChar(arayeh *self);

void _freeTypeSInt(arayeh *self);

void _freeTypeInt(arayeh *self);

void _freeTypeLInt(arayeh *self);

void _freeTypeFloat(arayeh *self);

void _freeTypeDouble(arayeh *self);

// Assign the initialized pointer of an array to the arayeh structs pointer.

void _setMemPtrTypeChar(arayeh *self, arayehType *array);

void _setMemPtrTypeSInt(arayeh *self, arayehType *array);

void _setMemPtrTypeInt(arayeh *self, arayehType *array);

void _setMemPtrTypeLInt(arayeh *self, arayehType *array);

void _setMemPtrTypeFloat(arayeh *self, arayehType *array);

void _setMemPtrTypeDouble(arayeh *self, arayehType *array);

// Add an element of a specific type to the arayeh.

void _addTypeChar(arayeh *self, size_t index, void *element);

void _addTypeSInt(arayeh *self, size_t index, void *element);

void _addTypeInt(arayeh *self, size_t index, void *element);

void _addTypeLInt(arayeh *self, size_t index, void *element);

void _addTypeFloat(arayeh *self, size_t index, void *element);

void _addTypeDouble(arayeh *self, size_t index, void *element);

// Merge an arayeh of a specific type into another arayeh.

int _mergeArayehTypeChar(arayeh *self, size_t startIndex, size_t step, arayeh *source);

int _mergeArayehTypeSInt(arayeh *self, size_t startIndex, size_t step, arayeh *source);

int _mergeArayehTypeInt(arayeh *self, size_t startIndex, size_t step, arayeh *source);

int _mergeArayehTypeLInt(arayeh *self, size_t startIndex, size_t step, arayeh *source);

int _mergeArayehTypeFloat(arayeh *self, size_t startIndex, size_t step, arayeh *source);

int _mergeArayehTypeDouble(arayeh *self, size_t startIndex, size_t step, arayeh *source);

// Merge a C standard array of a specific type into the arayeh.

int _mergeArrayTypeChar(arayeh *self, size_t startIndex, size_t step, size_t arraySize,
                        void *array);

int _mergeArrayTypeSInt(arayeh *self, size_t startIndex, size_t step, size_t arraySize,
                        void *array);

int _mergeArrayTypeInt(arayeh *self, size_t startIndex, size_t step, size_t arraySize,
                       void *array);

int _mergeArrayTypeLInt(arayeh *self, size_t startIndex, size_t step, size_t arraySize,
                        void *array);

int _mergeArrayTypeFloat(arayeh *self, size_t startIndex, size_t step, size_t arraySize,
                         void *array);

int _mergeArrayTypeDouble(arayeh *self, size_t startIndex, size_t step, size_t arraySize,
                          void *array);

// Get an element from arayeh.

void _getTypeChar(arayeh *self, size_t index, void *element);

void _getTypeSInt(arayeh *self, size_t index, void *element);

void _getTypeInt(arayeh *self, size_t index, void *element);

void _getTypeLInt(arayeh *self, size_t index, void *element);

void _getTypeFloat(arayeh *self, size_t index, void *element);

void _getTypeDouble(arayeh *self, size_t index, void *element);

__END_DECLS

#endif    //__AA_A_TYPES_H__
