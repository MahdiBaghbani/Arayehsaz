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

int _extendArayehSize(arayeh *self, size_t extendSize)
{
    /*
     * This function will reallocate memory to the arayeh and its map.
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

    // set debug flag.
    int debug = self->_privateProperties.settings->allowDebugMessages == AA_ARAYEH_ON
                    ? TRUE
                    : FALSE;

    // track error state in the function.
    int state;

    // calculate new size for arayeh.
    size_t newSize = self->_privateProperties.size + extendSize;

    // size_t overflow protection.
    if (newSize < self->_privateProperties.size) {
        // wrong new size detected.
        // write to stderr and return error code.
        WARN_NEW_SIZE("_extendArayehSize()", debug);
        return AA_ARAYEH_WRONG_NEW_SIZE;
    }

    // initialize variables for allocating memory.
    char *mapPointer = NULL;
    arayehType arrayPointer;

    // this function identifies the right pointer for arayeh type and sets it to
    // point to NULL and also checks for possible overflow in size_t newSize.
    state = (self->_privateMethods.initArayeh)(self, &arrayPointer, newSize);

    // protection for possible overflow in size_t.
    if (state == AA_ARAYEH_FAILURE) {
        WARN_T_OVERFLOW("_extendArayehSize()", debug);
        return AA_ARAYEH_OVERFLOW;
    }

    // reallocate memory to map and arayeh.
    mapPointer =
        (char *) realloc(self->_privateProperties.map, sizeof *mapPointer * newSize);
    state = (self->_privateMethods.reallocArayeh)(self, &arrayPointer, newSize);

    // check if memory re-allocated or not.
    if (state == AA_ARAYEH_FAILURE || mapPointer == NULL) {
        // free map and arayeh pointers.
        free(mapPointer);
        (self->_privateMethods.freeArayeh)(self);

        // write to stderr and return error code.
        WARN_REALLOC("_extendArayehSize()", debug);
        return AA_ARAYEH_REALLOC_DENIED;
    }

    // set new map elements to '0' [AA_ARAYEH_OFF].
    for (size_t i = self->_privateProperties.size; i < newSize; ++i) {
        mapPointer[i] = AA_ARAYEH_OFF;
    }

    // update arayeh parameters.
    (self->_privateMethods.setArayehMemoryPointer)(self, &arrayPointer);
    self->_privateProperties.map  = mapPointer;
    self->_privateProperties.size = newSize;
    self->size                    = newSize;

    // return success code.
    return AA_ARAYEH_SUCCESS;
}

int _freeArayehMemory(arayeh **self)
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

    // free the arayeh's internal array pointer.
    ((*self)->_privateMethods.freeArayeh)(*self);

    // free map array pointer and nullify the pointer.
    free((*self)->_privateProperties.map);
    (*self)->_privateProperties.map = NULL;

    // free arayeh extension settings and nullify the pointer.
    free((*self)->_privateProperties.settings);
    (*self)->_privateProperties.settings = NULL;

    // reset arayeh parameters.
    (*self)->type                    = 0;
    (*self)->next                    = 0;
    (*self)->used                    = 0;
    (*self)->size                    = 0;
    (*self)->_privateProperties.type = 0;
    (*self)->_privateProperties.next = 0;
    (*self)->_privateProperties.used = 0;
    (*self)->_privateProperties.size = 0;

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
    char allowExtendSize = self->_privateProperties.settings->allowExtendSize;
    char allowExtendOnAdd =
        self->_privateProperties.extendSizeSettings->allowExtendOnAdd;

    // set debug flag.
    int debug = self->_privateProperties.settings->allowDebugMessages == AA_ARAYEH_ON
                    ? TRUE
                    : FALSE;

    // track error state in the function.
    int state;

    // check if arayeh is full.
    if (self->_privateProperties.used == self->_privateProperties.size) {
        // decide to extend arayeh size based on arayeh settings.
        switch (allowExtendSize) {
        case AA_ARAYEH_ON:
            // extend arayeh size.
            state = _calculateAndExtendSize(self);
            // stop function and return error value if extending arayeh size failed.
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
        // if manual is enabled, check against the correct extend size rule.
        case AA_ARAYEH_MANUAL_SETTINGS:
            switch (allowExtendOnAdd) {
            case AA_ARAYEH_ON:
                // extend arayeh size.
                state = _calculateAndExtendSize(self);
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
                FATAL_WRONG_SETTINGS("_addToArayeh() function, allowExtendOnAdd "
                                     "value is not correct.",
                                     debug);
            }
        default:
            FATAL_WRONG_SETTINGS(
                "_addToArayeh() function, allowExtendSize value is not correct.",
                debug);
        }
    }

    // add element.
    (self->_privateMethods.addElementToArayeh)(self, self->_privateProperties.next,
                                               element);

    // update "map" and "used".
    self->_privateProperties.map[self->_privateProperties.next] = AA_ARAYEH_ON;
    self->_privateProperties.used++;

    // update "next" pointer.
    _UpdateNextLocationPointer(self);

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
    char allowExtendSize = self->_privateProperties.settings->allowExtendSize;
    char allowExtendOnInsert =
        self->_privateProperties.extendSizeSettings->allowExtendOnInsert;

    // set debug flag.
    int debug = self->_privateProperties.settings->allowDebugMessages == AA_ARAYEH_ON
                    ? TRUE
                    : FALSE;

    // track error state in the function.
    int state = AA_ARAYEH_SUCCESS;

    // check if index is bigger or equal to size of arayeh.
    if (self->_privateProperties.size <= index) {
        // decide to extend arayeh size based on arayeh settings.
        switch (allowExtendSize) {
        case AA_ARAYEH_ON:
            // extend arayeh size until "index" is less than the arayeh size.
            do {
                state = _calculateAndExtendSize(self);
                // stop function and return error value if extending arayeh size
                // failed.
                if (state != AA_ARAYEH_SUCCESS) {
                    return state;
                }
            } while (self->_privateProperties.size <= index);
            break;
        case AA_ARAYEH_OFF:
            // write to stderr and return error code.
            WARN_WRONG_INDEX("_insertToArayeh() function, index is equal or bigger "
                             "than arayeh size!",
                             debug);
            return AA_ARAYEH_WRONG_INDEX;
            break;
            // if manual is enabled, check against the correct extend size rule.
        case AA_ARAYEH_MANUAL_SETTINGS:
            switch (allowExtendOnInsert) {
            case AA_ARAYEH_ON:
                // extend arayeh size until "index" is less than the arayeh size.
                do {
                    state = _calculateAndExtendSize(self);
                    // stop function and return error value if extending arayeh size
                    // failed.
                    if (state != AA_ARAYEH_SUCCESS) {
                        return state;
                    }
                } while (self->_privateProperties.size <= index);
                break;
            case AA_ARAYEH_OFF:
                // write to stderr and return error code.
                WARN_WRONG_INDEX(
                    "_insertToArayeh() function, index is equal or bigger "
                    "than arayeh size!",
                    debug);
                return AA_ARAYEH_WRONG_INDEX;
                break;
            default:
                FATAL_WRONG_SETTINGS(
                    "_insertToArayeh() function, allowExtendOnInsert "
                    "value is not correct.",
                    debug);
            }
        default:
            FATAL_WRONG_SETTINGS(
                "_insertToArayeh() function, allowExtendSize value is not correct.",
                debug);
        }
    }

    // insert element.
    if (index == self->_privateProperties.next) {
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
        (self->_privateMethods.addElementToArayeh)(self, index, element);
        // update arayeh parameters.
        if (self->_privateProperties.map[index] == AA_ARAYEH_OFF) {
            // update "map" and "used" if they aren't already counted for this index.
            self->_privateProperties.map[index] = AA_ARAYEH_ON;
            self->_privateProperties.used++;
            self->used = self->_privateProperties.used;
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
    char allowExtendSize = self->_privateProperties.settings->allowExtendSize;
    char allowExtendOnFill =
        self->_privateProperties.extendSizeSettings->allowExtendOnFill;

    // set debug flag.
    int debug = self->_privateProperties.settings->allowDebugMessages == AA_ARAYEH_ON
                    ? TRUE
                    : FALSE;

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
        WARN_WRONG_STEP(
            "_fillArayeh() function, step should be bigger or equal to 1!", debug);
        return AA_ARAYEH_WRONG_STEP;
    }

    // check if startIndex or endIndex indexes are greater than arayeh size.
    if (self->_privateProperties.size <= startIndex ||
        self->_privateProperties.size < endIndex) {
        // decide to extend arayeh size based on arayeh settings.
        switch (allowExtendSize) {
        case AA_ARAYEH_ON:
            // extend arayeh size until startIndex and endIndex indexes are less than
            // the arayeh size.
            do {
                state = _calculateAndExtendSize(self);
                // stop function and return error value if extending arayeh size
                // failed.
                if (state != AA_ARAYEH_SUCCESS) {
                    return state;
                }
            } while (self->_privateProperties.size <= startIndex ||
                     self->_privateProperties.size < endIndex);
            break;
        case AA_ARAYEH_OFF:
            // write to stderr and return error code.
            WARN_WRONG_INDEX("_fillArayeh() function, startIndex or endIndex is "
                             "greater than arayeh size!",
                             debug);
            return AA_ARAYEH_WRONG_INDEX;
            break;
            // if manual is enabled, check against the correct extend size rule.
        case AA_ARAYEH_MANUAL_SETTINGS:
            switch (allowExtendOnFill) {
            case AA_ARAYEH_ON:
                // extend arayeh size until startIndex and endIndex indexes are less
                // than the arayeh size.
                do {
                    state = _calculateAndExtendSize(self);
                    // stop function and return error value if extending arayeh size
                    // failed.
                    if (state != AA_ARAYEH_SUCCESS) {
                        return state;
                    }
                } while (self->_privateProperties.size <= startIndex ||
                         self->_privateProperties.size < endIndex);
                break;
            case AA_ARAYEH_OFF:
                // write to stderr and return error code.
                WARN_WRONG_INDEX("_fillArayeh() function, startIndex or endIndex is "
                                 "greater than arayeh size!",
                                 debug);
                return AA_ARAYEH_WRONG_INDEX;
                break;
            default:
                FATAL_WRONG_SETTINGS("_fillArayeh() function, allowExtendOnFill "
                                     "value is not correct.",
                                     debug);
            }
        default:
            FATAL_WRONG_SETTINGS(
                "_fillArayeh() function, allowExtendSize value is not correct.",
                debug);
        }
    }

    // TODO how about just using "insert"? since insert also uses "add" method
    // TODO implicitly.
    // fill the arayeh.
    for (size_t index = startIndex; index < endIndex; index += step) {

        // if index is less (more) than array.next, use insert function so it
        // won't affect next pointer, if index is equal to array.next, use add
        // to also update next pointer.
        if (index < self->_privateProperties.next ||
            index > self->_privateProperties.next) {
            state = (self->insert)(self, index, element);
        } else {
            state = (self->add)(self, element);
        }
    }

    // return error state code.
    return state;
}

int _mergeListToArayeh(arayeh *self, size_t startIndex, size_t listSize, void *list)
{
    /*
     * This function will merge a default C arayeh
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
     * listSize     size of the C arayeh.
     * list         the C array to be merged into the arayeh.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in configuration.h .
     *
     */

    // set debug flag.
    int debug = self->_privateProperties.settings->allowDebugMessages == AA_ARAYEH_ON
                    ? TRUE
                    : FALSE;

    // track error state in the function.
    int state = AA_ARAYEH_SUCCESS;

    // calculate endIndex.
    size_t endIndex = startIndex + listSize;

    // check if startIndex or endIndex indexes are greater than arayeh size.
    if (self->_privateProperties.size <= startIndex ||
        self->_privateProperties.size < endIndex) {
        // decide to extend arayeh size based on arayeh settings.
        if (self->_privateProperties.settings->allowExtendSize == AA_ARAYEH_ON) {
            // extend arayeh size until startIndex and endIndex indexes are less than
            // the arayeh size.
            do {
                state = _calculateAndExtendSize(self);
                // stop function and return error value if extending arayeh size
                // failed.
                if (state != AA_ARAYEH_SUCCESS) {
                    return state;
                }
            } while (self->_privateProperties.size <= startIndex ||
                     self->_privateProperties.size < endIndex);
        } else {
            // check if startIndex is greater than the arayeh size.
            if (self->_privateProperties.size <= startIndex) {
                // write to stderr and return error code.
                WARN_WRONG_INDEX(
                    "_mergeListToArayeh() function, start index is greater than "
                    "the arayeh size!",
                    debug);
                return AA_ARAYEH_WRONG_INDEX;
            }

            // check if list size exceeds arayeh size if being started from
            // startIndex.
            if (self->_privateProperties.size < endIndex) {
                // write to stderr and return error code.
                WARN_EXCEED_ARAYEH_SIZE(
                    "_mergeListToArayeh() function, starting from the specified "
                    "index, arayeh doesn't have enough space to merge this list.",
                    debug);
                return AA_ARAYEH_NOT_ENOUGH_SPACE;
            }
        }
    }

    // insert C array elements into arayeh.
    state =
        (self->_privateMethods.mergeListToArayeh)(self, startIndex, listSize, list);

    // return error state code.
    return state;
}

int _getElementFromArayeh(arayeh *self, size_t index, void *destination)
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

    // set debug flag.
    int debug = self->_privateProperties.settings->allowDebugMessages == AA_ARAYEH_ON
                    ? TRUE
                    : FALSE;

    // check arayeh bounds.
    if (index >= self->_privateProperties.size) {
        WARN_WRONG_INDEX("index out of range! _getElementFromArayeh()", debug);
        return AA_ARAYEH_WRONG_INDEX;
    }

    // copy data to destination memory location.
    (self->_privateMethods.getElementFromArayeh)(self, index, destination);

    // return success code.
    return AA_ARAYEH_SUCCESS;
}

void _setArayehSettings(arayeh *self, arayehSettings *newSettings)
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

    // shorten name for god's sake.
    arayehSettings *settings = self->_privateProperties.settings;

    // override new settings.
    settings->allowDebugMessages = newSettings->allowDebugMessages;
    settings->allowExtendSize    = newSettings->allowExtendSize;
}

void _setArayehExtendSizeSettings(arayeh *self,
                                  arayehExtendSizeSettings *newSettings)
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

    // shorten name for god's sake.
    arayehExtendSizeSettings *settings = self->_privateProperties.extendSizeSettings;

    // override new settings.
    settings->allowExtendOnAdd       = newSettings->allowExtendOnAdd;
    settings->allowExtendOnInsert    = newSettings->allowExtendOnInsert;
    settings->allowExtendOnFill      = newSettings->allowExtendOnFill;
    settings->allowExtendOnMergeList = newSettings->allowExtendOnMergeList;
}

size_t _defaultGrowthFactor(arayeh *arayeh)
{
    /*
     * This function will calculate the extension size of memory.
     *
     * This is the default function to calculate memory growth size,
     * users can use their appropriate functions and ignore this.
     *
     * ARGUMENTS:
     * self             pointer to the arayeh object.
     *
     * RETURN:
     * extension_size   the size of extra memory space to be
     *                  added to the current memory space.
     *
     */

    // derived from python source code.
    // calculate the extension size of memory.
    // This over-allocates proportional to the ARAYEH size,
    // making room for additional growth. The over-allocation is mild,
    // but is enough to give linear-time amortized behavior over a long
    // sequence of adding elements to arayeh in the presence of
    // a poorly-performing system realloc().
    // The growth pattern is:  0, 4, 8, 16, 25, 35, 46, 58, 72, 88, ...

    size_t current_size   = arayeh->_privateProperties.size;
    size_t extension_size = (current_size >> 3) + (current_size < 9 ? 3 : 6);
    return extension_size;
}

void _setGrowthFactorFunction(arayeh *self, size_t (*growthFactor)(arayeh *array))
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
    (self->_privateMethods.growthFactor) = growthFactor;
}

int _calculateAndExtendSize(arayeh *self)
{
    /*
     * This function will calculate the extension size of memory and extends arayeh
     * size.
     *
     * ARGUMENTS:
     * self             pointer to the arayeh object.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in configuration.h .
     *
     */

    // track error state in the function.
    int state;

    // calculate the extension memory size using growth factor function.
    size_t extension_size = (self->_privateMethods.growthFactor)(self);

    // extend arayeh size.
    state = (self->extendSize)(self, extension_size);

    // return error state.
    return state;
}

void _setPublicMethods(arayeh *self)
{
    /*
     * This function assigns pointers to public functions of an arayeh instance.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     *
     */

    self->extendSize                  = _extendArayehSize;
    self->freeArayeh                  = _freeArayehMemory;
    self->add                         = _addToArayeh;
    self->insert                      = _insertToArayeh;
    self->fill                        = _fillArayeh;
    self->mergeList                   = _mergeListToArayeh;
    self->get                         = _getElementFromArayeh;
    self->setArayehSettings           = _setArayehSettings;
    self->setArayehExtendSizeSettings = _setArayehExtendSizeSettings;
    self->setGrowthFactorFunction     = _setGrowthFactorFunction;
}

void _setPrivateMethods(arayeh *self, size_t type)
{
    /*
     * This function assigns pointers to public functions of an arayeh instance.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * type         type of arayeh elements.
     *
     */

    // set memory space growth factor function to default.
    self->_privateMethods.growthFactor = _defaultGrowthFactor;

    // assign based on the arayeh type.
    switch (type) {
    case AA_ARAYEH_TYPE_CHAR:
        self->_privateMethods.initArayeh             = _initTypeChar;
        self->_privateMethods.mallocArayeh           = _mallocTypeChar;
        self->_privateMethods.reallocArayeh          = _reallocTypeChar;
        self->_privateMethods.freeArayeh             = _freeTypeChar;
        self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeChar;
        self->_privateMethods.addElementToArayeh     = _addTypeChar;
        self->_privateMethods.mergeListToArayeh      = _mergeListTypeChar;
        self->_privateMethods.getElementFromArayeh   = _getTypeChar;
        break;

    case AA_ARAYEH_TYPE_SINT:
        self->_privateMethods.initArayeh             = _initTypeSInt;
        self->_privateMethods.mallocArayeh           = _mallocTypeSInt;
        self->_privateMethods.reallocArayeh          = _reallocTypeSInt;
        self->_privateMethods.freeArayeh             = _freeTypeSInt;
        self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeSInt;
        self->_privateMethods.addElementToArayeh     = _addTypeSInt;
        self->_privateMethods.mergeListToArayeh      = _mergeListTypeSInt;
        self->_privateMethods.getElementFromArayeh   = _getTypeSInt;
        break;

    case AA_ARAYEH_TYPE_INT:
        self->_privateMethods.initArayeh             = _initTypeInt;
        self->_privateMethods.mallocArayeh           = _mallocTypeInt;
        self->_privateMethods.reallocArayeh          = _reallocTypeInt;
        self->_privateMethods.freeArayeh             = _freeTypeInt;
        self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeInt;
        self->_privateMethods.addElementToArayeh     = _addTypeInt;
        self->_privateMethods.mergeListToArayeh      = _mergeListTypeInt;
        self->_privateMethods.getElementFromArayeh   = _getTypeInt;
        break;

    case AA_ARAYEH_TYPE_LINT:
        self->_privateMethods.initArayeh             = _initTypeLInt;
        self->_privateMethods.mallocArayeh           = _mallocTypeLInt;
        self->_privateMethods.reallocArayeh          = _reallocTypeLInt;
        self->_privateMethods.freeArayeh             = _freeTypeLInt;
        self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeLInt;
        self->_privateMethods.addElementToArayeh     = _addTypeLInt;
        self->_privateMethods.mergeListToArayeh      = _mergeListTypeLInt;
        self->_privateMethods.getElementFromArayeh   = _getTypeLInt;
        break;

    case AA_ARAYEH_TYPE_FLOAT:
        self->_privateMethods.initArayeh             = _initTypeFloat;
        self->_privateMethods.mallocArayeh           = _mallocTypeFloat;
        self->_privateMethods.reallocArayeh          = _reallocTypeFloat;
        self->_privateMethods.freeArayeh             = _freeTypeFloat;
        self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeFloat;
        self->_privateMethods.addElementToArayeh     = _addTypeFloat;
        self->_privateMethods.mergeListToArayeh      = _mergeListTypeFloat;
        self->_privateMethods.getElementFromArayeh   = _getTypeFloat;
        break;

    case AA_ARAYEH_TYPE_DOUBLE:
        self->_privateMethods.initArayeh             = _initTypeDouble;
        self->_privateMethods.mallocArayeh           = _mallocTypeDouble;
        self->_privateMethods.reallocArayeh          = _reallocTypeDouble;
        self->_privateMethods.freeArayeh             = _freeTypeDouble;
        self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeDouble;
        self->_privateMethods.addElementToArayeh     = _addTypeDouble;
        self->_privateMethods.mergeListToArayeh      = _mergeListTypeDouble;
        self->_privateMethods.getElementFromArayeh   = _getTypeDouble;
        break;
    default:
        // TODO Error Handler
        break;
    }
}

void _UpdateNextLocationPointer(arayeh *self)
{
    /*
     * This function purpose is to update
     * array.next variable to point to next empty [available]
     * slot in the arayeh.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     */

    while (self->_privateProperties.next < self->_privateProperties.size &&
           self->_privateProperties.map[self->_privateProperties.next] ==
               AA_ARAYEH_ON) {
        self->_privateProperties.next++;
    }

    // update public next property.
    self->next = self->_privateProperties.next;
}
