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

DEFINES += qh_QHpointer # libqhull/user.h

include(../qhull-warn.pri)
include(../qhull-libsrc.pri)
