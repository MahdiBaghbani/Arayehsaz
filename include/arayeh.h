/**
 * @file       include/arayeh.h
 * @author     Mohammad Mahdi Baghbani Pourvahid
 * @date       2020-2022
 * @version    0.1.0
 * @copyright  GNU Affero General Public License.
 *
 * @brief      Main header file for Arayehsaz Library.
 * @details    This header contains all the necessary functions and macros of Arayehsaz
 * library.
 */

/*
 * This file is a part of:
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

#ifndef __AA_A_ARAYEH_H__
#define __AA_A_ARAYEH_H__

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef SIZE_MAX
#    ifdef __SIZE_MAX__
#        define SIZE_MAX __SIZE_MAX__
#    endif
#endif

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

/** @ingroup arayeh_truefalse
 * @{
 */

#define AA_ARAYEH_TRUE  1
#define AA_ARAYEH_FALSE 0

/** @} */

/**
 * @defgroup arayeh_errors Preprocessor symbols error codes.
 *
 * @brief Error codes for error handling purposes.
 *
 * These macros are used to define a set of error codes that arayeh functions would return
 * in case of error, users can use these codes to debug their code or perform necessary
 * error handling operations.
 */

/** @ingroup arayeh_errors
 * @{
 */

#define AA_ARAYEH_FAILURE          0 /**< @brief operation unsuccessful. */
#define AA_ARAYEH_SUCCESS          1 /**< @brief operation successful. */
#define AA_ARAYEH_WRONG_TYPE       2 /**< @brief wrong type for arayeh. */
#define AA_ARAYEH_WRONG_NEW_SIZE   3 /**< @brief wrong new size for arayeh. */
#define AA_ARAYEH_OVERFLOW         4 /**< @brief overflow detected. */
#define AA_ARAYEH_REALLOC_DENIED   5 /**< @brief reallocation cannot be completed. */
#define AA_ARAYEH_WRONG_INDEX      6 /**< @brief wrong index. */
#define AA_ARAYEH_NOT_ENOUGH_SPACE 7 /**< @brief not enough memory space. */
#define AA_ARAYEH_WRONG_STEP       8 /**< @brief wrong step size. */

/** @} */

/** @ingroup arayeh_switches
 * @{
 */

#define AA_ARAYEH_OFF    0 /**< @brief switch is off. */
#define AA_ARAYEH_ON     1 /**< @brief switch is on. */
#define AA_ARAYEH_MANUAL 3 /**< @brief switch is set to manual. */

/** @} */

/**
 * @defgroup arayeh_types Preprocessor symbols arayeh types.
 *
 * @brief Available types for arayeh.
 *
 * These macros are used to define available arayeh types, and their values are needed for
 * internal arayeh functions.
 */

/** @ingroup arayeh_types
 * @{
 */

#define AA_ARAYEH_TYPE_CHAR   1 /**< @brief arayeh type char. */
#define AA_ARAYEH_TYPE_SINT   2 /**< @brief arayeh type short int. */
#define AA_ARAYEH_TYPE_INT    3 /**< @brief arayeh type int. */
#define AA_ARAYEH_TYPE_LINT   4 /**< @brief arayeh type long int. */
#define AA_ARAYEH_TYPE_FLOAT  5 /**< @brief arayeh type float. */
#define AA_ARAYEH_TYPE_DOUBLE 6 /**< @brief arayeh type double. */

/** @} */

/** @cond DO_NOT_DOCUMENT */
__BEGIN_DECLS
/** @endcond */

// Prototype of arayeh struct.
typedef struct arayeh_struct arayeh;

/**
 * @brief A type union to hold pointer to a supported array types.
 *
 * This union holds a pointer to an array of supported type, when initializing arayeh,
 * depending on the type specified by user, one these pointers will be assigned to
 * a memory location of the actual internal array.
 *
 */
typedef union {
    /** @brief pointer to the array of type char. */
    char *char_pointer;

    /** @brief pointer to the array of type short int. */
    short int *short_int_pointer;

    /** @brief pointer to the array of type int. */
    int *int_pointer;

    /** @brief pointer to the array of type long int. */
    long int *long_int_pointer;

    /** @brief pointer to the array of type float. */
    float *float_pointer;

    /** @brief pointer to the array of type double. */
    double *double_pointer;

} arayeh_types;

/**
 * @brief A type structure to hold arayeh size extension setting.
 *
 * This struct hold the method specific settings for arayeh size extension.
 */
typedef struct {
    /** @brief allow extending arayeh size when using add method. */
    char extend_add;

    /** @brief allow extending arayeh size when using insert method. */
    char extend_insert;

    /** @brief allow extending arayeh size when using fill method. */
    char extend_fill;

    /** @brief allow extending arayeh size when using merge list method. */
    char extend_merge_arayeh;

    /** @brief allow extending arayeh size when using merge list method. */
    char extend_merge_array;

} arayeh_size_settings;

/**
 * @brief A type structure to hold arayeh settings.
 *
 * This struct holds general arayeh settings.
 */
typedef struct {
    /** @brief allow debug messages to be printed on stdout and stderr. */
    char debug_messages;

    /** @brief allow extending arayeh size whenever needed. */
    char extend_size;

    /** @brief holds method specific size extension settings. */
    arayeh_size_settings *method_size;

} arayeh_settings;

/**
 * @brief A type def to hold arayeh map.
 *
 * This type uses bitfields of size 1 bit in pack of 8 bits (1 byte)
 * to store the state of each cell in an arayeh as defined below:
 * bit 1: means cell is filled with data.
 * bit 0: means cell is empty.
 *
 * This method is used to reduce the size of map to 1/8 as instead of using whole 1 byte
 * (8 bits) to store a boolean state of only 1 cell, we can now store state of 8 cells.
 */
typedef uint8_t arayeh_map;

/**
 * @brief Arayeh main data structure with public and private members.
 */
typedef struct arayeh_struct {

    struct {
        /** @brief holds type of arayeh. */
        size_t type;

        /** @brief holds next empty cell index. */
        size_t next;

        /** @brief holds number of used cells. */
        size_t used;

        /** @brief holds total cell size of arayeh. */
        size_t size;
    };

    /**
     * @private
     * @brief Arayeh private properties structure.
     *
     * This structure holds arayeh properties like type,
     * size etc, manually changing this structure member's value
     * will corrupt arayeh logic and should be avoided.
     *
     */
    struct private_properties {
        /** @brief holds type of arayeh. */
        size_t type;

        /** @brief holds next empty cell index. */
        size_t next;

        /** @brief holds number of used cells. */
        size_t used;

        /** @brief holds total cell size of arayeh. */
        size_t size;

        /** @brief holds internal array pointer. */
        arayeh_types array;

        /** @brief holds a map of arayeh cells showing empty or used. */
        arayeh_map *map;

        /** @brief hold settings for arayeh. */
        arayeh_settings *settings;

    } _private_properties;

    struct {

        /**
         * @brief this function will reallocate memory of the arayeh with new size.
         *
         * @param[in] self          pointer to the arayeh object.
         * @param[in] new_size      size change.
         *
         * @return a code that indicates successful operation or an error code defined in
         * arayeh.h .
         */
        int (*resize_memory)(arayeh *self, size_t new_size);

        /**
         * @brief this function will increase the memory of arayeh.
         *
         * @param[in] self          pointer to the arayeh object.
         * @param[in] extend_size   size increment.
         *
         * @return a code that indicates successful operation or an error code defined in
         * arayeh.h .
         */
        int (*extend_size)(arayeh *self, size_t extend_size);

        /**
         * @brief this function will free the arayeh and reset its parameters.
         *
         * @param[in] self          pointer to pointer to arayeh object.
         *
         * @return a code that indicates successful operation or an error code defined in
         * arayeh.h .
         */
        int (*free_arayeh)(arayeh **self);

        /**
         * @brief this function will create an exact copy of "self" arayeh.
         *
         * @param[in] self          pointer to the arayeh object.
         *
         * @return A pointer to the initialized arayeh or NULL in case of any error.
         */
        arayeh *(*duplicate)(arayeh *self);

        /**
         * @brief this function will add an element into the next empty arayeh cell.
         *
         * this function will insert an "element" into arayeh at the next empty
         * location in the arayeh. if arayeh is full, it will extend arayeh size
         * according to arayeh size settings.
         *
         * @param[in] self          pointer to the arayeh object.
         * @param[in] element       pointer to a variable to be added to the arayeh.
         *
         * @return a code that indicates successful operation or an error code defined in
         * arayeh.h .
         */
        int (*add)(arayeh *self, void *element);

        /**
         * @brief this function will insert an element into an arayeh cell at the
         * specified index.
         *
         * @param[in] self          pointer to the arayeh object.
         * @param[in] index         index of the arayeh cell to insert the element.
         * @param[in] element       pointer to a variable to be added to the arayeh.
         *
         * @return a code that indicates successful operation or an error code defined in
         * arayeh.h .
         */
        int (*insert)(arayeh *self, size_t index, void *element);

        /**
         * @brief this function will fill a range of arayeh cells arayeh with an element.
         *
         * this function will fill arayeh with an element from index (inclusive)
         * "start" to index (exclusive) "end" with step size "step".
         *
         * @param[in] self          pointer to the arayeh object.
         * @param[in] start_index   starting index (inclusive).
         * @param[in] step          step size.
         * @param[in] end_index     ending index (exclusive).
         * @param[in] element       pointer to a variable to be added to the arayeh.
         *
         * @return a code that indicates successful operation or an error code defined in
         * arayeh.h .
         *
         * @warning using a negative number for step would result in a very very big
         * number because of type conversion to size_t.
         */
        int (*fill)(arayeh *self, size_t start_index, size_t step, size_t end_index,
                    void *element);

        /**
         * @brief this function will merge an arayeh into another arayeh.
         *
         * this function will merge an arayeh (source) into current arayeh (self), with
         * specified step from the specified start index of (self) arayeh.
         *
         * @param[in] self          pointer to the arayeh object.
         * @param[in] start_index   starting index in the arayeh "self".
         * @param[in] step          step size.
         * @param[in] source        the arayeh to be merged into the "self" arayeh.
         *
         * @return a code that indicates successful operation or an error code defined in
         * arayeh.h .
         *
         * @warning using a negative number for step would result in a very very big
         * number because of type conversion to size_t.
         */
        int (*merge_arayeh)(arayeh *self, size_t start_index, size_t step,
                            arayeh *source);

        /**
         * @brief this function will merge a C array into an arayeh.
         *
         * this function will merge a default C array
         * (for example int a[4] = {1, 2, 3, 4};) into arayeh, the starting
         * index for merging is "startIndex" and the size of C array determines the
         * last index (in the example above the size of C array is 4).
         *
         * @param[in] self          pointer to the arayeh object.
         * @param[in] start_index   starting index in the arayeh "self".
         * @param[in] step          step size.
         * @param[in] array_size    size of the C arayeh.
         * @param[in] array         pointer the C array to be merged into the arayeh.
         *
         * @return a code that indicates successful operation or an error code defined in
         * arayeh.h .
         *
         * @warning using a negative number for step would result in a very very big
         * number because of type conversion to size_t.
         */
        int (*merge_array)(arayeh *self, size_t start_index, size_t step,
                           size_t array_size, void *array);

        /**
         * @brief this function will get an element from an arayeh cell.
         *
         * this function copies data in "index" cell of the arayeh to the
         * "destination" memory location.
         *
         * @param[in] self              pointer to the arayeh object.
         * @param[in] index             index of the element to be copied to destination.
         * @param[in,out] destination   pointer to the destination memory location.
         *
         * @return a code that indicates successful operation or an error code defined in
         * arayeh.h .
         */
        int (*get)(arayeh *self, size_t index, void *destination);

        // this function copies data in "index" cell of the arayeh to the
        // "destination" memory location.
        int (*get_arayeh)(arayeh *self, size_t start_index, size_t step, size_t end_index,
                          arayeh *destination);    // TODO

        // this function copies data in "index" cell of the arayeh to the
        // "destination" memory location.
        int (*get_array)(arayeh *self, size_t start_index, size_t step, size_t end_index,
                         void *destination);    // TODO

        // TODO: reduceSize, compact, max, min, sum, multiply, changeType
        // TODO: deleteItem, deleteSlice, pop, popArayeh, popArraySlice,
        // TODO: contains, count, reorder, shuffle, reverse, sort, isEmpty, showSettings
        // TODO: complete error tracing.

        /**
         * @brief this function will override arayeh default settings.
         *
         * @param[in] self              pointer to the arayeh object.
         * @param[in] settings          setting to apply to arayeh.
         */
        void (*set_settings)(arayeh *self, arayeh_settings *settings);

        /**
         * @brief this function will override arayeh extend size default settings.
         *
         * @param[in] self              pointer to the arayeh object.
         * @param[in] settings          setting to apply to arayeh.
         */
        void (*set_size_settings)(arayeh *self, arayeh_size_settings *settings);

        /**
         * @brief  this function sets arayeh growth factor calculator.
         *
         * this function will override the arayehs default growth factor function
         * with a new function provided by user.
         *
         * @param[in] self              pointer to the arayeh object.
         * @param[in] growth_factor     pointer to a growth factor calculator function.
         */
        void (*set_growth_factor)(arayeh *self, size_t (*growth_factor)(arayeh *));
    };

    /**
     * @private
     * @brief Arayeh private methods structure.
     *
     * This structure holds arayeh private methods, which are used internally to
     * perform lots of type related operations.
     *
     */
    struct private_methods {

        /**
         * @brief this function initializes arayeh pointer.
         *
         * this function will pick the right type for arayeh pointer in the
         * arayeh_type union and will set it to NULL, it also checks initial_size of
         * arayeh for possible overflows.
         *
         * @param[in] self          pointer to the arayeh object.
         * @param[in] arayeh_types  arayeh types union.
         * @param[in] initial_size  size of arayeh.
         *
         * @return a code that indicates successful operation or an error code defined in
         * arayeh.h .
         */
        int (*init_arayeh)(arayeh *self, arayeh_types *array, size_t initial_size);

        /**
         * @brief this function allocates memory for arayeh based on its type.
         *
         * @param[in] self          pointer to the arayeh object.
         * @param[in] arayeh_types  arayeh types union.
         * @param[in] initial_size  size of arayeh.
         *
         * @return a code that indicates successful operation or an error code defined in
         * arayeh.h .
         */
        int (*malloc_arayeh)(arayeh *self, arayeh_types *array, size_t initial_size);

        /**
         * @brief this function re-allocates memory for arayeh based on its type.
         *
         * @param[in] self          pointer to the arayeh object.
         * @param[in] arayeh_types  arayeh types union.
         * @param[in] initial_size  size of arayeh.
         *
         * @return a code that indicates successful operation or an error code defined in
         * arayeh.h .
         */
        int (*realloc_arayeh)(arayeh *self, arayeh_types *array, size_t initial_size);

        /**
         * @brief this function frees arayeh memory.
         *
         * @param[in] self          pointer the arayeh object.
         *
         */
        void (*free_arayeh)(arayeh *self);

        /**
         * @brief this function will calculate arayeh growth factor.
         *
         * this function is implemented as a way to control the
         * dynamic growth rate of the arayeh memory space.
         *
         * @param[in] self          pointer to the arayeh object.
         *
         * @return the size of extra memory space to be added to the current memory space.
         */
        size_t (*growth_factor)(arayeh *self);

        /**
         * @brief this function will set pointer to internal array of the arayeh.
         *
         * this function assigns the address of an initialized pointer to an array to the
         * arayeh structs pointer.
         *
         * @param[in] self          pointer to the arayeh object.
         * @param[in] arayeh_types  arayeh types union.
         *
         */
        void (*set_memory_pointer)(arayeh *self, arayeh_types *array);

        /**
         * @brief this function will add an element into an arayeh cell.
         *
         * @param[in] self          pointer to the arayeh object.
         * @param[in] index         index of the arayeh cell to insert the element.
         * @param[in] element       pointer to a variable to be added to the arayeh.
         *
         */
        void (*add_to_arayeh)(arayeh *self, size_t index, void *element);

        /**
         * @brief this function will merge an arayeh into another arayeh.
         *
         * this function will merge an arayeh (source) into current arayeh (self), with
         * specified step from the specified start index of (self) arayeh.
         *
         * @param[in] self          pointer to the arayeh object.
         * @param[in] start_index   starting index in the arayeh "self".
         * @param[in] step          step size.
         * @param[in] source        the arayeh to be merged into the "self" arayeh.
         *
         * @return a code that indicates successful operation or an error code defined in
         * arayeh.h .
         */
        int (*merge_from_arayeh)(arayeh *self, size_t start_index, size_t step,
                                 arayeh *source);

        /**
         * @brief this function will merge a C array into an arayeh.
         *
         * this function merges a C standard array of a specific type into the
         * arayeh of the same type.
         *
         * @param[in] self          pointer to the arayeh object.
         * @param[in] start_index   starting index in the arayeh "self".
         * @param[in] step          step size.
         * @param[in] array_size    size of the C arayeh.
         * @param[in] array         pointer the C array to be merged into the arayeh.
         *
         * @return a code that indicates successful operation or an error code defined in
         * arayeh.h .
         */
        int (*merge_from_array)(arayeh *self, size_t start_index, size_t step,
                                size_t array_size, void *array);

        /**
         * @brief get an element from arayeh cell.
         *
         * this function gets an element from arayeh and places it into a destination
         * memory location provided by caller.
         *
         * @param[in] self          pointer to the arayeh object.
         * @param[in] index         index of the element to be copied.
         * @param[in] destination   pointer to the destination memory location.
         *
         * @return a code that indicates successful operation or an error code defined in
         * arayeh.h .
         */
        void (*get_from_arayeh)(arayeh *self, size_t index, void *destination);

    } _private_methods;

} arayeh;

/**
 * @brief Creates an arayeh with specified type and size.
 *
 * This function will create an arayeh of one the supported types
 * and size of "initial_size" if it's possible
 *
 * @param[in] type          type of arayeh.
 * @param[in] initial_size  size of arayeh.
 *
 * @return A pointer to the initialized arayeh or NULL in case of any error.
 */

arayeh *Arayeh(size_t type, size_t initial_size);

/** @cond DO_NOT_DOCUMENT */
__END_DECLS
/** @endcond */

#endif    //__AA_A_ARAYEH_H__
