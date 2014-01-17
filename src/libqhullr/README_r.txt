Converting libqhull to libqhullr

Todo 

3>..\..\src\qhullr\unix_r.c(39) : warning C4273: '_isatty' : inconsistent dll linkage
3>        C:\Program Files\Microsoft Visual Studio 8\VC\INCLUDE\io.h(209) : see previous definition of '_isatty'

Redo usage note for qhullr.cpp

Add qhull-libqhull-src.pri to libqhull.pro
Remove #SOURCE from libqhullr.pro
   It changes the RelativePath to one fewer
     From
     				RelativePath="..\libqhullr\stat_r.h" />
     To
     				RelativePath="..\..\libqhullr\stat_r.h" />
---
How is roadTest.h done, it has the right path in vcproj

---
/*** uncomment here and qhull_a.h
     if string.h does not define memcpy()
#include <memory.h>
*/

---
Run through valgrind

---
Fix or "sample code" in user_r.h

and in user_r.c
  qh_call_qhull(qh, void )
    template for calling qhull from inside your program

--
Try with and without qh_NOmem

==============
Steps

Build qhullr.sln from qhull_all.sln
  Shadow build isn't working for header files. libbqhull and libqhullr
   RelativePath="..\..\src\libqhull\
  Doesn't create qhullstatic_rd.lib
  Inconsistent dll linkage for _isatty
  
  include only libqhullstaticr and qhullr
  remove libqhull, libqhullp, libqhullr to avoid double searches
  remove all but testqset from testqset
  
Replace all include files with _r.h

[qhull_all] Remove all spaces before the parens 'qh_... (...)' 
[qhull_all] Change copyright to 2014

Checked in source

Check for access to .c and .h files

Add qhmemT *qh before all routines
   # Routines with arguments, 3648+498 occurrences
   {qh_[a-zA-Z0-9_]*[^_]\(}{[^)/]}
   \1qhmemT *qh, \2

   # Routines with comment args, 15+ occurrences
   {qh_[a-zA-Z0-9_]*[^_]\(}{[/]}
   \1qhmemT *qh \2
   
Exceptions 104+55 instances
  qhmemT *qh, void
  qhmemT *qh

  # times
  SETtruncate_(qhmemT *qh, 
  _(
  
  qhmemT *qh, qhmemT *qh,
  qhmemT *qh,

  qhmemT *qh, qhmemT *qh
  qhmemT *qh

In C code
  ^{  *qh_.*}qhmemT *qh
  \1qh

  # 602 occurrences, needs repeat  
  ^{ .*}qhmemT *qh
  \1qh
 
  # 3746 occurrences
  {[^a-z]}qh {[a-zA-Z]}
  \1qh->\2

All files, 891 occurrences
  qhmemT \*qh{[^a-zA-Z]}
  qhT *qh\1

  qhT *qh *
  qhT *qh, void *
  
  qhmem.
  qh->qhmem.
  
  # 99 occurrences
  qhstat 
  qh->qhstat.
  
Removed rboxT from rboxlib_r.c

1138 errors and 438 warnings.

Remove dependency on libqhull_r for statT
Convert FOREACHsetelement_i_ in libqhull_r.h 
traceN needs qh for qh_fprintf
add qh to () calls

Down to 600 errors

Thurs at 7:18p after fixing all of the compile errors and removing qh_qhPOINTER

# Debug version of qhullr

ISPY-/local/qhull/bin> rbox 100000 t100 s | qhullr

Convex hull of 100000 points in 3-d:

  Number of vertices: 100000
  Number of facets: 199996

Statistics for: rbox 100000 t100 s | qhullr

  Number of points processed: 100000
  Number of hyperplanes created: 565761
  Number of distance tests for qhull: 4376829
  CPU seconds to compute hull (after input): 1.688

# Release version 2012.1

ISPY-/local/qhull/bin> rbox 100000 t100 s | qhull

Convex hull of 100000 points in 3-d:

  Number of vertices: 100000
  Number of facets: 199996

Statistics for: rbox 100000 t100 s | qhull

  Number of points processed: 100000
  Number of hyperplanes created: 565761
  Number of distance tests for qhull: 4376829
  CPU seconds to compute hull (after input):  1
  