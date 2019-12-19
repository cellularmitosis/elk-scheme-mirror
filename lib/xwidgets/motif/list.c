#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/List.h>

static Object String_Table_To_Scheme (XmString *tab, int len) {
    Object ret, tail;
    char *text;
    GC_Node2;

    tail = ret = P_Make_List (Make_Integer (len), Null);
    GC_Link2 (ret, tail);
    for ( ; len > 0; len--, tail = Cdr (tail)) {
        if (!XmStringGetLtoR (*tab++, XmSTRING_DEFAULT_CHARSET, &text))
            text = "";
        Car (tail) = Make_String (text, strlen (text));
    }
    GC_Unlink;
    return ret;
}

static SYMDESCR Type_Syms[] = {
   { "initial",      XmINITIAL },
   { "modification", XmMODIFICATION },
   { "addition",     XmADDITION },
   { 0, 0}
};

static Object Get_List_CB (XmListCallbackStruct *p) {
    Object ret, s;
    char *text;
    GC_Node2;

    if (!XmStringGetLtoR (p->item, XmSTRING_DEFAULT_CHARSET, &text))
        text = "";
    ret = s = Make_String (text, strlen (text));
    GC_Link2 (ret, s);
    ret = Cons (ret, Null);
    if (p->reason == XmCR_MULTIPLE_SELECT
            || p->reason == XmCR_EXTENDED_SELECT) {
        s = String_Table_To_Scheme (p->selected_items, p->selected_item_count);
        ret = Cons (s, ret);
        s = Bits_To_Symbols ((unsigned long)p->selection_type, 0, Type_Syms);
        ret = Cons (s, ret);
    } else {
        ret = Cons (Make_Integer (p->item_position), ret);
    }
    s = Get_Any_CB ((XmAnyCallbackStruct *)p);
    ret = Cons (Cdr (s), ret);
    ret = Cons (Car (s), ret);
    GC_Unlink;
    return ret;
}

static Object S_Callback_List_BrowseSelectionCallback (XtArgVal x) {
   return Get_List_CB ((XmListCallbackStruct *)x);
}

static Object S_Callback_List_DefaultActionCallback (XtArgVal x) {
   return Get_List_CB ((XmListCallbackStruct *)x);
}

static Object S_Callback_List_ExtendedSelectionCallback (XtArgVal x) {
   return Get_List_CB ((XmListCallbackStruct *)x);
}

static Object S_Callback_List_MultipleSelectionCallback (XtArgVal x) {
   return Get_List_CB ((XmListCallbackStruct *)x);
}

static Object S_Callback_List_SingleSelectionCallback (XtArgVal x) {
   return Get_List_CB ((XmListCallbackStruct *)x);
}

void elk_init_motif_list () {
    XtResourceList r = 0;
    Define_Class ("list", xmListWidgetClass, r, 0);
    Define_Callback ("list", "singleSelectionCallback", 1);
    Define_Callback ("list", "multipleSelectionCallback", 1);
    Define_Callback ("list", "extendedSelectionCallback", 1);
    Define_Callback ("list", "defaultActionCallback", 1);
    Define_Callback ("list", "browseSelectionCallback", 1);
    Define_Converter_To_Scheme ("callback:list-singleSelectionCallback", S_Callback_List_SingleSelectionCallback);
    Define_Converter_To_Scheme ("callback:list-multipleSelectionCallback", S_Callback_List_MultipleSelectionCallback);
    Define_Converter_To_Scheme ("callback:list-extendedSelectionCallback", S_Callback_List_ExtendedSelectionCallback);
    Define_Converter_To_Scheme ("callback:list-defaultActionCallback", S_Callback_List_DefaultActionCallback);
    Define_Converter_To_Scheme ("callback:list-browseSelectionCallback", S_Callback_List_BrowseSelectionCallback);
    P_Provide(Intern("motif:list"));
}
