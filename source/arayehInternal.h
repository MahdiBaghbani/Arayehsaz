/* source/arayehInternal.h
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

#ifndef __AA_A_ARRAYSINTERNALS1D_H__
#define __AA_A_ARRAYSINTERNALS1D_H__

#include "arrays1d.h"

// To ensure that the names declared in this portion of code have C linkage,
// and thus C++ name mangling is not performed while using this code with C++.
#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

__BEGIN_DECLS

void _extendSizeArray1D(array1d *array, size_t extendSize);

void _freeArray1D(array1d *array);

void _fillArray1D(array1d *array, size_t start, size_t step, size_t end, void *element);

void _addArray1D(array1d *array, void *element);

void _insertArray1D(array1d *array, size_t index, void *element);

void _addListArray1D(array1d *self, void *list, size_t listSize, size_t startIndex);

void _getArray1D(array1d *array, size_t index, void *destination);

void _setPublicMethods(array1d *self);

void _setPrivateMethods(array1d *array, size_t type);

void _nextUpdaterArray1D(array1d *array);

int _initTypeChar(array1d *self, arrayType *array, size_t initialSize);

int _initTypeSInt(array1d *self, arrayType *array, size_t initialSize);

int _initTypeInt(array1d *self, arrayType *array, size_t initialSize);

int _initTypeLInt(array1d *self, arrayType *array, size_t initialSize);

int _initTypeFloat(array1d *self, arrayType *array, size_t initialSize);

int _initTypeDouble(array1d *self, arrayType *array, size_t initialSize);

int _mallocTypeChar(array1d *self, arrayType *array, size_t initialSize);

int _mallocTypeSInt(array1d *self, arrayType *array, size_t initialSize);

int _mallocTypeInt(array1d *self, arrayType *array, size_t initialSize);

int _mallocTypeLInt(array1d *self, arrayType *array, size_t initialSize);

int _mallocTypeFloat(array1d *self, arrayType *array, size_t initialSize);

int _mallocTypeDouble(array1d *self, arrayType *array, size_t initialSize);

int _reallocTypeChar(array1d *self, arrayType *array, size_t newSize);

int _reallocTypeSInt(array1d *self, arrayType *array, size_t newSize);

int _reallocTypeInt(array1d *self, arrayType *array, size_t newSize);

int _reallocTypeLInt(array1d *self, arrayType *array, size_t newSize);

int _reallocTypeFloat(array1d *self, arrayType *array, size_t newSize);

int _reallocTypeDouble(array1d *self, arrayType *array, size_t newSize);

void _freeTypeChar(array1d *self);

void _freeTypeSInt(array1d *self);

void _freeTypeInt(array1d *self);

void _freeTypeLInt(array1d *self);

void _freeTypeFloat(array1d *self);

void _freeTypeDouble(array1d *self);

void _setTypeChar(array1d *self, arrayType *array);

void _setTypeSInt(array1d *self, arrayType *array);

void _setTypeInt(array1d *self, arrayType *array);

void _setTypeLInt(array1d *self, arrayType *array);

void _setTypeFloat(array1d *self, arrayType *array);

void _setTypeDouble(array1d *self, arrayType *array);

void _addTypeChar(array1d *self, size_t index, void *element);

void _addTypeSInt(array1d *self, size_t index, void *element);

void _addTypeInt(array1d *self, size_t index, void *element);

void _addTypeLInt(array1d *self, size_t index, void *element);

void _addTypeFloat(array1d *self, size_t index, void *element);

void _addTypeDouble(array1d *self, size_t index, void *element);

void _appendTypeChar(array1d *self, void *list, size_t listSize, size_t startIndex);

void _appendTypeSInt(array1d *self, void *list, size_t listSize, size_t startIndex);

void _appendTypeInt(array1d *self, void *list, size_t listSize, size_t startIndex);

void _appendTypeLInt(array1d *self, void *list, size_t listSize, size_t startIndex);

void _appendTypeFloat(array1d *self, void *list, size_t listSize, size_t startIndex);

void _appendTypeDouble(array1d *self, void *list, size_t listSize, size_t startIndex);

void _getTypeChar(array1d *self, size_t index, void *element);

void _getTypeSInt(array1d *self, size_t index, void *element);

void _getTypeInt(array1d *self, size_t index, void *element);

void _getTypeLInt(array1d *self, size_t index, void *element);

void _getTypeFloat(array1d *self, size_t index, void *element);

void _getTypeDouble(array1d *self, size_t index, void *element);

__END_DECLS

#endif //__AA_A_ARRAYSINTERNALS1D_H__
