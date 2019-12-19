#include "../xt.h"
#include <X11/Xaw/Grip.h>

static Object S_Callback_Grip_Callback (XtArgVal x) {
   Object args, ret, t;
    register unsigned int i;
    GripCallData p = (GripCallData)x;
    GC_Node3;

    args = ret = t = Null;
    GC_Link3 (args, ret, t);
    args = Get_Event_Args (p->event);
    ret = Cons (Copy_List (args), Null);
    Destroy_Event_Args (args);
    t = P_Make_List (Make_Integer (p->num_params), Null);
    for (i = 0, Cdr (ret) = t; i < p->num_params; i++, t = Cdr (t)) {
        Object s;

        s = Make_String (p->params[i], strlen (p->params[i]));
        Car (t) = s;
    }
    GC_Unlink;
    return ret;
}

void elk_init_xaw_grip () {
    XtResourceList r = 0;
    Define_Class ("grip", gripWidgetClass, r, 0);
    Define_Callback ("grip", "callback", 1);
    Define_Converter_To_Scheme ("callback:grip-callback", S_Callback_Grip_Callback);
    P_Provide(Intern("xaw:grip"));
}
