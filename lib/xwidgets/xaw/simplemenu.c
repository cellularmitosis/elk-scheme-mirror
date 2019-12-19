#include "../xt.h"
#include <X11/Xaw/SimpleMenu.h>

static Object P_Simplemenu_Add_Global_Actions (Object c) {
   Check_Context (c);
    XawSimpleMenuAddGlobalActions (CONTEXT(c)->context);
    return Void;
}

static Object P_Simplemenu_Get_Active_Entry (Object w) {
   Check_Widget_Class (w, simpleMenuWidgetClass);
    return
        Make_Widget_Foreign (XawSimpleMenuGetActiveEntry (WIDGET(w)->widget));
}

static Object P_Simplemenu_Clear_Active_Entry (Object w) {
   Check_Widget_Class (w, simpleMenuWidgetClass);
    XawSimpleMenuClearActiveEntry (WIDGET(w)->widget);
    return Void;
}

void elk_init_xaw_simplemenu () {
    XtResourceList r = 0;
    Define_Class ("simplemenu", simpleMenuWidgetClass, r, 0);
    Define_Primitive (P_Simplemenu_Clear_Active_Entry, "simplemenu-clear-active-entry", 1, 1, EVAL);
    Define_Primitive (P_Simplemenu_Get_Active_Entry, "simplemenu-get-active-entry", 1, 1, EVAL);
    Define_Primitive (P_Simplemenu_Add_Global_Actions, "simplemenu-add-global-actions", 1, 1, EVAL);
    P_Provide(Intern("xaw:simplemenu"));
}
