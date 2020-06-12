/** source/arayeh.c
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

#include "../include/arayeh.h"
#include "../include/methods.h"

arayeh *newArayeh(size_t type, size_t initialSize)
{
    /*
     * This function will create an array of type "type"
     * (one the supported types defined in configuration.h)
     * and size of  "initialSize" if it's possible
     * (you have enough memory and right to allocate that memory).
     *
     * ARGUMENTS:
     * initialSize  size of array.
     * type         type of array elements.
     *
     * RETURN:
     * A pointer to the initialized array.
     * or
     * return NULL in case of error.
     */

    // check array type.
    if (type != AA_ARAYEH_TYPE_CHAR && type != AA_ARAYEH_TYPE_SINT &&
        type != AA_ARAYEH_TYPE_INT && type != AA_ARAYEH_TYPE_LINT &&
        type != AA_ARAYEH_TYPE_FLOAT && type != AA_ARAYEH_TYPE_DOUBLE) {
        // wrong array type.
        return NULL;
    }

    // initialize a pointer and allocate memory.
    arayeh *self = (arayeh *) malloc(sizeof *self);

    // assign public methods.
    _setPublicMethods(self);

    // assign private methods based on array type.
    _setPrivateMethods(self, type);

    // initialize variables for allocating memory.
    char *mapPointer = NULL;
    arayehType arrayPointer;

    // this function identifies the right pointer for array type and sets it to point
    // to NULL and also checks for possible overflow in size_t initialSize.
    int state = (self->_privateMethods.initArayeh)(self, &arrayPointer, initialSize);

    // check for possible size_t overflow.
    if (state == AA_ARAYEH_FAILURE) {
        // overflow detected.
        // free self.
        free(self);
        return NULL;
    }

    // allocate memory to map and array.
    mapPointer = (char *) malloc(sizeof *mapPointer * initialSize);
    state = (self->_privateMethods.mallocArayeh)(self, &arrayPointer, initialSize);

    // check if memory allocated or not.
    if (state == AA_ARAYEH_FAILURE || mapPointer == NULL) {
        // free map, array and self pointers.
        free(mapPointer);
        (self->_privateMethods.freeArayeh)(self);
        free(self);
        return NULL;
    }

    // set all map elements to '0' [AA_ARAYEH_OFF].
    for (size_t i = 0; i < initialSize; ++i) {
        mapPointer[i] = AA_ARAYEH_OFF;
    }

    // create array default setting holder.
    arayehSetting *defaultSettings =
        (arayehSetting *) malloc(sizeof *defaultSettings);

    // set default setting.
    defaultSettings->allowDebugMessages     = AA_ARAYEH_OFF;
    defaultSettings->allowExtendOnAdd       = AA_ARAYEH_ON;
    defaultSettings->allowExtendOnInsert    = AA_ARAYEH_ON;
    defaultSettings->allowExtendOnFill      = AA_ARAYEH_ON;
    defaultSettings->allowExtendOnMergeList = AA_ARAYEH_ON;

    // set array parameters.
    (self->_privateMethods.setArayehMemoryPointer)(self, &arrayPointer);
    self->_internalProperties.map      = mapPointer;
    self->_internalProperties.type     = type;
    self->_internalProperties.settings = defaultSettings;
    self->_internalProperties.next     = 0;
    self->_internalProperties.used     = 0;
    self->_internalProperties.size     = initialSize;

    return self;
}
