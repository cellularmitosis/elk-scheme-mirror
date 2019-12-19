/* font.c
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

#include "xlib.h"

#include <string.h>

Object Sym_Char_Info;
static Object Sym_Font_Info, Sym_Min, Sym_Max;

Generic_Predicate (Font)

static int Font_Equal (Object x, Object y) {
    Font id1 = FONT(x)->id, id2 = FONT(y)->id;
    if (id1 && id2)
        return id1 == id2 && FONT(x)->dpy == FONT(y)->dpy;
    else
        return 0;
}

Generic_Print (Font, "#[font %lu]", FONT(x)->id ? FONT(x)->id
                                                : (unsigned int)FIXNUM(x))

static int Font_Visit (Object *fp, int (*f)()) {
    (*f)(&FONT(*fp)->name);
    return 0;
}

Generic_Get_Display (Font, FONT)

static Object Internal_Make_Font (int finalize, Display *dpy, Object name,
                                  Font id, XFontStruct *info) {
    Object f;
    GC_Node;

    GC_Link (name);
    f = Alloc_Object (sizeof (struct S_Font), T_Font, 0);
    FONT(f)->dpy = dpy;
    if (TYPE(name) == T_Symbol)
        name = SYMBOL(name)->name;
    FONT(f)->name = name;
    FONT(f)->id = id;
    FONT(f)->info = info;
    if (id)
        Register_Object (f, (GENERIC)dpy, finalize ? P_Close_Font : (PFO)0, 0);
    GC_Unlink;
    return f;
}

/* Backwards compatibility: */
Object Make_Font (Display *dpy, Object name, Font id, XFontStruct *info) {
    return Internal_Make_Font (1, dpy, name, id, info);
}

Object Make_Font_Foreign (Display *dpy, Object name, Font id,
                          XFontStruct *info) {
    return Internal_Make_Font (0, dpy, name, id, info);
}

Font Get_Font (Object f) {
    Check_Type (f, T_Font);
    Open_Font_Maybe (f);
    return FONT(f)->id;
}

static XFontStruct *Internal_Open_Font (Display *d, Object name) {
    register char *s;
    XFontStruct *p;
    Alloca_Begin;

    Get_Strsym_Stack (name, s);
    Disable_Interrupts;
    if ((p = XLoadQueryFont (d, s)) == 0)
        Primitive_Error ("cannot open font: ~s", name);
    Enable_Interrupts;
    Alloca_End;
    return p;
}

static Object P_Open_Font (Object d, Object name) {
    XFontStruct *p;

    Check_Type (d, T_Display)
    p = Internal_Open_Font (DISPLAY(d)->dpy, name);
    return Make_Font (DISPLAY(d)->dpy, name, p->fid, p);
}

void Open_Font_Maybe (Object f) {
    Object name;
    XFontStruct *p;

    name = FONT(f)->name;
    if (!Truep (name))
        Primitive_Error ("invalid font");
    if (FONT(f)->id == 0) {
        p = Internal_Open_Font (FONT(f)->dpy, name);
        FONT(f)->id = p->fid;
        FONT(f)->info = p;
        Register_Object (f, (GENERIC)(FONT(f)->dpy), P_Close_Font, 0);
    }
}

Object P_Close_Font (Object f) {
    Check_Type (f, T_Font);
    if (FONT(f)->id)
        XUnloadFont (FONT(f)->dpy, FONT(f)->id);
    FONT(f)->id = 0;
    Deregister_Object (f);
    return Void;
}

static Object P_Font_Name (Object f) {
    Check_Type (f, T_Font);
    return FONT(f)->name;
}

static Object P_Gcontext_Font (Object g) {
    register struct S_Gc *p;
    register XFontStruct *info;

    Check_Type (g, T_Gc);
    p = GCONTEXT(g);
    Disable_Interrupts;
    info = XQueryFont (p->dpy, XGContextFromGC (p->gc));
    Enable_Interrupts;
    return Make_Font_Foreign (p->dpy, False, (Font)0, info);
}

static Object Internal_List_Fonts (Object d, Object pat, int with_info) {
    char **ret;
    int n;
    XFontStruct *iret;
    register int i;
    Object f, v;
    Display *dpy;
    GC_Node2;

    Check_Type (d, T_Display);
    dpy = DISPLAY(d)->dpy;
    Disable_Interrupts;
    if (with_info)
        ret = XListFontsWithInfo (dpy, Get_Strsym (pat), 65535, &n, &iret);
    else
        ret = XListFonts (dpy, Get_Strsym (pat), 65535, &n);
    Enable_Interrupts;
    v = Make_Vector (n, Null);
    f = Null;
    GC_Link2 (f, v);
    for (i = 0; i < n; i++) {
        f = Make_String (ret[i], strlen (ret[i]));
        if (with_info)
            f = Make_Font (dpy, f, (Font)0, &iret[i]);
        VECTOR(v)->data[i] = f;
    }
    GC_Unlink;
    if (with_info)
        XFreeFontInfo (ret, (XFontStruct *)0, 0);
    else
        XFreeFontNames (ret);
    return v;
}

static Object P_List_Font_Names (Object d, Object pat) {
    return Internal_List_Fonts (d, pat, 0);
}

static Object P_List_Fonts (Object d, Object pat) {
    return Internal_List_Fonts (d, pat, 1);
}

static Object P_Font_Info (Object f) {
    Check_Type (f, T_Font);
    FI = *FONT(f)->info;
    return Record_To_Vector (Font_Info_Rec, Font_Info_Size,
        Sym_Font_Info, FONT(f)->dpy, ~0L);
}

static Object P_Char_Info (Object f, Object index) {
    register int t = TYPE(index);
    register unsigned int i;
    register XCharStruct *cp;
    register XFontStruct *p;
    char *msg = "argument must be integer, character, 'min, or 'max";

    Check_Type (f, T_Font);
    Open_Font_Maybe (f);
    p = FONT(f)->info;
    cp = &p->max_bounds;
    if (t == T_Symbol) {
        if (EQ(index, Sym_Min))
            cp = &p->min_bounds;
        else if (!EQ(index, Sym_Max))
            Primitive_Error (msg);
    } else {
        if (t == T_Character)
            i = CHAR(index);
        else if (t == T_Fixnum || t == T_Bignum)
            i = (unsigned)Get_Integer (index);
        else
            Primitive_Error (msg);
        if (!p->min_byte1 && !p->max_byte1) {
            if (i < p->min_char_or_byte2 || i > p->max_char_or_byte2)
                Range_Error (index);
            i -= p->min_char_or_byte2;
        } else {
            register unsigned int b1 = i & 0xff, b2 = (i >> 8) & 0xff;
            if (b1 < p->min_byte1 || b1 > p->max_byte1 ||
                    b2 < p->min_char_or_byte2 || b2 > p->max_char_or_byte2)
                Range_Error (index);
            b1 -= p->min_byte1;
            b2 -= p->min_char_or_byte2;
            i = b1 * (p->max_char_or_byte2 - p->min_char_or_byte2 + 1) + b2;
        }
        if (p->per_char)
            cp = p->per_char + i;
    }
    CI = *cp;
    return Record_To_Vector (Char_Info_Rec, Char_Info_Size,
        Sym_Char_Info, FONT(f)->dpy, ~0L);
}

static Object P_Font_Properties (Object f) {
    register int i, n;
    Object v, a, val, x;
    GC_Node4;

    Check_Type (f, T_Font);
    n = FONT(f)->info->n_properties;
    v = Make_Vector (n, Null);
    a = val = Null;
    GC_Link4 (v, a, val, f);
    for (i = 0; i < n; i++) {
        register XFontProp *p = FONT(f)->info->properties+i;
        a = Make_Atom (p->name);
        val = Make_Unsigned_Long ((unsigned long)p->card32);
        x = Cons (a, val);
        VECTOR(v)->data[i] = x;
    }
    GC_Unlink;
    return v;
}

static Object P_Font_Path (Object d) {
    Object v;
    int i, n;
    char **ret;
    GC_Node;

    Check_Type (d, T_Display);
    Disable_Interrupts;
    ret = XGetFontPath (DISPLAY(d)->dpy, &n);
    Enable_Interrupts;
    v = Make_Vector (n, Null);
    GC_Link (v);
    for (i = 0; i < n; i++) {
        Object x;

        x = Make_String (ret[i], strlen (ret[i]));
        VECTOR(v)->data[i] = x;
    }
    GC_Unlink;
    XFreeFontPath (ret);
    return P_Vector_To_List (v);
}

static Object P_Set_Font_Path (Object d, Object p) {
    register char **path;
    register int i, n;
    Object c;
    Alloca_Begin;

    Check_Type (d, T_Display);
    Check_List (p);
    n = Fast_Length (p);
    Alloca (path, char**, n * sizeof (char *));
    for (i = 0; i < n; i++, p = Cdr (p)) {
        c = Car (p);
        Get_Strsym_Stack (c, path[i]);
    }
    XSetFontPath (DISPLAY(d)->dpy, path, n);
    Alloca_End;
    return Void;
}

void elk_init_xlib_font () {
    Define_Symbol (&Sym_Font_Info, "font-info");
    Define_Symbol (&Sym_Char_Info, "char-info");
    Define_Symbol (&Sym_Min, "min");
    Define_Symbol (&Sym_Max, "max");
    T_Font = Define_Type (0, "font", NOFUNC, sizeof (struct S_Font),
        Font_Equal, Font_Equal, Font_Print, Font_Visit);
    Define_Primitive (P_Fontp,           "font?",           1, 1, EVAL);
    Define_Primitive (P_Font_Display,    "font-display",    1, 1, EVAL);
    Define_Primitive (P_Open_Font,       "open-font",       2, 2, EVAL);
    Define_Primitive (P_Close_Font,      "close-font",      1, 1, EVAL);
    Define_Primitive (P_Font_Name,       "font-name",       1, 1, EVAL);
    Define_Primitive (P_Gcontext_Font,   "gcontext-font",   1, 1, EVAL);
    Define_Primitive (P_List_Font_Names, "list-font-names", 2, 2, EVAL);
    Define_Primitive (P_List_Fonts,      "list-fonts",      2, 2, EVAL);
    Define_Primitive (P_Font_Info,       "xlib-font-info",  1, 1, EVAL);
    Define_Primitive (P_Char_Info,       "xlib-char-info",  2, 2, EVAL);
    Define_Primitive (P_Font_Properties, "font-properties", 1, 1, EVAL);
    Define_Primitive (P_Font_Path,       "font-path",       1, 1, EVAL);
    Define_Primitive (P_Set_Font_Path,   "set-font-path!",  2, 2, EVAL);
}
