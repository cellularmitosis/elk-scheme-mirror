#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>

void elk_init_motif_shell () {
    XtResourceList r = 0;
    r = (XtResourceList)XtMalloc (2 * sizeof (XtResource));
    r[0].resource_name = "width";
    r[0].resource_class = "Width";
    r[0].resource_type = "Dimension";
    r[1].resource_name = "height";
    r[1].resource_class = "Height";
    r[1].resource_type = "Dimension";
    Define_Class ("menu-shell", xmMenuShellWidgetClass, r, 2);
    Define_Class ("dialog-shell", xmDialogShellWidgetClass, r, 0);
    Define_Class ("application-shell", applicationShellWidgetClass, r, 0);
    Define_Class ("toplevel-shell", topLevelShellWidgetClass, r, 0);
    Define_Class ("transient-shell", transientShellWidgetClass, r, 0);
    Define_Class ("vendor-shell", vendorShellWidgetClass, r, 0);
    Define_Class ("wm-shell", wmShellWidgetClass, r, 0);
    Define_Class ("override-shell", overrideShellWidgetClass, r, 0);
    Define_Class ("shell", shellWidgetClass, r, 0);
    P_Provide(Intern("motif:shell"));
}
