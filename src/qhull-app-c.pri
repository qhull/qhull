# -------------------------------------------------
# qhull-app-c.pri -- Qt include project for C qhull applications linked to libqhull
# -------------------------------------------------

DESTDIR = ../../bin
TEMPLATE = app
CONFIG += console warn_on
CONFIG -= qt incremental

LIBS += -L../../lib
build_pass:CONFIG(debug, debug|release){
   LIBS += -lqhull-d
   OBJECTS_DIR = Debug
}else:build_pass:CONFIG(release, debug|release){
   LIBS += -lqhull
   OBJECTS_DIR = Release
}

INCLUDEPATH += ../libqhull
CONFIG += qhull_warn_conversion
include(../qhull-warn.pri)

