#include "../xt.h"
#include <X11/Xaw/Dialog.h>

void elk_init_xaw_dialog () {
    XtResourceList r = 0;
    Define_Class ("dialog", dialogWidgetClass, r, 0);
    P_Provide(Intern("xaw:dialog"));
}
