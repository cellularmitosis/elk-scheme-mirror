#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/DrawnB.h>

void elk_init_motif_drawnbutton () {
    XtResourceList r = 0;
    Define_Class ("drawn-button", xmDrawnButtonWidgetClass, r, 0);
    Define_Callback ("drawn-button", "resizeCallback", 1);
    Define_Callback ("drawn-button", "exposeCallback", 1);
    Define_Callback ("drawn-button", "disarmCallback", 1);
    Define_Callback ("drawn-button", "armCallback", 1);
    Define_Callback ("drawn-button", "activateCallback", 1);
    P_Provide(Intern("motif:drawn-button"));
}
