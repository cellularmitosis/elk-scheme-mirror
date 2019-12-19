#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/MainW.h>

void elk_init_motif_mainwindow () {
    XtResourceList r = 0;
    Define_Class ("main-window", xmMainWindowWidgetClass, r, 0);
    P_Provide(Intern("motif:main-window"));
}
