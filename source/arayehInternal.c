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
#include "configurations.h"

void _extendSizeArray1D(array1d *self, size_t extendSize) {
    /*
     * This function will reallocate memory to array and it's map
     *
     * ARGUMENTS:
     * self             pointer to an array object
     * extendSize       size increment
     *
     */

    // calculate new size for array
    size_t newSize = self->_internalProperties.size + extendSize;

    // size_t overflow protection
    if (newSize < self->_internalProperties.size) {
        // TODO error handler
        abort();
    }

    // initialize variables for allocating memory
    char *mapPointer = NULL;
    arrayType arrayPointer;
    // this function identifies the right pointer for array type and sets it to point to NULL
    // and also checks for possible overflow in size_t newSize
    int state = (self->_privateMethods.initArray)(self, &arrayPointer, newSize);

    // protection for possible overflow in size_t
    if (state == FAILURE) {
        // TODO error handler
        abort();
    }

    // reallocate memory to map and array
    mapPointer = (char *) realloc(self->_internalProperties.map, sizeof *mapPointer * newSize);
    state = (self->_privateMethods.reallocArray)(self, &arrayPointer, newSize);

    // check if memory allocated or not
    if (state == FAILURE || mapPointer == NULL) {
        // printf("Error: unable to allocate memory!\n");
        // free map and array pointers
        free(mapPointer);
        (self->_privateMethods.freeArray)(self);

        // failure
        // TODO error handler
        abort();
    }

    // set new map elements to '0' [IS_EMPTY]
    for (size_t i = self->_internalProperties.size; i < newSize; ++i) {
        self->_internalProperties.map[i] = IS_EMPTY;
    }

    // set array parameters
    (self->_privateMethods.setArray)(self, &arrayPointer);
    self->_internalProperties.map = mapPointer;
    self->_internalProperties.size = newSize;
}

void _freeArray1D(array1d *self) {
    /*
     * This function will free an array and reset it's parameters
     *
     * ARGUMENTS:
     * self         pointer to an array object
     *
     */

    // free array pointer
    (self->_privateMethods.freeArray)(self);

    // free map pointer
    free(self->_internalProperties.map);
    self->_internalProperties.map = NULL;

    // reset array parameters
    self->_internalProperties.type = 0;
    self->_internalProperties.next = 0;
    self->_internalProperties.used = 0;
    self->_internalProperties.size = 0;

    // free array pointer
    free(self);
}


void _fillArray1D(array1d *self, size_t start, size_t step, size_t end, void *element) {
    /*
     * This function will fill array with an element
     * from index (inclusive) "start" to index (exclusive) "end"
     * with step size "step"
     *
     * it will update "map" and "used" parameters
     * it may update "next" parameter
     *
     * ARGUMENTS:
     * self           pointer to an array object
     * start          starting index (inclusive)
     * step           step size
     * end            ending index (exclusive)
     * element        pointer to a variable that must fill the array
     *
     */

    if (start < 0 || end > self->_internalProperties.size) {
        // TODO Error handler
        abort();
    }

    if (step <= 0) {
        // TODO Error handler
        //printf("Error: step size can't be less than 1.\n");
        abort();
    }

    // fill the array
    for (size_t i = start; i < end; i += step) {
        // assign element to array
        (self->_privateMethods.addArray)(self, i, element);

        // update array parameters
        if (self->_internalProperties.map[i] == IS_EMPTY) {
            // element has been assigned to an empty slot in array,
            // so update the map and +1 to used slots
            self->_internalProperties.map[i] = IS_FILLED;
            self->_internalProperties.used++;
        }
    }

    // update "next" parameter of array
    if (start <= self->_internalProperties.next) {
        // 0 is empty, 1 is data existing in the array, 2 is fill data
        // before fill
        // 111111111111111111111111110000000000000000000111111111111
        //          ^                ^              ^
        //        start         self->_internalProperties.next        end
        //
        // after fill
        // 111111111222222222222222222222222222222220000111111111111
        //                                          ^
        //                                     self->_internalProperties.next
        // the above case is for step = 1, if step is more than 1,
        // if (next - start) % step == 0, we can add 1 to 'next', because it will be filled.
        //
        // finally we will check next map slot to make sure it's empty and 'next' is valid
        // and we will keep adding 1 to next until map[next] == IS_EMPTY.
        //
        if (step == 1) {
            self->_internalProperties.next = end;
        } else if ((self->_internalProperties.next - start) % step == 0) {
            self->_internalProperties.next++;
        }

        // update "next"
        _nextUpdaterArray1D(self);
    }
}

void _addArray1D(array1d *self, void *element) {
    /*
     * This function will insert an "element" into array at index = self->_internalProperties.next
     * function will extend size of array in case of self->_internalProperties.size == self->_internalProperties.used
     * it will update "map" and "used" and "next" parameters
     * it may update "size" parameter
     *
     * self->_internalProperties.next will be updated in a manner that it points to the
     * next EMPTY slot in the array
     *
     * ARGUMENTS:
     * self           pointer to an array object
     * element        pointer to a variable to be added to the array
     *
     */

    // extend array size if needed
    if (self->_internalProperties.used == self->_internalProperties.size) {
        (self->extendSize)(self, self->_internalProperties.size);
    }

    // add element
    (self->_privateMethods.addArray)(self, self->_internalProperties.next, element);

    // update "map" and "used"
    self->_internalProperties.map[self->_internalProperties.next] = IS_FILLED;
    self->_internalProperties.used++;

    // update "next"
    _nextUpdaterArray1D(self);
}

void _insertArray1D(array1d *self, size_t index, void *element) {
    /*
     * This function will insert an "element" into array at "index"
     * function WON'T increase array size!
     * it may update "map" and "used" and "next" parameters
     *
     * ARGUMENTS:
     * self         pointer to an array object
     * element      pointer to a variable to be inserted into the array
     *
     */

    // tracks errors in function
    int state = SUCCESS;

    // check array bounds
    if (index >= self->_internalProperties.size || index < 0) {
        // TODO error handler
        // state =
        abort();
    }

    // insert element
    if (index == self->_internalProperties.next) {
        // use _addArray1D function to
        // take care of everything
        _addArray1D(self, element);

    } else {
        // assign element
        (self->_privateMethods.addArray)(self, index, element);
        // update array parameters
        if (index > self->_internalProperties.next && self->_internalProperties.map[index] == IS_EMPTY) {
            // update "map" and "used" if they
            // aren't already counted for this index
            self->_internalProperties.map[index] = IS_FILLED;
            self->_internalProperties.used++;
        }
    }
}

void _addListArray1D(array1d *self, void *list, size_t listSize, size_t startIndex) {
    if (self->_internalProperties.size <= startIndex || self->_internalProperties.size < startIndex + listSize) {
        // TODO error handling
        abort();
    }

    (self->_privateMethods.appendArray)(self, list, listSize, startIndex);
}

void _getArray1D(array1d *self, size_t index, void *destination) {
    if (self->_internalProperties.size <= index) {
        // TODO error handling
        abort();
    }
    (self->_privateMethods.getElementArray)(self, index, destination);
}

void _setPublicMethods(array1d *self) {
    self->extendSize = _extendSizeArray1D;
    self->delete = _freeArray1D;
    self->fill = _fillArray1D;
    self->add = _addArray1D;
    self->insert = _insertArray1D;
    self->appendList = _addListArray1D;
    self->get = _getArray1D;
}

void _setPrivateMethods(array1d *self, size_t type) {

    // decide which type to use
    switch (type) {
        case TYPE_CHAR:
            self->_privateMethods.initArray = _initTypeChar;
            self->_privateMethods.mallocArray = _mallocTypeChar;
            self->_privateMethods.reallocArray = _reallocTypeChar;
            self->_privateMethods.freeArray = _freeTypeChar;
            self->_privateMethods.setArray = _setTypeChar;
            self->_privateMethods.addArray = _addTypeChar;
            self->_privateMethods.appendArray = _appendTypeChar;
            self->_privateMethods.getElementArray = _getTypeChar;
            break;

        case TYPE_SINT:
            self->_privateMethods.initArray = _initTypeSInt;
            self->_privateMethods.mallocArray = _mallocTypeSInt;
            self->_privateMethods.reallocArray = _reallocTypeSInt;
            self->_privateMethods.freeArray = _freeTypeSInt;
            self->_privateMethods.setArray = _setTypeSInt;
            self->_privateMethods.addArray = _addTypeSInt;
            self->_privateMethods.appendArray = _appendTypeSInt;
            self->_privateMethods.getElementArray = _getTypeSInt;
            break;

        case TYPE_INT:
            self->_privateMethods.initArray = _initTypeInt;
            self->_privateMethods.mallocArray = _mallocTypeInt;
            self->_privateMethods.reallocArray = _reallocTypeInt;
            self->_privateMethods.freeArray = _freeTypeInt;
            self->_privateMethods.setArray = _setTypeInt;
            self->_privateMethods.addArray = _addTypeInt;
            self->_privateMethods.appendArray = _appendTypeInt;
            self->_privateMethods.getElementArray = _getTypeInt;
            break;

        case TYPE_LINT:
            self->_privateMethods.initArray = _initTypeLInt;
            self->_privateMethods.mallocArray = _mallocTypeLInt;
            self->_privateMethods.reallocArray = _reallocTypeLInt;
            self->_privateMethods.freeArray = _freeTypeLInt;
            self->_privateMethods.setArray = _setTypeLInt;
            self->_privateMethods.addArray = _addTypeLInt;
            self->_privateMethods.appendArray = _appendTypeLInt;
            self->_privateMethods.getElementArray = _getTypeLInt;
            break;

        case TYPE_FLOAT:
            self->_privateMethods.initArray = _initTypeFloat;
            self->_privateMethods.mallocArray = _mallocTypeFloat;
            self->_privateMethods.reallocArray = _reallocTypeFloat;
            self->_privateMethods.freeArray = _freeTypeFloat;
            self->_privateMethods.setArray = _setTypeFloat;
            self->_privateMethods.addArray = _addTypeFloat;
            self->_privateMethods.appendArray = _appendTypeFloat;
            self->_privateMethods.getElementArray = _getTypeFloat;
            break;

        case TYPE_DOUBLE:
            self->_privateMethods.initArray = _initTypeDouble;
            self->_privateMethods.mallocArray = _mallocTypeDouble;
            self->_privateMethods.reallocArray = _reallocTypeDouble;
            self->_privateMethods.freeArray = _freeTypeDouble;
            self->_privateMethods.setArray = _setTypeDouble;
            self->_privateMethods.addArray = _addTypeDouble;
            self->_privateMethods.appendArray = _appendTypeDouble;
            self->_privateMethods.getElementArray = _getTypeDouble;
            break;
        default:
            // TODO Error Handler
            break;
    }
}

void _nextUpdaterArray1D(array1d *self) {
    /*
     * This function purpose is to update
     * array.next variable to point to next empty [available]
     * slot in the array
     *
     * ARGUMENTS:
     * self           pointer to array variable
     */

    while (self->_internalProperties.next < self->_internalProperties.size &&
           self->_internalProperties.map[self->_internalProperties.next] == IS_FILLED) {
        self->_internalProperties.next++;
    }
}

//--------------------------------------- ARRAY INITIALIZATION ---------------------------------------------------------

int _initTypeChar(array1d *self, arrayType *array, size_t initialSize) {
    array->pChar = NULL;
    return (initialSize > (size_t) SIZE_MAX / sizeof array->pChar) ? FAILURE : SUCCESS;
}

int _initTypeSInt(array1d *self, arrayType *array, size_t initialSize) {
    array->pShortInt = NULL;
    return (initialSize > (size_t) SIZE_MAX / sizeof array->pShortInt) ? FAILURE : SUCCESS;
}

int _initTypeInt(array1d *self, arrayType *array, size_t initialSize) {
    array->pInt = NULL;
    return (initialSize > (size_t) SIZE_MAX / sizeof array->pInt) ? FAILURE : SUCCESS;
}

int _initTypeLInt(array1d *self, arrayType *array, size_t initialSize) {
    array->pLongInt = NULL;
    return (initialSize > (size_t) SIZE_MAX / sizeof array->pLongInt) ? FAILURE : SUCCESS;
}

int _initTypeFloat(array1d *self, arrayType *array, size_t initialSize) {
    array->pFloat = NULL;
    return (initialSize > (size_t) SIZE_MAX / sizeof array->pFloat) ? FAILURE : SUCCESS;
}

int _initTypeDouble(array1d *self, arrayType *array, size_t initialSize) {
    array->pDouble = NULL;
    return (initialSize > (size_t) SIZE_MAX / sizeof array->pDouble) ? FAILURE : SUCCESS;
}

//-------------------------------------------- ARRAY MALLOC ------------------------------------------------------------

int _mallocTypeChar(array1d *self, arrayType *array, size_t initialSize) {
    array->pChar = (char *) malloc(sizeof *array->pChar * initialSize);
    return (array->pChar == NULL) ? FAILURE : SUCCESS;
}

int _mallocTypeSInt(array1d *self, arrayType *array, size_t initialSize) {
    array->pShortInt = (short int *) malloc(sizeof *array->pShortInt * initialSize);
    return (array->pShortInt == NULL) ? FAILURE : SUCCESS;
}

int _mallocTypeInt(array1d *self, arrayType *array, size_t initialSize) {
    array->pInt = (int *) malloc(sizeof *array->pInt * initialSize);
    return (array->pInt == NULL) ? FAILURE : SUCCESS;
}

int _mallocTypeLInt(array1d *self, arrayType *array, size_t initialSize) {
    array->pLongInt = (long int *) malloc(sizeof *array->pLongInt * initialSize);
    return (array->pLongInt == NULL) ? FAILURE : SUCCESS;
}

int _mallocTypeFloat(array1d *self, arrayType *array, size_t initialSize) {
    array->pFloat = (float *) malloc(sizeof *array->pFloat * initialSize);
    return (array->pFloat == NULL) ? FAILURE : SUCCESS;
}

int _mallocTypeDouble(array1d *self, arrayType *array, size_t initialSize) {
    array->pDouble = (double *) malloc(sizeof *array->pDouble * initialSize);
    return (array->pDouble == NULL) ? FAILURE : SUCCESS;
}

//-------------------------------------------- ARRAY REALLOC -----------------------------------------------------------

int _reallocTypeChar(array1d *self, arrayType *array, size_t newSize) {
    array->pChar = (char *) realloc(self->_internalProperties.array.pChar, sizeof *array->pChar * newSize);
    return (array->pChar == NULL) ? FAILURE : SUCCESS;
}

int _reallocTypeSInt(array1d *self, arrayType *array, size_t newSize) {
    array->pShortInt = (short int *) realloc(self->_internalProperties.array.pShortInt,
                                             sizeof *array->pShortInt * newSize);
    return (array->pShortInt == NULL) ? FAILURE : SUCCESS;
}

int _reallocTypeInt(array1d *self, arrayType *array, size_t newSize) {
    array->pInt = (int *) realloc(self->_internalProperties.array.pInt, sizeof *array->pInt * newSize);
    return (array->pInt == NULL) ? FAILURE : SUCCESS;
}

int _reallocTypeLInt(array1d *self, arrayType *array, size_t newSize) {
    array->pLongInt = (long int *) realloc(self->_internalProperties.array.pLongInt, sizeof *array->pLongInt * newSize);
    return (array->pLongInt == NULL) ? FAILURE : SUCCESS;
}

int _reallocTypeFloat(array1d *self, arrayType *array, size_t newSize) {
    array->pFloat = (float *) realloc(self->_internalProperties.array.pFloat, sizeof *array->pFloat * newSize);
    return (array->pFloat == NULL) ? FAILURE : SUCCESS;
}

int _reallocTypeDouble(array1d *self, arrayType *array, size_t newSize) {
    array->pDouble = (double *) realloc(self->_internalProperties.array.pDouble, sizeof *array->pDouble * newSize);
    return (array->pDouble == NULL) ? FAILURE : SUCCESS;
}

//--------------------------------------------- ARRAY FREE -------------------------------------------------------------

void _freeTypeChar(array1d *self) {
    free(self->_internalProperties.array.pChar);
    self->_internalProperties.array.pChar = NULL;
}

void _freeTypeSInt(array1d *self) {
    free(self->_internalProperties.array.pShortInt);
    self->_internalProperties.array.pShortInt = NULL;
}

void _freeTypeInt(array1d *self) {
    free(self->_internalProperties.array.pInt);
    self->_internalProperties.array.pInt = NULL;
}

void _freeTypeLInt(array1d *self) {
    free(self->_internalProperties.array.pLongInt);
    self->_internalProperties.array.pLongInt = NULL;
}

void _freeTypeFloat(array1d *self) {
    free(self->_internalProperties.array.pFloat);
    self->_internalProperties.array.pFloat = NULL;
}

void _freeTypeDouble(array1d *self) {
    free(self->_internalProperties.array.pDouble);
    self->_internalProperties.array.pDouble = NULL;
}

//--------------------------------------------- ARRAY SET --------------------------------------------------------------

void _setTypeChar(array1d *self, arrayType *array) {
    self->_internalProperties.array.pChar = array->pChar;
}

void _setTypeSInt(array1d *self, arrayType *array) {
    self->_internalProperties.array.pShortInt = array->pShortInt;
}

void _setTypeInt(array1d *self, arrayType *array) {
    self->_internalProperties.array.pInt = array->pInt;
}

void _setTypeLInt(array1d *self, arrayType *array) {
    self->_internalProperties.array.pLongInt = array->pLongInt;
}

void _setTypeFloat(array1d *self, arrayType *array) {
    self->_internalProperties.array.pFloat = array->pFloat;
}

void _setTypeDouble(array1d *self, arrayType *array) {
    self->_internalProperties.array.pDouble = array->pDouble;
}

//---------------------------------------------- ARRAY ADD -------------------------------------------------------------

void _addTypeChar(array1d *self, size_t index, void *element) {
    self->_internalProperties.array.pChar[index] = *((char *) element);
}

void _addTypeSInt(array1d *self, size_t index, void *element) {
    self->_internalProperties.array.pShortInt[index] = *((short int *) element);
}

void _addTypeInt(array1d *self, size_t index, void *element) {
    self->_internalProperties.array.pInt[index] = *((int *) element);
}

void _addTypeLInt(array1d *self, size_t index, void *element) {
    self->_internalProperties.array.pLongInt[index] = *((long int *) element);
}

void _addTypeFloat(array1d *self, size_t index, void *element) {
    self->_internalProperties.array.pFloat[index] = *((float *) element);
}

void _addTypeDouble(array1d *self, size_t index, void *element) {
    self->_internalProperties.array.pDouble[index] = *((double *) element);
}

//-------------------------------------------- ARRAY APPEND ------------------------------------------------------------

void _appendTypeChar(array1d *self, void *list, size_t listSize, size_t startIndex) {
    char *temp = (char *) list;
    for (size_t i = 0; i < listSize; ++i) {
        (self->insert)(self, startIndex + i, temp + i);
    }
}

void _appendTypeSInt(array1d *self, void *list, size_t listSize, size_t startIndex) {
    short int *temp = (short int *) list;
    for (size_t i = 0; i < listSize; ++i) {
        (self->insert)(self, startIndex + i, temp + i);
    }
}

void _appendTypeInt(array1d *self, void *list, size_t listSize, size_t startIndex) {
    int *temp = (int *) list;
    for (size_t i = 0; i < listSize; ++i) {
        (self->insert)(self, startIndex + i, temp + i);
    }
}

void _appendTypeLInt(array1d *self, void *list, size_t listSize, size_t startIndex) {
    long int *temp = (long int *) list;
    for (size_t i = 0; i < listSize; ++i) {
        (self->insert)(self, startIndex + i, temp + i);
    }
}

void _appendTypeFloat(array1d *self, void *list, size_t listSize, size_t startIndex) {
    float *temp = (float *) list;
    for (size_t i = 0; i < listSize; ++i) {
        (self->insert)(self, startIndex + i, temp + i);
    }
}

void _appendTypeDouble(array1d *self, void *list, size_t listSize, size_t startIndex) {
    double *temp = (double *) list;
    for (size_t i = 0; i < listSize; ++i) {
        (self->insert)(self, startIndex + i, temp + i);
    }
}

//---------------------------------------------- ARRAY GET -------------------------------------------------------------

void _getTypeChar(array1d *self, size_t index, void *element) {
    char *ptr = (char *) element;
    *ptr = self->_internalProperties.array.pChar[index];
}

void _getTypeSInt(array1d *self, size_t index, void *element) {
    short int *ptr = (short int *) element;
    *ptr = self->_internalProperties.array.pShortInt[index];
}

void _getTypeInt(array1d *self, size_t index, void *element) {
    int *ptr = (int *) element;
    *ptr = self->_internalProperties.array.pInt[index];
}

void _getTypeLInt(array1d *self, size_t index, void *element) {
    long int *ptr = (long int *) element;
    *ptr = self->_internalProperties.array.pLongInt[index];
}

void _getTypeFloat(array1d *self, size_t index, void *element) {
    float *ptr = (float *) element;
    *ptr = self->_internalProperties.array.pFloat[index];
}

void _getTypeDouble(array1d *self, size_t index, void *element) {
    double *ptr = (double *) element;
    *ptr = self->_internalProperties.array.pDouble[index];
}
