# -------------------------------------------------
# libqhull.pro -- Qt project for Qhull shared library
# -------------------------------------------------

include(../qhull-warn.pri)

DESTDIR = ../../lib
DLLDESTDIR = ../../bin
TEMPLATE = lib
CONFIG += shared warn_on
CONFIG -= qt

build_pass:CONFIG(debug, debug|release):{
    TARGET = qhull_d
    OBJECTS_DIR = Debug
}else:build_pass:CONFIG(release, debug|release):{
    TARGET = qhull
    OBJECTS_DIR = Release
}
win32-msvc* : QMAKE_LFLAGS += /INCREMENTAL:NO

win32-msvc* : DEF_FILE += ../../src/libqhull/qhull-exports.def

include(../qhull-libqhull-src.pri)

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
