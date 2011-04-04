# -------------------------------------------------
# libqhullstaticp.pro -- Qhull static library with qh_qhPointer
# -------------------------------------------------

include(../qhull-warn.pri)
include(../qhull-libsrc.pri)

DESTDIR = ../../lib
TEMPLATE = lib
CONFIG += staticlib warn_on
CONFIG -= qt
build_pass:CONFIG(debug, debug|release) {
    TARGET = qhullstatic-pd
    OBJECTS_DIR = Debug
}else:build_pass:CONFIG(release, debug|release) {
    TARGET = qhullstatic-p
    OBJECTS_DIR = Release
}

DEFINES += qh_QHpointer # libqhull/user.h

