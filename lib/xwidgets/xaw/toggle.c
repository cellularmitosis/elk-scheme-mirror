#include "../xt.h"
#include <X11/Xaw/Toggle.h>

static XtArgVal C_Toggle_RadioData (Object x) {
   return (XtArgVal)Get_Integer (x);
}

static Object S_Toggle_RadioData (XtArgVal x) {
   return Make_Integer ((int)x);
}

static Object P_Toggle_Change_Radio_Group (Object w1, Object w2) {
   Check_Widget_Class (w1, toggleWidgetClass);
    Check_Widget_Class (w2, toggleWidgetClass);
    XawToggleChangeRadioGroup (WIDGET(w1)->widget, WIDGET(w2)->widget);
    return Void;
}

static Object P_Toggle_Get_Current (Object w) {
   Check_Widget_Class (w, toggleWidgetClass);
    return Make_Integer ((int)XawToggleGetCurrent (WIDGET(w)->widget));
}

static Object P_Toggle_Set_Current (Object w, Object x) {
   Check_Widget_Class (w, toggleWidgetClass);
    XawToggleSetCurrent (WIDGET(w)->widget, (caddr_t)Get_Integer (x));
    return Void;
}

static Object P_Toggle_Unset_Current (Object w) {
   Check_Widget_Class (w, toggleWidgetClass);
    XawToggleUnsetCurrent (WIDGET(w)->widget);
    return Void;
}

void elk_init_xaw_toggle () {
    XtResourceList r = 0;
    Define_Class ("toggle", toggleWidgetClass, r, 0);
    Define_Callback ("toggle", "callback", 0);
    Define_Primitive (P_Toggle_Unset_Current, "toggle-unset-current!", 1, 1, EVAL);
    Define_Primitive (P_Toggle_Set_Current, "toggle-set-current!", 2, 2, EVAL);
    Define_Primitive (P_Toggle_Get_Current, "toggle-get-current", 1, 1, EVAL);
    Define_Primitive (P_Toggle_Change_Radio_Group, "toggle-change-radio-group!", 2, 2, EVAL);
    Define_Converter_To_Scheme ("toggle-radioData", S_Toggle_RadioData);
    Define_Converter_To_C ("toggle-radioData", C_Toggle_RadioData);
    P_Provide(Intern("xaw:toggle"));
}
