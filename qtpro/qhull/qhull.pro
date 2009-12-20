# -------------------------------------------------
# qhull.pro -- Qt project file for qhull.exe
# -------------------------------------------------

TARGET = qhull
DESTDIR = ../..
TEMPLATE = app
CONFIG += console
build_pass:CONFIG(debug, debug|release):{
   LIBS += ../../libqhulld.a
   OBJECTS_DIR = ../../tmp/qhull/Debug
}else:build_pass:CONFIG(release, debug|release):{
   LIBS += ../../libqhull.a
   OBJECTS_DIR = ../../tmp/qhull/Release
}
QT -= gui
CONFIG -= app_bundle
MOC_DIR = ../../tmp/moc
RCC_DIR = ../../tmp/rcc
INCLUDEPATH = ../../cpp;../../cpp/road;../../tmp
VPATH = ../..
SOURCES += src/unix.c
HEADERS += src/libqhull.h
