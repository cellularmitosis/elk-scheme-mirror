#include "../xt.h"
#include <X11/Xaw/Panner.h>

static Object S_Callback_Panner_ReportCallback (XtArgVal x) {
   XawPannerReport *p = (XawPannerReport *)x;

    return Cons (Make_Integer (p->slider_x), Make_Integer (p->slider_y));
}

void elk_init_xaw_panner () {
    XtResourceList r = 0;
    Define_Class ("panner", pannerWidgetClass, r, 0);
    Define_Callback ("panner", "reportCallback", 1);
    Define_Converter_To_Scheme ("callback:panner-reportCallback", S_Callback_Panner_ReportCallback);
    P_Provide(Intern("xaw:panner"));
}
