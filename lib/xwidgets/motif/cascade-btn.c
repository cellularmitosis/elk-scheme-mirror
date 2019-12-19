#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/CascadeB.h>
#include <Xm/CascadeBG.h>

void elk_init_motif_cascadebutton () {
    XtResourceList r = 0;
    Define_Class ("cascade-button-gadget", xmCascadeButtonGadgetClass, r, 0);
    Define_Class ("cascade-button", xmCascadeButtonWidgetClass, r, 0);
    Define_Callback ("cascade-button-gadget", "cascadingCallback", 1);
    Define_Callback ("cascade-button-gadget", "activateCallback", 1);
    Define_Callback ("cascade-button", "cascadingCallback", 1);
    Define_Callback ("cascade-button", "activateCallback", 1);
    P_Provide(Intern("motif:cascade-btn"));
}
