# -------------------------------------------------
# qhalf.pro -- Qt project file for qconvex.exe
# -------------------------------------------------

TARGET = qhalf
DESTDIR = ../..
TEMPLATE = app
CONFIG += console warn_on
CONFIG -= app_bundle
LIBS += -L../..
# QMAKE_CFLAGS += -fno-strict-aliasing
QMAKE_CFLAGS += -Wall -Wextra -Wshadow -Wcast-qual -Wwrite-strings
QMAKE_CFLAGS += -Wno-sign-conversion # Many size_t vs. int errors
build_pass:CONFIG(debug, debug|release):{
   LIBS += libqhulld
   OBJECTS_DIR = ../../tmp/qconvex/Debug
}else:build_pass:CONFIG(release, debug|release):{
   LIBS += libqhull
   OBJECTS_DIR = ../../tmp/qconvex/Release
}
QT -= gui
MOC_DIR = ../../tmp/moc
RCC_DIR = ../../tmp/rcc
INCLUDEPATH = ../../tmp
VPATH = ../..
SOURCES += src/qhalf.c
HEADERS += src/libqhull.h
