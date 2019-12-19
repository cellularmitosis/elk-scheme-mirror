;; paned.d
;;
;; $Id$
;;
;; Copyright 1990, 1991, 1992, 1993, 1994, 1995, Oliver Laumann, Berlin
;; Copyright 2002, 2003 Sam Hocevar <sam@hocevar.net>, Paris
;;
;; This software was derived from Elk 1.2, which was Copyright 1987, 1988,
;; 1989, Nixdorf Computer AG and TELES GmbH, Berlin (Elk 1.2 has been written
;; by Oliver Laumann for TELES Telematic Services, Berlin, in a joint project
;; between TELES and Nixdorf Microprocessor Engineering, Berlin).
;;
;; Oliver Laumann, TELES GmbH, Nixdorf Computer AG and Sam Hocevar, as co-
;; owners or individual owners of copyright in this software, grant to any
;; person or company a worldwide, royalty free, license to
;;
;;    i) copy this software,
;;   ii) prepare derivative works based on this software,
;;  iii) distribute copies of this software or derivative works,
;;   iv) perform this software, or
;;    v) display this software,
;;
;; provided that this notice is not removed and that neither Oliver Laumann
;; nor Teles nor Nixdorf are deemed to have made any representations as to
;; the suitability of this software for any purpose nor are held responsible
;; for any defects of this software.
;;
;; THERE IS ABSOLUTELY NO WARRANTY FOR THIS SOFTWARE.

(define-widget-type 'paned "Paned.h")

(define-widget-class 'paned 'panedWidgetClass)

(define-primitive 'paned-allow-resize '(w enable)
"   Check_Widget (w);
    Check_Type (enable, T_Boolean);
    XawPanedAllowResize (WIDGET(w)->widget, EQ (enable, True));
    return Void;")

(define-primitive 'paned-set-min-max! '(w min max)
"   Check_Widget (w);
    XawPanedSetMinMax (WIDGET(w)->widget, Get_Integer (min),
        Get_Integer (max));
    return Void;")

(define-primitive 'paned-get-min-max '(w)
"   int min, max;
    Check_Widget (w);
    XawPanedGetMinMax (WIDGET(w)->widget, &min, &max);
    return Cons (Make_Integer (min), Make_Integer (max));")

(define-primitive 'paned-set-refigure-mode! '(w enable)
"   Check_Widget_Class (w, panedWidgetClass);
    Check_Type (enable, T_Boolean);
    XawPanedSetRefigureMode (WIDGET(w)->widget, EQ (enable, True));
    return Void;")

(define-primitive 'paned-get-num-sub '(w)
"   Check_Widget_Class (w, panedWidgetClass);
    return Make_Integer (XawPanedGetNumSub (WIDGET(w)->widget));")
