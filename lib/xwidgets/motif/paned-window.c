#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/PanedW.h>

extern WidgetClass xmSashWidgetClass;

void elk_init_motif_panedwindow () {
    XtResourceList r = 0;
    Define_Class ("sash", xmSashWidgetClass, r, 0);
    Define_Class ("paned-window", xmPanedWindowWidgetClass, r, 0);
    P_Provide(Intern("motif:paned-window"));
}
