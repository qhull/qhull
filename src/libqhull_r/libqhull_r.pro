# -------------------------------------------------
# libqhull_r.pro -- Qt project for Qhull shared library
#
# It uses reentrant Qhull
# -------------------------------------------------

include(../qhull-warn.pri)

DESTDIR = ../../lib
DLLDESTDIR = ../../bin
TEMPLATE = lib
CONFIG += shared warn_on
CONFIG -= qt

build_pass:CONFIG(debug, debug|release):{
    TARGET = qhull_rd
    OBJECTS_DIR = Debug
}else:build_pass:CONFIG(release, debug|release):{
    TARGET = qhull_r
    OBJECTS_DIR = Release
}
win32-msvc* : QMAKE_LFLAGS += /INCREMENTAL:NO

win32-msvc* : DEF_FILE += ../../src/libqhull_r/qhull_r-exports.def

# libqhull_r/libqhull_r.pro and ../qhull-libqhull-src_r.pri have the same SOURCES and HEADERS

SOURCES += ../libqhull_r/global_r.c
SOURCES += ../libqhull_r/stat_r.c
SOURCES += ../libqhull_r/geom2_r.c
SOURCES += ../libqhull_r/poly2_r.c
SOURCES += ../libqhull_r/merge_r.c
SOURCES += ../libqhull_r/libqhull_r.c
SOURCES += ../libqhull_r/geom_r.c
SOURCES += ../libqhull_r/poly_r.c
SOURCES += ../libqhull_r/qset_r.c
SOURCES += ../libqhull_r/mem_r.c
SOURCES += ../libqhull_r/random_r.c
SOURCES += ../libqhull_r/usermem_r.c
SOURCES += ../libqhull_r/userprintf_r.c
SOURCES += ../libqhull_r/io_r.c
SOURCES += ../libqhull_r/user_r.c
SOURCES += ../libqhull_r/rboxlib_r.c
SOURCES += ../libqhull_r/userprintf_rbox_r.c

HEADERS += ../libqhull_r/geom_r.h
HEADERS += ../libqhull_r/io_r.h
HEADERS += ../libqhull_r/libqhull_r.h
HEADERS += ../libqhull_r/mem_r.h
HEADERS += ../libqhull_r/merge_r.h
HEADERS += ../libqhull_r/poly_r.h
HEADERS += ../libqhull_r/random_r.h
HEADERS += ../libqhull_r/qhull_ra.h
HEADERS += ../libqhull_r/qset_r.h
HEADERS += ../libqhull_r/stat_r.h
HEADERS += ../libqhull_r/user_r.h
