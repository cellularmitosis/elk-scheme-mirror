#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/Form.h>

void elk_init_motif_form () {
    XtResourceList r = 0;
    Define_Class ("form", xmFormWidgetClass, r, 0);
    P_Provide(Intern("motif:form"));
}
