#include "../xt.h"
#include <X11/Xaw/StripChart.h>

static void Get_Value (Widget w, XtPointer client_data, XtPointer value) {
    Object ret;

    ret = Funcall (Get_Function ((int)client_data), Null, 0);
    switch (TYPE(ret)) {
    case T_Fixnum: *(double *)value = (double)FIXNUM(ret); break;
    case T_Flonum: *(double *)value = FLONUM(ret)->val; break;
    case T_Bignum: *(double *)value = Bignum_To_Double (ret); break;
    default: Primitive_Error ("stripchart sampler must return number");
    }
}

static Object P_Stripchart_Set_Sampler (Object w, Object p) {
   int i;
    Arg a[1];
    XtCallbackList c;

    Check_Widget_Class (w, stripChartWidgetClass);
    Check_Procedure (p);
    XtSetArg (a[0], XtNgetValue, &c);
    XtGetValues (WIDGET(w)->widget, a, 1);
    if (c[0].callback)
        Primitive_Error ("stripchart already has a sampler");
    i = Register_Function (p);
    XtAddCallback (WIDGET(w)->widget, XtNgetValue, Get_Value, (XtPointer)i);
    return Make_Id ('s', (XtPointer)WIDGET(w)->widget, i);
}

static Object P_Stripchart_Remove_Sampler (Object i) {
   Widget w;

    w = (Widget)Use_Id (i, 's');
    XtRemoveCallback (w, XtNgetValue, Get_Value,
        (XtPointer)IDENTIFIER(i)->num);
    Deregister_Function (IDENTIFIER(i)->num);
    return Void;
}

void elk_init_xaw_stripchart () {
    XtResourceList r = 0;
    Define_Class ("stripchart", stripChartWidgetClass, r, 0);
    Define_Primitive (P_Stripchart_Remove_Sampler, "stripchart-remove-sampler", 1, 1, EVAL);
    Define_Primitive (P_Stripchart_Set_Sampler, "stripchart-set-sampler", 2, 2, EVAL);
    P_Provide(Intern("xaw:stripchart"));
}
