///
/// Remove unneeded variable used to store return value.
///
// Confidence: Moderate
// Copyright: (C) 2012 Peter Senna Tschudin, INRIA/LIP6.  GPLv2.
// URL: http://coccinelle.lip6.fr/
// Comments: Comments on code can be deleted if near code that is removed.
//           "when strict" can be removed to get more hits, but adds false
//           positives

virtual patch
virtual report
virtual context
virtual org

@depends on patch && !(file in "ext")@
type T;
constant C;
identifier ret;
@@
- T ret = C;
... when != ret
    when strict
return
- ret
+ C
;

@depends on context && !(file in "ext")@
type T;
constant C;
identifier ret;
@@
* T ret = C;
... when != ret
    when strict
* return ret;

@r1 depends on (report || org) && !(file in "ext")@
type T;
constant C;
identifier ret;
position p1, p2;
@@
T ret@p1 = C;
... when != ret
    when strict
return ret@p2;

@script:python depends on report@
p1 << r1.p1;
p2 << r1.p2;
C << r1.C;
ret << r1.ret;
@@
coccilib.report.print_report(p1[0], "Unneeded variable: \"" + ret +
			     "\". Return \"" + C + "\" on line "
			     + p2[0].line)

@script:python depends on org@
p1 << r1.p1;
p2 << r1.p2;
C << r1.C;
ret << r1.ret;
@@
cocci.print_main("unneeded \"" + ret + "\" variable", p1)
cocci.print_sec("return " + C + " here", p2)
