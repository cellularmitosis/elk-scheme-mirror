#include "../xt.h"
#include <Xm/Xm.h>
#include <Xm/BulletinB.h>

void elk_init_motif_bulletinboard () {
    XtResourceList r = 0;
    Define_Class ("bulletin-board", xmBulletinBoardWidgetClass, r, 0);
    P_Provide(Intern("motif:bulletin-brd"));
}
