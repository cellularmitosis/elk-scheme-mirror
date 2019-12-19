#include "../xt.h"
#include <X11/Xaw/MenuButton.h>

void elk_init_xaw_menubutton () {
    XtResourceList r = 0;
    Define_Class ("menubutton", menuButtonWidgetClass, r, 0);
    P_Provide(Intern("xaw:menubutton"));
}
