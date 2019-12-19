#include "../xt.h"
#include <X11/Xaw/Viewport.h>

void elk_init_xaw_viewport () {
    XtResourceList r = 0;
    Define_Class ("viewport", viewportWidgetClass, r, 0);
    P_Provide(Intern("xaw:viewport"));
}
