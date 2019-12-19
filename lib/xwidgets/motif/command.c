#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/Command.h>

static Object S_Callback_Command_CommandChangedCallback (XtArgVal x) {
   return Get_Selection_CB ((XmCommandCallbackStruct *)x);
}

static Object S_Callback_Command_CommandEnteredCallback (XtArgVal x) {
   return Get_Selection_CB ((XmCommandCallbackStruct *)x);
}

void elk_init_motif_command () {
    XtResourceList r = 0;
    Define_Class ("command", xmCommandWidgetClass, r, 0);
    Define_Callback ("command", "commandEnteredCallback", 1);
    Define_Callback ("command", "commandChangedCallback", 1);
    Define_Converter_To_Scheme ("callback:command-commandEnteredCallback", S_Callback_Command_CommandEnteredCallback);
    Define_Converter_To_Scheme ("callback:command-commandChangedCallback", S_Callback_Command_CommandChangedCallback);
    P_Provide(Intern("motif:command"));
}
