#include "../xt.h"
#include <X11/Xaw/Tree.h>

static Object P_Tree_Force_Layout (Object w) {
   Check_Widget_Class (w, treeWidgetClass);
    XawTreeForceLayout (WIDGET(w)->widget);
    return Void;
}

void elk_init_xaw_tree () {
    XtResourceList r = 0;
    Define_Class ("tree", treeWidgetClass, r, 0);
    Define_Primitive (P_Tree_Force_Layout, "tree-force-layout", 1, 1, EVAL);
    P_Provide(Intern("xaw:tree"));
}
