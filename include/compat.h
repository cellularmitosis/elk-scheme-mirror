/* compat.h: Definitions that were used in older versions of Elk, but are
 * now obsolete and should not be used any longer.
 *
 * $Id$
 *
 * Copyright 1990, 1991, 1992, 1993, 1994, 1995, Oliver Laumann, Berlin
 * Copyright 2002, 2003 Sam Hocevar <sam@hocevar.net>, Paris
 *
 * This software was derived from Elk 1.2, which was Copyright 1987, 1988,
 * 1989, Nixdorf Computer AG and TELES GmbH, Berlin (Elk 1.2 has been written
 * by Oliver Laumann for TELES Telematic Services, Berlin, in a joint project
 * between TELES and Nixdorf Microprocessor Engineering, Berlin).
 *
 * Oliver Laumann, TELES GmbH, Nixdorf Computer AG and Sam Hocevar, as co-
 * owners or individual owners of copyright in this software, grant to any
 * person or company a worldwide, royalty free, license to
 *
 *    i) copy this software,
 *   ii) prepare derivative works based on this software,
 *  iii) distribute copies of this software or derivative works,
 *   iv) perform this software, or
 *    v) display this software,
 *
 * provided that this notice is not removed and that neither Oliver Laumann
 * nor Teles nor Nixdorf are deemed to have made any representations as to
 * the suitability of this software for any purpose nor are held responsible
 * for any defects of this software.
 *
 * THERE IS ABSOLUTELY NO WARRANTY FOR THIS SOFTWARE.
 */

#define Declare_C_Strings   Alloca_Begin
#define Make_C_String       Get_Strsym_Stack
#define Dispose_C_Strings   Alloca_End

#define Val(x)              Cdr(x)

#define FIXNUM_FITS_UNSIGNED   UFIXNUM_FITS
#define SETFAST(x,y)       ((x) = (y))

#define Make_Fixnum         Make_Integer

/* The names of a few functions implementing primitives have been changed
 * for consistency:
 */
#define P_Setcar            P_Set_Car
#define P_Setcdr            P_Set_Cdr
#define P_With_Input        P_With_Input_From_File
#define P_With_Output       P_With_Output_To_File
#define P_Call_With_Input   P_Call_With_Input_File
#define P_Call_With_Output  P_Call_With_Output_File
#define P_Call_CC           P_Call_With_Current_Continuation
#define P_Promise_Env       P_Promise_Environment
#define P_Procedure_Env     P_Procedure_Environment
#define P_Control_Point_Env P_Control_Point_Environment
#define P_Curr_Input_Port   P_Current_Input_Port
#define P_Curr_Output_Port  P_Current_Output_Port
#define P_Env_List          P_Environment_To_List
#define P_Char_Lower_Case   P_Char_Lower_Casep
#define P_Char_Upper_Case   P_Char_Upper_Casep
#define P_Char_Alphabetic   P_Char_Alphabeticp
#define P_Char_Numeric      P_Char_Numericp
#define P_Char_Whitespace   P_Char_Whitespacep
#define P_Chr_Eq            P_Char_Eq
#define P_Chr_Less          P_Char_Less
#define P_Chr_Greater       P_Char_Greater
#define P_Chr_Eq_Less       P_Char_Eq_Less
#define P_Chr_Eq_Greater    P_Char_Eq_Greater
#define P_Chr_CI_Eq         P_Char_CI_Eq
#define P_Chr_CI_Less       P_Char_CI_Less
#define P_Chr_CI_Greater    P_Char_CI_Greater
#define P_Chr_CI_Eq_Less    P_Char_CI_Eq_Less
#define P_Chr_CI_Eq_Greater P_Char_CI_Eq_Greater
#define P_Str_Eq            P_String_Eq
#define P_Str_Less          P_String_Less
#define P_Str_Greater       P_String_Greater
#define P_Str_Eq_Less       P_String_Eq_Less
#define P_Str_Eq_Greater    P_String_Eq_Greater
#define P_Str_CI_Eq         P_String_CI_Eq
#define P_Str_CI_Less       P_String_CI_Less
#define P_Str_CI_Greater    P_String_CI_Greater
#define P_Str_CI_Eq_Less    P_String_CI_Eq_Less
#define P_Str_CI_Eq_Greater P_String_CI_Eq_Greater
