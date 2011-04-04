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
   LIBS += -lqhull$$VERS_MAJ-d
   OBJECTS_DIR = Debug
}else:build_pass:CONFIG(release, debug|release){
   LIBS += -lqhull$$VERS_MAJ
   OBJECTS_DIR = Release
}
win32-msvc* : QMAKE_LFLAGS += /INCREMENTAL:NO

DEFINES += qh_QHpointer # libqhull/user.h

INCLUDEPATH += ../libqhull
CONFIG += qhull_warn_conversion


