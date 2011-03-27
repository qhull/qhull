# -------------------------------------------------
# qhull-app-shared.pri -- Qt include project for C qhull applications linked to libqhull (shared library)
# -------------------------------------------------

DESTDIR = ../../bin
TEMPLATE = app
CONFIG += console warn_on
CONFIG -= qt

LIBS += -L../../bin
build_pass:CONFIG(debug, debug|release){
   LIBS += -lqhull-d
   OBJECTS_DIR = Debug
}else:build_pass:CONFIG(release, debug|release){
   LIBS += -lqhull
   OBJECTS_DIR = Release
}
win32-msvc* : QMAKE_LFLAGS += /INCREMENTAL:NO

INCLUDEPATH += ../libqhull
CONFIG += qhull_warn_conversion

include(qhull-warn.pri)

