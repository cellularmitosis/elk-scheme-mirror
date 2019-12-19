#include "../xt.h"
#include <X11/Xaw/Porthole.h>

static SYMDESCR Panner_Syms[] = {
    { "slider-x",       XawPRSliderX },
    { "slider-y",       XawPRSliderY },
    { "slider-width",   XawPRSliderWidth },
    { "slider-height",  XawPRSliderHeight },
    { "canvas-width",   XawPRCanvasWidth },
    { "canvas-height",  XawPRCanvasHeight },
    { 0, 0 }
};

static Object S_Callback_Porthole_ReportCallback (XtArgVal x) {
   Object ret;
    XawPannerReport *p = (XawPannerReport *)x;
    GC_Node;

    ret = Null;
    GC_Link (ret);
    ret = Cons (Make_Integer (p->canvas_height), ret);
    ret = Cons (Make_Integer (p->canvas_width), ret);
    ret = Cons (Make_Integer (p->slider_height), ret);
    ret = Cons (Make_Integer (p->slider_width), ret);
    ret = Cons (Make_Integer (p->slider_y), ret);
    ret = Cons (Make_Integer (p->slider_x), ret);
    ret = Cons (Bits_To_Symbols ((unsigned long)p->changed, 1, Panner_Syms),
        ret);
    GC_Unlink;
    return ret;
}

void elk_init_xaw_porthole () {
    XtResourceList r = 0;
    Define_Class ("porthole", portholeWidgetClass, r, 0);
    Define_Callback ("porthole", "reportCallback", 1);
    Define_Converter_To_Scheme ("callback:porthole-reportCallback", S_Callback_Porthole_ReportCallback);
    P_Provide(Intern("xaw:porthole"));
}
