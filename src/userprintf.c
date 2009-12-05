/*<html><pre>  -<a                             href="qh-user.htm"
  >-------------------------------</a><a name="TOP">-</a>

   userprintf.c 
   qh_fprintf() and qh_fprintf_rbox()

   see README.txt  see COPYING.txt for copyright information.

   If you redefine one of these functions you must redefine all of them.
   If you recompile and load this file, then userprintf.o will not be loaded
   from qhull.a or qhull.lib

   See qhulllib.h for data structures, macros, and user-callable functions.
   See user.c for qhull-related, redefinable functions
   see user.h for user-definable constants
   See usermem.c for qh_exit(), qh_free(), and qh_malloc()
   see Qhull.cpp and RboxPoints.cpp for examples.

   Please report any errors that you fix to qhull@qhull.org
*/

#include "qhulllib.h" 

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/*-<a                             href="qh-user.htm#TOC"
   >-------------------------------</a><a name="qh_fprintf">-</a>
  
   qh_fprintf(fp, msgcode, format, list of args )
     print arguments to *fp according to format
     Use qh_fprintf_rbox() for rboxlib.c

   notes:
     same as fprintf()
     fgets() is not trapped like fprintf()
     exit qh_fprintf via qh_errexit() 
     exit qh_fprintf_rbox via qh_errexit_rbox()
*/

void qh_fprintf(FILE *fp, int msgcode, const char *fmt, ... ) {
    va_list args;

    va_start(args, fmt);
    if (qh ANNOTATEoutput) {
      fprintf(fp, "[QH%.4d]", msgcode);
    }else if (msgcode >= MSG_ERROR && msgcode < MSG_STDERR ) {
      fprintf(fp, "QH%.4d ", msgcode);
    }
    vfprintf(fp, fmt, args);
    va_end(args);
} /* qh_fprintf */

void qh_fprintf_rbox(FILE *fp, int msgcode, const char *fmt, ... ) {
    va_list args;
    
    if (msgcode >= MSG_ERROR && msgcode < MSG_STDERR)
      fprintf(fp, "QH%.4d ", msgcode);
    va_start(args, fmt);
    vfprintf(fp, fmt, args);
    va_end(args);
} /* qh_fprintf_rbox */

