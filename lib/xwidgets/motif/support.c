#include "../xt.h"
#include <Xm/Xm.h>

SYMDESCR Reason_Syms[] = {
    { "none",                   XmCR_NONE },
    { "help",                   XmCR_HELP },
    { "value-changed",          XmCR_VALUE_CHANGED },
    { "increment",              XmCR_INCREMENT },
    { "decrement",              XmCR_DECREMENT },
    { "page-increment",         XmCR_PAGE_INCREMENT },
    { "page-decrement",         XmCR_PAGE_DECREMENT },
    { "to-top",                 XmCR_TO_TOP },
    { "to-bottom",              XmCR_TO_BOTTOM },
    { "drag",                   XmCR_DRAG },
    { "activate",               XmCR_ACTIVATE },
    { "arm",                    XmCR_ARM },
    { "disarm",                 XmCR_DISARM },
    { "map",                    XmCR_MAP },
    { "unmap",                  XmCR_UNMAP },
    { "focus",                  XmCR_FOCUS },
    { "losing-focus",           XmCR_LOSING_FOCUS },
    { "modifying-text-value",   XmCR_MODIFYING_TEXT_VALUE },

   { "moving-insert-cursor",   XmCR_MOVING_INSERT_CURSOR },
    { "execute",                XmCR_EXECUTE },
    { "single-select",          XmCR_SINGLE_SELECT },
    { "multiple-select",        XmCR_MULTIPLE_SELECT },
    { "extended-select",        XmCR_EXTENDED_SELECT },
    { "browse-select",          XmCR_BROWSE_SELECT },
    { "default-action",         XmCR_DEFAULT_ACTION },
    { "clipboard-data-request", XmCR_CLIPBOARD_DATA_REQUEST },
    { "clipboard-data-delete",  XmCR_CLIPBOARD_DATA_DELETE },
    { "cascading",              XmCR_CASCADING },
    { "ok",                     XmCR_OK },
    { "cancel",                 XmCR_CANCEL },
    { "apply",                  XmCR_APPLY },
    { "no-match",               XmCR_NO_MATCH },
    { "command-entered",        XmCR_COMMAND_ENTERED },
    { "command-changed",        XmCR_COMMAND_CHANGED },
    { "expose",                 XmCR_EXPOSE },
    { "resize",                 XmCR_RESIZE },
    { "input",                  XmCR_INPUT },
    { 0, 0 }
};

Object Get_Any_CB (void *_p) {
    XmAnyCallbackStruct *p = _p;
    Object args, ret;
    GC_Node2;

    args = ret = Null;
    GC_Link2 (ret, args);
    if (p->event) {
        args = Get_Event_Args (p->event);
        ret = Copy_List (args);
        Destroy_Event_Args (args);
    }
    ret = Cons (Bits_To_Symbols ((unsigned long)p->reason, 0, Reason_Syms),
              ret);
    GC_Unlink;
    return ret;
}

Object Get_Selection_CB (void *_p) {
    XmSelectionBoxCallbackStruct *p = _p;
    Object ret, s;
    char *text;
    GC_Node2;

    if (!XmStringGetLtoR (p->value, XmSTRING_DEFAULT_CHARSET, &text))
        text = "";
    ret = s = Make_String (text, strlen (text));
    GC_Link2 (ret, s);
    ret = Cons (ret, Null);
    s = Get_Any_CB ((XmAnyCallbackStruct *)p);
    ret = Cons (Cdr (s), ret);
    ret = Cons (Car (s), ret);
    GC_Unlink;
    return ret;
}

static XtArgVal Scheme_To_String_Table (Object x) {
    Object t;
    char *s;
    XmString *tab;
    int i = 0;
    Alloca_Begin;

    tab = (XmString *)XtMalloc (Get_Integer (P_Length (x))
        * sizeof (XmString));
    /* tab is never freed since the converter must return a new address
     * each time it is called.
     */
    for (t = x; TYPE(t) == T_Pair; t = Cdr (t)) {
        Get_Strsym_Stack (Car (t), s);
        tab[i++] = XmStringCreate (s, XmSTRING_DEFAULT_CHARSET);
    }
    Alloca_End;
    return (XtArgVal)tab;
}

static Object P_Update_Display (Object w) {
   Check_Widget (w);
    XmUpdateDisplay (WIDGET(w)->widget);
    return Void;
}

static Object S_KeySym (XtArgVal x) {
   return Make_Char ((int)x);
}

static XtArgVal C_KeySym (Object x) {
   Check_Type (x, T_Character); return (XtArgVal)CHAR(x);
}

static Object S_HorizontalPosition (XtArgVal x) {
   return Make_Integer (*(Position *)(void *)&x);
}

static Object S_VerticalPosition (XtArgVal x) {
   return Make_Integer (*(Position *)(void *)&x);
}

static Object S_HorizontalDimension (XtArgVal x) {
   return Make_Integer (*(Dimension *)(void *)&x);
}

static Object S_VerticalDimension (XtArgVal x) {
   return Make_Integer (*(Dimension *)(void *)&x);
}

static Object S_HorizontalInt (XtArgVal x) {
   return Make_Integer (*(int *)(void *)&x);
}

static Object S_VerticalInt (XtArgVal x) {
   return Make_Integer (*(int *)(void *)&x);
}

static XtArgVal C_HorizontalPosition (Object x) {
   return (XtArgVal)Get_Integer (x);
}

static XtArgVal C_VerticalPosition (Object x) {
   return (XtArgVal)Get_Integer (x);
}

static XtArgVal C_HorizontalDimension (Object x) {
   return (XtArgVal)Get_Unsigned (x);
}

static XtArgVal C_VerticalDimension (Object x) {
   return (XtArgVal)Get_Unsigned (x);
}

static XtArgVal C_HorizontalInt (Object x) {
   return (XtArgVal)Get_Integer (x);
}

static XtArgVal C_VerticalInt (Object x) {
   return (XtArgVal)Get_Integer (x);
}

static Object S_ShellHorizPos (XtArgVal x) {
   return Make_Integer (*(Position *)(void *)&x);
}

static Object S_ShellVertPos (XtArgVal x) {
   return Make_Integer (*(Position *)(void *)&x);
}

static Object S_ShellHorizDim (XtArgVal x) {
   return Make_Integer (*(Dimension *)(void *)&x);
}

static Object S_ShellVertDim (XtArgVal x) {
   return Make_Integer (*(Dimension *)(void *)&x);
}

static XtArgVal C_ShellHorizPos (Object x) {
   return (XtArgVal)Get_Integer (x);
}

static XtArgVal C_ShellVertPos (Object x) {
   return (XtArgVal)Get_Integer (x);
}

static XtArgVal C_ShellHorizDim (Object x) {
   return (XtArgVal)Get_Unsigned (x);
}

static XtArgVal C_ShellVertDim (Object x) {
   return (XtArgVal)Get_Unsigned (x);
}

static Object S_HorizontalScrollBar (XtArgVal x) {
   return Make_Widget_Foreign ((Widget)x);
}

static Object S_VerticalScrollBar (XtArgVal x) {
   return Make_Widget_Foreign ((Widget)x);
}

static Object S_WorkWindow (XtArgVal x) {
   return Make_Widget_Foreign ((Widget)x);
}

static Object S_CommandWindow (XtArgVal x) {
   return Make_Widget_Foreign ((Widget)x);
}

static Object S_MenuBar (XtArgVal x) {
   return Make_Widget_Foreign ((Widget)x);
}

static Object S_SubMenuId (XtArgVal x) {
   return Make_Widget_Foreign ((Widget)x);
}

static Object S_MenuHistory (XtArgVal x) {
   return Make_Widget_Foreign ((Widget)x);
}

static Object S_MenuHelpWidget (XtArgVal x) {
   return Make_Widget_Foreign ((Widget)x);
}

static Object S_BottomWidget (XtArgVal x) {
   return Make_Widget_Foreign ((Widget)x);
}

static Object S_LeftWidget (XtArgVal x) {
   return Make_Widget_Foreign ((Widget)x);
}

static Object S_RightWidget (XtArgVal x) {
   return Make_Widget_Foreign ((Widget)x);
}

static Object S_TopWidget (XtArgVal x) {
   return Make_Widget_Foreign ((Widget)x);
}

static XtArgVal C_HorizontalScrollBar (Object x) {
   extern WidgetClass xmScrollBarWidgetClass;
    Check_Widget_Class (x, xmScrollBarWidgetClass);
    return (XtArgVal)WIDGET(x)->widget;
}

static XtArgVal C_VerticalScrollBar (Object x) {
   extern WidgetClass xmScrollBarWidgetClass;
    Check_Widget_Class (x, xmScrollBarWidgetClass);
    return (XtArgVal)WIDGET(x)->widget;
}

static XtArgVal C_WorkWindow (Object x) {
   Check_Widget (x); return (XtArgVal)WIDGET(x)->widget;
}

static XtArgVal C_CommandWindow (Object x) {
   Check_Widget (x); return (XtArgVal)WIDGET(x)->widget;
}

static XtArgVal C_MenuBar (Object x) {
   Check_Widget (x); return (XtArgVal)WIDGET(x)->widget;
}

static XtArgVal C_SubMenuId (Object x) {
   Check_Widget (x); return (XtArgVal)WIDGET(x)->widget;
}

static XtArgVal C_MenuHistory (Object x) {
   Check_Widget (x); return (XtArgVal)WIDGET(x)->widget;
}

static XtArgVal C_MenuHelpWidget (Object x) {
   Check_Widget (x); return (XtArgVal)WIDGET(x)->widget;
}

static XtArgVal C_BottomWidget (Object x) {
   Check_Widget (x); return (XtArgVal)WIDGET(x)->widget;
}

static XtArgVal C_LeftWidget (Object x) {
   Check_Widget (x); return (XtArgVal)WIDGET(x)->widget;
}

static XtArgVal C_RightWidget (Object x) {
   Check_Widget (x); return (XtArgVal)WIDGET(x)->widget;
}

static XtArgVal C_TopWidget (Object x) {
   Check_Widget (x); return (XtArgVal)WIDGET(x)->widget;
}

static Object S_Callback_ApplyCallback (XtArgVal x) {
   return Get_Selection_CB ((XmSelectionBoxCallbackStruct *)x);
}

static Object S_Callback_CancelCallback (XtArgVal x) {
   return Get_Selection_CB ((XmSelectionBoxCallbackStruct *)x);
}

static Object S_Callback_NoMatchCallback (XtArgVal x) {
   return Get_Selection_CB ((XmSelectionBoxCallbackStruct *)x);
}

static Object S_Callback_OkCallback (XtArgVal x) {
   return Get_Selection_CB ((XmSelectionBoxCallbackStruct *)x);
}

static Object S_Callback_HelpCallback (XtArgVal x) {
   return Get_Any_CB ((XmAnyCallbackStruct *)x);
}

static Object S_Callback_ActivateCallback (XtArgVal x) {
   return Get_Any_CB ((XmAnyCallbackStruct *)x);
}

static Object S_Callback_ArmCallback (XtArgVal x) {
   return Get_Any_CB ((XmAnyCallbackStruct *)x);
}

static Object S_Callback_DisarmCallback (XtArgVal x) {
   return Get_Any_CB ((XmAnyCallbackStruct *)x);
}

static Object S_Callback_CascadingCallback (XtArgVal x) {
   return Get_Any_CB ((XmAnyCallbackStruct *)x);
}

static Object S_Callback_ExposeCallback (XtArgVal x) {
   return Get_Any_CB ((XmAnyCallbackStruct *)x);
}

static Object S_Callback_InputCallback (XtArgVal x) {
   return Get_Any_CB ((XmAnyCallbackStruct *)x);
}

static Object S_Callback_ResizeCallback (XtArgVal x) {
   return Get_Any_CB ((XmAnyCallbackStruct *)x);
}

static Object S_XmString (XtArgVal x) {
   char *text;
    if (!XmStringGetLtoR ((XmString)x, XmSTRING_DEFAULT_CHARSET, &text))
        text = "";
    return Make_String (text, strlen (text));
}

static XtArgVal C_XmString (Object x) {
   char *s;
    XtArgVal ret;
    Alloca_Begin;
    Get_Strsym_Stack (x, s);
    ret = (XtArgVal)XmStringCreateLtoR (s, XmSTRING_DEFAULT_CHARSET);
    Alloca_End;
    return ret;
}

static XtArgVal C_XmStringTable (Object x) {
   return Scheme_To_String_Table (x);
}

void elk_init_motif_support () {
    XtResourceList r = 0;
    Define_Class ("manager", xmManagerWidgetClass, r, 0);
    Define_Class ("primitive", xmPrimitiveWidgetClass, r, 0);
    Define_Primitive (P_Update_Display, "update-display", 1, 1, EVAL);
    Define_Converter_To_C ("XmStringTable", C_XmStringTable);
    Define_Converter_To_C ("XmString", C_XmString);
    Define_Converter_To_Scheme ("XmString", S_XmString);
    Define_Converter_To_Scheme ("callback:resizeCallback", S_Callback_ResizeCallback);
    Define_Converter_To_Scheme ("callback:inputCallback", S_Callback_InputCallback);
    Define_Converter_To_Scheme ("callback:exposeCallback", S_Callback_ExposeCallback);
    Define_Converter_To_Scheme ("callback:cascadingCallback", S_Callback_CascadingCallback);
    Define_Converter_To_Scheme ("callback:disarmCallback", S_Callback_DisarmCallback);
    Define_Converter_To_Scheme ("callback:armCallback", S_Callback_ArmCallback);
    Define_Converter_To_Scheme ("callback:activateCallback", S_Callback_ActivateCallback);
    Define_Converter_To_Scheme ("callback:helpCallback", S_Callback_HelpCallback);
    Define_Converter_To_Scheme ("callback:okCallback", S_Callback_OkCallback);
    Define_Converter_To_Scheme ("callback:noMatchCallback", S_Callback_NoMatchCallback);
    Define_Converter_To_Scheme ("callback:cancelCallback", S_Callback_CancelCallback);
    Define_Converter_To_Scheme ("callback:applyCallback", S_Callback_ApplyCallback);
    Define_Converter_To_C ("topWidget", C_TopWidget);
    Define_Converter_To_C ("rightWidget", C_RightWidget);
    Define_Converter_To_C ("leftWidget", C_LeftWidget);
    Define_Converter_To_C ("bottomWidget", C_BottomWidget);
    Define_Converter_To_C ("menuHelpWidget", C_MenuHelpWidget);
    Define_Converter_To_C ("menuHistory", C_MenuHistory);
    Define_Converter_To_C ("subMenuId", C_SubMenuId);
    Define_Converter_To_C ("menuBar", C_MenuBar);
    Define_Converter_To_C ("commandWindow", C_CommandWindow);
    Define_Converter_To_C ("workWindow", C_WorkWindow);
    Define_Converter_To_C ("verticalScrollBar", C_VerticalScrollBar);
    Define_Converter_To_C ("horizontalScrollBar", C_HorizontalScrollBar);
    Define_Converter_To_Scheme ("topWidget", S_TopWidget);
    Define_Converter_To_Scheme ("rightWidget", S_RightWidget);
    Define_Converter_To_Scheme ("leftWidget", S_LeftWidget);
    Define_Converter_To_Scheme ("bottomWidget", S_BottomWidget);
    Define_Converter_To_Scheme ("menuHelpWidget", S_MenuHelpWidget);
    Define_Converter_To_Scheme ("menuHistory", S_MenuHistory);
    Define_Converter_To_Scheme ("subMenuId", S_SubMenuId);
    Define_Converter_To_Scheme ("menuBar", S_MenuBar);
    Define_Converter_To_Scheme ("commandWindow", S_CommandWindow);
    Define_Converter_To_Scheme ("workWindow", S_WorkWindow);
    Define_Converter_To_Scheme ("verticalScrollBar", S_VerticalScrollBar);
    Define_Converter_To_Scheme ("horizontalScrollBar", S_HorizontalScrollBar);
    Define_Converter_To_C ("ShellVertDim", C_ShellVertDim);
    Define_Converter_To_C ("ShellHorizDim", C_ShellHorizDim);
    Define_Converter_To_C ("ShellVertPos", C_ShellVertPos);
    Define_Converter_To_C ("ShellHorizPos", C_ShellHorizPos);
    Define_Converter_To_Scheme ("ShellVertDim", S_ShellVertDim);
    Define_Converter_To_Scheme ("ShellHorizDim", S_ShellHorizDim);
    Define_Converter_To_Scheme ("ShellVertPos", S_ShellVertPos);
    Define_Converter_To_Scheme ("ShellHorizPos", S_ShellHorizPos);
    Define_Converter_To_C ("VerticalInt", C_VerticalInt);
    Define_Converter_To_C ("HorizontalInt", C_HorizontalInt);
    Define_Converter_To_C ("VerticalDimension", C_VerticalDimension);
    Define_Converter_To_C ("HorizontalDimension", C_HorizontalDimension);
    Define_Converter_To_C ("VerticalPosition", C_VerticalPosition);
    Define_Converter_To_C ("HorizontalPosition", C_HorizontalPosition);
    Define_Converter_To_Scheme ("VerticalInt", S_VerticalInt);
    Define_Converter_To_Scheme ("HorizontalInt", S_HorizontalInt);
    Define_Converter_To_Scheme ("VerticalDimension", S_VerticalDimension);
    Define_Converter_To_Scheme ("HorizontalDimension", S_HorizontalDimension);
    Define_Converter_To_Scheme ("VerticalPosition", S_VerticalPosition);
    Define_Converter_To_Scheme ("HorizontalPosition", S_HorizontalPosition);
    Define_Converter_To_C ("KeySym", C_KeySym);
    Define_Converter_To_Scheme ("KeySym", S_KeySym);
    P_Provide(Intern("motif:support"));
}
