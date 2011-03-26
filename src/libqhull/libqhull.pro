# -------------------------------------------------
# libqhull.pro -- Qt project for Qhull static library
#   Built with qh_QHpointer=0.  See libqhullp.pro
# -------------------------------------------------

DESTDIR = ../../lib
TEMPLATE = lib
CONFIG += staticlib warn_on
CONFIG -= qt
build_pass:CONFIG(debug, debug|release):{
    TARGET = qhull-d
    OBJECTS_DIR = Debug
}else:build_pass:CONFIG(release, debug|release):{
    TARGET = qhull
    OBJECTS_DIR = Release
}
*g++ {
    COMPVER = $$system(gcc -v)
    contains(COMPVER, 4.1)|contains(COMPVER, 4.2)|contains(COMPVER, 4.3) {
        QMAKE_CFLAGS += -fno-strict-aliasing # Avoids core dumps in qset.c with -O2
    }
    # QMAKE_CFLAGS_WARN_ON += -Werror # Treat warnings as errors
    QMAKE_CFLAGS_WARN_ON += -Wcast-qual -Wextra -Wshadow -Wwrite-strings

    #QMAKE_CFLAGS_WARN_ON += -Wno-sign-conversion # Many size_t vs. int warnings
    #QMAKE_CFLAGS_WARN_ON += -Wconversion # No workaround for bit-field conversions
}

# libqhull.pro and libqhullp.pro are the same for SOURCES and HEADERS
# Order object files by frequency of execution.  Small files at end.
SOURCES += rboxlib.c
SOURCES += user.c
SOURCES += global.c
SOURCES += stat.c
SOURCES += io.c
SOURCES += geom2.c
SOURCES += poly2.c
SOURCES += merge.c
SOURCES += libqhull.c
SOURCES += geom.c
SOURCES += poly.c
SOURCES += qset.c
SOURCES += mem.c
SOURCES += usermem.c
SOURCES += userprintf.c
SOURCES += random.c

HEADERS += geom.h
HEADERS += io.h
HEADERS += libqhull.h
HEADERS += mem.h
HEADERS += merge.h
HEADERS += poly.h
HEADERS += random.h
# The file, qhull.h, is for backwards compatibility.
HEADERS += qhull_a.h
HEADERS += qset.h
HEADERS += stat.h
HEADERS += user.h

OTHER_FILES += Makefile.txt
OTHER_FILES += Mborland
OTHER_FILES += qh-geom.htm
OTHER_FILES += qh-globa.htm
OTHER_FILES += qh-io.htm
OTHER_FILES += qh-mem.htm
OTHER_FILES += qh-merge.htm
OTHER_FILES += qh-poly.htm
OTHER_FILES += qh-qhull.htm
OTHER_FILES += qh-set.htm
OTHER_FILES += qh-stat.htm
OTHER_FILES += qh-user.htm
