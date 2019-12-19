#include "../xt.h"
#include <X11/Xaw/SmeBSB.h>

void elk_init_xaw_smebsb () {
    XtResourceList r = 0;
    Define_Class ("smebsb", smeBSBObjectClass, r, 0);
    Define_Callback ("smebsb", "callback", 0);
    P_Provide(Intern("xaw:smebsb"));
}
