#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/Separator.h>
#include <Xm/SeparatoG.h>

void elk_init_motif_separator () {
    XtResourceList r = 0;
    Define_Class ("separator-gadget", xmSeparatorGadgetClass, r, 0);
    Define_Class ("separator", xmSeparatorWidgetClass, r, 0);
    P_Provide(Intern("motif:separator"));
}
