#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/LabelG.h>

void elk_init_motif_label () {
    XtResourceList r = 0;
    Define_Class ("label-gadget", xmLabelGadgetClass, r, 0);
    Define_Class ("label", xmLabelWidgetClass, r, 0);
    P_Provide(Intern("motif:label"));
}
