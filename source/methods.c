/** source/methods.c
 *
 * This file is a part of:
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

#include "../include/methods.h"

#include "../include/algorithms.h"
#include "../include/fatal.h"
#include "../include/functions.h"

int _resize_memory(arayeh *self, size_t new_size)
{
    /*
     * This function will reallocate memory to the arayeh and its map.
     *
     * ARGUMENTS:
     * self          pointer to the arayeh object.
     * new_size      size increment.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in arayeh.h .
     *
     */

    // shorten names for god's sake.
    struct private_methods *private_methods       = &self->_private_methods;
    struct private_properties *private_properties = &self->_private_properties;

    // shorten setting names.
    char debug_messages = private_properties->settings->debug_messages;

    // set debug flag.
    int debug = debug_messages == AA_ARAYEH_ON ? AA_ARAYEH_TRUE : AA_ARAYEH_FALSE;

    // track error state in the function.
    int state;

    // initialize variables for allocating memory.
    char *map_pointer = NULL;
    arayeh_types arayeh_pointer;

    // this function identifies the right pointer for arayeh type and sets it to
    // point to NULL and also checks for possible overflow in size_t new_size.
    state = private_methods->init_arayeh(self, &arayeh_pointer, new_size);

    // protection for possible overflow in size_t.
    if (state == AA_ARAYEH_FAILURE) {
        WARN_T_OVERFLOW("_resize_memory()", debug);
        return AA_ARAYEH_OVERFLOW;
    }

    // reallocate memory to map and arayeh.
    map_pointer =
        (char *) realloc(private_properties->map, sizeof *map_pointer * new_size);
    state = private_methods->realloc_arayeh(self, &arayeh_pointer, new_size);

    // check if memory re-allocated or not.
    if (state == AA_ARAYEH_FAILURE || map_pointer == NULL) {
        // free map and arayeh pointers.
        free(map_pointer);
        private_methods->free_arayeh(self);

        // write to stderr and return error code.
        WARN_REALLOC("_resize_memory()", debug);
        return AA_ARAYEH_REALLOC_DENIED;
    }

    // set pointers to memory locations.
    private_methods->set_memory_pointer(self, &arayeh_pointer);
    private_properties->map = map_pointer;

    // update arayeh parameters.
    private_properties->size = new_size;
    self->size               = new_size;

    // return success code.
    return AA_ARAYEH_SUCCESS;
}

int _extend_size(arayeh *self, size_t extend_size)
{
    /*
     * This function will reallocate memory to the arayeh and its map.
     * The reallocation with this function increases size of the arayeh.
     *
     * ARGUMENTS:
     * self          pointer to the arayeh object.
     * extend_size   size increment.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in arayeh.h .
     *
     */

    // shorten names for god's sake.
    struct private_properties *private_properties = &self->_private_properties;

    // shorten setting names.
    char debug_messages = private_properties->settings->debug_messages;

    // set debug flag.
    int debug = debug_messages == AA_ARAYEH_ON ? AA_ARAYEH_TRUE : AA_ARAYEH_FALSE;

    // track error state in the function.
    int state;

    // store current size as old size for future use.
    size_t old_size = private_properties->size;

    // calculate new size for arayeh.
    size_t new_size = old_size + extend_size;

    // size_t overflow protection.
    if (new_size < old_size) {
        // wrong new size detected.
        // write to stderr and return error code.
        WARN_NEW_SIZE("_extend_size()", debug);
        return AA_ARAYEH_WRONG_NEW_SIZE;
    }

    // resize memory.
    state = self->resize_memory(self, new_size);

    // in case of unsuccessful size increase,
    // abort and return error state code.
    if (state != AA_ARAYEH_SUCCESS) {
        return state;
    }

    // set new map elements to '0' [AA_ARAYEH_OFF].
    // new elements determined from difference in old size and new size.
    for (size_t index = old_size; index < new_size; index++) {
        private_properties->map[index] = AA_ARAYEH_OFF;
    }

    // return success code.
    return AA_ARAYEH_SUCCESS;
}

int _free_memory(arayeh **self)
{
    /*
     * This function will free the arayeh and reset its parameters.
     *
     * ARGUMENTS:
     * self         pointer to the pointer to the arayeh object.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in arayeh.h .
     */

    // shorten names for god's sake.
    arayeh *to_be_freed                           = (*self);
    struct private_methods *private_methods       = &to_be_freed->_private_methods;
    struct private_properties *private_properties = &to_be_freed->_private_properties;

    // reset arayeh parameters.
    to_be_freed->type        = 0;
    to_be_freed->next        = 0;
    to_be_freed->used        = 0;
    to_be_freed->size        = 0;
    private_properties->type = 0;
    private_properties->next = 0;
    private_properties->used = 0;
    private_properties->size = 0;

    // free the arayeh's internal array pointer.
    private_methods->free_arayeh(*self);

    // free map array pointer and nullify the pointer.
    free(private_properties->map);
    private_properties->map = NULL;

    // free arayeh method specific size settings.
    free(private_properties->settings->method_size);

    // nullify the pointer.
    private_properties->settings->method_size = NULL;

    // free arayeh settings.
    free(private_properties->settings);

    // nullify the pointer.
    private_properties->settings = NULL;

    // free arayeh pointer and nullify the arayeh pointer.
    free(*self);
    *self = NULL;

    // return success code.
    return AA_ARAYEH_SUCCESS;
}

arayeh *_duplicate_arayeh(arayeh *self)
{
    /*
     * This function will create an exact copy of "self" arayeh.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     *
     * RETURN:
     * A pointer to the initialized arayeh.
     * or
     * return NULL in case of error.
     */

    // shorten names for god's sake.
    struct private_properties *private_properties = &self->_private_properties;

    // shorten setting names.
    char debug_messages = private_properties->settings->debug_messages;

    // set debug flag.
    int debug = debug_messages == AA_ARAYEH_ON ? AA_ARAYEH_TRUE : AA_ARAYEH_FALSE;

    // track error state in the function.
    int state;

    // create new arayeh with "self" properties.
    arayeh *duplicate = Arayeh(private_properties->type, private_properties->size);

    // check errors.
    if (duplicate == NULL) {
        WARN_INIT_FAIL("_duplicate_arayeh() method, can not create new arayeh.", debug);
        return NULL;
    }

    // apply self settings to new arayeh.
    duplicate->set_settings(duplicate, private_properties->settings);
    duplicate->set_size_settings(duplicate, private_properties->settings->method_size);

    // copy "self" arayeh into "duplicate" arayeh.
    state = duplicate->merge_arayeh(duplicate, 0, 1, self);

    // check errors.
    if (state != AA_ARAYEH_SUCCESS) {
        WARN_INIT_FAIL("_duplicate_arayeh() method, merge arayeh method failed.", debug);
    }

    // return pointer to the duplicated arayeh.
    return duplicate;
}

int _add_to_arayeh(arayeh *self, void *element)
{
    /*
     * This function will insert an "element" into arayeh at
     * index = self->_private_properties.next.
     *
     * function will extend size of arayeh in case of
     * self->_private_properties.size == self->_private_properties.used.
     *
     * it will update "map" and "used" and "next" parameters.
     * it may update "size" parameter (based on the user specified settings).
     *
     * self->_private_properties.next will be updated in a way that it points to
     * the next EMPTY slot in the arayeh.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * element      pointer to a variable to be added to the arayeh.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in arayeh.h .
     */

    // shorten names for god's sake.
    struct private_methods *private_methods       = &self->_private_methods;
    struct private_properties *private_properties = &self->_private_properties;

    // shorten setting names.
    char debug_messages = private_properties->settings->debug_messages;
    char extend_size    = private_properties->settings->extend_size;
    char extend_add     = private_properties->settings->method_size->extend_add;

    // set debug flag.
    int debug = debug_messages == AA_ARAYEH_ON ? AA_ARAYEH_TRUE : AA_ARAYEH_FALSE;

    // track error state in the function.
    int state;

    // check if arayeh is full.
    if (private_properties->used == private_properties->size) {
        // decide to extend arayeh size based on arayeh settings.
        switch (extend_size) {
        case AA_ARAYEH_ON:
            // extend arayeh size.
            state = auto_extend_memory(self);
            // stop function and return error value if extending arayeh size failed.
            if (state != AA_ARAYEH_SUCCESS) {
                return state;
            }
            break;
        case AA_ARAYEH_OFF:
            // write to stderr and return error code.
            WARN_WRONG_INDEX(
                "_add_to_arayeh() method, not enough space left in the arayeh.", debug);
            return AA_ARAYEH_NOT_ENOUGH_SPACE;
        // if manual is enabled, check against the correct extend size rule.
        case AA_ARAYEH_MANUAL:
            switch (extend_add) {
            case AA_ARAYEH_ON:
                // extend arayeh size.
                state = auto_extend_memory(self);
                // stop function and return error value if extending arayeh size
                // failed.
                if (state != AA_ARAYEH_SUCCESS) {
                    return state;
                }
                break;
            case AA_ARAYEH_OFF:
                // write to stderr and return error code.
                WARN_WRONG_INDEX(
                    "_add_to_arayeh() method, not enough space left in the arayeh.",
                    debug);
                return AA_ARAYEH_NOT_ENOUGH_SPACE;
            default:
                FATAL_WRONG_SETTINGS("_add_to_arayeh() method, extend_add "
                                     "value is not correct.",
                                     AA_ARAYEH_TRUE);
            }
            break;
        default:
            FATAL_WRONG_SETTINGS(
                "_add_to_arayeh() method, extend_size value is not correct.",
                AA_ARAYEH_TRUE);
        }
    }

    // add element.
    private_methods->add_to_arayeh(self, private_properties->next, element);

    // update "map".
    private_properties->map[private_properties->next] = AA_ARAYEH_ON;

    // update both public and private "used" counter.
    private_properties->used++;
    self->used = private_properties->used;

    // update "next" pointer.
    update_next_index(self);

    // return success code.
    return AA_ARAYEH_SUCCESS;
}

int _insert_to_arayeh(arayeh *self, size_t index, void *element)
{
    /*
     * This function will insert an "element" into arayeh at "index".
     *
     * it will update "map" and "used" parameters.
     * it may update "next" parameter.
     * it may update "size" (based on the user specified settings).
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * element      pointer to a variable to be inserted into the arayeh.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * index        index of the desired arayeh cell to insert the element.
     * element      pointer to a variable to be added to the arayeh.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in arayeh.h .
     *
     */

    // shorten names for god's sake.
    struct private_methods *private_methods       = &self->_private_methods;
    struct private_properties *private_properties = &self->_private_properties;

    // shorten setting names.
    char debug_messages = private_properties->settings->debug_messages;
    char extend_size    = private_properties->settings->extend_size;
    char extend_insert  = private_properties->settings->method_size->extend_insert;

    // set debug flag.
    int debug = debug_messages == AA_ARAYEH_ON ? AA_ARAYEH_TRUE : AA_ARAYEH_FALSE;

    // track error state in the function.
    int state = AA_ARAYEH_SUCCESS;

    // check if index is bigger or equal to size of arayeh.
    if (private_properties->size <= index) {
        // calculate memory growth size needed.
        size_t growth_size = index - private_properties->size + 1;

        // decide to extend arayeh size based on arayeh settings.
        switch (extend_size) {
        case AA_ARAYEH_ON:
            // extend arayeh size.
            state = self->extend_size(self, growth_size);

            // check for unsuccessful size extension.
            if (state != AA_ARAYEH_SUCCESS) {
                return state;
            }
            break;
        case AA_ARAYEH_OFF:
            // write to stderr and return error code.
            WARN_WRONG_INDEX("_insert_to_arayeh() method, index is equal or bigger "
                             "than arayeh size!",
                             debug);
            return AA_ARAYEH_NOT_ENOUGH_SPACE;
            // if manual is enabled, check against the correct extend size rule.
        case AA_ARAYEH_MANUAL:
            switch (extend_insert) {
            case AA_ARAYEH_ON:
                // extend arayeh size.
                state = self->extend_size(self, growth_size);

                // check for unsuccessful size extension.
                if (state != AA_ARAYEH_SUCCESS) {
                    return state;
                }
                break;
            case AA_ARAYEH_OFF:
                // write to stderr and return error code.
                WARN_WRONG_INDEX("_insert_to_arayeh() method, index is equal or bigger "
                                 "than arayeh size!",
                                 debug);
                return AA_ARAYEH_NOT_ENOUGH_SPACE;
            default:
                FATAL_WRONG_SETTINGS("_insert_to_arayeh() method, extend_insert "
                                     "value is not correct.",
                                     AA_ARAYEH_TRUE);
            }
            break;
        default:
            FATAL_WRONG_SETTINGS(
                "_insert_to_arayeh() method, extend_size value is not correct.",
                AA_ARAYEH_TRUE);
        }
    }

    // insert element.
    if (index == private_properties->next) {
        // use arayeh.add for insertion if the index is same as next empty
        // slot in the arayeh.
        // this function will automatically update next pointer.
        // it may also need to extend arayeh memory size.
        state = (self->add)(self, element);
    } else {
        // if index is less (more) than the next pointer, just assign element
        // and check for arayeh map to see if that cell was already filled
        // or not, if it had, then "used" and map will stay same, but
        // if it was uninitialized, update map and "used" counter.

        // assign element.
        private_methods->add_to_arayeh(self, index, element);

        // update "map" if it isn't already counted for this index
        // and increase "used" counter.
        if (private_properties->map[index] == AA_ARAYEH_OFF) {
            // update map.
            private_properties->map[index] = AA_ARAYEH_ON;

            // update both public and private "used" counter.
            private_properties->used++;
            self->used = private_properties->used;
        }
    }

    // return error state code.
    return state;
}

int _fill_arayeh(arayeh *self, size_t start_index, size_t step, size_t end_index,
                 void *element)
{
    /*
     * This function will fill arayeh with an element
     * from index (inclusive) "start_index" to index (exclusive) "end_index"
     * with step size "step".
     *
     * it will update "map" and "used" parameters.
     * it may update "size" and "next" parameter.
     *
     * ARGUMENTS:
     * self          pointer to the arayeh object.
     * start_index   starting index (inclusive).
     * step          step size.
     *      WARNING:
     *          using negative number for step would result in
     *          a very very big number because of type conversion to size_t.
     * end_index     ending index (exclusive).
     * element       pointer to a variable that must fill the arayeh.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in arayeh.h .
     *
     */

    // shorten names for god's sake.
    struct private_properties *private_properties = &self->_private_properties;

    // shorten setting names.
    char debug_messages = private_properties->settings->debug_messages;
    char extend_size    = private_properties->settings->extend_size;
    char extend_fill    = private_properties->settings->method_size->extend_fill;

    // set debug flag.
    int debug = debug_messages == AA_ARAYEH_ON ? AA_ARAYEH_TRUE : AA_ARAYEH_FALSE;

    // track error state in the function.
    int state = AA_ARAYEH_SUCCESS;

    // check if starting index being greater than the ending index.
    if (end_index < start_index) {
        // write to stderr and return error code.
        WARN_WRONG_INDEX("_fill_arayeh() method, start_index index is greater than "
                         "end_index index!",
                         debug);
        return AA_ARAYEH_WRONG_INDEX;
    }

    // check step size.
    if (step <= 0) {
        // write to stderr and return error code.
        WARN_WRONG_STEP("_fill_arayeh() method, step should be bigger or equal to 1!",
                        debug);
        return AA_ARAYEH_WRONG_STEP;
    }

    // check if end_index indexes is greater than arayeh size.
    if (private_properties->size < end_index) {
        // calculate memory growth size needed.
        size_t growthSize = end_index - private_properties->size;

        // decide to extend arayeh size based on arayeh settings.
        switch (extend_size) {
        case AA_ARAYEH_ON:
            // extend arayeh size.
            state = self->extend_size(self, growthSize);

            // check for unsuccessful size extension.
            if (state != AA_ARAYEH_SUCCESS) {
                return state;
            }
            break;
        case AA_ARAYEH_OFF:
            // write to stderr and return error code.
            WARN_WRONG_INDEX("_fill_arayeh() method, start_index or end_index is "
                             "greater than arayeh size!",
                             debug);
            return AA_ARAYEH_NOT_ENOUGH_SPACE;
            // if manual is enabled, check against the correct extend size rule.
        case AA_ARAYEH_MANUAL:
            switch (extend_fill) {
            case AA_ARAYEH_ON:
                // extend arayeh size.
                state = self->extend_size(self, growthSize);

                // check for unsuccessful size extension.
                if (state != AA_ARAYEH_SUCCESS) {
                    return state;
                }
                break;
            case AA_ARAYEH_OFF:
                // write to stderr and return error code.
                WARN_WRONG_INDEX("_fill_arayeh() method, start_index or end_index is "
                                 "greater than arayeh size!",
                                 debug);
                return AA_ARAYEH_NOT_ENOUGH_SPACE;
            default:
                FATAL_WRONG_SETTINGS("_fill_arayeh() method, extend_fill "
                                     "value is not correct.",
                                     AA_ARAYEH_TRUE);
            }
            break;
        default:
            FATAL_WRONG_SETTINGS(
                "_fill_arayeh() method, extend_size value is not correct.",
                AA_ARAYEH_TRUE);
        }
    }

    // fill the arayeh using a sequence of insert method.
    for (size_t index = start_index; index < end_index; index += step) {
        state = (self->insert)(self, index, element);
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }

    // return error state code.
    return state;
}

int _merge_from_arayeh(arayeh *self, size_t start_index, size_t step, arayeh *source)
{
    /*
     * This function will merge an arayeh (source) into current arayeh (self), with
     * specified step from the specified start index of (self) arayeh.
     *
     * it will update "map" and "used" parameters.
     * it may update "size" and "next" parameter.
     *
     * ARGUMENTS:
     * self          pointer to the arayeh object.
     * start_index   starting index in the arayeh self.
     * step          step size.
     *      WARNING:
     *          using negative number for step would result in
     *          a very very big number because of type conversion to size_t.
     * source       the arayeh to be merged into the "self" arayeh.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in arayeh.h .
     *
     */

    // shorten names for god's sake.
    struct private_methods *self_private_methods         = &self->_private_methods;
    struct private_properties *self_private_properties   = &self->_private_properties;
    struct private_properties *source_private_properties = &source->_private_properties;

    // shorten setting names.
    char debug_messages = self_private_properties->settings->debug_messages;
    char extend_size    = self_private_properties->settings->extend_size;
    char extend_merge_arayeh =
        self_private_properties->settings->method_size->extend_merge_arayeh;

    // set debug flag.
    int debug = debug_messages == AA_ARAYEH_ON ? AA_ARAYEH_TRUE : AA_ARAYEH_FALSE;

    // track error state in the function.
    int state = AA_ARAYEH_SUCCESS;

    // check that both arayehs have same type.
    if (self_private_properties->type != source_private_properties->type) {
        WARN_WRONG_TYPE(
            "_merge_from_arayeh() method, self and source type doesn't match.", debug);
        return AA_ARAYEH_WRONG_TYPE;
    }

    // check step size.
    if (step <= 0) {
        // write to stderr and return error code.
        WARN_WRONG_STEP(
            "_merge_from_arayeh() method, step should be bigger or equal to 1!", debug);
        return AA_ARAYEH_WRONG_STEP;
    }

    // calculate the step size space overhead, imagine an arayeh of size 5
    // if you want to merge this source arayeh with step size of 1, it needs 5 cells
    // in self arayeh, but how about step size 2 or more?
    // see below:
    //
    // | - | - | - | - |
    //
    // the |'s represents source arayeh element and - shows the space between them
    // while merging, for step 1 the space between each | would be 0, means
    // they will be added next to each another, and for step 2 there will be
    // 1 cell in between two source arayeh elements, so the size of cells between
    // elements can be written like this (step - 1), the number of -'s are
    // always one less than numbers of |'s and can be defined by (sourceArayehSize - 1).
    // so the total number of empty cells between source arayeh elements can be
    // found from (sourceArayehSize - 1) * (step - 1) .
    size_t sourceArayehSize = source_private_properties->size;
    size_t stepOverhead     = (sourceArayehSize - 1) * (step - 1);

    // calculate endIndex.
    size_t endIndex = start_index + sourceArayehSize + stepOverhead;

    // check if endIndex indexes is greater than arayeh size.
    if (self_private_properties->size < endIndex) {
        // calculate memory growth size needed.
        size_t growthSize = endIndex - self_private_properties->size;

        // decide to extend arayeh size based on arayeh settings.
        switch (extend_size) {
        case AA_ARAYEH_ON:
            // extend arayeh size.
            state = self->extend_size(self, growthSize);

            // check for unsuccessful size extension.
            if (state != AA_ARAYEH_SUCCESS) {
                return state;
            }
            break;
        case AA_ARAYEH_OFF:
            // write to stderr and return error code.
            WARN_WRONG_INDEX("_merge_from_arayeh() method, low memory space to merge!",
                             debug);
            return AA_ARAYEH_NOT_ENOUGH_SPACE;
            // if manual is enabled, check against the correct extend size rule.
        case AA_ARAYEH_MANUAL:
            switch (extend_merge_arayeh) {
            case AA_ARAYEH_ON:
                // extend arayeh size.
                state = self->extend_size(self, growthSize);

                // check for unsuccessful size extension.
                if (state != AA_ARAYEH_SUCCESS) {
                    return state;
                }
                break;
            case AA_ARAYEH_OFF:
                // write to stderr and return error code.
                WARN_WRONG_INDEX("_merge_from_arayeh() method, low memory space to merge",
                                 debug);
                return AA_ARAYEH_NOT_ENOUGH_SPACE;
            default:
                FATAL_WRONG_SETTINGS("_merge_from_arayeh() method, extend_merge_arayeh "
                                     "value is not correct.",
                                     AA_ARAYEH_TRUE);
            }
            break;
        default:
            FATAL_WRONG_SETTINGS(
                "_merge_from_arayeh() method, extend_size value is not correct.",
                AA_ARAYEH_TRUE);
        }
    }

    // insert source arayeh elements into self arayeh.
    // updating arayeh parameters is delegated to "insert" method.
    state = self_private_methods->merge_from_arayeh(self, start_index, step, source);

    // update next index pointer.
    update_next_index(self);

    // return error state code.
    return state;
}

int _merge_from_array(arayeh *self, size_t start_index, size_t step, size_t array_size,
                      void *array)
{
    /*
     * This function will merge a default C array
     * (for example int a[4] = {1, 2, 3, 4};) into the arayeh with step, the starting
     * index for merging is "start_index" and the size of C array and step determines
     * the last index (in the example above the size of C arayeh is 4 with step 1).
     *
     * it will update "map" and "used" parameters.
     * it may update "size" and "next" parameter.
     *
     * ARGUMENTS:
     * self          pointer to the arayeh object.
     * start_index   starting index in the arayeh self.
     * step          step size.
     *      WARNING:
     *          using negative number for step would result in
     *          a very very big number because of type conversion to size_t.
     * array_size    size of the C arayeh.
     * array         the C array to be merged into the arayeh.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in arayeh.h .
     *
     */

    // shorten names for god's sake.
    struct private_methods *private_methods       = &self->_private_methods;
    struct private_properties *private_properties = &self->_private_properties;

    // shorten setting names.
    char debug_messages = private_properties->settings->debug_messages;
    char extend_size    = private_properties->settings->extend_size;
    char extend_merge_array =
        private_properties->settings->method_size->extend_merge_array;

    // set debug flag.
    int debug = debug_messages == AA_ARAYEH_ON ? AA_ARAYEH_TRUE : AA_ARAYEH_FALSE;

    // track error state in the function.
    int state = AA_ARAYEH_SUCCESS;

    // check step size.
    if (step <= 0) {
        // write to stderr and return error code.
        WARN_WRONG_STEP(
            "_merge_from_array() method, step should be bigger or equal to 1!", debug);
        return AA_ARAYEH_WRONG_STEP;
    }

    // calculate the step size space overhead, imagine an array of size 5
    // if you want to merge this array with step size of 1, it needs 5 cells
    // in arayeh, but how about step size 2 or more?
    // see below:
    //
    // | - | - | - | - |
    //
    // the |'s represents array element and - shows the space between them
    // while merging, for step 1 the space between each | would be 0, means
    // they will be added next to each another, and for step 2 there will be
    // 1 cell in between two array elements, so the size of cells between
    // elements can be written like this (step - 1), the number of -'s are
    // always one less than numbers of |'s and can be defined by (array_size - 1).
    // so the total number of empty cells between array elements can be
    // found from (array_size - 1) * (step - 1) .
    size_t step_overhead = (array_size - 1) * (step - 1);

    // calculate end_index.
    size_t end_index = start_index + array_size + step_overhead;

    // check if end_index indexes is greater than arayeh size.
    if (private_properties->size < end_index) {
        // calculate memory growth size needed.
        size_t growthSize = end_index - private_properties->size;

        // decide to extend arayeh size based on arayeh settings.
        switch (extend_size) {
        case AA_ARAYEH_ON:
            // extend arayeh size.
            state = self->extend_size(self, growthSize);

            // check for unsuccessful size extension.
            if (state != AA_ARAYEH_SUCCESS) {
                return state;
            }
            break;
        case AA_ARAYEH_OFF:
            // write to stderr and return error code.
            WARN_WRONG_INDEX("_merge_from_array() method, low memory space to merge!",
                             debug);
            return AA_ARAYEH_NOT_ENOUGH_SPACE;
            // if manual is enabled, check against the correct extend size rule.
        case AA_ARAYEH_MANUAL:
            switch (extend_merge_array) {
            case AA_ARAYEH_ON:
                // extend arayeh size.
                state = self->extend_size(self, growthSize);

                // check for unsuccessful size extension.
                if (state != AA_ARAYEH_SUCCESS) {
                    return state;
                }
                break;
            case AA_ARAYEH_OFF:
                // write to stderr and return error code.
                WARN_WRONG_INDEX("_merge_from_array() method, low memory space to merge",
                                 debug);
                return AA_ARAYEH_NOT_ENOUGH_SPACE;
            default:
                FATAL_WRONG_SETTINGS("_merge_from_array() method, extend_merge_array "
                                     "value is not correct.",
                                     AA_ARAYEH_TRUE);
            }
            break;
        default:
            FATAL_WRONG_SETTINGS(
                "_merge_from_array() method, extend_size value is not correct.",
                AA_ARAYEH_TRUE);
        }
    }

    // insert C array elements into arayeh.
    // updating arayeh parameters is delegated to "insert" method.
    state = private_methods->merge_from_array(self, start_index, step, array_size, array);

    // return error state code.
    return state;
}

int _get_from_arayeh(arayeh *self, size_t index, void *destination)
{
    /*
     * This function copies data in "index" cell of the arayeh to the "destination"
     * memory location.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * index        index of the element to be copied.
     * destination  pointer to the destination memory location.
     *
     */

    // shorten names for god's sake.
    struct private_methods *private_methods       = &self->_private_methods;
    struct private_properties *private_properties = &self->_private_properties;

    // shorten setting names.
    char debug_messages = private_properties->settings->debug_messages;

    // set debug flag.
    int debug = debug_messages == AA_ARAYEH_ON ? AA_ARAYEH_TRUE : AA_ARAYEH_FALSE;

    // check arayeh bounds.
    if (index >= private_properties->size) {
        WARN_WRONG_INDEX("_get_from_arayeh()method, index out of range!", debug);
        return AA_ARAYEH_WRONG_INDEX;
    }

    // copy data to destination memory location.
    private_methods->get_from_arayeh(self, index, destination);

    // return success code.
    return AA_ARAYEH_SUCCESS;
}

void _set_settings(arayeh *self, arayeh_settings *new_settings)
{
    /*
     * This function will override arayeh default settings with new one.
     *
     * ARGUMENTS:
     * self              pointer to the arayeh object.
     * new_settings      new setting to apply to arayeh.
     *
     * RETURN:
     * no return, it's void dude.
     *
     */

    // shorten names for god's sake.
    arayeh_settings *settings = self->_private_properties.settings;

    // override new settings.
    settings->debug_messages = new_settings->debug_messages;
    settings->extend_size    = new_settings->extend_size;
}

void _set_size_settings(arayeh *self, arayeh_size_settings *new_settings)
{
    /*
     * This function will override arayeh default extend size settings with new one.
     *
     * ARGUMENTS:
     * self              pointer to the arayeh object.
     * new_settings      new setting to apply to arayeh.
     *
     * RETURN:
     * no return, it's void dude.
     *
     */

    // shorten names for god's sake.
    arayeh_size_settings *settings = self->_private_properties.settings->method_size;

    // override new settings.
    settings->extend_add          = new_settings->extend_add;
    settings->extend_insert       = new_settings->extend_insert;
    settings->extend_fill         = new_settings->extend_fill;
    settings->extend_merge_arayeh = new_settings->extend_merge_arayeh;
    settings->extend_merge_array  = new_settings->extend_merge_array;
}

void _set_growth_factor(arayeh *self, size_t (*growth_factor)(arayeh *))
{
    /*
     * This function will override the arayehs default growth factor function
     * with a new function provided by user.
     *
     * ARGUMENTS:
     * self             pointer to the arayeh object.
     *
     * RETURN:
     * no return, it's void dude.
     *
     */

    // shorten names for god's sake.
    struct private_methods *private_methods = &self->_private_methods;

    private_methods->growth_factor = growth_factor;
}
