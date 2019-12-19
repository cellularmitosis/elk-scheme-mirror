#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/Scale.h>

static Object Get_Scale_CB (XmScaleCallbackStruct *p) {
    Object ret, s;
    extern SYMDESCR Reason_Syms[];
    GC_Node2;

    ret = s = Make_Integer (p->value);
    GC_Link2 (ret, s);
    ret = Cons (ret, Null);
#ifdef SCALE_WIDGET_WORKS   /* It doesn't. */
    s = Get_Any_CB ((XmAnyCallbackStruct *)p);
#else
    s = Intern ("event-goes-here-when-Xm-is-fixed");
    s = Cons (s, Null);
    s = Cons (Bits_To_Symbols ((unsigned long)p->reason, 0, Reason_Syms), s);
#endif
    ret = Cons (Cdr (s), ret);
    ret = Cons (Car (s), ret);
    GC_Unlink;
    return ret;
}

static Object S_Callback_Scale_DragCallback (XtArgVal x) {
   return Get_Scale_CB ((XmScaleCallbackStruct *)x);
}

static Object S_Callback_Scale_ValueChangedCallback (XtArgVal x) {
   return Get_Scale_CB ((XmScaleCallbackStruct *)x);
}

void elk_init_motif_scale () {
    XtResourceList r = 0;
    Define_Class ("scale", xmScaleWidgetClass, r, 0);
    Define_Callback ("scale", "valueChangedCallback", 1);
    Define_Callback ("scale", "dragCallback", 1);
    Define_Converter_To_Scheme ("callback:scale-valueChangedCallback", S_Callback_Scale_ValueChangedCallback);
    Define_Converter_To_Scheme ("callback:scale-dragCallback", S_Callback_Scale_DragCallback);
    P_Provide(Intern("motif:scale"));
}
