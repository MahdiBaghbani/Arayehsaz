/** source/types.c
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

#include "../include/types.h"

/* Overflow happens when the arayeh initial size is bigger than the
 * max allowed size (defined as MAX_SIZE in size_type) divided by the
 * length of desired data type.
 *
 * for example MAX_SIZE in my machine is 18446744073709551615 and length of
 * an int data type is 4, so if array initial size is bigger than
 * 18446744073709551615 / 4 = 4611686018427387904, then an overflow occurs.
 *
 * the formula to determine if overflow happens or not is defined below:
 * (initialSize > (size_t) SIZE_MAX / sizeof datatype)
 *
 */

// Initialize arayeh pointer.

int _initPtrTypeChar(arayeh *self, arayehType *array, size_t initialSize)
{
    array->charPtr = NULL;
    return (initialSize > (size_t) SIZE_MAX / sizeof *(array->charPtr))
               ? AA_ARAYEH_FAILURE
               : AA_ARAYEH_SUCCESS;
}

int _initPtrTypeSInt(arayeh *self, arayehType *array, size_t initialSize)
{
    array->shortIntPtr = NULL;
    return (initialSize > (size_t) SIZE_MAX / sizeof *(array->shortIntPtr))
               ? AA_ARAYEH_FAILURE
               : AA_ARAYEH_SUCCESS;
}

int _initPtrTypeInt(arayeh *self, arayehType *array, size_t initialSize)
{
    array->intPtr = NULL;
    return (initialSize > (size_t) SIZE_MAX / sizeof *(array->intPtr))
               ? AA_ARAYEH_FAILURE
               : AA_ARAYEH_SUCCESS;
}

int _initPtrTypeLInt(arayeh *self, arayehType *array, size_t initialSize)
{
    array->longIntPtr = NULL;
    return (initialSize > (size_t) SIZE_MAX / sizeof *(array->longIntPtr))
               ? AA_ARAYEH_FAILURE
               : AA_ARAYEH_SUCCESS;
}

int _initPtrTypeFloat(arayeh *self, arayehType *array, size_t initialSize)
{
    array->floatPtr = NULL;
    return (initialSize > (size_t) SIZE_MAX / sizeof *(array->floatPtr))
               ? AA_ARAYEH_FAILURE
               : AA_ARAYEH_SUCCESS;
}

int _initPtrTypeDouble(arayeh *self, arayehType *array, size_t initialSize)
{
    array->doublePtr = NULL;
    return (initialSize > (size_t) SIZE_MAX / sizeof *(array->doublePtr))
               ? AA_ARAYEH_FAILURE
               : AA_ARAYEH_SUCCESS;
}

// Allocate memory for arayeh.

int _mallocTypeChar(arayeh *self, arayehType *array, size_t initialSize)
{
    array->charPtr = (char *) malloc(sizeof *array->charPtr * initialSize);
    return (array->charPtr == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _mallocTypeSInt(arayeh *self, arayehType *array, size_t initialSize)
{
    array->shortIntPtr = (short int *) malloc(sizeof *array->shortIntPtr * initialSize);
    return (array->shortIntPtr == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _mallocTypeInt(arayeh *self, arayehType *array, size_t initialSize)
{
    array->intPtr = (int *) malloc(sizeof *array->intPtr * initialSize);
    return (array->intPtr == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _mallocTypeLInt(arayeh *self, arayehType *array, size_t initialSize)
{
    array->longIntPtr = (long int *) malloc(sizeof *array->longIntPtr * initialSize);
    return (array->longIntPtr == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _mallocTypeFloat(arayeh *self, arayehType *array, size_t initialSize)
{
    array->floatPtr = (float *) malloc(sizeof *array->floatPtr * initialSize);
    return (array->floatPtr == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _mallocTypeDouble(arayeh *self, arayehType *array, size_t initialSize)
{
    array->doublePtr = (double *) malloc(sizeof *array->doublePtr * initialSize);
    return (array->doublePtr == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

// Re-allocate memory for arayeh.

int _reallocTypeChar(arayeh *self, arayehType *array, size_t newSize)
{
    array->charPtr = (char *) realloc(self->_privateProperties.array.charPtr,
                                      sizeof *array->charPtr * newSize);
    return (array->charPtr == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _reallocTypeSInt(arayeh *self, arayehType *array, size_t newSize)
{
    array->shortIntPtr = (short int *) realloc(self->_privateProperties.array.shortIntPtr,
                                               sizeof *array->shortIntPtr * newSize);
    return (array->shortIntPtr == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _reallocTypeInt(arayeh *self, arayehType *array, size_t newSize)
{
    array->intPtr = (int *) realloc(self->_privateProperties.array.intPtr,
                                    sizeof *array->intPtr * newSize);
    return (array->intPtr == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _reallocTypeLInt(arayeh *self, arayehType *array, size_t newSize)
{
    array->longIntPtr = (long int *) realloc(self->_privateProperties.array.longIntPtr,
                                             sizeof *array->longIntPtr * newSize);
    return (array->longIntPtr == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _reallocTypeFloat(arayeh *self, arayehType *array, size_t newSize)
{
    array->floatPtr = (float *) realloc(self->_privateProperties.array.floatPtr,
                                        sizeof *array->floatPtr * newSize);
    return (array->floatPtr == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _reallocTypeDouble(arayeh *self, arayehType *array, size_t newSize)
{
    array->doublePtr = (double *) realloc(self->_privateProperties.array.doublePtr,
                                          sizeof *array->doublePtr * newSize);
    return (array->doublePtr == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

// Free arayeh memory.

void _freeTypeChar(arayeh *self)
{
    free(self->_privateProperties.array.charPtr);
    self->_privateProperties.array.charPtr = NULL;
}

void _freeTypeSInt(arayeh *self)
{
    free(self->_privateProperties.array.shortIntPtr);
    self->_privateProperties.array.shortIntPtr = NULL;
}

void _freeTypeInt(arayeh *self)
{
    free(self->_privateProperties.array.intPtr);
    self->_privateProperties.array.intPtr = NULL;
}

void _freeTypeLInt(arayeh *self)
{
    free(self->_privateProperties.array.longIntPtr);
    self->_privateProperties.array.longIntPtr = NULL;
}

void _freeTypeFloat(arayeh *self)
{
    free(self->_privateProperties.array.floatPtr);
    self->_privateProperties.array.floatPtr = NULL;
}

void _freeTypeDouble(arayeh *self)
{
    free(self->_privateProperties.array.doublePtr);
    self->_privateProperties.array.doublePtr = NULL;
}

// Assign the initialized pointer of an array to the arayeh structs pointer.

void _setMemPtrTypeChar(arayeh *self, arayehType *array)
{
    self->_privateProperties.array.charPtr = array->charPtr;
}

void _setMemPtrTypeSInt(arayeh *self, arayehType *array)
{
    self->_privateProperties.array.shortIntPtr = array->shortIntPtr;
}

void _setMemPtrTypeInt(arayeh *self, arayehType *array)
{
    self->_privateProperties.array.intPtr = array->intPtr;
}

void _setMemPtrTypeLInt(arayeh *self, arayehType *array)
{
    self->_privateProperties.array.longIntPtr = array->longIntPtr;
}

void _setMemPtrTypeFloat(arayeh *self, arayehType *array)
{
    self->_privateProperties.array.floatPtr = array->floatPtr;
}

void _setMemPtrTypeDouble(arayeh *self, arayehType *array)
{
    self->_privateProperties.array.doublePtr = array->doublePtr;
}

// Add an element of a specific type to the arayeh.

void _addTypeChar(arayeh *self, size_t index, void *element)
{
    self->_privateProperties.array.charPtr[index] = *((char *) element);
}

void _addTypeSInt(arayeh *self, size_t index, void *element)
{
    self->_privateProperties.array.shortIntPtr[index] = *((short int *) element);
}

void _addTypeInt(arayeh *self, size_t index, void *element)
{
    self->_privateProperties.array.intPtr[index] = *((int *) element);
}

void _addTypeLInt(arayeh *self, size_t index, void *element)
{
    self->_privateProperties.array.longIntPtr[index] = *((long int *) element);
}

void _addTypeFloat(arayeh *self, size_t index, void *element)
{
    self->_privateProperties.array.floatPtr[index] = *((float *) element);
}

void _addTypeDouble(arayeh *self, size_t index, void *element)
{
    self->_privateProperties.array.doublePtr[index] = *((double *) element);
}

// Merge a C standard array of a specific type into the arayeh.

int _mergeArrayTypeChar(arayeh *self, size_t startIndex, size_t listSize, void *list)
{
    int state;
    char *temp = (char *) list;
    for (size_t i = 0; i < listSize; ++i) {
        state = (self->insert)(self, startIndex + i, temp + i);
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }
    return state;
}

int _mergeArrayTypeSInt(arayeh *self, size_t startIndex, size_t listSize, void *list)
{
    int state;
    short int *temp = (short int *) list;
    for (size_t i = 0; i < listSize; ++i) {
        state = (self->insert)(self, startIndex + i, temp + i);
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }
    return state;
}

int _mergeArrayTypeInt(arayeh *self, size_t startIndex, size_t listSize, void *list)
{
    int state;
    int *temp = (int *) list;
    for (size_t i = 0; i < listSize; ++i) {
        state = (self->insert)(self, startIndex + i, temp + i);
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }
    return state;
}

int _mergeArrayTypeLInt(arayeh *self, size_t startIndex, size_t listSize, void *list)
{
    int state;
    long int *temp = (long int *) list;
    for (size_t i = 0; i < listSize; ++i) {
        state = (self->insert)(self, startIndex + i, temp + i);
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }
    return state;
}

int _mergeArrayTypeFloat(arayeh *self, size_t startIndex, size_t listSize, void *list)
{
    int state;
    float *temp = (float *) list;
    for (size_t i = 0; i < listSize; ++i) {
        state = (self->insert)(self, startIndex + i, temp + i);
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }
    return state;
}

int _mergeArrayTypeDouble(arayeh *self, size_t startIndex, size_t listSize, void *list)
{
    int state;
    double *temp = (double *) list;
    for (size_t i = 0; i < listSize; ++i) {
        state = (self->insert)(self, startIndex + i, temp + i);
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }
    return state;
}

// Get an element from arayeh.

void _getTypeChar(arayeh *self, size_t index, void *element)
{
    char *ptr = (char *) element;
    *ptr      = self->_privateProperties.array.charPtr[index];
}

void _getTypeSInt(arayeh *self, size_t index, void *element)
{
    short int *ptr = (short int *) element;
    *ptr           = self->_privateProperties.array.shortIntPtr[index];
}

void _getTypeInt(arayeh *self, size_t index, void *element)
{
    int *ptr = (int *) element;
    *ptr     = self->_privateProperties.array.intPtr[index];
}

void _getTypeLInt(arayeh *self, size_t index, void *element)
{
    long int *ptr = (long int *) element;
    *ptr          = self->_privateProperties.array.longIntPtr[index];
}

void _getTypeFloat(arayeh *self, size_t index, void *element)
{
    float *ptr = (float *) element;
    *ptr       = self->_privateProperties.array.floatPtr[index];
}

void _getTypeDouble(arayeh *self, size_t index, void *element)
{
    double *ptr = (double *) element;
    *ptr        = self->_privateProperties.array.doublePtr[index];
}
