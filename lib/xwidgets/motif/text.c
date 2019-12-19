#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/Text.h>

static Object S_Callback_Text_ValueChangedCallback (XtArgVal x) {
   return Get_Any_CB ((XmAnyCallbackStruct *)x);
}

void elk_init_motif_text () {
    XtResourceList r = 0;
    r = (XtResourceList)XtMalloc (10 * sizeof (XtResource));
    r[0].resource_name = "pendingDelete";
    r[0].resource_class = "PendingDelete";
    r[0].resource_type = "Boolean";
    r[1].resource_name = "selectThreshold";
    r[1].resource_class = "SelectThreshold";
    r[1].resource_type = "Int";
    r[2].resource_name = "blinkRate";
    r[2].resource_class = "BlinkRate";
    r[2].resource_type = "Int";
    r[3].resource_name = "columns";
    r[3].resource_class = "Columns";
    r[3].resource_type = "Short";
    r[4].resource_name = "cursorPositionVisible";
    r[4].resource_class = "CursorPositionVisible";
    r[4].resource_type = "Boolean";
    r[5].resource_name = "fontList";
    r[5].resource_class = "FontList";
    r[5].resource_type = "FontList";
    r[6].resource_name = "resizeHeight";
    r[6].resource_class = "ResizeHeight";
    r[6].resource_type = "Boolean";
    r[7].resource_name = "resizeWidth";
    r[7].resource_class = "ResizeWidth";
    r[7].resource_type = "Boolean";
    r[8].resource_name = "rows";
    r[8].resource_class = "Rows";
    r[8].resource_type = "Short";
    r[9].resource_name = "wordWrap";
    r[9].resource_class = "WordWrap";
    r[9].resource_type = "Boolean";
    Define_Class ("text", xmTextWidgetClass, r, 10);
    Define_Callback ("text", "valueChangedCallback", 1);
    Define_Callback ("text", "activateCallback", 1);
    Define_Converter_To_Scheme ("callback:text-valueChangedCallback", S_Callback_Text_ValueChangedCallback);
    P_Provide(Intern("motif:text"));
}
