#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/DrawingA.h>

void elk_init_motif_drawingarea () {
    XtResourceList r = 0;
    Define_Class ("drawing-area", xmDrawingAreaWidgetClass, r, 0);
    Define_Callback ("drawing-area", "resizeCallback", 1);
    Define_Callback ("drawing-area", "inputCallback", 1);
    Define_Callback ("drawing-area", "exposeCallback", 1);
    P_Provide(Intern("motif:drawing-area"));
}
