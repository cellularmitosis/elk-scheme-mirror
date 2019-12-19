#include "../xt.h"
#include <X11/Xaw/Label.h>

void elk_init_xaw_label () {
    XtResourceList r = 0;
    Define_Class ("label", labelWidgetClass, r, 0);
    P_Provide(Intern("xaw:label"));
}
