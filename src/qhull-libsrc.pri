# -------------------------------------------------
# qhull-libsrc.pri -- Qt include project for libqhull sources and headers
#   libqhull.pro, libqhullp.pro, and libqhulldll.pro are the same for SOURCES and HEADERS
# -------------------------------------------------

# Duplicated in libqhull/libqhull.pro for ease of use in QtCreator
# qset.c requires -fno-script-aliasing for gcc 4.1 to 4.3
*g++ {
    COMPVER = $$system(gcc -v)
    contains(COMPVER,4.1)|contains(COMPVER,4.2)|contains(COMPVER,4.3) {
        QMAKE_CFLAGS += -fno-strict-aliasing # Avoid core dumps in qset.c with -O2
    }
}
# Order object files by frequency of execution.  Small files at end.
# Current directory is caller
SOURCES += ../libqhull/global.c
SOURCES += ../libqhull/stat.c
SOURCES += ../libqhull/geom2.c
SOURCES += ../libqhull/poly2.c
SOURCES += ../libqhull/merge.c
SOURCES += ../libqhull/libqhull.c
SOURCES += ../libqhull/geom.c
SOURCES += ../libqhull/poly.c
SOURCES += ../libqhull/qset.c
SOURCES += ../libqhull/mem.c
SOURCES += ../libqhull/random.c
SOURCES += ../libqhull/usermem.c
SOURCES += ../libqhull/userprintf.c
SOURCES += ../libqhull/io.c
SOURCES += ../libqhull/user.c
SOURCES += ../libqhull/rboxlib.c
SOURCES += ../libqhull/userprintf_rbox.c

HEADERS += ../libqhull/geom.h
HEADERS += ../libqhull/io.h
HEADERS += ../libqhull/libqhull.h
HEADERS += ../libqhull/mem.h
HEADERS += ../libqhull/merge.h
HEADERS += ../libqhull/poly.h
HEADERS += ../libqhull/random.h
# The file, libqhull/qhull.h, is for backwards compatibility.
HEADERS += ../libqhull/qhull_a.h
HEADERS += ../libqhull/qset.h
HEADERS += ../libqhull/stat.h
HEADERS += ../libqhull/user.h
