Converting libqhull to libqhullr

==========================
Todo 

After qmake, need to update HEADER paths for libqhull, libqhullr, libqhullcpp libqhullpcpp
    Path="..\lib
    Path="..\..\src\lib

---
Convert testqset.c to testqset_r.c
   Try to make qhT and mem_r.c etc. plugable

Convert user_eg,etc and branch old code to user_egp...

At initialization, check for compatible libqhull.  Add a version check to libqhull

p4 delete src/qhull-libqhullr-src.pri

---
3>..\..\src\qhullr\unix_r.c(39) : warning C4273: '_isatty' : inconsistent dll linkage
3>        C:\Program Files\Microsoft Visual Studio 8\VC\INCLUDE\io.h(209) : see previous definition of '_isatty'

---
Redo usage note for qhullr.cpp

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

--
Update 
  README.txt -- the new subprojects
  CMakeLists.txt
  
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
 59 files changed, 8849 insertions(+), 8900 deletions(-)

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

# Release version of rboxr and qhullr

ISPY-/local/qhull/bin> rboxr 100000 t100 s | qhullr

Convex hull of 100000 points in 3-d:

  Number of vertices: 100000
  Number of facets: 199996

Statistics for: rboxr 100000 t100 s | qhullr

  Number of points processed: 100000
  Number of hyperplanes created: 565761
  Number of distance tests for qhull: 4376829
  CPU seconds to compute hull (after input):  1

-----
Reorganized projects for cpp. 

Fixed up qhull_p-exports.def.  qhull_r-exports.def has no DATA records.

user_eg3 with libqhullpcpp worked correctly the first time

IISPY-/local/qhull/bin>   user_eg3 rbox "100000 t100 s"  qhull
rbox 100000 t100 s

Results of qhull

Convex hull of 100000 points in 3-d:

  Number of vertices: 100000
  Number of facets: 199996

Statistics for: rbox "100000 t100 s" | qhull

  Number of points processed: 100000
  Number of hyperplanes created: 565761
  Number of distance tests for qhull: 4376829
  CPU seconds to compute hull (after input): 1.672
  