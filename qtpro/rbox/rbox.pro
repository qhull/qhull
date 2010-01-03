# -------------------------------------------------
# rbox.pro -- Qt project for rbox.exe
# -------------------------------------------------
TARGET = rbox
DESTDIR = ../..
TEMPLATE = app
CONFIG += console
LIBS += -L../..
build_pass:CONFIG(debug, debug|release):{
   LIBS += libqhulld
   OBJECTS_DIR = ../../tmp/rbox/Debug
}else:build_pass:CONFIG(release, debug|release):{
   LIBS += libqhull
   OBJECTS_DIR = ../../tmp/rbox/Release
}
QT -= gui
CONFIG -= app_bundle
MOC_DIR = ../../tmp/moc
RCC_DIR = ../../tmp/rcc
INCLUDEPATH = ../../cpp;../../cpp/road;../../tmp
VPATH = ../..
SOURCES += src/rbox.c
HEADERS += src/libqhull.h
