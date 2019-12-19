#include "../xt.h"
#include <X11/Xaw/Command.h>

void elk_init_xaw_command () {
    XtResourceList r = 0;
    Define_Class ("command", commandWidgetClass, r, 0);
    Define_Callback ("command", "callback", 0);
    P_Provide(Intern("xaw:command"));
}
