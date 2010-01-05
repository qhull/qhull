# -------------------------------------------------
# qvoronoi.pro -- Qt project file for qvoronoi.exe
# -------------------------------------------------

TARGET = qvoronoi
DESTDIR = ../..
TEMPLATE = app
CONFIG += console warn_on
CONFIG -= app_bundle
LIBS += -L../..
QMAKE_CFLAGS += -Wall -Wextra -Wshadow -Wcast-qual -Wwrite-strings
QMAKE_CFLAGS += -Wno-sign-conversion # Many size_t vs. int errors
build_pass:CONFIG(debug, debug|release):{
   LIBS += libqhulld
   OBJECTS_DIR = ../../tmp/qvoronoi/Debug
}else:build_pass:CONFIG(release, debug|release):{
   LIBS += libqhull
   OBJECTS_DIR = ../../tmp/qvoronoi/Release
}
QT -= gui
MOC_DIR = ../../tmp/moc
RCC_DIR = ../../tmp/rcc
INCLUDEPATH = ../../tmp
VPATH = ../..
SOURCES += src/qvoronoi.c
HEADERS += src/libqhull.h
