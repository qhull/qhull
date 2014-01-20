# -------------------------------------------------
# testqset.pro -- Qt project file for testqset.exe
# -------------------------------------------------

include(../qhull-warn.pri)

TARGET = testqsetr

DESTDIR = ../../bin
TEMPLATE = app
CONFIG += console warn_on
CONFIG -= qt
CONFIG += qhull_warn_conversion

build_pass:CONFIG(debug, debug|release){
   OBJECTS_DIR = Debug
}else:build_pass:CONFIG(release, debug|release){
   OBJECTS_DIR = Release
}

INCLUDEPATH += ../libqhullr

SOURCES += testqset_r.c
SOURCES += ../libqhullr/qset_r.c
SOURCES += ../libqhullr/mem_r.c

HEADERS += ../libqhullr/mem_r.h
HEADERS += ../libqhullr/qset_r.h

