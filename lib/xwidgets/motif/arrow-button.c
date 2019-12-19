#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/ArrowB.h>
#include <Xm/ArrowBG.h>

void elk_init_motif_arrowbutton () {
    XtResourceList r = 0;
    Define_Class ("arrow-button-gadget", xmArrowButtonGadgetClass, r, 0);
    Define_Class ("arrow-button", xmArrowButtonWidgetClass, r, 0);
    Define_Callback ("arrow-button-gadget", "disarmCallback", 1);
    Define_Callback ("arrow-button-gadget", "armCallback", 1);
    Define_Callback ("arrow-button-gadget", "activateCallback", 1);
    Define_Callback ("arrow-button", "disarmCallback", 1);
    Define_Callback ("arrow-button", "armCallback", 1);
    Define_Callback ("arrow-button", "activateCallback", 1);
    P_Provide(Intern("motif:arrow-button"));
}
