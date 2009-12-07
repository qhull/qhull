# -------------------------------------------------
# qhull.pro -- Qt project file for qhull.exe
# -------------------------------------------------
QT -= gui
TARGET = qhull
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
LIBS = ../../libqhull.a
DESTDIR = ../..
OBJECTS_DIR = ../../tmp/obj
MOC_DIR = ../../tmp/moc
RCC_DIR = ../../tmp/rcc
INCLUDEPATH = ../../cpp;../../cpp/road;../../tmp
VPATH = ../..
SOURCES += src/unix.c
HEADERS += src/qhulllib.h
