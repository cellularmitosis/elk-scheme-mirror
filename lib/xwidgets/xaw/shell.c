#include "../xt.h"

#include <X11/Shell.h>

void elk_init_xaw_shell () {
    XtResourceList r = 0;
    Define_Class ("application-shell", applicationShellWidgetClass, r, 0);
    Define_Class ("toplevel-shell", topLevelShellWidgetClass, r, 0);
    Define_Class ("transient-shell", transientShellWidgetClass, r, 0);
    Define_Class ("wm-shell", wmShellWidgetClass, r, 0);
    Define_Class ("override-shell", overrideShellWidgetClass, r, 0);
    Define_Class ("shell", shellWidgetClass, r, 0);
    P_Provide(Intern("xaw:shell"));
}
