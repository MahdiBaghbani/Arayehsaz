/* source/arrays1d.h
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

#ifndef __AA_A_ARRAYS1D_H__
#define __AA_A_ARRAYS1D_H__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "configurations.h"

#ifndef SIZE_MAX
# ifdef __SIZE_MAX__
#  define SIZE_MAX __SIZE_MAX__
# endif
#endif

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

// Prototype array structs.
typedef struct arayehStruct arayeh;

// Supported array types.
typedef union arrayTypeUnion {
    char        *pChar;
    short int   *pShortInt;
    int         *pInt;
    long int    *pLongInt;
    float       *pFloat;
    double      *pDouble;
} arrayType;

// Array 1D definition.
typedef struct arayehStruct {

    // variables to hold state of the array.
    struct internalProperties {
        arrayType   array;
        char        *map;
        size_t      type;
        size_t      next;
        size_t      used;
        size_t      size;
    } _internalProperties;

    // public methods of arrays, accessible for everyone.
    struct {

        void (*extendSize)(arayeh *self, size_t extendSize);

        void (*delete)(arayeh *self);

        void (*fill)(arayeh *self, size_t start, size_t step, size_t end, void *element);

        void (*add)(arayeh *self, void *element);

        void (*insert)(arayeh *self, size_t index, void *element);

        void (*mergeCArray)(arayeh *self, void *list, size_t listSize, size_t startIndex);

        void (*get)(arayeh *self, size_t index, void *destination);

    };

    // private methods of array, should not be used by users.
    struct privateMethods {

        int (*initArayeh)(arayeh *self, arrayType *array, size_t initialSize);

        int (*mallocArayeh)(arayeh *self, arrayType *array, size_t initialSize);

        int (*reallocArayeh)(arayeh *self, arrayType *array, size_t initialSize);

        void (*freeArayeh)(arayeh *self);

        void (*setArayehMemoryPointer)(arayeh *self, arrayType *array);

        void (*addElementToArayeh)(arayeh *self, size_t index, void *element);

        void (*appendElementToArayeh)(arayeh *self, void *list, size_t listSize, size_t startIndex);

        void (*getElementFromArayeh)(arayeh *self, size_t index, void *destination);

    } _privateMethods;

} arayeh;

arayeh *newArayeh1D(size_t type, size_t initialSize);
/*
 * This function will create an array of type "type"
 * (one the supported types defined in configuration.h)
 * and size of  "initialSize" if it's possible
 * (you have enough memory and right to allocate that memory).
 *
 * ARGUMENTS:
 * initialSize    size of array.
 * type           type of array elements.
 *
 * RETURN:
 * A pointer to the initialized array.
 * or
 * Prints error message and exits.
 */

__END_DECLS

#endif //__AA_A_ARRAYS1D_H__
