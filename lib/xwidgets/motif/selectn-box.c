#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/SelectioB.h>

static SYMDESCR Type_Syms[] = {
   { "dialog-prompt",       XmDIALOG_PROMPT },
   { "dialog-selection",    XmDIALOG_SELECTION },
   { "dialog-work-area",    XmDIALOG_WORK_AREA },
   { 0, 0}
};

static XtArgVal C_Selection_Box_DialogType (Object x) {
   return (XtArgVal)Symbols_To_Bits (x, 0, Type_Syms);
}

void elk_init_motif_selectionbox () {
    XtResourceList r = 0;
    Define_Class ("selection-box", xmSelectionBoxWidgetClass, r, 0);
    Define_Callback ("selection-box", "helpCallback", 1);
    Define_Callback ("selection-box", "okCallback", 1);
    Define_Callback ("selection-box", "noMatchCallback", 1);
    Define_Callback ("selection-box", "cancelCallback", 1);
    Define_Callback ("selection-box", "applyCallback", 1);
    Define_Converter_To_C ("selection-box-dialogType", C_Selection_Box_DialogType);
    P_Provide(Intern("motif:selectn-box"));
}
