#include "../xt.h"
#include <X11/Xaw/Repeater.h>

void elk_init_xaw_repeater () {
    XtResourceList r = 0;
    Define_Class ("repeater", repeaterWidgetClass, r, 0);
    Define_Callback ("repeater", "callback", 0);
    Define_Callback ("repeater", "stopCallback", 0);
    Define_Callback ("repeater", "startCallback", 0);
    P_Provide(Intern("xaw:repeater"));
}
