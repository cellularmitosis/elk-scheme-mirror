#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/MessageB.h>

static SYMDESCR Type_Syms[] = {
   { "dialog-error",        XmDIALOG_ERROR },
   { "dialog-information",  XmDIALOG_INFORMATION },
   { "dialog-message",      XmDIALOG_MESSAGE },
   { "dialog-question",     XmDIALOG_QUESTION },
   { "dialog-warning",      XmDIALOG_WARNING },
   { "dialog-working",      XmDIALOG_WORKING },
   { 0, 0}
};

static XtArgVal C_Message_Box_DialogType (Object x) {
   return (XtArgVal)Symbols_To_Bits (x, 0, Type_Syms);
}

static Object S_Callback_Message_Box_CancelCallback (XtArgVal x) {
   return Get_Any_CB ((XmAnyCallbackStruct *)x);
}

static Object S_Callback_Message_Box_OkCallback (XtArgVal x) {
   return Get_Any_CB ((XmAnyCallbackStruct *)x);
}

void elk_init_motif_messagebox () {
    XtResourceList r = 0;
    Define_Class ("message-box", xmMessageBoxWidgetClass, r, 0);
    Define_Callback ("message-box", "okCallback", 1);
    Define_Callback ("message-box", "cancelCallback", 1);
    Define_Converter_To_Scheme ("callback:message-box-okCallback", S_Callback_Message_Box_OkCallback);
    Define_Converter_To_Scheme ("callback:message-box-cancelCallback", S_Callback_Message_Box_CancelCallback);
    Define_Converter_To_C ("message-box-dialogType", C_Message_Box_DialogType);
    P_Provide(Intern("motif:message-box"));
}
