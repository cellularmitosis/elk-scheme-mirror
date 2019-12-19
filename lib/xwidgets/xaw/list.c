#include "../xt.h"
#include <X11/Xaw/List.h>


static char **Get_List (Object x) {
    register int i, n;
    register char *s, **l;
    Alloca_Begin;

    Check_List (x);
    n = Fast_Length (x);
    l = (char **)XtMalloc ((n+1) * sizeof (char *));
    for (i = 0; i < n; i++, x = Cdr (x)) {
        Get_Strsym_Stack (Car (x), s);
        l[i] = XtNewString (s);
    }
    l[i] = 0;
    Alloca_End;
    return l;
}

static Object S_Callback_List_Callback (XtArgVal x) {
   XawListReturnStruct *p = (XawListReturnStruct *)x;
    return Cons (Make_String (p->string, strlen (p->string)),
        Make_Integer (p->list_index));
}

static XtArgVal C_List_List (Object x) {
   return (XtArgVal)Get_List (x);
}

static Object P_List_Change (Object w, Object x, Object resize) {
   Check_Widget_Class (w, listWidgetClass);
    Check_Type (resize, T_Boolean);
    XawListChange (WIDGET(w)->widget, Get_List (x), 0, 0, EQ (resize, True));
    return Void;
}

static Object P_List_Highlight (Object w, Object i) {
   Check_Widget_Class (w, listWidgetClass);
    XawListHighlight (WIDGET(w)->widget, Get_Integer (i));
    return Void;
}

static Object P_List_Unhighlight (Object w) {
   Check_Widget_Class (w, listWidgetClass);
    XawListUnhighlight (WIDGET(w)->widget);
    return Void;
}

static Object P_List_Current (Object w) {
   XawListReturnStruct *p;

    Check_Widget_Class (w, listWidgetClass);
    p = XawListShowCurrent (WIDGET(w)->widget);
    if (p->list_index == XAW_LIST_NONE)
        return False;
    return Cons (Make_String (p->string, strlen (p->string)),
        Make_Integer (p->list_index));
}

void elk_init_xaw_list () {
    XtResourceList r = 0;
    Define_Class ("list", listWidgetClass, r, 0);
    Define_Callback ("list", "callback", 1);
    Define_Primitive (P_List_Current, "list-current", 1, 1, EVAL);
    Define_Primitive (P_List_Unhighlight, "list-unhighlight", 1, 1, EVAL);
    Define_Primitive (P_List_Highlight, "list-highlight", 2, 2, EVAL);
    Define_Primitive (P_List_Change, "list-change!", 3, 3, EVAL);
    Define_Converter_To_C ("list-list", C_List_List);
    Define_Converter_To_Scheme ("callback:list-callback", S_Callback_List_Callback);
    P_Provide(Intern("xaw:list"));
}
