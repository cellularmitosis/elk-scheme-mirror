#include "../xt.h"
#include <X11/Xaw/Box.h>

void elk_init_xaw_box () {
    XtResourceList r = 0;
    Define_Class ("box", boxWidgetClass, r, 0);
    P_Provide(Intern("xaw:box"));
}
