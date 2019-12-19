#include "../xt.h"
#include <X11/Xaw/Scrollbar.h>

static SYMDESCR Orientation_Syms[] = {
    { "horizontal",  XtorientHorizontal },
    { "vertical",    XtorientVertical },
    { 0, 0 }
};

static XtArgVal C_Scrollbar_Orientation (Object x) {
   return (XtArgVal)Symbols_To_Bits (x, 0, Orientation_Syms);
}

static Object S_Scrollbar_Orientation (XtArgVal x) {
   return Bits_To_Symbols ((unsigned long)x, 0, Orientation_Syms);
}

static Object S_Callback_Scrollbar_ScrollProc (XtArgVal x) {
    return Make_Integer ((int)x);
}

static Object S_Callback_Scrollbar_JumpProc (XtArgVal x) {
    return Make_Reduced_Flonum ((double)*(float *)x);
}

static Object P_Scrollbar_Set_Thumb (Object w, Object t, Object s) {
   Check_Widget_Class (w, scrollbarWidgetClass);
    XawScrollbarSetThumb (WIDGET(w)->widget, Get_Double (t), Get_Double (s));
    return Void;
}

void elk_init_xaw_scrollbar () {
    XtResourceList r = 0;
    Define_Class ("scrollbar", scrollbarWidgetClass, r, 0);
    Define_Callback ("scrollbar", "jumpProc", 1);
    Define_Callback ("scrollbar", "scrollProc", 1);
    Define_Primitive (P_Scrollbar_Set_Thumb, "scrollbar-set-thumb!", 3, 3, EVAL);
    Define_Converter_To_Scheme ("callback:scrollbar-jumpProc", S_Callback_Scrollbar_JumpProc);
    Define_Converter_To_Scheme ("callback:scrollbar-scrollProc", S_Callback_Scrollbar_ScrollProc);
    Define_Converter_To_Scheme ("scrollbar-orientation", S_Scrollbar_Orientation);
    Define_Converter_To_C ("scrollbar-orientation", C_Scrollbar_Orientation);
    P_Provide(Intern("xaw:scrollbar"));
}
