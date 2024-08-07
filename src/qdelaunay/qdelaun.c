/*<html><pre>  -<a                             href="../libqhull/qh-qhull.htm"
  >-------------------------------</a><a name="TOP">-</a>

   qdelaun.c
     compute Delaunay triangulations and furthest-point Delaunay
     triangulations using qhull

   see unix.c for full interface

   Copyright (c) 1993-2020, The Geometry Center
*/

#include "libqhull/libqhull.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#if defined(_MSC_VER)
#include <io.h>
#define isatty _isatty
/* int _isatty(int); */

#else
int isatty(int);  /* returns 1 if stdin is a tty
                   if "Undefined symbol" this can be deleted along with call in main() */
#endif

/*-<a                             href="../libqhull/qh-qhull.htm#TOC"
  >-------------------------------</a><a name="prompt">-</a>

  qh_prompt
    long prompt for qhull

  notes:
    restricted version of libqhull.c

  notes:
    same text as unix.c
    see concise prompt below
    limit maximum literal to 1800 characters
*/

/* duplicated in qdelau_f.htm and qdelaun.htm */
char hidden_options[]=" d n v H U Qb QB Qc Qf Qg Qi Qm Qr Qv Qx TR E V FC Fi Fo Ft Fp FV Q0 Q1 Q2 Q3 Q4 Q5 Q6 Q7 Q8 Q9 Q10 Q11 Q17 ";

char qh_prompta[]= "\n\
qdelaunay -- compute the Delaunay triangulation\n\
    http://www.qhull.org  %s\n\
\n\
input (stdin):\n\
    first lines: dimension and number of points (or vice-versa).\n\
    other lines: point coordinates, best if one point per line\n\
    comments:    start with a non-numeric character\n\
\n\
options:\n\
    QJ   - joggled input instead of merged facets\n\
    Qt   - triangulated output\n\
    Qu   - compute furthest-site Delaunay triangulation\n\
\n\
Qhull control options:\n\
    Qa   - allow input with fewer or more points than coordinates\n\
    QJn  - randomly joggle input in range [-n,n]\n\
    QRn  - random rotation (n=seed, n=0 time, n=-1 time/no rotate)\n\
    Qs   - search all points for the initial simplex\n\
    Qz   - add point-at-infinity to Delaunay triangulation\n\
\n\
%s%s%s%s";  /* split up qh_prompt for Visual C++ */
char qh_promptb[]= "\
Qhull extra options:\n\
    QGn  - print Delaunay region if visible from point n, -n if not\n\
    QVn  - print Delaunay regions that include point n, -n if not\n\
    Qw   - allow option warnings\n\
    Q12  - allow wide facets and wide dupridge\n\
    Q14  - merge pinched vertices that create a dupridge\n\
\n\
T options:\n\
    TFn  - report summary when n or more facets created\n\
    TI file - input file, may be enclosed in single quotes\n\
    TO file - output file, may be enclosed in single quotes\n\
    Ts   - statistics\n\
    Tv   - verify result: structure, convexity, and in-circle test\n\
    Tz   - send all output to stdout\n\
\n\
";
char qh_promptc[]= "\
Trace options:\n\
    T4   - trace at level n, 4=all, 5=mem/gauss, -1= events\n\
    Ta   - annotate output with message codes\n\
    TAn  - stop qhull after adding n vertices\n\
     TCn - stop qhull after building cone for point n\n\
     TVn - stop qhull after adding point n, -n for before\n\
    Tc   - check frequently during execution\n\
    Tf   - flush each qh_fprintf for debugging segfaults\n\
    TPn  - turn on tracing when point n added to hull\n\
     TMn - turn on tracing at merge n\n\
     TWn - trace merge facets when width > n\n\
\n\
Precision options:\n\
    Cn   - radius of centrum (roundoff added).  Merge facets if non-convex\n\
     An  - cosine of maximum angle.  Merge facets if cosine > n or non-convex\n\
           C-0 roundoff, A-0.99/C-0.01 pre-merge, A0.99/C0.01 post-merge\n\
    Rn   - randomly perturb computations by a factor of [1-n,1+n]\n\
    Wn   - min facet width for outside point (before roundoff)\n\
\n\
Output formats (may be combined; if none, produces a summary to stdout):\n\
    f    - facet dump\n\
    G    - Geomview output (see below)\n\
    i    - vertices incident to each Delaunay region\n\
    m    - Mathematica output (2-d only, lifted to a paraboloid)\n\
    o    - OFF format (dim, points, and facets as a paraboloid)\n\
    p    - point coordinates (lifted to a paraboloid)\n\
    s    - summary (stderr)\n\
\n\
";
char qh_promptd[]= "\
More formats:\n\
    Fa   - area for each Delaunay region\n\
    FA   - compute total area for option 's'\n\
    Fc   - count plus coincident points for each Delaunay region\n\
    Fd   - use cdd format for input (homogeneous with offset first)\n\
    FD   - use cdd format for numeric output (offset first)\n\
    FF   - facet dump without ridges\n\
    FI   - ID of each Delaunay region\n\
    Fm   - merge count for each Delaunay region (511 max)\n\
    FM   - Maple output (2-d only, lifted to a paraboloid)\n\
    Fn   - count plus neighboring region for each Delaunay region\n\
    FN   - count plus neighboring region for each point\n\
    FO   - options and precision constants\n\
    FP   - nearest point and distance for each coincident point\n\
    FQ   - command used for qdelaunay\n\
    Fs   - summary: #int (8), dimension, #points, tot vertices, tot facets,\n\
                    output: #vertices, #Delaunay regions,\n\
                                #coincident points, #non-simplicial regions\n\
                    #real (2), max outer plane, min vertex\n\
    FS   - sizes:   #int (0)\n\
                    #real (2), tot area, 0\n\
    Fv   - count plus vertices for each Delaunay region\n\
    Fx   - extreme points of Delaunay triangulation (on convex hull)\n\
\n\
";
char qh_prompte[]= "\
Geomview output (2-d and 3-d points lifted to a paraboloid)\n\
    Ga   - all points as dots\n\
     Gp  -  coplanar points and vertices as radii\n\
     Gv  -  vertices as spheres\n\
    Gc   - centrums\n\
    GDn  - drop dimension n in 3-d and 4-d output\n\
    Gh   - hyperplane intersections\n\
    Gi   - inner planes only\n\
     Gn  -  no planes\n\
     Go  -  outer planes only\n\
    Gr   - ridges\n\
    Gt   - transparent outer ridges to view 3-d Delaunay\n\
\n\
Print options:\n\
    PAn  - keep n largest Delaunay regions by area\n\
    Pdk:n - drop facet if normal[k] <= n (default 0.0)\n\
    PDk:n - drop facet if normal[k] >= n\n\
    PFn  - keep Delaunay regions whose area is at least n\n\
    Pg   - print good Delaunay regions (needs 'QGn' or 'QVn')\n\
    PG   - print neighbors of good regions (needs 'QGn' or 'QVn')\n\
    PMn  - keep n Delaunay regions with most merges\n\
    Po   - force output.  If error, output neighborhood of facet\n\
    Pp   - do not report precision problems\n\
\n\
    .    - list of all options\n\
    -    - one line descriptions of all options\n\
    -?   - help with examples\n\
    -V   - version\n\
";
/* for opts, don't assign 'e' or 'E' to a flag (already used for exponent) */

/*-<a                             href="../libqhull/qh-qhull.htm#TOC"
  >-------------------------------</a><a name="prompt2">-</a>

  qh_prompt2
    synopsis for qhull
*/
char qh_prompt2[]= "\n\
qdelaunay -- compute the Delaunay triangulation.  Qhull %s\n\
    input (stdin): dimension, number of points, point coordinates\n\
    comments start with a non-numeric character\n\
\n\
options (qdelaun.htm):\n\
    Qu   - furthest-site Delaunay triangulation\n\
    Qt   - triangulated output\n\
    QJ   - joggled input instead of merged facets\n\
    Tv   - verify result: structure, convexity, and in-circle test\n\
    .    - concise list of all options\n\
    -    - one-line description of each option\n\
    -?   - this message\n\
    -V   - version\n\
\n\
output options (subset):\n\
    s    - summary of results (default)\n\
    i    - vertices incident to each Delaunay region\n\
    Fx   - extreme points (vertices of the convex hull)\n\
    G    - Geomview output (2-d and 3-d points lifted to a paraboloid)\n\
    m    - Mathematica output (2-d inputs lifted to a paraboloid)\n\
    o    - OFF format (shows the points lifted to a paraboloid)\n\
    QVn  - print Delaunay regions that include point n, -n if not\n\
    TI file - input file, may be enclosed in single quotes\n\
    TO file - output file, may be enclosed in single quotes\n\
\n\
examples:\n\
    rbox c P0 D2 | qdelaunay s o          rbox c P0 D2 | qdelaunay i\n\
    rbox c P0 D2 | qdelaunay Fv           rbox c P0 D2 | qdelaunay s Qu Fv\n\
    rbox c G1 d D2 | qdelaunay s i        rbox c G1 d D2 | qdelaunay Qt\n\
    rbox M3,4 z 100 D2 | qdelaunay s      rbox M3,4 z 100 D2 | qdelaunay s Qt\n\
\n\
";
/* for opts, don't assign 'e' or 'E' to a flag (already used for exponent) */

/*-<a                             href="../libqhull/qh-qhull.htm#TOC"
  >-------------------------------</a><a name="prompt3">-</a>

  qh_prompt3
    concise prompt for qhull
*/
char qh_prompt3[]= "\n\
Qhull %s\n\
Except for 'F.' and 'PG', upper-case options take an argument.\n\
\n\
 facet-dump     Geomview       incidences     mathematica    off-format\n\
 points-lifted  summary\n\
\n\
 Farea          FArea-total    Fcoincident    Fd-cdd-in      FD-cdd-out\n\
 FF-dump-xridge FIDs           Fmerges        FMaple         Fneighbors\n\
 FNeigh-vertex  FOptions       FPoint-near    FQdelaun       Fsummary\n\
 FSize          Fvertices      Fxtremes\n\
\n\
 Gall-points    Gcentrums      GDrop-dim      Ghyperplanes   Ginner\n\
 Gno-planes     Gouter         Gpoints        Gridges        Gtransparent\n\
 Gvertices\n\
\n\
 PArea-keep     Pdrop-d0:0D0   PFacet-area-keep  Pgood       PGood-neighbors\n\
 PMerge-keep    Poutput-forced Pprecision-not\n\
\n\
 Qallow-short   QGood-point    QJoggle        Qrotate        Qsearch-all\n\
 Qtriangulate   QupperDelaunay QVertex-good   Qwarn-allow    Qzinfinite\n\
 Q12-allow-wide Q14-merge-pinched\n\
\n\
 TFacet-log     TInput-file    TOutput-file   Tstatistics    Tverify\n\
 Tz-stdout\n\
\n\
 T4-trace       Tannotate      TAdd-stop      Tcheck-often   TCone-stop\n\
 Tflush         TMerge-trace   TPoint-trace   TVertex-stop   TWide-trace\n\
\n\
 Angle-max      Centrum-size   Random-dist    Wide-outside\n\
";

/*-<a                             href="../libqhull/qh-qhull.htm#TOC"
  >-------------------------------</a><a name="main">-</a>

  main( argc, argv )
    processes the command line, calls qhull() to do the work, and exits

  design:
    initializes data structures
    reads points
    finishes initialization
    computes convex hull and other structures
    checks the result
    writes the output
    frees memory
*/
int main(int argc, char *argv[]) {
  int curlong, totlong; /* used !qh_NOmem */
  int exitcode, numpoints, dim;
  coordT *points;
  boolT ismalloc;

  QHULL_LIB_CHECK /* Check for compatible library */

  if ((argc == 1) && isatty( 0 /*stdin*/)) {
    fprintf(stdout, qh_prompt2, qh_version);
    exit(qh_ERRnone);
  }
  if (argc > 1 && *argv[1] == '-' && (*(argv[1] + 1) == '?' || *(argv[1] + 1) == '-')) { /* -? or --help */
    fprintf(stdout, qh_prompt2, qh_version);
    exit(qh_ERRnone);
  }
  if (argc > 1 && *argv[1] == '-' && !*(argv[1]+1)) {
    fprintf(stdout, qh_prompta, qh_version,
                qh_promptb, qh_promptc, qh_promptd, qh_prompte);
    exit(qh_ERRnone);
  }
  if (argc > 1 && *argv[1] == '.' && !*(argv[1]+1)) {
    fprintf(stdout, qh_prompt3, qh_version);
    exit(qh_ERRnone);
  }
  if (argc > 1 && *argv[1] == '-' && *(argv[1]+1)=='V') {
      fprintf(stdout, "%s\n", qh_version2);
      exit(qh_ERRnone);
  }
  qh_init_A(stdin, stdout, stderr, argc, argv);  /* sets qh qhull_command */
  exitcode= setjmp(qh errexit); /* simple statement for CRAY J916 */
  if (!exitcode) {
    qh NOerrexit= False;
    qh_option("delaunay  Qbbound-last", NULL, NULL);
    qh DELAUNAY= True;     /* 'd'   */
    qh SCALElast= True;    /* 'Qbb' */
    qh KEEPcoplanar= True; /* 'Qc', to keep coplanars in 'p' */
    qh_checkflags(qh qhull_command, hidden_options);
    qh_initflags(qh qhull_command);
    points= qh_readpoints(&numpoints, &dim, &ismalloc);
    qh_init_B(points, numpoints, dim, ismalloc);
    qh_qhull();
    qh_check_output();
    qh_produce_output();
    if (qh VERIFYoutput && !qh FORCEoutput && !qh STOPpoint && !qh STOPcone)
      qh_check_points();
    exitcode= qh_ERRnone;
  }
  qh NOerrexit= True;  /* no more setjmp */
#ifdef qh_NOmem
  qh_freeqhull(qh_ALL);
#else
  qh_freeqhull(!qh_ALL);
  qh_memfreeshort(&curlong, &totlong);
  if (curlong || totlong)
    qh_fprintf_stderr(7079, "qhull internal warning (main): did not free %d bytes of long memory(%d pieces)\n",
       totlong, curlong);
#endif
  return exitcode;
} /* main */

