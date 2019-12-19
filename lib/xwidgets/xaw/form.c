#include "../xt.h"
#include <X11/Xaw/Form.h>

static Object P_Form_Do_Layout (Object w, Object enable) {
   Check_Widget_Class (w, formWidgetClass);
    Check_Type (enable, T_Boolean);
    XawFormDoLayout (WIDGET(w)->widget, EQ (enable, True));
    return Void;
}

void elk_init_xaw_form () {
    XtResourceList r = 0;
    Define_Class ("form", formWidgetClass, r, 0);
    Define_Primitive (P_Form_Do_Layout, "form-do-layout", 2, 2, EVAL);
    P_Provide(Intern("xaw:form"));
}
