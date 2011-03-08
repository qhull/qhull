# -------------------------------------------------
# libqhullp.pro -- Qhull static library with qh_qhPointer
#   see libqhull.pro
# -------------------------------------------------


DESTDIR = ../../lib
TEMPLATE = lib
CONFIG += staticlib warn_on
CONFIG -= qt
build_pass:CONFIG(debug, debug|release) {
    TARGET = qhull-pd
    OBJECTS_DIR = Debug
}else:build_pass:CONFIG(release, debug|release) {
    TARGET = qhull-p
    OBJECTS_DIR = Release
}

DEFINES += qh_QHpointer
*g++ {
    COMPVER = $$system(gcc -v)
    contains(COMPVER, 4.1)|contains(COMPVER, 4.2)|contains(COMPVER, 4.3) {
        QMAKE_CFLAGS += -fno-strict-aliasing # Avoid core dumps in qset.c with -O2
    }
    QMAKE_CFLAGS_WARN_ON += -Werror -Wcast-qual -Wextra -Wshadow -Wwrite-strings
    #QMAKE_CFLAGS_WARN_ON += -Wno-sign-conversion # Many size_t vs. int warnings
    #QMAKE_CFLAGS_WARN_ON += -Wconversion # No workaround for bit-field conversions
}

# libqhull.pro and libqhullp.pro are the same for SOURCES and HEADERS
# Order object files by frequency of execution.  Small files at end.
SOURCES += ../libqhull/rboxlib.c
SOURCES += ../libqhull/user.c
SOURCES += ../libqhull/global.c
SOURCES += ../libqhull/stat.c
SOURCES += ../libqhull/io.c
SOURCES += ../libqhull/geom2.c
SOURCES += ../libqhull/poly2.c
SOURCES += ../libqhull/merge.c
SOURCES += ../libqhull/libqhull.c
SOURCES += ../libqhull/geom.c
SOURCES += ../libqhull/poly.c
SOURCES += ../libqhull/qset.c
SOURCES += ../libqhull/mem.c
SOURCES += ../libqhull/usermem.c
SOURCES += ../libqhull/userprintf.c
SOURCES += ../libqhull/random.c

# Headers duplicated from libqhull.pro for convenience
HEADERS += ../libqhull/geom.h
HEADERS += ../libqhull/io.h
HEADERS += ../libqhull/libqhull.h
HEADERS += ../libqhull/mem.h
HEADERS += ../libqhull/merge.h
HEADERS += ../libqhull/poly.h
HEADERS += ../libqhull/random.h
HEADERS += ../libqhull/qhull_a.h
HEADERS += ../libqhull/qset.h
HEADERS += ../libqhull/stat.h
HEADERS += ../libqhull/user.h

# See libqhull.pro for other files
