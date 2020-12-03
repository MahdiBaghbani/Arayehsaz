/** source/methods.c
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

#include "../include/methods.h"

#include "../include/algorithms.h"
#include "../include/fatal.h"
#include "../include/functions.h"

int _resizeMemory(arayeh *self, size_t newSize)
{
    /*
     * This function will reallocate memory to the arayeh and its map.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * newSize      size increment.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in configuration.h .
     *
     */

    // shorten names for god's sake.
    struct privateMethods *privateMethods       = &self->_privateMethods;
    struct privateProperties *privateProperties = &self->_privateProperties;
    char debugMessages = privateProperties->settings->debugMessages;

    // set debug flag.
    int debug = debugMessages == AA_ARAYEH_ON ? TRUE : FALSE;

    // track error state in the function.
    int state;

    // initialize variables for allocating memory.
    char *mapPtr = NULL;
    arayehType arayehPtr;

    // this function identifies the right pointer for arayeh type and sets it to
    // point to NULL and also checks for possible overflow in size_t newSize.
    state = privateMethods->initArayeh(self, &arayehPtr, newSize);

    // protection for possible overflow in size_t.
    if (state == AA_ARAYEH_FAILURE) {
        WARN_T_OVERFLOW("_resizeMemory()", debug);
        return AA_ARAYEH_OVERFLOW;
    }

    // reallocate memory to map and arayeh.
    mapPtr = (char *) realloc(privateProperties->map, sizeof *mapPtr * newSize);
    state  = privateMethods->reallocArayeh(self, &arayehPtr, newSize);

    // check if memory re-allocated or not.
    if (state == AA_ARAYEH_FAILURE || mapPtr == NULL) {
        // free map and arayeh pointers.
        free(mapPtr);
        privateMethods->freeArayeh(self);

        // write to stderr and return error code.
        WARN_REALLOC("_resizeMemory()", debug);
        return AA_ARAYEH_REALLOC_DENIED;
    }

    // set pointers to memory locations.
    privateMethods->setMemoryPointer(self, &arayehPtr);
    privateProperties->map = mapPtr;

    // update arayeh parameters.
    privateProperties->size = newSize;
    self->size              = newSize;

    // return success code.
    return AA_ARAYEH_SUCCESS;
}

int _extendSize(arayeh *self, size_t extendSize)
{
    /*
     * This function will reallocate memory to the arayeh and its map.
     * The reallocation with this function increases size of the arayeh.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * extendSize   size increment.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in configuration.h .
     *
     */

    // shorten names for god's sake.
    struct privateProperties *privateProperties = &self->_privateProperties;
    char debugMessages = privateProperties->settings->debugMessages;

    // set debug flag.
    int debug = debugMessages == AA_ARAYEH_ON ? TRUE : FALSE;

    // track error state in the function.
    int state;

    // store current size as old size for future use.
    size_t oldSize = privateProperties->size;

    // calculate new size for arayeh.
    size_t newSize = oldSize + extendSize;

    // size_t overflow protection.
    if (newSize < oldSize) {
        // wrong new size detected.
        // write to stderr and return error code.
        WARN_NEW_SIZE("_extendSize()", debug);
        return AA_ARAYEH_WRONG_NEW_SIZE;
    }

    // resize memory.
    state = self->resizeMemory(self, newSize);

    // in case of unsuccessful size increase,
    // abort and return error state code.
    if (state != AA_ARAYEH_SUCCESS) {
        return state;
    }

    // set new map elements to '0' [AA_ARAYEH_OFF].
    // new elements determined from difference in old size and new size.
    for (size_t i = oldSize; i < newSize; ++i) {
        privateProperties->map[i] = AA_ARAYEH_OFF;
    }

    // return success code.
    return AA_ARAYEH_SUCCESS;
}

int _freeMemory(arayeh **self)
{
    /*
     * This function will free the arayeh and reset its parameters.
     *
     * ARGUMENTS:
     * self         pointer to the pointer to the arayeh object.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in configuration.h .
     */

    // shorten names for god's sake.
    arayeh *toBeFreed                           = (*self);
    struct privateMethods *privateMethods       = &toBeFreed->_privateMethods;
    struct privateProperties *privateProperties = &toBeFreed->_privateProperties;

    // reset arayeh parameters.
    toBeFreed->type         = 0;
    toBeFreed->next         = 0;
    toBeFreed->used         = 0;
    toBeFreed->size         = 0;
    privateProperties->type = 0;
    privateProperties->next = 0;
    privateProperties->used = 0;
    privateProperties->size = 0;

    // free the arayeh's internal array pointer.
    privateMethods->freeArayeh(*self);

    // free map array pointer and nullify the pointer.
    free(privateProperties->map);
    privateProperties->map = NULL;

    // free arayeh method specific size settings.
    free(privateProperties->settings->methodSize);

    // nullify the pointer.
    privateProperties->settings->methodSize = NULL;

    // free arayeh settings.
    free(privateProperties->settings);

    // nullify the pointer.
    privateProperties->settings = NULL;

    // free arayeh pointer and nullify the arayeh pointer.
    free(*self);
    *self = NULL;

    // return success code.
    return AA_ARAYEH_SUCCESS;
}

int _addToArayeh(arayeh *self, void *element)
{
    /*
     * This function will insert an "element" into arayeh at
     * index = self->_privateProperties.next.
     *
     * function will extend size of arayeh in case of
     * self->_privateProperties.size == self->_privateProperties.used.
     *
     * it will update "map" and "used" and "next" parameters.
     * it may update "size" parameter (based on the user specified settings).
     *
     * self->_privateProperties.next will be updated in a way that it points to
     * the next EMPTY slot in the arayeh.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * element      pointer to a variable to be added to the arayeh.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in configuration.h .
     */

    // shorten names for god's sake.
    struct privateMethods *privateMethods       = &self->_privateMethods;
    struct privateProperties *privateProperties = &self->_privateProperties;
    char debugMessages = privateProperties->settings->debugMessages;
    char extendSize    = privateProperties->settings->extendSize;
    char extendAdd     = privateProperties->settings->methodSize->extendAdd;

    // set debug flag.
    int debug = debugMessages == AA_ARAYEH_ON ? TRUE : FALSE;

    // track error state in the function.
    int state;

    // check if arayeh is full.
    if (privateProperties->used == privateProperties->size) {
        // decide to extend arayeh size based on arayeh settings.
        switch (extendSize) {
        case AA_ARAYEH_ON:
            // extend arayeh size.
            state = extendMemory(self);
            // stop function and return error value if extending arayeh size failed.
            if (state != AA_ARAYEH_SUCCESS) {
                return state;
            }
            break;
        case AA_ARAYEH_OFF:
            // write to stderr and return error code.
            WARN_WRONG_INDEX(
                "_addToArayeh() function, not enough space left in the arayeh.", debug);
            return AA_ARAYEH_NOT_ENOUGH_SPACE;
            break;
        // if manual is enabled, check against the correct extend size rule.
        case AA_ARAYEH_MANUAL:
            switch (extendAdd) {
            case AA_ARAYEH_ON:
                // extend arayeh size.
                state = extendMemory(self);
                // stop function and return error value if extending arayeh size
                // failed.
                if (state != AA_ARAYEH_SUCCESS) {
                    return state;
                }
                break;
            case AA_ARAYEH_OFF:
                // write to stderr and return error code.
                WARN_WRONG_INDEX(
                    "_addToArayeh() function, not enough space left in the arayeh.",
                    debug);
                return AA_ARAYEH_NOT_ENOUGH_SPACE;
                break;
            default:
                FATAL_WRONG_SETTINGS("_addToArayeh() function, extendAdd "
                                     "value is not correct.",
                                     debug);
            }
        default:
            FATAL_WRONG_SETTINGS(
                "_addToArayeh() function, extendSize value is not correct.", debug);
        }
    }

    // add element.
    privateMethods->addToArayeh(self, privateProperties->next, element);

    // update "map".
    privateProperties->map[privateProperties->next] = AA_ARAYEH_ON;

    // update both public and private "used" counter.
    privateProperties->used++;
    self->used = privateProperties->used;

    // update "next" pointer.
    updateNextIndex(self);

    // return success code.
    return AA_ARAYEH_SUCCESS;
}

int _insertToArayeh(arayeh *self, size_t index, void *element)
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
     *              or an error code defined in configuration.h .
     *
     */

    // shorten names for god's sake.
    struct privateMethods *privateMethods       = &self->_privateMethods;
    struct privateProperties *privateProperties = &self->_privateProperties;
    char debugMessages = privateProperties->settings->debugMessages;
    char extendSize    = privateProperties->settings->extendSize;
    char extendInsert  = privateProperties->settings->methodSize->extendInsert;

    // set debug flag.
    int debug = debugMessages == AA_ARAYEH_ON ? TRUE : FALSE;

    // track error state in the function.
    int state = AA_ARAYEH_SUCCESS;

    // check if index is bigger or equal to size of arayeh.
    if (privateProperties->size <= index) {
        // decide to extend arayeh size based on arayeh settings.
        switch (extendSize) {
        case AA_ARAYEH_ON:
            // extend arayeh size until "index" is less than the arayeh size.
            do {
                state = extendMemory(self);
                // stop function and return error value if extending arayeh size
                // failed.
                if (state != AA_ARAYEH_SUCCESS) {
                    return state;
                }
            } while (privateProperties->size <= index);
            break;
        case AA_ARAYEH_OFF:
            // write to stderr and return error code.
            WARN_WRONG_INDEX("_insertToArayeh() function, index is equal or bigger "
                             "than arayeh size!",
                             debug);
            return AA_ARAYEH_WRONG_INDEX;
            break;
            // if manual is enabled, check against the correct extend size rule.
        case AA_ARAYEH_MANUAL:
            switch (extendInsert) {
            case AA_ARAYEH_ON:
                // extend arayeh size until "index" is less than the arayeh size.
                do {
                    state = extendMemory(self);
                    // stop function and return error value if extending arayeh size
                    // failed.
                    if (state != AA_ARAYEH_SUCCESS) {
                        return state;
                    }
                } while (privateProperties->size <= index);
                break;
            case AA_ARAYEH_OFF:
                // write to stderr and return error code.
                WARN_WRONG_INDEX("_insertToArayeh() function, index is equal or bigger "
                                 "than arayeh size!",
                                 debug);
                return AA_ARAYEH_WRONG_INDEX;
                break;
            default:
                FATAL_WRONG_SETTINGS("_insertToArayeh() function, extendInsert "
                                     "value is not correct.",
                                     debug);
            }
        default:
            FATAL_WRONG_SETTINGS(
                "_insertToArayeh() function, extendSize value is not correct.", debug);
        }
    }

    // insert element.
    if (index == privateProperties->next) {
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
        privateMethods->addToArayeh(self, index, element);

        // update "map" if it isn't already counted for this index
        // and increase "used" counter.
        if (privateProperties->map[index] == AA_ARAYEH_OFF) {
            // update map.
            privateProperties->map[index] = AA_ARAYEH_ON;

            // update both public and private "used" counter.
            privateProperties->used++;
            self->used = privateProperties->used;
        }
    }

    // return error state code.
    return state;
}

int _fillArayeh(arayeh *self, size_t startIndex, size_t step, size_t endIndex,
                void *element)
{
    /*
     * This function will fill arayeh with an element
     * from index (inclusive) "startIndex" to index (exclusive) "endIndex"
     * with step size "step".
     *
     * it will update "map" and "used" parameters.
     * it may update "size" and "next" parameter.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * startIndex   starting index (inclusive).
     * step         step size.
     * endIndex     ending index (exclusive).
     * element      pointer to a variable that must fill the arayeh.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in configuration.h .
     *
     */

    // shorten names for god's sake.
    struct privateProperties *privateProperties = &self->_privateProperties;
    char debugMessages = privateProperties->settings->debugMessages;
    char extendSize    = privateProperties->settings->extendSize;
    char extendFill    = privateProperties->settings->methodSize->extendFill;

    // set debug flag.
    int debug = debugMessages == AA_ARAYEH_ON ? TRUE : FALSE;

    // track error state in the function.
    int state = AA_ARAYEH_SUCCESS;

    // check if starting index being greater than the ending index.
    if (endIndex < startIndex) {
        // write to stderr and return error code.
        WARN_WRONG_INDEX("_fillArayeh() function, startIndex index is greater than "
                         "endIndex index!",
                         debug);
        return AA_ARAYEH_WRONG_INDEX;
    }

    // check step size.
    if (step <= 0) {
        // write to stderr and return error code.
        WARN_WRONG_STEP("_fillArayeh() function, step should be bigger or equal to 1!",
                        debug);
        return AA_ARAYEH_WRONG_STEP;
    }

    // check if startIndex or endIndex indexes are greater than arayeh size.
    if (privateProperties->size <= startIndex || privateProperties->size < endIndex) {
        // decide to extend arayeh size based on arayeh settings.
        switch (extendSize) {
        case AA_ARAYEH_ON:
            // extend arayeh size until startIndex and endIndex indexes are less than
            // the arayeh size.
            do {
                state = extendMemory(self);
                // stop function and return error value if extending arayeh size
                // failed.
                if (state != AA_ARAYEH_SUCCESS) {
                    return state;
                }
            } while (privateProperties->size <= startIndex ||
                     privateProperties->size < endIndex);
            break;
        case AA_ARAYEH_OFF:
            // write to stderr and return error code.
            WARN_WRONG_INDEX("_fillArayeh() function, startIndex or endIndex is "
                             "greater than arayeh size!",
                             debug);
            return AA_ARAYEH_WRONG_INDEX;
            break;
            // if manual is enabled, check against the correct extend size rule.
        case AA_ARAYEH_MANUAL:
            switch (extendFill) {
            case AA_ARAYEH_ON:
                // extend arayeh size until startIndex and endIndex indexes are less
                // than the arayeh size.
                do {
                    state = extendMemory(self);
                    // stop function and return error value if extending arayeh size
                    // failed.
                    if (state != AA_ARAYEH_SUCCESS) {
                        return state;
                    }
                } while (privateProperties->size <= startIndex ||
                         privateProperties->size < endIndex);
                break;
            case AA_ARAYEH_OFF:
                // write to stderr and return error code.
                WARN_WRONG_INDEX("_fillArayeh() function, startIndex or endIndex is "
                                 "greater than arayeh size!",
                                 debug);
                return AA_ARAYEH_WRONG_INDEX;
                break;
            default:
                FATAL_WRONG_SETTINGS("_fillArayeh() function, extendFill "
                                     "value is not correct.",
                                     debug);
            }
        default:
            FATAL_WRONG_SETTINGS(
                "_fillArayeh() function, extendSize value is not correct.", debug);
        }
    }

    // fill the arayeh using a sequence of insert method.
    for (size_t index = startIndex; index < endIndex; index += step) {
        state = (self->insert)(self, index, element);
        if (state != AA_ARAYEH_SUCCESS) {
            break;
        }
    }

    // return error state code.
    return state;
}

int _mergeFromArray(arayeh *self, size_t startIndex, size_t arraySize, void *array)
{
    /*
     * This function will merge a default C array
     * (for example int a[4] = {1, 2, 3, 4};) into the arayeh, the starting index
     * for merging is "startIndex" and the size of C array determines the last index
     * (in the example above the size of C arayeh is 4).
     *
     * it will update "map" and "used" parameters.
     * it may update "size" and "next" parameter.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * startIndex   starting index in the arayeh arayeh.
     * arraySize    size of the C arayeh.
     * array        the C array to be merged into the arayeh.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in configuration.h .
     *
     */

    // shorten names for god's sake.
    struct privateMethods *privateMethods       = &self->_privateMethods;
    struct privateProperties *privateProperties = &self->_privateProperties;
    char debugMessages    = privateProperties->settings->debugMessages;
    char extendSize       = privateProperties->settings->extendSize;
    char extendMergeArray = privateProperties->settings->methodSize->extendMergeArray;

    // set debug flag.
    int debug = debugMessages == AA_ARAYEH_ON ? TRUE : FALSE;

    // track error state in the function.
    int state = AA_ARAYEH_SUCCESS;

    // calculate endIndex.
    size_t endIndex = startIndex + arraySize;

    // check if startIndex or endIndex indexes are greater than arayeh size.
    if (privateProperties->size <= startIndex || privateProperties->size < endIndex) {
        // decide to extend arayeh size based on arayeh settings.
        switch (extendSize) {
        case AA_ARAYEH_ON:
            // extend arayeh size until startIndex and endIndex indexes are less than
            // the arayeh size.
            do {
                state = extendMemory(self);
                // stop function and return error value if extending arayeh size
                // failed.
                if (state != AA_ARAYEH_SUCCESS) {
                    return state;
                }
            } while (privateProperties->size <= startIndex ||
                     privateProperties->size < endIndex);
            break;
        case AA_ARAYEH_OFF:
            // check if startIndex is greater than the arayeh size.
            if (privateProperties->size <= startIndex) {
                // write to stderr and return error code.
                WARN_WRONG_INDEX(
                    "_mergeFromArray() function, start index is greater than "
                    "the arayeh size!",
                    debug);
                return AA_ARAYEH_WRONG_INDEX;
            }

            // check if array size exceeds arayeh size if being started from
            // startIndex.
            if (privateProperties->size < endIndex) {
                // write to stderr and return error code.
                WARN_EXCEED_ARAYEH_SIZE(
                    "_mergeFromArray() function, starting from the specified "
                    "index, arayeh doesn't have enough space to merge this array.",
                    debug);
                return AA_ARAYEH_NOT_ENOUGH_SPACE;
            }
            break;
            // if manual is enabled, check against the correct extend size rule.
        case AA_ARAYEH_MANUAL:
            switch (extendMergeArray) {
            case AA_ARAYEH_ON:
                // extend arayeh size until startIndex and endIndex indexes are less
                // than the arayeh size.
                do {
                    state = extendMemory(self);
                    // stop function and return error value if extending arayeh size
                    // failed.
                    if (state != AA_ARAYEH_SUCCESS) {
                        return state;
                    }
                } while (privateProperties->size <= startIndex ||
                         privateProperties->size < endIndex);
                break;
            case AA_ARAYEH_OFF:
                // check if startIndex is greater than the arayeh size.
                if (privateProperties->size <= startIndex) {
                    // write to stderr and return error code.
                    WARN_WRONG_INDEX(
                        "_mergeFromArray() function, start index is greater than "
                        "the arayeh size!",
                        debug);
                    return AA_ARAYEH_WRONG_INDEX;
                }

                // check if array size exceeds arayeh size if being started from
                // startIndex.
                if (privateProperties->size < endIndex) {
                    // write to stderr and return error code.
                    WARN_EXCEED_ARAYEH_SIZE(
                        "_mergeFromArray() function, starting from the specified "
                        "index, arayeh doesn't have enough space to merge this "
                        "array.",
                        debug);
                    return AA_ARAYEH_NOT_ENOUGH_SPACE;
                }
                break;
            default:
                FATAL_WRONG_SETTINGS("_fillArayeh() function, extendMergeArray "
                                     "value is not correct.",
                                     debug);
            }
        default:
            FATAL_WRONG_SETTINGS(
                "_fillArayeh() function, extendSize value is not correct.", debug);
        }
    }

    // insert C array elements into arayeh.
    // updating arayeh parameters is delegated to "insert" method.
    state = privateMethods->mergeFromArray(self, startIndex, arraySize, array);

    // return error state code.
    return state;
}

int _getFromArayeh(arayeh *self, size_t index, void *destination)
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
    struct privateMethods *privateMethods       = &self->_privateMethods;
    struct privateProperties *privateProperties = &self->_privateProperties;
    char debugMessages = privateProperties->settings->debugMessages;

    // set debug flag.
    int debug = debugMessages == AA_ARAYEH_ON ? TRUE : FALSE;

    // check arayeh bounds.
    if (index >= privateProperties->size) {
        WARN_WRONG_INDEX("index out of range! _getFromArayeh()", debug);
        return AA_ARAYEH_WRONG_INDEX;
    }

    // copy data to destination memory location.
    privateMethods->getFromArayeh(self, index, destination);

    // return success code.
    return AA_ARAYEH_SUCCESS;
}

void _setSettings(arayeh *self, arayehSettings *newSettings)
{
    /*
     * This function will override arayeh default settings with new one.
     *
     * ARGUMENTS:
     * self             pointer to the arayeh object.
     * newSettings      new setting to apply to arayeh.
     *
     * RETURN:
     * no return, it's void dude.
     *
     */

    // shorten names for god's sake.
    arayehSettings *settings = self->_privateProperties.settings;

    // override new settings.
    settings->debugMessages = newSettings->debugMessages;
    settings->extendSize    = newSettings->extendSize;
}

void _setSizeSettings(arayeh *self, arayehSizeSettings *newSettings)
{
    /*
     * This function will override arayeh default extend size settings with new one.
     *
     * ARGUMENTS:
     * self             pointer to the arayeh object.
     * newSettings      new setting to apply to arayeh.
     *
     * RETURN:
     * no return, it's void dude.
     *
     */

    // shorten names for god's sake.
    arayehSizeSettings *settings = self->_privateProperties.settings->methodSize;

    // override new settings.
    settings->extendAdd        = newSettings->extendAdd;
    settings->extendInsert     = newSettings->extendInsert;
    settings->extendFill       = newSettings->extendFill;
    settings->extendMergeArray = newSettings->extendMergeArray;
}

void _setGrowthFactor(arayeh *self, size_t (*growthFactor)(arayeh *array))
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
    struct privateMethods *privateMethods = &self->_privateMethods;

    privateMethods->growthFactor = growthFactor;
}
