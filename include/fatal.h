/** include/fatal.h
 *
 * This file is a part of:
 * Azadeh Afzar - Arayehsaz (AA-A).
 *
 * Original writer:
 * Copyright (C) 2019 Christian W. Zuckschwerdt <zany@triq.net>
 *
 * Adopted by:
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

#ifndef __AA_A_FATAL_H__
#define __AA_A_FATAL_H__

// macros for extracting line number from error code.
#define STRINGIFYX(x) #x
#define STRINGIFY(x)  STRINGIFYX(x)
#define FILE_LINE     __FILE__ ":" STRINGIFY(__LINE__)

/*
    Use below macros like this:

    char *buf = malloc(size);
    if (!buf)
        FATAL_MALLOC("my_func()");

*/

// macros for fatal error codes.
#define FATAL(what, allow_print)                                     \
    do {                                                             \
        if (allow_print) {                                           \
            fprintf(stderr, "FATAL: " what " from " FILE_LINE "\n"); \
        }                                                            \
        exit(1);                                                     \
    } while (0)
#define FATAL_MALLOC(what, allow_print) \
    FATAL("low memory? malloc() failed in " what, allow_print)
#define FATAL_CALLOC(what, allow_print) \
    FATAL("low memory? calloc() failed in " what, allow_print)
#define FATAL_REALLOC(what, allow_print) \
    FATAL("low memory? realloc() failed in " what, allow_print)
#define FATAL_STRDUP(what, allow_print) \
    FATAL("low memory? strdup() failed in " what, allow_print)
#define FATAL_OVERFLOW(what, allow_print) \
    FATAL("number is too big? failed in " what, allow_print)
#define FATAL_WRONG_TYPE(what, allow_print) \
    FATAL("wrong arayeh type? failed in " what, allow_print)
#define FATAL_WRONG_SETTINGS(what, allow_print) \
    FATAL("wrong settings detected. failed in " what, allow_print)

// macros for fatal warning codes.
#define WARN(what, allow_print)                                        \
    do {                                                               \
        if (allow_print) {                                             \
            fprintf(stderr, "WARNING: " what " from " FILE_LINE "\n"); \
        }                                                              \
    } while (0)
#define WARN_MALLOC(what, allow_print) \
    WARN("low memory? malloc() failed in " what, allow_print)
#define WARN_CALLOC(what, allow_print) \
    WARN("low memory? calloc() failed in " what, allow_print)
#define WARN_REALLOC(what, allow_print) \
    WARN("low memory? realloc() failed in " what, allow_print)
#define WARN_INIT_FAIL(what, allow_print) \
    WARN("arayeh initialization error, failed in " what, allow_print)
#define WARN_STRDUP(what, allow_print) \
    WARN("low memory? strdup() failed in " what, allow_print)
#define WARN_WRONG_TYPE(what, allow_print) \
    WARN("wrong arayeh type? failed in " what, allow_print)
#define WARN_T_OVERFLOW(what, allow_print) \
    WARN("possible size_t overflow, failed in " what, allow_print)
#define WARN_NEW_SIZE(what, allow_print) \
    WARN("new size is less than current size, failed in " what, allow_print)
#define WARN_WRONG_INDEX(what, allow_print)        WARN("failed in " what, allow_print)
#define WARN_WRONG_STEP(what, allow_print)         WARN("failed in " what, allow_print)
#define WARN_EXCEED_ARAYEH_SIZE(what, allow_print) WARN("failed in " what, allow_print)

#endif    //__AA_A_FATAL_H__
