# -------------------------------------------------
# libqhullr.pro -- Qt project for Qhull shared library
#   Built with qh_QHpointer=1
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

win32-msvc* : DEF_FILE += ../../src/libqhullr/qhull-exports_r.def

DEFINES += qh_QHpointer # libqhull/user.h

include(../qhull-libqhullr-src.pri)

# Order object files by frequency of execution.  Small files at end.
# SOURCES += rboxlib_r.c
# SOURCES += user_r.c
# SOURCES += global_r.c
# SOURCES += stat_r.c
# SOURCES += io_r.c
# SOURCES += geom2_r.c
# SOURCES += poly2_r.c
# SOURCES += merge_r.c
# SOURCES += libqhull_r.c
# SOURCES += geom_r.c
# SOURCES += poly_r.c
# SOURCES += qset_r.c
# SOURCES += mem_r.c
# SOURCES += usermem_r.c
# SOURCES += userprintf_r.c
# SOURCES += userprintf_rbox_r.c
# SOURCES += random_r.c

# HEADERS += geom_r.h
# HEADERS += io_r.h
# HEADERS += libqhull_r.h
# HEADERS += mem_r.h
# HEADERS += merge_r.h
# HEADERS += poly_r.h
# HEADERS += random_r.h
# HEADERS += qhull_ra.h
# HEADERS += qset_r.h
# HEADERS += stat_r.h
# HEADERS += user_r.h
 