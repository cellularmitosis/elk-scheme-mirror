#include "../xt.h"
#include <X11/Xaw/AsciiText.h>

static XtArgVal C_Ascii_Text_TextSink (Object x) {
    Primitive_Error ("cannot get or set sink/source");
}

static XtArgVal C_Ascii_Text_TextSource (Object x) {
    Primitive_Error ("cannot get or set sink/source");
}

static Object S_Ascii_Text_TextSink (XtArgVal x) {
    Primitive_Error ("cannot get or set sink/source");
}

static Object S_Ascii_Text_TextSource (XtArgVal x) {
    Primitive_Error ("cannot get or set sink/source");
}

static Object P_Ascii_Text_String (Object w) {
   Arg a[1];
    char *s;

    Check_Widget_Class (w, asciiTextWidgetClass);
    XtSetArg (a[0], XtNstring, &s);
    XtGetValues (WIDGET(w)->widget, a, 1);
    return Make_String (s, strlen (s));
}

void elk_init_xaw_asciitext () {
    XtResourceList r = 0;
    r = (XtResourceList)XtMalloc (10 * sizeof (XtResource));
    r[0].resource_name = "font";
    r[0].resource_class = "Font";
    r[0].resource_type = "FontStruct";
    r[1].resource_name = "foreground";
    r[1].resource_class = "Foreground";
    r[1].resource_type = "Pixel";
    r[2].resource_name = "dataCompression";
    r[2].resource_class = "DataCompression";
    r[2].resource_type = "Boolean";
    r[3].resource_name = "displayNonprinting";
    r[3].resource_class = "Output";
    r[3].resource_type = "Boolean";
    r[4].resource_name = "echo";
    r[4].resource_class = "Output";
    r[4].resource_type = "Boolean";
    r[5].resource_name = "editType";
    r[5].resource_class = "EditType";
    r[5].resource_type = "EditMode";
    r[6].resource_name = "length";
    r[6].resource_class = "Length";
    r[6].resource_type = "Int";
    r[7].resource_name = "pieceSize";
    r[7].resource_class = "PieceSize";
    r[7].resource_type = "Int";
    r[8].resource_name = "string";
    r[8].resource_class = "String";
    r[8].resource_type = "String";
    r[9].resource_name = "type";
    r[9].resource_class = "Type";
    r[9].resource_type = "AsciiType";
    Define_Class ("ascii-text", asciiTextWidgetClass, r, 10);
    Define_Primitive (P_Ascii_Text_String, "ascii-text-string", 1, 1, EVAL);
    Define_Converter_To_Scheme ("ascii-text-textSource", S_Ascii_Text_TextSource);
    Define_Converter_To_Scheme ("ascii-text-textSink", S_Ascii_Text_TextSink);
    Define_Converter_To_C ("ascii-text-textSource", C_Ascii_Text_TextSource);
    Define_Converter_To_C ("ascii-text-textSink", C_Ascii_Text_TextSink);
    P_Provide(Intern("xaw:ascii"));
}
