# -------------------------------------------------
# qhull-libqhull-src_r.pri -- Qt include project for reentrant libqhullr sources and headers
# -------------------------------------------------

# Order object files by frequency of execution.  Small files at end.
# Current directory is caller
SOURCES += ../libqhullr/global_r.c
SOURCES += ../libqhullr/stat_r.c
SOURCES += ../libqhullr/geom2_r.c
SOURCES += ../libqhullr/poly2_r.c
SOURCES += ../libqhullr/merge_r.c
SOURCES += ../libqhullr/libqhull_r.c
SOURCES += ../libqhullr/geom_r.c
SOURCES += ../libqhullr/poly_r.c
SOURCES += ../libqhullr/qset_r.c
SOURCES += ../libqhullr/mem_r.c
SOURCES += ../libqhullr/random_r.c
SOURCES += ../libqhullr/usermem_r.c
SOURCES += ../libqhullr/userprintf_r.c
SOURCES += ../libqhullr/io_r.c
SOURCES += ../libqhullr/user_r.c
SOURCES += ../libqhullr/rboxlib_r.c
SOURCES += ../libqhullr/userprintf_rbox_r.c

HEADERS += ../libqhullr/geom_r.h
HEADERS += ../libqhullr/io_r.h
HEADERS += ../libqhullr/libqhull_r.h
HEADERS += ../libqhullr/mem_r.h
HEADERS += ../libqhullr/merge_r.h
HEADERS += ../libqhullr/poly_r.h
HEADERS += ../libqhullr/random_r.h
HEADERS += ../libqhullr/qhull_ra.h
HEADERS += ../libqhullr/qset_r.h
HEADERS += ../libqhullr/stat_r.h
HEADERS += ../libqhullr/user_r.h
