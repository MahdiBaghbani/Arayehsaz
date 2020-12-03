/** include/arayeh.h
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

#ifndef __AA_A_ARAYEH_H__
#define __AA_A_ARAYEH_H__

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef SIZE_MAX
#    ifdef __SIZE_MAX__
#        define SIZE_MAX __SIZE_MAX__
#    endif
#endif

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

// false true symbolic.
#ifndef FALSE
#    define FALSE 0
#endif

#ifndef TRUE
#    define TRUE 1
#endif

// return codes.
#define AA_ARAYEH_FAILURE          0
#define AA_ARAYEH_SUCCESS          1
#define AA_ARAYEH_WRONG_TYPE       2
#define AA_ARAYEH_WRONG_NEW_SIZE   3
#define AA_ARAYEH_OVERFLOW         4
#define AA_ARAYEH_REALLOC_DENIED   5
#define AA_ARAYEH_WRONG_INDEX      6
#define AA_ARAYEH_NOT_ENOUGH_SPACE 7
#define AA_ARAYEH_WRONG_STEP       8

// map characters.
#define AA_ARAYEH_OFF    '0'
#define AA_ARAYEH_ON     '1'
#define AA_ARAYEH_MANUAL '3'

// arayeh types.
#define AA_ARAYEH_TYPE_CHAR   1
#define AA_ARAYEH_TYPE_SINT   2
#define AA_ARAYEH_TYPE_INT    3
#define AA_ARAYEH_TYPE_LINT   4
#define AA_ARAYEH_TYPE_FLOAT  5
#define AA_ARAYEH_TYPE_DOUBLE 6

__BEGIN_DECLS

// Prototype of arayeh struct.
typedef struct arayehStruct arayeh;

// Supported arayeh types.
typedef union arayehTypeUnion {

    // pointer to the array of type char.
    char *charPtr;

    // pointer to the array of type short int.
    short int *shortIntPtr;

    // pointer to the array of type int.
    int *intPtr;

    // pointer to the array of type long int.
    long int *longIntPtr;

    // pointer to the array of type float.
    float *floatPtr;

    // pointer to the array of type double.
    double *doublePtr;
} arayehType;

typedef struct arayehSizeSettingsStruct {

    // allow extending arayeh size when using add method.
    char extendAdd;

    // allow extending arayeh size when using insert method.
    char extendInsert;

    // allow extending arayeh size when using fill method.
    char extendFill;

    // allow extending arayeh size when using merge list method.
    char extendMergeArray;
} arayehSizeSettings;

// Arayeh settings.
typedef struct arayehSettingsStruct {

    // allow debug messages to be printed on stdout and stderr.
    char debugMessages;

    // allow extending arayeh size whenever needed.
    char extendSize;

    // holds method specific size extension settings.
    arayehSizeSettings *methodSize;
} arayehSettings;

// Arayeh definition.
typedef struct arayehStruct {

    // Public properties of arayeh.
    struct {

        // holds type of arayeh.
        size_t type;

        // holds next pointer, the pointer is pointing
        // at the next empty cell in the arayeh.
        size_t next;

        // holds the number of filled cells.
        size_t used;

        // holds current size of arayeh.
        size_t size;

        // hold settings for arayeh.
        arayehSettings *settings;
    };

    // Private properties of arayeh.
    struct privateProperties {

        // holds type of arayeh.
        size_t type;

        // holds next pointer, the pointer is pointing
        // at the next empty cell in the arayeh.
        size_t next;

        // holds the number of filled cells.
        size_t used;

        // holds current size of arayeh.
        size_t size;

        // holds actual array.
        arayehType array;

        // holds a map of arayeh cells, indicates they are empty or filled.
        // using type char for this is to minimize the impact of memory usage.
        char *map;

        // hold settings for arayeh.
        arayehSettings *settings;

    } _privateProperties;

    // Public methods of arayehs, accessible for everyone.
    struct {

        // this function will reallocate memory to the arayeh and its map.
        int (*resizeMemory)(arayeh *self, size_t newSize);

        // this function will reallocate memory to the arayeh and its map.
        // the reallocation with this function increases size of the arayeh.
        int (*extendSize)(arayeh *self, size_t extendSize);

        // this function will free the arayeh and reset its parameters.
        int (*freeArayeh)(arayeh **self);

        // this function will insert an "element" into arayeh at the next empty
        // location in the arayeh. if arayeh is full, it will extend arayeh size.
        int (*add)(arayeh *self, void *element);

        // this function will insert an "element" into arayeh at "index".
        int (*insert)(arayeh *self, size_t index, void *element);

        // this function will fill arayeh with an element from index (inclusive)
        // "start" to index (exclusive) "end" with step size "step".
        int (*fill)(arayeh *self, size_t startIndex, size_t step, size_t endIndex,
                    void *element);

        // this function will merge a default C array
        // (for example int a[4] = {1, 2, 3, 4};) into arayeh, the starting
        // index for merging is "startIndex" and the size of C array determines the
        // last index (in the example above the size of C array is 4).
        int (*mergeArray)(arayeh *self, size_t startIndex, size_t arraySize, void *array);

        // this function copies data in "index" cell of the arayeh to the
        // "destination" memory location.
        int (*get)(arayeh *self, size_t index, void *destination);

        // this function will override arayeh default settings.
        void (*setSettings)(arayeh *self, arayehSettings *settings);

        // this function will override arayeh extend size default settings.
        void (*setSizeSettings)(arayeh *self, arayehSizeSettings *settings);

        // this function will override the arayehs default growth factor function
        // with a new function provided by user.
        void (*setGrowthFactor)(arayeh *self, size_t (*growthFactor)(arayeh *self));
    };

    // Private methods of arayeh, should not be used by users.
    struct privateMethods {

        // this function initializes arayeh pointer.
        int (*initArayeh)(arayeh *self, arayehType *array, size_t initialSize);

        // this function allocates memory for arayeh.
        int (*mallocArayeh)(arayeh *self, arayehType *array, size_t initialSize);

        // this function re-allocates memory for arayeh.
        int (*reallocArayeh)(arayeh *self, arayehType *array, size_t initialSize);

        // this frees arayeh memory.
        void (*freeArayeh)(arayeh *self);

        // this function is implemented as a way to control the
        // dynamic growth rate of the arayeh memory space.
        size_t (*growthFactor)(arayeh *self);

        // this function assigns the initialized pointer of an array to the arayeh
        // structs pointer.
        void (*setMemoryPointer)(arayeh *self, arayehType *array);

        // this function adds an element of a specific type to the arayeh.
        void (*addToArayeh)(arayeh *self, size_t index, void *element);

        // this function merges a C standard array of a specific type into the
        // arayeh of the same type.
        int (*mergeFromArray)(arayeh *self, size_t startIndex, size_t arraySize,
                              void *array);
        // this function gets an element from arayeh and places it into a destination
        // memory location provided by caller.
        void (*getFromArayeh)(arayeh *self, size_t index, void *destination);

    } _privateMethods;

} arayeh;

arayeh *Arayeh(size_t type, size_t initialSize);
/*
 * This function will create an arayeh of type "type"
 * (one the supported types defined in configuration.h)
 * and size of "initialSize" if it's possible
 * (you have enough memory and right to allocate that memory).
 *
 * ARGUMENTS:
 * initialSize  size of arayeh.
 * type         type of arayeh elements.
 *
 * RETURN:
 * A pointer to the initialized arayeh.
 * or
 * return NULL in case of error.
 */

__END_DECLS

#endif    //__AA_A_ARAYEH_H__
