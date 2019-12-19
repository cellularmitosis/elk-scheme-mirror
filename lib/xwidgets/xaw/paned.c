#include "../xt.h"
#include <X11/Xaw/Paned.h>

static Object P_Paned_Allow_Resize (Object w, Object enable) {
   Check_Widget (w);
    Check_Type (enable, T_Boolean);
    XawPanedAllowResize (WIDGET(w)->widget, EQ (enable, True));
    return Void;
}

static Object P_Paned_Set_Min_Max (Object w, Object min, Object max) {
   Check_Widget (w);
    XawPanedSetMinMax (WIDGET(w)->widget, Get_Integer (min),
        Get_Integer (max));
    return Void;
}

static Object P_Paned_Get_Min_Max (Object w) {
   int min, max;
    Check_Widget (w);
    XawPanedGetMinMax (WIDGET(w)->widget, &min, &max);
    return Cons (Make_Integer (min), Make_Integer (max));
}

static Object P_Paned_Set_Refigure_Mode (Object w, Object enable) {
   Check_Widget_Class (w, panedWidgetClass);
    Check_Type (enable, T_Boolean);
    XawPanedSetRefigureMode (WIDGET(w)->widget, EQ (enable, True));
    return Void;
}

static Object P_Paned_Get_Num_Sub (Object w) {
   Check_Widget_Class (w, panedWidgetClass);
    return Make_Integer (XawPanedGetNumSub (WIDGET(w)->widget));
}

void elk_init_xaw_paned () {
    XtResourceList r = 0;
    Define_Class ("paned", panedWidgetClass, r, 0);
    Define_Primitive (P_Paned_Get_Num_Sub, "paned-get-num-sub", 1, 1, EVAL);
    Define_Primitive (P_Paned_Set_Refigure_Mode, "paned-set-refigure-mode!", 2, 2, EVAL);
    Define_Primitive (P_Paned_Get_Min_Max, "paned-get-min-max", 1, 1, EVAL);
    Define_Primitive (P_Paned_Set_Min_Max, "paned-set-min-max!", 3, 3, EVAL);
    Define_Primitive (P_Paned_Allow_Resize, "paned-allow-resize", 2, 2, EVAL);
    P_Provide(Intern("xaw:paned"));
}
