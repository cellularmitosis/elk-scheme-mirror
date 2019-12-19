/* malloc.c
 *
 * $Id$
 *
 * Copyright 1990, 1991, 1992, 1993, 1994, 1995, Oliver Laumann, Berlin
 * Copyright 2002, 2003 Sam Hocevar <sam@hocevar.net>, Paris
 *
 * This software was derived from Elk 1.2, which was Copyright 1987, 1988,
 * 1989, Nixdorf Computer AG and TELES GmbH, Berlin (Elk 1.2 has been written
 * by Oliver Laumann for TELES Telematic Services, Berlin, in a joint project
 * between TELES and Nixdorf Microprocessor Engineering, Berlin).
 *
 * Oliver Laumann, TELES GmbH, Nixdorf Computer AG and Sam Hocevar, as co-
 * owners or individual owners of copyright in this software, grant to any
 * person or company a worldwide, royalty free, license to
 *
 *    i) copy this software,
 *   ii) prepare derivative works based on this software,
 *  iii) distribute copies of this software or derivative works,
 *   iv) perform this software, or
 *    v) display this software,
 *
 * provided that this notice is not removed and that neither Oliver Laumann
 * nor Teles nor Nixdorf are deemed to have made any representations as to
 * the suitability of this software for any purpose nor are held responsible
 * for any defects of this software.
 *
 * THERE IS ABSOLUTELY NO WARRANTY FOR THIS SOFTWARE.
 */

#include "config.h"

#include <stdlib.h>

#include "kernel.h"

char *Safe_Malloc (unsigned int size) {
    char *ret;

    Disable_Interrupts;
    if ((ret = malloc (size)) == 0) {
        if (Interpreter_Initialized)
            Primitive_Error ("not enough memory to malloc ~s bytes",
                Make_Integer (size));
        else
            Fatal_Error ("not enough memory to malloc %u bytes", size);
    }
    Enable_Interrupts;
    return ret;
}

char *Safe_Realloc (char *ptr, unsigned int size) {
    char *ret;

    Disable_Interrupts;
    if ((ret = ptr ? realloc (ptr, size) : malloc (size)) == 0) {
        if (Interpreter_Initialized)
            Primitive_Error ("not enough memory to malloc ~s bytes",
                Make_Integer (size));
        else
            Fatal_Error ("not enough memory to malloc %u bytes", size);
    }
    Enable_Interrupts;
    return ret;
}
