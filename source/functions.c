/** source/functions.c
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

#include "../include/functions.h"

#include "../include/algorithms.h"
#include "../include/fatal.h"
#include "../include/methods.h"
#include "../include/types.h"

int extendMemory(arayeh *self)
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

    // shorten names for god's sake.
    struct privateMethods *privateMethods = &self->_privateMethods;

    // track error state in the function.
    int state;

    // calculate the extension memory size using growth factor function.
    size_t extension_size = privateMethods->growthFactor(self);

    // extend arayeh size.
    state = self->extendSize(self, extension_size);

    // return error state.
    return state;
}

void setPublicMethods(arayeh *self)
{
    /*
     * This function assigns pointers to public functions of an arayeh instance.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     *
     * RETURN:
     * no return, it's void dude.
     *
     */

    self->resizeMemory    = _resizeMemory;
    self->extendSize      = _extendSize;
    self->freeArayeh      = _freeMemory;
    self->add             = _addToArayeh;
    self->insert          = _insertToArayeh;
    self->fill            = _fillArayeh;
    self->mergeArray      = _mergeFromArray;
    self->get             = _getFromArayeh;
    self->setSettings     = _setSettings;
    self->setSizeSettings = _setSizeSettings;
    self->setGrowthFactor = _setGrowthFactor;
}

void setPrivateMethods(arayeh *self, size_t type)
{
    /*
     * This function assigns pointers to private functions of an arayeh instance.
     *
     * ARGUMENTS:
     * self         pointer to the arayeh object.
     * type         type of arayeh elements.
     *
     * RETURN:
     * no return, it's void dude.
     *
     */

    // shorten names for god's sake.
    // shorten names for god's sake.
    struct privateMethods *privateMethods = &self->_privateMethods;

    // set memory space growth factor function to default.
    privateMethods->growthFactor = growthFactorPython;

    // assign based on the arayeh type.
    switch (type) {
    case AA_ARAYEH_TYPE_CHAR:
        privateMethods->initArayeh       = _initPtrTypeChar;
        privateMethods->mallocArayeh     = _mallocTypeChar;
        privateMethods->reallocArayeh    = _reallocTypeChar;
        privateMethods->freeArayeh       = _freeTypeChar;
        privateMethods->setMemoryPointer = _setMemPtrTypeChar;
        privateMethods->addToArayeh      = _addTypeChar;
        privateMethods->mergeFromArray   = _mergeArrayTypeChar;
        privateMethods->getFromArayeh    = _getTypeChar;
        break;

    case AA_ARAYEH_TYPE_SINT:
        privateMethods->initArayeh       = _initPtrTypeSInt;
        privateMethods->mallocArayeh     = _mallocTypeSInt;
        privateMethods->reallocArayeh    = _reallocTypeSInt;
        privateMethods->freeArayeh       = _freeTypeSInt;
        privateMethods->setMemoryPointer = _setMemPtrTypeSInt;
        privateMethods->addToArayeh      = _addTypeSInt;
        privateMethods->mergeFromArray   = _mergeArrayTypeSInt;
        privateMethods->getFromArayeh    = _getTypeSInt;
        break;

    case AA_ARAYEH_TYPE_INT:
        privateMethods->initArayeh       = _initPtrTypeInt;
        privateMethods->mallocArayeh     = _mallocTypeInt;
        privateMethods->reallocArayeh    = _reallocTypeInt;
        privateMethods->freeArayeh       = _freeTypeInt;
        privateMethods->setMemoryPointer = _setMemPtrTypeInt;
        privateMethods->addToArayeh      = _addTypeInt;
        privateMethods->mergeFromArray   = _mergeArrayTypeInt;
        privateMethods->getFromArayeh    = _getTypeInt;
        break;

    case AA_ARAYEH_TYPE_LINT:
        privateMethods->initArayeh       = _initPtrTypeLInt;
        privateMethods->mallocArayeh     = _mallocTypeLInt;
        privateMethods->reallocArayeh    = _reallocTypeLInt;
        privateMethods->freeArayeh       = _freeTypeLInt;
        privateMethods->setMemoryPointer = _setMemPtrTypeLInt;
        privateMethods->addToArayeh      = _addTypeLInt;
        privateMethods->mergeFromArray   = _mergeArrayTypeLInt;
        privateMethods->getFromArayeh    = _getTypeLInt;
        break;

    case AA_ARAYEH_TYPE_FLOAT:
        privateMethods->initArayeh       = _initPtrTypeFloat;
        privateMethods->mallocArayeh     = _mallocTypeFloat;
        privateMethods->reallocArayeh    = _reallocTypeFloat;
        privateMethods->freeArayeh       = _freeTypeFloat;
        privateMethods->setMemoryPointer = _setMemPtrTypeFloat;
        privateMethods->addToArayeh      = _addTypeFloat;
        privateMethods->mergeFromArray   = _mergeArrayTypeFloat;
        privateMethods->getFromArayeh    = _getTypeFloat;
        break;

    case AA_ARAYEH_TYPE_DOUBLE:
        privateMethods->initArayeh       = _initPtrTypeDouble;
        privateMethods->mallocArayeh     = _mallocTypeDouble;
        privateMethods->reallocArayeh    = _reallocTypeDouble;
        privateMethods->freeArayeh       = _freeTypeDouble;
        privateMethods->setMemoryPointer = _setMemPtrTypeDouble;
        privateMethods->addToArayeh      = _addTypeDouble;
        privateMethods->mergeFromArray   = _mergeArrayTypeDouble;
        privateMethods->getFromArayeh    = _getTypeDouble;
        break;
    default:
        WARN_WRONG_TYPE("setPrivateMethods", TRUE);
    }
}
