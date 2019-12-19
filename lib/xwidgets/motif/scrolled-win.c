#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/ScrolledW.h>

static SYMDESCR Scrolling_Syms[] = {
   { "automatic",           XmAUTOMATIC },
   { "application-defined", XmAPPLICATION_DEFINED },
   { "AUTOMATIC",           XmAUTOMATIC },            /* see above */
   { "APPLICATION_DEFINED", XmAPPLICATION_DEFINED },
   { "application_defined", XmAPPLICATION_DEFINED },
   { 0, 0}
};

static XtArgVal C_ScrollingPolicy (Object x) {
   if (TYPE(x) == T_String) x = P_String_To_Symbol(x);
    return (XtArgVal)Symbols_To_Bits (x, 0, Scrolling_Syms);
}

void elk_init_motif_scrolledwindow () {
    XtResourceList r = 0;
    Define_Class ("scrolled-window", xmScrolledWindowWidgetClass, r, 0);
    Define_Converter_To_C ("scrollingPolicy", C_ScrollingPolicy);
    P_Provide(Intern("motif:scrolled-win"));
}
