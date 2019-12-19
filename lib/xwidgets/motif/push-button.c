#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>

void elk_init_motif_pushbutton () {
    XtResourceList r = 0;
    Define_Class ("push-button-gadget", xmPushButtonGadgetClass, r, 0);
    Define_Class ("push-button", xmPushButtonWidgetClass, r, 0);
    Define_Callback ("push-button-gadget", "disarmCallback", 1);
    Define_Callback ("push-button-gadget", "armCallback", 1);
    Define_Callback ("push-button-gadget", "activateCallback", 1);
    Define_Callback ("push-button", "disarmCallback", 1);
    Define_Callback ("push-button", "armCallback", 1);
    Define_Callback ("push-button", "activateCallback", 1);
    P_Provide(Intern("motif:push-button"));
}
