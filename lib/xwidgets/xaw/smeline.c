#include "../xt.h"
#include <X11/Xaw/SmeLine.h>

void elk_init_xaw_smeline () {
    XtResourceList r = 0;
    Define_Class ("smeline", smeLineObjectClass, r, 0);
    P_Provide(Intern("xaw:smeline"));
}
