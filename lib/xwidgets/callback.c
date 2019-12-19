/* callback.c
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

#include "xt.h"

void Remove_All_Callbacks (Widget w);

typedef struct {
    PFX2S converter;
    int num;
} CLIENT_DATA;

Object Get_Callbackfun (XtPointer c) {
    register CLIENT_DATA *cd = (CLIENT_DATA *)c;
    return cd ? Get_Function (cd->num) : False;
}

static void Callback_Proc (Widget w, XtPointer client_data,
                           XtPointer call_data) {
    register CLIENT_DATA *cd = (CLIENT_DATA *)client_data;
    Object args;
    GC_Node;

    args = Null;
    GC_Link (args);
    if (cd->converter)
        args = Cons ((cd->converter)((XtArgVal)call_data), args);
    args = Cons (Make_Widget_Foreign (w), args);
    GC_Unlink;
    (void)Funcall (Get_Callbackfun (client_data), args, 0);
}

/*ARGSUSED*/
void Destroy_Callback_Proc (Widget w, XtPointer client_data,
                            XtPointer call_data) {
    Object x;

    x = Find_Object (T_Widget, (GENERIC)0, Match_Xt_Obj, w);
    if (Nullp (x) || WIDGET(x)->free)
        return;
    WIDGET(x)->free = 1;
    Remove_All_Callbacks (w);
    Deregister_Object (x);
}

/* The code assumes that callbacks are called in the order they
 * have been added.  The Destroy_Callback_Proc() must always be
 * the last callback in the destroy callback list of each widget.
 *
 * When the destroy callback list of a widget is modified
 * (via P_Add_Callbacks or P_Set_Values), Fiddle_Destroy_Callback()
 * must be called to remove the Destroy_Callback_Proc() and put
 * it back to the end of the callback list.
 */
void Fiddle_Destroy_Callback (Widget w) {
    XtRemoveCallback (w, XtNdestroyCallback, Destroy_Callback_Proc,
        (XtPointer)0);
    XtAddCallback (w, XtNdestroyCallback, Destroy_Callback_Proc, (XtPointer)0);
}

void Check_Callback_List (Object x) {
    Object tail;

    Check_List (x);
    for (tail = x; !Nullp (tail); tail = Cdr (tail))
        Check_Procedure (Car (tail));
}

static Object P_Add_Callbacks (Object w, Object name, Object cbl) {
    register char *s;
    register int n;
    XtCallbackList callbacks;
    Alloca_Begin;

    Check_Widget (w);
    Check_Callback_List (cbl);
    s = Get_Strsym (name);
    Make_Resource_Name (s);
    n = Fast_Length (cbl);
    Alloca (callbacks, XtCallbackRec*, (n+1) * sizeof (XtCallbackRec));
    callbacks[n].callback = 0;
    callbacks[n].closure = 0;
    Fill_Callbacks (cbl, callbacks, n,
        Find_Callback_Converter (XtClass (WIDGET(w)->widget), s, name));
    XtAddCallbacks (WIDGET(w)->widget, s, callbacks);
    if (streq (s, XtNdestroyCallback))
        Fiddle_Destroy_Callback (WIDGET(w)->widget);
    Alloca_End;
    return Void;
}

void Fill_Callbacks (Object src, XtCallbackList dst, register int n,
                     PFX2S conv) {
    register CLIENT_DATA *cd;
    register int i, j;
    Object tail;

    for (i = 0, tail = src; i < n; i++, tail = Cdr (tail)) {
        j = Register_Function (Car (tail));
        cd = (CLIENT_DATA *)XtMalloc (sizeof (CLIENT_DATA));
        cd->converter = conv;
        cd->num = j;
        dst[i].callback = (XtCallbackProc)Callback_Proc;
        dst[i].closure = (XtPointer)cd;
    }
}

void Remove_All_Callbacks (Widget w) {
    Arg a[1];
    XtCallbackList c;
    XtResource *r;
    int nr, nc;
    register int i, j;

    Get_All_Resources (0, w, XtClass (w), &r, &nr, &nc);
    for (j = 0; j < nr; j++) {
        if (streq (r[j].resource_type, XtRCallback)) {
            XtSetArg (a[0], r[j].resource_name, &c);
            XtGetValues (w, a, 1);
            for (i = 0; c[i].callback; i++) {
                register CLIENT_DATA *cd = (CLIENT_DATA *)c[i].closure;
                if (c[i].callback == (XtCallbackProc)Callback_Proc && cd) {
                    Deregister_Function (cd->num);
                    XtFree ((char *)cd);
                }
            }
        }
    }
    XtFree ((char *)r);
}

void elk_init_xt_callback () {
    Define_Primitive (P_Add_Callbacks, "add-callbacks", 3, 3, EVAL);
}
