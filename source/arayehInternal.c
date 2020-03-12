/** source/arayehInternal.c
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

#include "../include/arayehInternal.h"

int _extendArayehSize(arayeh *array, size_t extendSize)
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

    // calculate new size for arayeh.
    size_t newSize = array->_internalProperties.size + extendSize;

    // size_t overflow protection.
    if (newSize < array->_internalProperties.size) {
        // wrong new size detected.
        // write to stderr and return error code.
        WARN_NEW_SIZE("_extendArayehSize()");
        return AA_ARAYEH_WRONG_NEW_SIZE;
    }

    // initialize variables for allocating memory.
    char *mapPointer = NULL;
    arrayType arrayPointer;

    // this function identifies the right pointer for arayeh type and sets it to
    // point to NULL and also checks for possible overflow in size_t newSize.
    int state = (array->_privateMethods.initArayeh)(array, &arrayPointer, newSize);

    // protection for possible overflow in size_t.
    if (state == AA_ARAYEH_FAILURE) {
        WARN_T_OVERFLOW("_extendArayehSize()");
        return AA_ARAYEH_OVERFLOW;
    }

    // reallocate memory to map and arayeh.
    mapPointer = (char *) realloc(array->_internalProperties.map,
                                  sizeof *mapPointer * newSize);
    state = (array->_privateMethods.reallocArayeh)(array, &arrayPointer, newSize);

    // check if memory re-allocated or not.
    if (state == AA_ARAYEH_FAILURE || mapPointer == NULL) {
        // free map and arayeh pointers.
        free(mapPointer);
        (array->_privateMethods.freeArayeh)(array);

        // write to stderr and return error code.
        WARN_REALLOC("_extendArayehSize()");
        return AA_ARAYEH_REALLOC_DENIED;
    }

    // set new map elements to '0' [IS_EMPTY].
    for (size_t i = array->_internalProperties.size; i < newSize; ++i) {
        mapPointer[i] = IS_EMPTY;
    }

    // update arayeh parameters.
    (array->_privateMethods.setArayehMemoryPointer)(array, &arrayPointer);
    array->_internalProperties.map  = mapPointer;
    array->_internalProperties.size = newSize;

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

    // free arayeh pointer.
    ((*self)->_privateMethods.freeArayeh)(*self);

    // free map pointer and nullify the pointer.
    free((*self)->_internalProperties.map);
    (*self)->_internalProperties.map = NULL;

    // reset arayeh parameters.
    (*self)->_internalProperties.type = 0;
    (*self)->_internalProperties.next = 0;
    (*self)->_internalProperties.used = 0;
    (*self)->_internalProperties.size = 0;

    // free arayeh pointer and nullify the arayeh pointer.
    free(*self);
    *self = NULL;

    // return success code.
    return AA_ARAYEH_SUCCESS;
}

int _addToArayeh(arayeh *array, void *element)
{
    /*
     * This function will insert an "element" into arayeh at
     * index = self->_internalProperties.next.
     *
     * function will extend size of arayeh in case of
     * self->_internalProperties.size == self->_internalProperties.used.
     *
     * it will update "map" and "used" and "next" parameters.
     * it may update "size" parameter.
     *
     * self->_internalProperties.next will be updated in a manner that it points to
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

    // track error state in the function.
    int state;

    // extend arayeh size if needed.
    if (array->_internalProperties.used == array->_internalProperties.size) {

        // extend arayeh size.
        state = (array->extendSize)(array, array->_internalProperties.size);

        // stop function and return error value if extending arayeh size failed.
        if (state != AA_ARAYEH_SUCCESS) {
            return state;
        }
    }

    // add element.
    (array->_privateMethods.addElementToArayeh)(
        array, array->_internalProperties.next, element);

    // update "map" and "used".
    array->_internalProperties.map[array->_internalProperties.next] = IS_FILLED;
    array->_internalProperties.used++;

    // update "next" pointer.
    _UpdateNextLocationPointer(array);

    // return success code.
    return AA_ARAYEH_SUCCESS;
}

int _insertToArayeh(arayeh *array, size_t index, void *element)
{
    /*
     * This function will insert an "element" into arayeh at "index".
     *
     * this function WON'T increase arayeh size!
     *
     * it will update "map" and "used" parameters.
     * it may update "size" and "next" parameter.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * element      pointer to a variable to be inserted into the arayeh.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * element      pointer to a variable to be added to the arayeh.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in configuration.h .
     *
     */

    // track error state in the function.
    int state = AA_ARAYEH_SUCCESS;

    // check index number to be within arayeh bounds.
    if (index < 0) {
        // write to stderr and return error code.
        WARN_WRONG_INDEX("_insertToArayeh() function, index is less than 0!");
        return AA_ARAYEH_WRONG_INDEX;
    }

    if (index >= array->_internalProperties.size) {
        // write to stderr and return error code.
        WARN_WRONG_INDEX(
            "_insertToArayeh() function, index is bigger than arayeh size!");
        return AA_ARAYEH_WRONG_INDEX;
    }

    // insert element.
    if (index == array->_internalProperties.next) {
        // use _addToArayeh for insertion if the index is same as next empty
        // slot in the arayeh.
        // this function will automatically update next pointer.
        // also it may need to extend arayeh memory size.
        state = _addToArayeh(array, element);
    } else {
        // if index is less (more) than the next pointer, just assign element
        // and check for arayeh map to see if the index had previous value
        // (IS_FILLED) or not, if it had, then "used" and map will stay same, but
        // if it was uninitialized, update map and "used" counter.

        // assign element.
        (array->_privateMethods.addElementToArayeh)(array, index, element);
        // update arayeh parameters.
        if (array->_internalProperties.map[index] == IS_EMPTY) {
            // update "map" and "used" if they aren't already counted for this index.
            array->_internalProperties.map[index] = IS_FILLED;
            array->_internalProperties.used++;
        }
    }

    // return error state code.
    return state;
}

int _fillArayeh(arayeh *array, size_t start, size_t step, size_t end, void *element)
{
    /*
     * This function will fill arayeh with an element
     * from index (inclusive) "start" to index (exclusive) "end"
     * with step size "step".
     *
     * it will update "map" and "used" parameters.
     * it may update "size" and "next" parameter.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * start        starting index (inclusive).
     * step         step size.
     * end          ending index (exclusive).
     * element      pointer to a variable that must fill the arayeh.
     *
     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in configuration.h .
     *
     */

    // track error state in the function.
    int state = AA_ARAYEH_SUCCESS;

    // check starting index to be within arayeh bounds.
    if (start < 0) {
        // write to stderr and return error code.
        WARN_WRONG_INDEX("_fillArayeh() function, start is less than 0!");
        return AA_ARAYEH_WRONG_INDEX;
    }

    if (start >= array->_internalProperties.size) {
        // write to stderr and return error code.
        WARN_WRONG_INDEX(
            "_fillArayeh() function, start is bigger than arayeh size!");
        return AA_ARAYEH_WRONG_INDEX;
    }

    // check step size.
    if (step <= 0) {
        // write to stderr and return error code.
        WARN_WRONG_INDEX(
            "_fillArayeh() function, step should be bigger or equal to 1!");
        return AA_ARAYEH_WRONG_STEP;
    }

    // fill the arayeh.
    for (size_t index = start; index < end; index += step) {

        // if index is less (more) than array.next, use insert function so it
        // won't affect next pointer, if index is equal to array.next, use add
        // to also update next pointer.
        if (index < array->_internalProperties.next ||
            index > array->_internalProperties.next) {
            state = (array->insert)(array, index, element);
        } else {
            state = (array->add)(array, element);
        }
    }

    // return error state code.
    return state;
}

void _mergeListToArayeh(arayeh *self, size_t startIndex, size_t listSize, void *list)
{
    /*
     * This function will merge a default C arayeh
     * (for example int a[4] = {1, 2, 3, 4};) into arayeh arayeh, the starting index
     * for merging is "startIndex" and the size of C arayeh determines the last index
     * (in the example above the size of C arayeh is 4).
     *
     * this function WON'T increase arayeh size!
     *
     * it may update "map" and "used" and "next" parameters.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * startIndex   starting index in the arayeh arayeh.
     * listSize     size of the C arayeh.
     * list         the C array to be merged into the arayeh.
     *
     */

    // check arayeh bounds.
    if (self->_internalProperties.size <= startIndex ||
        self->_internalProperties.size < startIndex + listSize) {
        // TODO error handling
        abort();
    }

    // insert C array elements into arayeh.
    (self->_privateMethods.mergeListToArayeh)(self, startIndex, listSize, list);
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

    // check arayeh bounds.
    if (index >= self->_internalProperties.size) {
        WARN_WRONG_INDEX("index out of range! _getElementFromArayeh()");
        return AA_ARAYEH_WRONG_INDEX;
    }

    // copy data to destination memory location.
    (self->_privateMethods.getElementFromArayeh)(self, index, destination);

    // return success code.
    return AA_ARAYEH_SUCCESS;
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

    self->extendSize = _extendArayehSize;
    self->freeArayeh = _freeArayehMemory;
    self->fill       = _fillArayeh;
    self->add        = _addToArayeh;
    self->insert     = _insertToArayeh;
    self->mergeList  = _mergeListToArayeh;
    self->get        = _getElementFromArayeh;
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

    // assign based on the arayeh type.
    switch (type) {
    case TYPE_CHAR:
        self->_privateMethods.initArayeh             = _initTypeChar;
        self->_privateMethods.mallocArayeh           = _mallocTypeChar;
        self->_privateMethods.reallocArayeh          = _reallocTypeChar;
        self->_privateMethods.freeArayeh             = _freeTypeChar;
        self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeChar;
        self->_privateMethods.addElementToArayeh     = _addTypeChar;
        self->_privateMethods.mergeListToArayeh      = _mergeListTypeChar;
        self->_privateMethods.getElementFromArayeh   = _getTypeChar;
        break;

    case TYPE_SINT:
        self->_privateMethods.initArayeh             = _initTypeSInt;
        self->_privateMethods.mallocArayeh           = _mallocTypeSInt;
        self->_privateMethods.reallocArayeh          = _reallocTypeSInt;
        self->_privateMethods.freeArayeh             = _freeTypeSInt;
        self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeSInt;
        self->_privateMethods.addElementToArayeh     = _addTypeSInt;
        self->_privateMethods.mergeListToArayeh      = _mergeListTypeSInt;
        self->_privateMethods.getElementFromArayeh   = _getTypeSInt;
        break;

    case TYPE_INT:
        self->_privateMethods.initArayeh             = _initTypeInt;
        self->_privateMethods.mallocArayeh           = _mallocTypeInt;
        self->_privateMethods.reallocArayeh          = _reallocTypeInt;
        self->_privateMethods.freeArayeh             = _freeTypeInt;
        self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeInt;
        self->_privateMethods.addElementToArayeh     = _addTypeInt;
        self->_privateMethods.mergeListToArayeh      = _mergeListTypeInt;
        self->_privateMethods.getElementFromArayeh   = _getTypeInt;
        break;

    case TYPE_LINT:
        self->_privateMethods.initArayeh             = _initTypeLInt;
        self->_privateMethods.mallocArayeh           = _mallocTypeLInt;
        self->_privateMethods.reallocArayeh          = _reallocTypeLInt;
        self->_privateMethods.freeArayeh             = _freeTypeLInt;
        self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeLInt;
        self->_privateMethods.addElementToArayeh     = _addTypeLInt;
        self->_privateMethods.mergeListToArayeh      = _mergeListTypeLInt;
        self->_privateMethods.getElementFromArayeh   = _getTypeLInt;
        break;

    case TYPE_FLOAT:
        self->_privateMethods.initArayeh             = _initTypeFloat;
        self->_privateMethods.mallocArayeh           = _mallocTypeFloat;
        self->_privateMethods.reallocArayeh          = _reallocTypeFloat;
        self->_privateMethods.freeArayeh             = _freeTypeFloat;
        self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeFloat;
        self->_privateMethods.addElementToArayeh     = _addTypeFloat;
        self->_privateMethods.mergeListToArayeh      = _mergeListTypeFloat;
        self->_privateMethods.getElementFromArayeh   = _getTypeFloat;
        break;

    case TYPE_DOUBLE:
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

void _UpdateNextLocationPointer(arayeh *array)
{
    /*
     * This function purpose is to update
     * array.next variable to point to next empty [available]
     * slot in the arayeh.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     */

    while (array->_internalProperties.next < array->_internalProperties.size &&
           array->_internalProperties.map[array->_internalProperties.next] ==
               IS_FILLED) {
        array->_internalProperties.next++;
    }
}
