#include "../xt.h"
#include <X11/Xaw/Sme.h>

void elk_init_xaw_sme () {
    XtResourceList r = 0;
    Define_Class ("sme", smeObjectClass, r, 0);
    P_Provide(Intern("xaw:sme"));
}
