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

#include "../include/fatal.h"
#include "../include/functions.h"

arayeh *Arayeh(size_t type, size_t initialSize)
{
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

    // check arayeh type.
    if (type < AA_ARAYEH_TYPE_CHAR || AA_ARAYEH_TYPE_DOUBLE < type) {
        // wrong arayeh type.
        FATAL_WRONG_TYPE("Arayeh()", TRUE);
    }

    // initialize a pointer and allocate memory.
    arayeh *self = (arayeh *) malloc(sizeof *self);

    // shorten names for god's sake.
    struct privateMethods *privateMethods       = &self->_privateMethods;
    struct privateProperties *privateProperties = &self->_privateProperties;

    // assign public methods.
    setPublicMethods(self);

    // assign private methods based on arayeh type.
    setPrivateMethods(self, type);

    // initialize variables for allocating memory.
    char *mapPtr = NULL;
    arayehType arrayPtr;

    /* Overflow happens when the arayeh initial size is bigger than the
     * max allowed size (defined as MAX_SIZE in size_type) divided by the
     * length of desired data type.
     *
     * for example MAX_SIZE in my machine is 18446744073709551615 and length of
     * an int data type is 4, so if arayeh initial size is bigger than
     * 18446744073709551615 / 4 = 4611686018427387904, then an overflow occurs.
     *
     * the formula to determine if overflow happens or not is defined below:
     * (initialSize > (size_t) SIZE_MAX / sizeof datatype)
     *
     */

    // this function identifies the right pointer for arayeh type and sets it to point
    // to NULL and also checks for possible overflow in size_t initialSize.
    int state = privateMethods->initArayeh(self, &arrayPtr, initialSize);

    // check for possible size_t overflow.
    if (state == AA_ARAYEH_FAILURE) {
        // free self.
        free(self);
        // overflow detected.
        FATAL_OVERFLOW("Arayeh()", TRUE);
    }

    // allocate memory to map and array.
    mapPtr = (char *) malloc(sizeof *mapPtr * initialSize);
    state  = privateMethods->mallocArayeh(self, &arrayPtr, initialSize);

    // check if memory allocated or not.
    if (state == AA_ARAYEH_FAILURE || mapPtr == NULL) {
        // free map, array and self pointers.
        free(mapPtr);
        privateMethods->freeArayeh(self);
        free(self);
        return NULL;
    }

    // set all map elements to '0' [AA_ARAYEH_OFF].
    for (size_t i = 0; i < initialSize; ++i) {
        mapPtr[i] = AA_ARAYEH_OFF;
    }

    // set pointers to memory locations.
    privateMethods->setMemoryPointer(self, &arrayPtr);
    privateProperties->map = mapPtr;

    // set arayeh parameters.
    self->type              = type;
    self->next              = 0;
    self->used              = 0;
    self->size              = initialSize;
    privateProperties->type = type;
    privateProperties->next = 0;
    privateProperties->used = 0;
    privateProperties->size = initialSize;

    // create arayeh default setting holder.
    arayehSettings *defaultSettings = (arayehSettings *) malloc(sizeof *defaultSettings);

    // set default setting.
    defaultSettings->debugMessages = AA_ARAYEH_OFF;
    defaultSettings->extendSize    = AA_ARAYEH_ON;
    defaultSettings->methodSize    = NULL;

    // assign setting pointer to the arayeh private properties.
    privateProperties->settings = defaultSettings;

    // create arayeh default method specific size extension setting holder.
    arayehSizeSettings *methodSize = (arayehSizeSettings *) malloc(sizeof *methodSize);

    // set default settings.
    methodSize->extendAdd        = AA_ARAYEH_ON;
    methodSize->extendInsert     = AA_ARAYEH_ON;
    methodSize->extendFill       = AA_ARAYEH_ON;
    methodSize->extendMergeArray = AA_ARAYEH_ON;

    // assign setting pointer to the arayeh private properties.
    privateProperties->settings->methodSize = methodSize;

    return self;
}
