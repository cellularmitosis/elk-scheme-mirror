#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/RowColumn.h>

static SYMDESCR Type_Syms[] = {
   { "work-area",        XmWORK_AREA },
   { "menu-bar",         XmMENU_BAR },
   { "menu-pulldown",    XmMENU_PULLDOWN },
   { "menu-popup",       XmMENU_POPUP },
   { "menu-option",      XmMENU_OPTION },
   { 0, 0}
};

static void Post_Handler (Widget w, XtPointer client_data, XEvent *event,
                          Boolean *unused) {
    unsigned int b;
    Arg a;
    XButtonPressedEvent *ep = (XButtonPressedEvent *)event;
    Widget popup = (Widget)client_data;

    XtSetArg (a, XmNwhichButton, &b);
    XtGetValues (popup, &a, 1);
    if (ep->button != b)
        return;
    XmMenuPosition (popup, ep);
    XtManageChild (popup);
}

static Object Get_Row_Column_CB (XmRowColumnCallbackStruct *p) {
    Object ret, s;
    GC_Node2;

    ret = s = Make_Widget_Foreign (p->widget);
    GC_Link2 (ret, s);
    ret = Cons (ret, Null);
    s = Get_Any_CB ((XmAnyCallbackStruct *)p);
    ret = Cons (Cdr (s), ret);
    ret = Cons (Car (s), ret);
    GC_Unlink;
    return ret;
}

static Object P_Popup_Menu_Attach_To (Object m, Object w) {
   XtPointer client_data;
    Arg a;
    Check_Widget_Class (m, xmRowColumnWidgetClass);
    Check_Widget (w);
    XtSetArg (a, XmNuserData, &client_data);
    XtGetValues (WIDGET(w)->widget, &a, 1);
    if (client_data)
        XtRemoveEventHandler (WIDGET(w)->widget, ButtonPressMask, 0,
            Post_Handler, client_data);
    client_data = (XtPointer)WIDGET(m)->widget;
    XtAddEventHandler (WIDGET(w)->widget, ButtonPressMask, 0,
        Post_Handler, client_data);
    client_data = (XtPointer)WIDGET(m)->widget;
    XtSetValues (WIDGET(w)->widget, &a, 1);
    return Void;
}

static Object S_Callback_Row_Column_EntryCallback (XtArgVal x) {
   return Get_Row_Column_CB ((XmRowColumnCallbackStruct *)x);
}

static XtArgVal C_Row_Column_RowColumnType (Object x) {
   return (XtArgVal)Symbols_To_Bits (x, 0, Type_Syms);
}

static XtArgVal C_Row_Column_WhichButton (Object x) {
   return (XtArgVal)Get_Integer (x);
}

static Object S_Row_Column_WhichButton (XtArgVal x) {
   return Make_Integer (x);
}

static XtArgVal C_Row_Column_EntryClass (Object x) {
   Check_Type (x, T_Class); return (XtArgVal)CLASS(x)->wclass;
}

static Object S_Row_Column_EntryClass (XtArgVal x) {
   return Make_Widget_Class ((WidgetClass)x);
}

void elk_init_motif_rowcolumn () {
    XtResourceList r = 0;
    Define_Class ("row-column", xmRowColumnWidgetClass, r, 0);
    Define_Callback ("row-column", "entryCallback", 1);
    Define_Primitive (P_Popup_Menu_Attach_To, "popup-menu-attach-to!", 2, 2, EVAL);
    Define_Converter_To_Scheme ("row-column-entryClass", S_Row_Column_EntryClass);
    Define_Converter_To_C ("row-column-entryClass", C_Row_Column_EntryClass);
    Define_Converter_To_Scheme ("row-column-whichButton", S_Row_Column_WhichButton);
    Define_Converter_To_C ("row-column-whichButton", C_Row_Column_WhichButton);
    Define_Converter_To_C ("row-column-rowColumnType", C_Row_Column_RowColumnType);
    Define_Converter_To_Scheme ("callback:row-column-entryCallback", S_Callback_Row_Column_EntryCallback);
    P_Provide(Intern("motif:row-column"));
}
