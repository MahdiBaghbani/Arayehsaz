/**
 * @file       source/types.c
 * @author     Mohammad Mahdi Baghbani Pourvahid
 * @date       2020-2021
 * @version    0.1.0
 * @copyright  GNU Affero General Public License.
 * @internal
 *
 * @brief      Type management source file for Arayehsaz Library.
 * @details    This source contains type specific Arayeh functions.
 */

/*
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

#include "../include/types.h"

#include "../include/functions.h"

/* Overflow happens when the arayeh initial size is bigger than the
 * max allowed size (defined as MAX_SIZE in size_type) divided by the
 * length of desired data type.
 *
 * for example MAX_SIZE in my machine is 18446744073709551615 and length of
 * an int data type is 4, so if array initial size is bigger than
 * 18446744073709551615 / 4 = 4611686018427387904, then an overflow occurs.
 *
 * the formula to determine if overflow happens or not is defined below:
 * (initial_size > (size_t) SIZE_MAX / sizeof datatype)
 *
 */

// Initialize arayeh pointer.

int _init_pointer_type_char(arayeh *self, arayeh_types *array, size_t initial_size)
{
    array->char_pointer = NULL;
    return (initial_size > (size_t) SIZE_MAX / sizeof *(array->char_pointer))
               ? AA_ARAYEH_FAILURE
               : AA_ARAYEH_SUCCESS;
}

int _init_pointer_type_short_int(arayeh *self, arayeh_types *array, size_t initial_size)
{
    array->short_int_pointer = NULL;
    return (initial_size > (size_t) SIZE_MAX / sizeof *(array->short_int_pointer))
               ? AA_ARAYEH_FAILURE
               : AA_ARAYEH_SUCCESS;
}

int _init_pointer_type_int(arayeh *self, arayeh_types *array, size_t initial_size)
{
    array->int_pointer = NULL;
    return (initial_size > (size_t) SIZE_MAX / sizeof *(array->int_pointer))
               ? AA_ARAYEH_FAILURE
               : AA_ARAYEH_SUCCESS;
}

int _init_pointer_type_long_int(arayeh *self, arayeh_types *array, size_t initial_size)
{
    array->long_int_pointer = NULL;
    return (initial_size > (size_t) SIZE_MAX / sizeof *(array->long_int_pointer))
               ? AA_ARAYEH_FAILURE
               : AA_ARAYEH_SUCCESS;
}

int _init_pointer_type_float(arayeh *self, arayeh_types *array, size_t initial_size)
{
    array->float_pointer = NULL;
    return (initial_size > (size_t) SIZE_MAX / sizeof *(array->float_pointer))
               ? AA_ARAYEH_FAILURE
               : AA_ARAYEH_SUCCESS;
}

int _init_pointer_type_double(arayeh *self, arayeh_types *array, size_t initial_size)
{
    array->double_pointer = NULL;
    return (initial_size > (size_t) SIZE_MAX / sizeof *(array->double_pointer))
               ? AA_ARAYEH_FAILURE
               : AA_ARAYEH_SUCCESS;
}

// Allocate memory for arayeh.

int _malloc_type_char(arayeh *self, arayeh_types *array, size_t initial_size)
{
    array->char_pointer = (char *) malloc(sizeof *array->char_pointer * initial_size);
    return (array->char_pointer == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _malloc_type_short_int(arayeh *self, arayeh_types *array, size_t initial_size)
{
    array->short_int_pointer =
        (short int *) malloc(sizeof *array->short_int_pointer * initial_size);
    return (array->short_int_pointer == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _malloc_type_int(arayeh *self, arayeh_types *array, size_t initial_size)
{
    array->int_pointer = (int *) malloc(sizeof *array->int_pointer * initial_size);
    return (array->int_pointer == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _malloc_type_long_int(arayeh *self, arayeh_types *array, size_t initial_size)
{
    array->long_int_pointer =
        (long int *) malloc(sizeof *array->long_int_pointer * initial_size);
    return (array->long_int_pointer == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _malloc_type_float(arayeh *self, arayeh_types *array, size_t initial_size)
{
    array->float_pointer = (float *) malloc(sizeof *array->float_pointer * initial_size);
    return (array->float_pointer == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _malloc_type_double(arayeh *self, arayeh_types *array, size_t initial_size)
{
    array->double_pointer =
        (double *) malloc(sizeof *array->double_pointer * initial_size);
    return (array->double_pointer == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

// Re-allocate memory for arayeh.

int _realloc_type_char(arayeh *self, arayeh_types *array, size_t new_size)
{
    array->char_pointer = (char *) realloc(self->_private_properties.array.char_pointer,
                                           sizeof *array->char_pointer * new_size);
    return (array->char_pointer == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _realloc_type_short_int(arayeh *self, arayeh_types *array, size_t new_size)
{
    array->short_int_pointer =
        (short int *) realloc(self->_private_properties.array.short_int_pointer,
                              sizeof *array->short_int_pointer * new_size);
    return (array->short_int_pointer == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _realloc_type_int(arayeh *self, arayeh_types *array, size_t new_size)
{
    array->int_pointer = (int *) realloc(self->_private_properties.array.int_pointer,
                                         sizeof *array->int_pointer * new_size);
    return (array->int_pointer == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _realloc_type_long_int(arayeh *self, arayeh_types *array, size_t new_size)
{
    array->long_int_pointer =
        (long int *) realloc(self->_private_properties.array.long_int_pointer,
                             sizeof *array->long_int_pointer * new_size);
    return (array->long_int_pointer == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _realloc_type_float(arayeh *self, arayeh_types *array, size_t new_size)
{
    array->float_pointer =
        (float *) realloc(self->_private_properties.array.float_pointer,
                          sizeof *array->float_pointer * new_size);
    return (array->float_pointer == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

int _realloc_type_double(arayeh *self, arayeh_types *array, size_t new_size)
{
    array->double_pointer =
        (double *) realloc(self->_private_properties.array.double_pointer,
                           sizeof *array->double_pointer * new_size);
    return (array->double_pointer == NULL) ? AA_ARAYEH_FAILURE : AA_ARAYEH_SUCCESS;
}

// Free arayeh memory.

void _free_type_char(arayeh *self)
{
    free(self->_private_properties.array.char_pointer);
    self->_private_properties.array.char_pointer = NULL;
}

void _free_type_short_int(arayeh *self)
{
    free(self->_private_properties.array.short_int_pointer);
    self->_private_properties.array.short_int_pointer = NULL;
}

void _free_type_int(arayeh *self)
{
    free(self->_private_properties.array.int_pointer);
    self->_private_properties.array.int_pointer = NULL;
}

void _free_type_long_int(arayeh *self)
{
    free(self->_private_properties.array.long_int_pointer);
    self->_private_properties.array.long_int_pointer = NULL;
}

void _free_type_float(arayeh *self)
{
    free(self->_private_properties.array.float_pointer);
    self->_private_properties.array.float_pointer = NULL;
}

void _free_type_double(arayeh *self)
{
    free(self->_private_properties.array.double_pointer);
    self->_private_properties.array.double_pointer = NULL;
}

// Assign the initialized pointer of an array to the arayeh structs pointer.

void _set_memory_pointer_type_char(arayeh *self, arayeh_types *array)
{
    self->_private_properties.array.char_pointer = array->char_pointer;
}

void _set_memory_pointer_type_short_int(arayeh *self, arayeh_types *array)
{
    self->_private_properties.array.short_int_pointer = array->short_int_pointer;
}

void _set_memory_pointer_type_int(arayeh *self, arayeh_types *array)
{
    self->_private_properties.array.int_pointer = array->int_pointer;
}

void _set_memory_pointer_type_long_int(arayeh *self, arayeh_types *array)
{
    self->_private_properties.array.long_int_pointer = array->long_int_pointer;
}

void _set_memory_pointer_type_float(arayeh *self, arayeh_types *array)
{
    self->_private_properties.array.float_pointer = array->float_pointer;
}

void _set_memory_pointer_type_double(arayeh *self, arayeh_types *array)
{
    self->_private_properties.array.double_pointer = array->double_pointer;
}

// Add an element of a specific type to the arayeh.

void _add_type_char(arayeh *self, size_t index, void *element)
{
    self->_private_properties.array.char_pointer[index] = *((char *) element);
}

void _add_type_short_int(arayeh *self, size_t index, void *element)
{
    self->_private_properties.array.short_int_pointer[index] = *((short int *) element);
}

void _add_type_int(arayeh *self, size_t index, void *element)
{
    self->_private_properties.array.int_pointer[index] = *((int *) element);
}

void _add_type_long_int(arayeh *self, size_t index, void *element)
{
    self->_private_properties.array.long_int_pointer[index] = *((long int *) element);
}

void _add_type_float(arayeh *self, size_t index, void *element)
{
    self->_private_properties.array.float_pointer[index] = *((float *) element);
}

void _add_type_double(arayeh *self, size_t index, void *element)
{
    self->_private_properties.array.double_pointer[index] = *((double *) element);
}

// Merge an arayeh of a specific type into another arayeh.

int _merge_arayeh_type_char(arayeh *self, size_t start_index, size_t step, arayeh *source)
{
    // shorten names for god's sake.
    struct private_properties *src_private_properties = &source->_private_properties;

    // track error state in the function.
    int state;

    // track index for insertion.
    size_t insert_index;

    // pointers.
    char *array_pointer = src_private_properties->array.char_pointer;
    char *element_pointer;

    for (size_t array_index = 0, arayeh_index = 0;
         array_index < src_private_properties->size;
         array_index++, arayeh_index += step) {

        // calculate next element location.
        element_pointer = array_pointer + array_index;

        // calculate next index.
        insert_index = start_index + arayeh_index;

        // do not insert element to self if its source is empty.
        if (is_arayeh_cell_empty(source, array_index)) {
            // go to next loop cycle.
            continue;
        }

        // insert element into arayeh.
        state = self->insert(self, insert_index, element_pointer);

        // in case of any error abort process and return error code.
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }

    // return error state code.
    return state;
}

int _merge_arayeh_type_short_int(arayeh *self, size_t start_index, size_t step,
                                 arayeh *source)
{
    // shorten names for god's sake.
    struct private_properties *src_private_properties = &source->_private_properties;

    // track error state in the function.
    int state;

    // track index for insertion.
    size_t insert_index;

    // pointers.
    short int *array_pointer = src_private_properties->array.short_int_pointer;
    short int *element_pointer;

    for (size_t array_index = 0, arayeh_index = 0;
         array_index < src_private_properties->size;
         array_index++, arayeh_index += step) {

        // calculate next element location.
        element_pointer = array_pointer + array_index;

        // calculate next index.
        insert_index = start_index + arayeh_index;

        // do not insert element to self if its source is empty.
        if (is_arayeh_cell_empty(source, array_index)) {
            // go to next loop cycle.
            continue;
        }

        // insert element into arayeh.
        state = self->insert(self, insert_index, element_pointer);

        // in case of any error abort process and return error code.
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }

    // return error state code.
    return state;
}

int _merge_arayeh_type_int(arayeh *self, size_t start_index, size_t step, arayeh *source)
{
    // shorten names for god's sake.
    struct private_properties *src_private_properties = &source->_private_properties;

    // track error state in the function.
    int state;

    // track index for insertion.
    size_t insert_index;

    // pointers.
    int *array_pointer = src_private_properties->array.int_pointer;
    int *element_pointer;

    for (size_t array_index = 0, arayeh_index = 0;
         array_index < src_private_properties->size;
         array_index++, arayeh_index += step) {

        // calculate next element location.
        element_pointer = array_pointer + array_index;

        // calculate next index.
        insert_index = start_index + arayeh_index;

        // do not insert element to self if its source is empty.
        if (is_arayeh_cell_empty(source, array_index)) {
            // go to next loop cycle.
            continue;
        }

        // insert element into arayeh.
        state = self->insert(self, insert_index, element_pointer);

        // in case of any error abort process and return error code.
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }

    // return error state code.
    return state;
}

int _merge_arayeh_type_long_int(arayeh *self, size_t start_index, size_t step,
                                arayeh *source)
{
    // shorten names for god's sake.
    struct private_properties *src_private_properties = &source->_private_properties;

    // track error state in the function.
    int state;

    // track index for insertion.
    size_t insert_index;

    // pointers.
    long int *array_pointer = src_private_properties->array.long_int_pointer;
    long int *element_pointer;

    for (size_t array_index = 0, arayeh_index = 0;
         array_index < src_private_properties->size;
         array_index++, arayeh_index += step) {

        // calculate next element location.
        element_pointer = array_pointer + array_index;

        // calculate next index.
        insert_index = start_index + arayeh_index;

        // do not insert element to self if its source is empty.
        if (is_arayeh_cell_empty(source, array_index)) {
            // go to next loop cycle.
            continue;
        }

        // insert element into arayeh.
        state = self->insert(self, insert_index, element_pointer);

        // in case of any error abort process and return error code.
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }

    // return error state code.
    return state;
}

int _merge_arayeh_type_float(arayeh *self, size_t start_index, size_t step,
                             arayeh *source)
{
    // shorten names for god's sake.
    struct private_properties *src_private_properties = &source->_private_properties;

    // track error state in the function.
    int state;

    // track index for insertion.
    size_t insert_index;

    // pointers.
    float *array_pointer = src_private_properties->array.float_pointer;
    float *element_pointer;

    for (size_t array_index = 0, arayeh_index = 0;
         array_index < src_private_properties->size;
         array_index++, arayeh_index += step) {

        // calculate next element location.
        element_pointer = array_pointer + array_index;

        // calculate next index.
        insert_index = start_index + arayeh_index;

        // do not insert element if its empty.
        if (is_arayeh_cell_empty(source, array_index)) {
            // go to next loop cycle.
            continue;
        }

        // insert element into arayeh.
        state = self->insert(self, insert_index, element_pointer);

        // in case of any error abort process and return error code.
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }

    // return error state code.
    return state;
}

int _merge_arayeh_type_double(arayeh *self, size_t start_index, size_t step,
                              arayeh *source)
{
    // shorten names for god's sake.
    struct private_properties *src_private_properties = &source->_private_properties;

    // track error state in the function.
    int state;

    // track index for insertion.
    size_t insert_index;

    // pointers.
    double *array_pointer = src_private_properties->array.double_pointer;
    double *element_pointer;

    for (size_t array_index = 0, arayeh_index = 0;
         array_index < src_private_properties->size;
         array_index++, arayeh_index += step) {

        // calculate next element location.
        element_pointer = array_pointer + array_index;

        // calculate next index.
        insert_index = start_index + arayeh_index;

        // do not insert element to self if its source is empty.
        if (is_arayeh_cell_empty(source, array_index)) {
            // go to next loop cycle.
            continue;
        }

        // insert element into arayeh.
        state = self->insert(self, insert_index, element_pointer);

        // in case of any error abort process and return error code.
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }

    // return error state code.
    return state;
}

// Merge a C standard array of a specific type into the arayeh.

int _merge_array_type_char(arayeh *self, size_t start_index, size_t step,
                           size_t array_size, void *array)
{
    // track error state in the function.
    int state;

    // track index for insertion.
    size_t insert_index;

    // pointers.
    char *array_pointer = (char *) array;
    char *element_pointer;

    for (size_t array_index = 0, arayeh_index = 0; array_index < array_size;
         array_index++, arayeh_index += step) {

        // calculate next element location.
        element_pointer = array_pointer + array_index;

        // calculate next index.
        insert_index = start_index + arayeh_index;

        state = self->insert(self, insert_index, element_pointer);

        // in case of any error abort process and return error code.
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }

    // return error state code.
    return state;
}

int _merge_array_type_short_int(arayeh *self, size_t start_index, size_t step,
                                size_t array_size, void *array)
{
    // track error state in the function.
    int state;

    // track index for insertion.
    size_t insert_index;

    // pointers.
    short int *array_pointer = (short int *) array;
    short int *element_pointer;

    for (size_t array_index = 0, arayeh_index = 0; array_index < array_size;
         array_index++, arayeh_index += step) {

        // calculate next element location.
        element_pointer = array_pointer + array_index;

        // calculate next index.
        insert_index = start_index + arayeh_index;

        state = self->insert(self, insert_index, element_pointer);

        // in case of any error abort process and return error code.
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }

    // return error state code.
    return state;
}

int _merge_array_type_int(arayeh *self, size_t start_index, size_t step,
                          size_t array_size, void *array)
{
    // track error state in the function.
    int state;

    // track index for insertion.
    size_t insert_index;

    // pointers.
    int *array_pointer = (int *) array;
    int *element_pointer;

    for (size_t array_index = 0, arayeh_index = 0; array_index < array_size;
         array_index++, arayeh_index += step) {

        // calculate next element location.
        element_pointer = array_pointer + array_index;

        // calculate next index.
        insert_index = start_index + arayeh_index;

        state = self->insert(self, insert_index, element_pointer);

        // in case of any error abort process and return error code.
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }

    // return error state code.
    return state;
}

int _merge_array_type_long_int(arayeh *self, size_t start_index, size_t step,
                               size_t array_size, void *array)
{
    // track error state in the function.
    int state;

    // track index for insertion.
    size_t insert_index;

    // pointers.
    long int *array_pointer = (long int *) array;
    long int *element_pointer;

    for (size_t array_index = 0, arayeh_index = 0; array_index < array_size;
         array_index++, arayeh_index += step) {

        // calculate next element location.
        element_pointer = array_pointer + array_index;

        // calculate next index.
        insert_index = start_index + arayeh_index;

        state = self->insert(self, insert_index, element_pointer);

        // in case of any error abort process and return error code.
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }

    // return error state code.
    return state;
}

int _merge_array_type_float(arayeh *self, size_t start_index, size_t step,
                            size_t array_size, void *array)
{
    // track error state in the function.
    int state;

    // track index for insertion.
    size_t insert_index;

    // pointers.
    float *array_pointer = (float *) array;
    float *element_pointer;

    for (size_t array_index = 0, arayeh_index = 0; array_index < array_size;
         array_index++, arayeh_index += step) {

        // calculate next element location.
        element_pointer = array_pointer + array_index;

        // calculate next index.
        insert_index = start_index + arayeh_index;

        state = self->insert(self, insert_index, element_pointer);

        // in case of any error abort process and return error code.
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }

    // return error state code.
    return state;
}

int _merge_array_type_double(arayeh *self, size_t start_index, size_t step,
                             size_t array_size, void *array)
{
    // track error state in the function.
    int state;

    // track index for insertion.
    size_t insert_index;

    // pointers.
    double *array_pointer = (double *) array;
    double *element_pointer;

    for (size_t array_index = 0, arayeh_index = 0; array_index < array_size;
         array_index++, arayeh_index += step) {

        // calculate next element location.
        element_pointer = array_pointer + array_index;

        // calculate next index.
        insert_index = start_index + arayeh_index;

        state = self->insert(self, insert_index, element_pointer);

        // in case of any error abort process and return error code.
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }

    // return error state code.
    return state;
}

// Get an element from arayeh.

void _get_type_char(arayeh *self, size_t index, void *element)
{
    char *ptr = (char *) element;
    *ptr      = self->_private_properties.array.char_pointer[index];
}

void _get_type_short_int(arayeh *self, size_t index, void *element)
{
    short int *ptr = (short int *) element;
    *ptr           = self->_private_properties.array.short_int_pointer[index];
}

void _get_type_int(arayeh *self, size_t index, void *element)
{
    int *ptr = (int *) element;
    *ptr     = self->_private_properties.array.int_pointer[index];
}

void _get_type_long_int(arayeh *self, size_t index, void *element)
{
    long int *ptr = (long int *) element;
    *ptr          = self->_private_properties.array.long_int_pointer[index];
}

void _get_type_float(arayeh *self, size_t index, void *element)
{
    float *ptr = (float *) element;
    *ptr       = self->_private_properties.array.float_pointer[index];
}

void _get_type_double(arayeh *self, size_t index, void *element)
{
    double *ptr = (double *) element;
    *ptr        = self->_private_properties.array.double_pointer[index];
}
