Converting libqhull to libqhullr

Build qhullr.sln from qhull_all.sln
  Shadow build isn't working for header files. libbqhull and libqhullr
   RelativePath="..\..\src\libqhull\
  Doesn't create qhullstatic_rd.lib
  Inconsistent dll linkage for _isatty
  
Replace all include files with _r.h

[qhull_all] Remove all spaces before the parens 'qh_... (...)' 
[qhull_all] Change copyright to 2014


Todo 

3>..\..\src\qhullr\unix_r.c(39) : warning C4273: '_isatty' : inconsistent dll linkage
3>        C:\Program Files\Microsoft Visual Studio 8\VC\INCLUDE\io.h(209) : see previous definition of '_isatty'

Redo usage note for qhullr.cpp
