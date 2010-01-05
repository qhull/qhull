# -------------------------------------------------
# user_eg2.pro -- Qt project for Qhull demonstration
# -------------------------------------------------
TARGET = user_eg2
DESTDIR = ../..
TEMPLATE = app
CONFIG += console warn_on
CONFIG -= app_bundle
LIBS += -L../..
QMAKE_CFLAGS += -Wall -Wextra -Wshadow -Wcast-qual -Wwrite-strings
QMAKE_CFLAGS += -Wno-sign-conversion # Many size_t vs. int errors
build_pass:CONFIG(debug, debug|release):{
   LIBS += libqhulld
   OBJECTS_DIR = ../../tmp/user_eg2/Debug
}else:build_pass:CONFIG(release, debug|release):{
   LIBS += libqhull
   OBJECTS_DIR = ../../tmp/user_eg2/Release
}
QT -= gui
CONFIG -= app_bundle
INCLUDEPATH = ../../tmp
VPATH = ../..
SOURCES += src/user_eg2.c
HEADERS += src/libqhull.h
