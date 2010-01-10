# -------------------------------------------------
# libqhullp.pro -- Qhull static library with qh_qhPointer
#   see libqhull.pro
# -------------------------------------------------

DESTDIR = ../..
TEMPLATE = lib
CONFIG += staticlib warn_on
CONFIG -= app_bundle qt
DEFINES += qh_QHpointer
# Appears to be needed for gcc 4.1, 4.2, and 4.3 with -O2
#QMAKE_CFLAGS += -fno-strict-aliasing
QMAKE_CFLAGS += -Wall -Wextra -Wshadow -Wcast-qual -Wwrite-strings
QMAKE_CFLAGS += -Wno-sign-conversion # Many size_t vs. int errors
#QMAKE_CFLAGS_DEBUG += -Wconversion # no workaround for bit-field conversion errors
build_pass:CONFIG(debug, debug|release):{
    TARGET = qhullpd
    OBJECTS_DIR = ../../tmp/libqhullp/Debug
}else:build_pass:CONFIG(release, debug|release):{
    TARGET = qhullp
    OBJECTS_DIR = ../../tmp/libqhullp/Release
}
MOC_DIR = ../../tmp/moc
RCC_DIR = ../../tmp/rcc

# libqhull.pro and libqhullp.pro are the same for SOURCES and HEADERS
# Order object files by frequency of execution.  Small files at end.
VPATH = ../..
SOURCES += src/rboxlib.c
SOURCES += src/user.c
SOURCES += src/global.c
SOURCES += src/stat.c
SOURCES += src/io.c
SOURCES += src/geom2.c
SOURCES += src/poly2.c
SOURCES += src/merge.c
SOURCES += src/libqhull.c
SOURCES += src/geom.c
SOURCES += src/poly.c
SOURCES += src/qset.c
SOURCES += src/mem.c
SOURCES += src/usermem.c
SOURCES += src/userprintf.c
SOURCES += src/random.c
HEADERS += src/geom.h
HEADERS += src/io.h
HEADERS += src/libqhull.h
HEADERS += src/mem.h
HEADERS += src/merge.h
HEADERS += src/poly.h
# qhull.h is for backwards compatibility
HEADERS += src/qhull_a.h
HEADERS += src/qset.h
HEADERS += src/random.h
HEADERS += src/stat.h
HEADERS += src/user.h
