#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/Frame.h>

void elk_init_motif_frame () {
    XtResourceList r = 0;
    Define_Class ("frame", xmFrameWidgetClass, r, 0);
    P_Provide(Intern("motif:frame"));
}
