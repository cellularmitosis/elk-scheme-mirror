/* wm.c
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

static Object Sym_Pointer_Root;

static Object P_Reparent_Window (Object w, Object parent, Object x,
                                 Object y) {
    Check_Type (w, T_Window);
    Check_Type (parent, T_Window);
    XReparentWindow (WINDOW(w)->dpy, WINDOW(w)->win, WINDOW(parent)->win,
        Get_Integer (x), Get_Integer (y));
    return Void;
}

static Object P_Install_Colormap (Object c) {
    Check_Type (c, T_Colormap);
    XInstallColormap (COLORMAP(c)->dpy, COLORMAP(c)->cm);
    return Void;
}

static Object P_Uninstall_Colormap (Object c) {
    Check_Type (c, T_Colormap);
    XUninstallColormap (COLORMAP(c)->dpy, COLORMAP(c)->cm);
    return Void;
}

static Object P_List_Installed_Colormaps (Object w) {
    int i, n;
    Colormap *ret;
    Object v;
    GC_Node;

    Check_Type (w, T_Window);
    ret = XListInstalledColormaps (WINDOW(w)->dpy, WINDOW(w)->win, &n);
    v = Make_Vector (n, Null);
    GC_Link (v);
    for (i = 0; i < n; i++) {
        Object c;

        c = Make_Colormap (0, WINDOW(w)->dpy, ret[i]);
        VECTOR(v)->data[i] = c;
    }
    XFree ((char *)ret);
    GC_Unlink;
    return v;
}

static Object P_Set_Input_Focus (Object d, Object win, Object revert_to,
                                 Object time) {
    Window focus = PointerRoot;

    Check_Type (d, T_Display);
    if (!EQ(win, Sym_Pointer_Root))
        focus = Get_Window (win);
    XSetInputFocus (DISPLAY(d)->dpy, focus, Symbols_To_Bits (revert_to, 0,
        Revert_Syms), Get_Time (time));
    return Void;
}

static Object P_Input_Focus (Object d) {
    Window win;
    int revert_to;
    Object ret, x;
    GC_Node;

    Check_Type (d, T_Display);
    XGetInputFocus (DISPLAY(d)->dpy, &win, &revert_to);
    ret = Cons (Null, Null);
    GC_Link (ret);
    x = Make_Window (0, DISPLAY(d)->dpy, win);
    Car (ret) = x;
    x = Bits_To_Symbols ((unsigned long)revert_to, 0, Revert_Syms);
    Cdr (ret) = x;
    GC_Unlink;
    return ret;
}

static Object P_General_Warp_Pointer (Object dpy, Object dst, Object dstx,
                                      Object dsty, Object src, Object srcx,
                                      Object srcy, Object srcw, Object srch) {
    Check_Type (dpy, T_Display);
    XWarpPointer (DISPLAY(dpy)->dpy, Get_Window (src), Get_Window (dst),
        Get_Integer (srcx), Get_Integer (srcy), Get_Integer (srcw),
        Get_Integer (srch), Get_Integer (dstx), Get_Integer (dsty));
    return Void;
}

static Object P_Bell (int argc, Object *argv) {
    register int percent = 0;

    Check_Type (argv[0], T_Display);
    if (argc == 2) {
        percent = Get_Integer (argv[1]);
        if (percent < -100 || percent > 100)
            Range_Error (argv[1]);
    }
    XBell (DISPLAY(argv[0])->dpy, percent);
    return Void;
}

static Object P_Set_Access_Control (Object dpy, Object on) {
    Check_Type (dpy, T_Display);
    Check_Type (on, T_Boolean);
    XSetAccessControl (DISPLAY(dpy)->dpy, EQ(on, True));
    return Void;
}

static Object P_Change_Save_Set (Object win, Object mode) {
    Check_Type (win, T_Window);
    XChangeSaveSet (WINDOW(win)->dpy, WINDOW(win)->win,
        Symbols_To_Bits (mode, 0, Saveset_Syms));
    return Void;
}

static Object P_Set_Close_Down_Mode (Object dpy, Object mode) {
    Check_Type (dpy, T_Display);
    XSetCloseDownMode (DISPLAY(dpy)->dpy,
        Symbols_To_Bits (mode, 0, Closemode_Syms));
    return Void;
}

static Object P_Get_Pointer_Mapping (Object dpy) {
    unsigned char map[256];
    register int i, n;
    Object ret;

    Check_Type (dpy, T_Display);
    n = XGetPointerMapping (DISPLAY(dpy)->dpy, map, 256);
    ret = Make_Vector (n, Null);
    for (i = 0; i < n; i++)
        VECTOR(ret)->data[i] = Make_Integer (map[i]);
    return ret;
}

static Object P_Set_Pointer_Mapping (Object dpy, Object map) {
    register int i, n;
    register unsigned char *p;
    Object ret;
    Alloca_Begin;

    Check_Type (dpy, T_Display);
    Check_Type (map, T_Vector);
    n = VECTOR(map)->size;
    Alloca (p, unsigned char*, n);
    for (i = 0; i < n; i++)
        p[i] = Get_Integer (VECTOR(map)->data[i]);
    ret = XSetPointerMapping (DISPLAY(dpy)->dpy, p, n) == MappingSuccess ?
        True : False;
    Alloca_End;
    return ret;
}

void elk_init_xlib_wm () {
    Define_Primitive (P_Reparent_Window,  "reparent-window",  4, 4, EVAL);
    Define_Primitive (P_Install_Colormap, "install-colormap", 1, 1, EVAL);
    Define_Primitive (P_Uninstall_Colormap,
                        "uninstall-colormap",                 1, 1, EVAL);
    Define_Primitive (P_List_Installed_Colormaps,
                        "list-installed-colormaps",           1, 1, EVAL);
    Define_Primitive (P_Set_Input_Focus,  "set-input-focus",  4, 4, EVAL);
    Define_Primitive (P_Input_Focus,      "input-focus",      1, 1, EVAL);
    Define_Primitive (P_General_Warp_Pointer,
                        "general-warp-pointer",               9, 9, EVAL);
    Define_Primitive (P_Bell,             "bell",             1, 2, VARARGS);
    Define_Primitive (P_Set_Access_Control,
                        "set-access-control",                 2, 2, EVAL);
    Define_Primitive (P_Change_Save_Set,  "change-save-set",  2, 2, EVAL);
    Define_Primitive (P_Set_Close_Down_Mode,
                        "set-close-down-mode",                2, 2, EVAL);
    Define_Primitive (P_Get_Pointer_Mapping,
                        "get-pointer-mapping",                1, 1, EVAL);
    Define_Primitive (P_Set_Pointer_Mapping,
                        "set-pointer-mapping",                2, 2, EVAL);
    Define_Symbol(&Sym_Pointer_Root, "pointer-root");
}
