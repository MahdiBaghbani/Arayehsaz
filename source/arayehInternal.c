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

#include "arayehInternal.h"

void _extendArayehSize(arayeh *array, size_t extendSize) {
    /*
     * This function will reallocate memory to the array and its map.
     *
     * ARGUMENTS:
     * self             pointer to the array object.
     * extendSize       size increment.
     *
     */

    // calculate new size for array.
    size_t newSize = array->_internalProperties.size + extendSize;

    // size_t overflow protection.
    if (newSize < array->_internalProperties.size) {
        // TODO error handler
        abort();
    }

    // initialize variables for allocating memory.
    char *mapPointer = NULL;
    arrayType arrayPointer;
    // this function identifies the right pointer for array type and sets it to point to NULL
    // and also checks for possible overflow in size_t newSize.
    int state = (array->_privateMethods.initArayeh)(array, &arrayPointer, newSize);

    // protection for possible overflow in size_t.
    if (state == AA_ARAYEH_FAILURE) {
        // TODO error handler
        abort();
    }

    // reallocate memory to map and array.
    mapPointer = (char *) realloc(array->_internalProperties.map, sizeof *mapPointer * newSize);
    state = (array->_privateMethods.reallocArayeh)(array, &arrayPointer, newSize);

    // check if memory allocated or not.
    if (state == AA_ARAYEH_FAILURE || mapPointer == NULL) {
        // free map and array pointers.
        free(mapPointer);
        (array->_privateMethods.freeArayeh)(array);

        // failure.
        // TODO error handler
        abort();
    }

    // set new map elements to '0' [IS_EMPTY].
    for (size_t i = array->_internalProperties.size; i < newSize; ++i) {
        array->_internalProperties.map[i] = IS_EMPTY;
    }

    // set array parameters.
    (array->_privateMethods.setArayehMemoryPointer)(array, &arrayPointer);
    array->_internalProperties.map = mapPointer;
    array->_internalProperties.size = newSize;
}

int _freeArayehMemory(arayeh **self) {
    /*
     * This function will free the array and reset its parameters.
     *
     * ARGUMENTS:
     * self         pointer to the pointer to the array object.

     * RETURN:
     * state        a code that indicates successful operation
     *              or an error code defined in configuration.h
     */

    // no way to test if "free" really worked or not ...
    // so I let this to be success.
    int state = AA_ARAYEH_SUCCESS;

    // free array pointer.
    ((*self)->_privateMethods.freeArayeh)(*self);

    // free map pointer and nullify the pointer.
    free((*self)->_internalProperties.map);
    (*self)->_internalProperties.map = NULL;

    // reset array parameters.
    (*self)->_internalProperties.type = 0;
    (*self)->_internalProperties.next = 0;
    (*self)->_internalProperties.used = 0;
    (*self)->_internalProperties.size = 0;

    // free array pointer and nullify the array pointer.
    free(*self);
    *self = NULL;

    // return function state.
    return state;
}


void _fillArayeh(arayeh *array, size_t start, size_t step, size_t end, void *element) {
    /*
     * This function will fill array with an element
     * from index (inclusive) "start" to index (exclusive) "end"
     * with step size "step".
     *
     * this function WON'T increase array size!
     *
     * it will update "map" and "used" parameters.
     * it may update "next" parameter.
     *
     * ARGUMENTS:
     * self           pointer to the array object.
     * start          starting index (inclusive).
     * step           step size.
     * end            ending index (exclusive).
     * element        pointer to a variable that must fill the array.
     *
     */

    if (start < 0 || end > array->_internalProperties.size) {
        // TODO Error handler
        abort();
    }

    if (step <= 0) {
        // TODO Error handler
        //printf("Error: step size can't be less than 1.\n");
        abort();
    }

    // fill the array.
    for (size_t i = start; i < end; i += step) {
        // assign element to array.
        (array->_privateMethods.addElementToArayeh)(array, i, element);

        // update array parameters.
        if (array->_internalProperties.map[i] == IS_EMPTY) {
            // element has been assigned to an empty slot in array,
            // so update the map and +1 to used slots.
            array->_internalProperties.map[i] = IS_FILLED;
            array->_internalProperties.used++;
        }
    }

    // update "next" parameter of array.
    if (start <= array->_internalProperties.next) {
        // 0 is empty, 1 is data existing in the array, 2 is fill data.
        //
        // before fill >>
        // 111111111111111111111111110000000000000000000111111111111
        //          ^                ^              ^
        //        start          next pointer      end
        //
        // after fill >>
        // 111111111222222222222222222222222222222220000111111111111
        //                                          ^
        //                                      next pointer
        //
        // the above case is for step = 1, if step is more than 1,
        // if (next - start) % step == 0, we can add 1 to 'next', because it will be filled.
        //
        // finally we will check next map slot to make sure it's empty and 'next' is valid
        // and we will keep adding 1 to next until map[next] == IS_EMPTY.
        //
        if (step == 1) {
            array->_internalProperties.next = end;
        } else if ((array->_internalProperties.next - start) % step == 0) {
            array->_internalProperties.next++;
        }

        // update "next" pointer.
        _UpdateNextLocationPointer(array);
    }
}

void _addToArayeh(arayeh *array, void *element) {
    /*
     * This function will insert an "element" into array at index = self->_internalProperties.next.
     *
     * function will extend size of array in case of self->_internalProperties.size == self->_internalProperties.used.
     *
     * it will update "map" and "used" and "next" parameters.
     * it may update "size" parameter.
     *
     * self->_internalProperties.next will be updated in a manner that it points to the
     * next EMPTY slot in the array.
     *
     * ARGUMENTS:
     * self           pointer to the array object.
     * element        pointer to a variable to be added to the array.
     *
     */

    // extend array size if needed.
    if (array->_internalProperties.used == array->_internalProperties.size) {
        (array->extendSize)(array, array->_internalProperties.size);
    }

    // add element.
    (array->_privateMethods.addElementToArayeh)(array, array->_internalProperties.next, element);

    // update "map" and "used".
    array->_internalProperties.map[array->_internalProperties.next] = IS_FILLED;
    array->_internalProperties.used++;

    // update "next" pointer.
    _UpdateNextLocationPointer(array);
}

void _insertToArayeh(arayeh *array, size_t index, void *element) {
    /*
     * This function will insert an "element" into array at "index".
     *
     * this function WON'T increase array size!
     *
     * it may update "map" and "used" and "next" parameters.
     *
     * ARGUMENTS:
     * self         pointer to the array object.
     * element      pointer to a variable to be inserted into the array.
     *
     */

    // tracks errors in function.
    int state = AA_ARAYEH_SUCCESS;

    // check array bounds.
    if (index >= array->_internalProperties.size || index < 0) {
        // TODO error handler
        // state =
        abort();
    }

    // insert element.
    if (index == array->_internalProperties.next) {
        // use _addToArayeh for insertion.
        _addToArayeh(array, element);

    } else {
        // assign element.
        (array->_privateMethods.addElementToArayeh)(array, index, element);
        // update array parameters.
        if (index > array->_internalProperties.next && array->_internalProperties.map[index] == IS_EMPTY) {
            // update "map" and "used" if they aren't already counted for this index.
            array->_internalProperties.map[index] = IS_FILLED;
            array->_internalProperties.used++;
        }
    }
}

void _mergeListToArayeh(arayeh *self, size_t startIndex, size_t listSize, void *list) {
    /*
     * This function will merge a default C array (for example int a[4] = {1, 2, 3, 4};)
     * into arayeh array, the starting index for merging is "startIndex" and the size of
     * C array determines the last index (in the example above the size of C array is 4).
     *
     * this function WON'T increase array size!
     *
     * it may update "map" and "used" and "next" parameters.
     *
     * ARGUMENTS:
     * self         pointer to the array object.
     * startIndex   starting index in the arayeh array.
     * listSize     size of the C array.
     * list         the C array to be merged into the arayeh array.
     *
     */

    // check array bounds.
    if (self->_internalProperties.size <= startIndex || self->_internalProperties.size < startIndex + listSize) {
        // TODO error handling
        abort();
    }

    // insert C array elements into arayeh array.
    (self->_privateMethods.mergeListToArayeh)(self, startIndex, listSize, list);
}

void _getElementFromArayeh(arayeh *self, size_t index, void *destination) {
    /*
     * This function copies data in "index" cell of the array to the "destination" memory location.
     *
     * ARGUMENTS:
     * self         pointer to the array object.
     * index        index of the element to be copied.
     * destination  pointer to the destination memory location.
     *
     */

    // check array bounds.
    if (self->_internalProperties.size <= index) {
        // TODO error handling
        abort();
    }

    // copy data to destination memory location.
    (self->_privateMethods.getElementFromArayeh)(self, index, destination);
}

void _setPublicMethods(arayeh *self) {
    /*
     * This function assigns pointers to public functions of an arayeh instance.
     *
     * ARGUMENTS:
     * self         pointer to the array object.
     *
     */

    self->extendSize = _extendArayehSize;
    self->freeArayeh = _freeArayehMemory;
    self->fill = _fillArayeh;
    self->add = _addToArayeh;
    self->insert = _insertToArayeh;
    self->mergeList = _mergeListToArayeh;
    self->get = _getElementFromArayeh;
}

void _setPrivateMethods(arayeh *self, size_t type) {
    /*
     * This function assigns pointers to public functions of an arayeh instance.
     *
     * ARGUMENTS:
     * self         pointer to the array object.
     * type         type of array elements.
     *
     */

    // assign based on the arayeh type.
    switch (type) {
        case TYPE_CHAR:
            self->_privateMethods.initArayeh = _initTypeChar;
            self->_privateMethods.mallocArayeh = _mallocTypeChar;
            self->_privateMethods.reallocArayeh = _reallocTypeChar;
            self->_privateMethods.freeArayeh = _freeTypeChar;
            self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeChar;
            self->_privateMethods.addElementToArayeh = _addTypeChar;
            self->_privateMethods.mergeListToArayeh = _mergeListTypeChar;
            self->_privateMethods.getElementFromArayeh = _getTypeChar;
            break;

        case TYPE_SINT:
            self->_privateMethods.initArayeh = _initTypeSInt;
            self->_privateMethods.mallocArayeh = _mallocTypeSInt;
            self->_privateMethods.reallocArayeh = _reallocTypeSInt;
            self->_privateMethods.freeArayeh = _freeTypeSInt;
            self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeSInt;
            self->_privateMethods.addElementToArayeh = _addTypeSInt;
            self->_privateMethods.mergeListToArayeh = _mergeListTypeSInt;
            self->_privateMethods.getElementFromArayeh = _getTypeSInt;
            break;

        case TYPE_INT:
            self->_privateMethods.initArayeh = _initTypeInt;
            self->_privateMethods.mallocArayeh = _mallocTypeInt;
            self->_privateMethods.reallocArayeh = _reallocTypeInt;
            self->_privateMethods.freeArayeh = _freeTypeInt;
            self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeInt;
            self->_privateMethods.addElementToArayeh = _addTypeInt;
            self->_privateMethods.mergeListToArayeh = _mergeListTypeInt;
            self->_privateMethods.getElementFromArayeh = _getTypeInt;
            break;

        case TYPE_LINT:
            self->_privateMethods.initArayeh = _initTypeLInt;
            self->_privateMethods.mallocArayeh = _mallocTypeLInt;
            self->_privateMethods.reallocArayeh = _reallocTypeLInt;
            self->_privateMethods.freeArayeh = _freeTypeLInt;
            self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeLInt;
            self->_privateMethods.addElementToArayeh = _addTypeLInt;
            self->_privateMethods.mergeListToArayeh = _mergeListTypeLInt;
            self->_privateMethods.getElementFromArayeh = _getTypeLInt;
            break;

        case TYPE_FLOAT:
            self->_privateMethods.initArayeh = _initTypeFloat;
            self->_privateMethods.mallocArayeh = _mallocTypeFloat;
            self->_privateMethods.reallocArayeh = _reallocTypeFloat;
            self->_privateMethods.freeArayeh = _freeTypeFloat;
            self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeFloat;
            self->_privateMethods.addElementToArayeh = _addTypeFloat;
            self->_privateMethods.mergeListToArayeh = _mergeListTypeFloat;
            self->_privateMethods.getElementFromArayeh = _getTypeFloat;
            break;

        case TYPE_DOUBLE:
            self->_privateMethods.initArayeh = _initTypeDouble;
            self->_privateMethods.mallocArayeh = _mallocTypeDouble;
            self->_privateMethods.reallocArayeh = _reallocTypeDouble;
            self->_privateMethods.freeArayeh = _freeTypeDouble;
            self->_privateMethods.setArayehMemoryPointer = _setMemoryPointerTypeDouble;
            self->_privateMethods.addElementToArayeh = _addTypeDouble;
            self->_privateMethods.mergeListToArayeh = _mergeListTypeDouble;
            self->_privateMethods.getElementFromArayeh = _getTypeDouble;
            break;
        default:
            // TODO Error Handler
            break;
    }
}

void _UpdateNextLocationPointer(arayeh *array) {
    /*
     * This function purpose is to update
     * array.next variable to point to next empty [available]
     * slot in the array.
     *
     * ARGUMENTS:
     * self         pointer to the array object.
     */

    while (array->_internalProperties.next < array->_internalProperties.size &&
           array->_internalProperties.map[array->_internalProperties.next] == IS_FILLED) {
        array->_internalProperties.next++;
    }
}
