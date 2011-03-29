# -------------------------------------------------
# qhull-app-shared.pri -- Qt include project for C qhull applications linked to libqhull (shared library)
# -------------------------------------------------

DESTDIR = ../../bin
TEMPLATE = app
CONFIG += console warn_on
CONFIG -= qt

LIBS += -L../../lib
build_pass:CONFIG(debug, debug|release){
   LIBS += -lqhull-d6
   OBJECTS_DIR = Debug
}else:build_pass:CONFIG(release, debug|release){
   LIBS += -lqhull6
   OBJECTS_DIR = Release
}
win32-msvc* : QMAKE_LFLAGS += /INCREMENTAL:NO

DEFINES += qh_QHpointer # libqhull/user.h

INCLUDEPATH += ../libqhull
CONFIG += qhull_warn_conversion

include(qhull-warn.pri)

