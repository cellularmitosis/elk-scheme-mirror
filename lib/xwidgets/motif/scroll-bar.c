#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/ScrollBar.h>

static Object Get_Scrollbar_CB (XmScrollBarCallbackStruct *p) {
    Object ret, s;
    GC_Node2;

    ret = s = Cons (Make_Integer (p->pixel), Null);
    GC_Link2 (ret, s);
    ret = Cons (Make_Integer (p->value), ret);
    s = Get_Any_CB ((XmAnyCallbackStruct *)p);
    ret = Cons (Cdr (s), ret);
    ret = Cons (Car (s), ret);
    GC_Unlink;
    return ret;
}

static Object S_Callback_Scroll_Bar_DecrementCallback (XtArgVal x) {
   return Get_Scrollbar_CB ((XmScrollBarCallbackStruct *)x);
}

static Object S_Callback_Scroll_Bar_IncrementCallback (XtArgVal x) {
   return Get_Scrollbar_CB ((XmScrollBarCallbackStruct *)x);
}

static Object S_Callback_Scroll_Bar_PageDecrementCallback (XtArgVal x) {
   return Get_Scrollbar_CB ((XmScrollBarCallbackStruct *)x);
}

static Object S_Callback_Scroll_Bar_PageIncrementCallback (XtArgVal x) {
   return Get_Scrollbar_CB ((XmScrollBarCallbackStruct *)x);
}

static Object S_Callback_Scroll_Bar_DragCallback (XtArgVal x) {
   return Get_Scrollbar_CB ((XmScrollBarCallbackStruct *)x);
}

static Object S_Callback_Scroll_Bar_ToTopCallback (XtArgVal x) {
   return Get_Scrollbar_CB ((XmScrollBarCallbackStruct *)x);
}

static Object S_Callback_Scroll_Bar_ToBottomCallback (XtArgVal x) {
   return Get_Scrollbar_CB ((XmScrollBarCallbackStruct *)x);
}

static Object S_Callback_Scroll_Bar_ValueChangedCallback (XtArgVal x) {
   return Get_Scrollbar_CB ((XmScrollBarCallbackStruct *)x);
}

void elk_init_motif_scrollbar () {
    XtResourceList r = 0;
    Define_Class ("scroll-bar", xmScrollBarWidgetClass, r, 0);
    Define_Callback ("scroll-bar", "valueChangedCallback", 1);
    Define_Callback ("scroll-bar", "toBottomCallback", 1);
    Define_Callback ("scroll-bar", "toTopCallback", 1);
    Define_Callback ("scroll-bar", "dragCallback", 1);
    Define_Callback ("scroll-bar", "pageIncrementCallback", 1);
    Define_Callback ("scroll-bar", "pageDecrementCallback", 1);
    Define_Callback ("scroll-bar", "incrementCallback", 1);
    Define_Callback ("scroll-bar", "decrementCallback", 1);
    Define_Converter_To_Scheme ("callback:scroll-bar-valueChangedCallback", S_Callback_Scroll_Bar_ValueChangedCallback);
    Define_Converter_To_Scheme ("callback:scroll-bar-toBottomCallback", S_Callback_Scroll_Bar_ToBottomCallback);
    Define_Converter_To_Scheme ("callback:scroll-bar-toTopCallback", S_Callback_Scroll_Bar_ToTopCallback);
    Define_Converter_To_Scheme ("callback:scroll-bar-dragCallback", S_Callback_Scroll_Bar_DragCallback);
    Define_Converter_To_Scheme ("callback:scroll-bar-pageIncrementCallback", S_Callback_Scroll_Bar_PageIncrementCallback);
    Define_Converter_To_Scheme ("callback:scroll-bar-pageDecrementCallback", S_Callback_Scroll_Bar_PageDecrementCallback);
    Define_Converter_To_Scheme ("callback:scroll-bar-incrementCallback", S_Callback_Scroll_Bar_IncrementCallback);
    Define_Converter_To_Scheme ("callback:scroll-bar-decrementCallback", S_Callback_Scroll_Bar_DecrementCallback);
    P_Provide(Intern("motif:scroll-bar"));
}
