# -------------------------------------------------
# qhull-app-shared.pri -- Qt include project for C qhull applications linked to libqhull (shared library)
# -------------------------------------------------

include(qhull-warn.pri)

DESTDIR = ../../bin
TEMPLATE = app
CONFIG += console warn_on
CONFIG -= qt

LIBS += -L../../lib
build_pass:CONFIG(debug, debug|release){
   LIBS += -lqhull_d$$qhull_VERSION_MAJOR
   OBJECTS_DIR = Debug
}else:build_pass:CONFIG(release, debug|release){
   LIBS += -lqhull$$qhull_VERSION_MAJOR
   OBJECTS_DIR = Release
}
win32-msvc* : QMAKE_LFLAGS += /INCREMENTAL:NO

DEFINES += qh_QHpointer # libqhull/user.h
win32-msvc* : DEFINES += qh_QHpointer_dllimport # libqhull/user.h

INCLUDEPATH += ../libqhull
CONFIG += qhull_warn_conversion


