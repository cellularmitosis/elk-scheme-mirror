#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>

static Object S_Callback_Toggle_Button_ValueChangedCallback (XtArgVal x) {
   return Get_Any_CB ((XmAnyCallbackStruct *)x);
}

static Object S_Callback_Toggle_Button_Gadget_ValueChangedCallback (XtArgVal x) {
   return Get_Any_CB ((XmAnyCallbackStruct *)x);
}

void elk_init_motif_togglebutton () {
    XtResourceList r = 0;
    Define_Class ("toggle-button-gadget", xmToggleButtonGadgetClass, r, 0);
    Define_Class ("toggle-button", xmToggleButtonWidgetClass, r, 0);
    Define_Callback ("toggle-button-gadget", "valueChangedCallback", 1);
    Define_Callback ("toggle-button-gadget", "disarmCallback", 1);
    Define_Callback ("toggle-button-gadget", "armCallback", 1);
    Define_Callback ("toggle-button", "valueChangedCallback", 1);
    Define_Callback ("toggle-button", "disarmCallback", 1);
    Define_Callback ("toggle-button", "armCallback", 1);
    Define_Converter_To_Scheme ("callback:toggle-button-gadget-valueChangedCallback", S_Callback_Toggle_Button_Gadget_ValueChangedCallback);
    Define_Converter_To_Scheme ("callback:toggle-button-valueChangedCallback", S_Callback_Toggle_Button_ValueChangedCallback);
    P_Provide(Intern("motif:toggle-btn"));
}
