#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/FileSB.h>

void elk_init_motif_fileselection () {
    XtResourceList r = 0;
    Define_Class ("file-selection", xmFileSelectionBoxWidgetClass, r, 0);
    Define_Callback ("file-selection", "helpCallback", 1);
    Define_Callback ("file-selection", "okCallback", 1);
    Define_Callback ("file-selection", "noMatchCallback", 1);
    Define_Callback ("file-selection", "cancelCallback", 1);
    Define_Callback ("file-selection", "applyCallback", 1);
    P_Provide(Intern("motif:file-selectn"));
}
