# -------------------------------------------------
# qvoronoi.pro -- Qt project file for qvoronoi.exe
# -------------------------------------------------

TARGET = qvoronoi
DESTDIR = ../..
TEMPLATE = app
CONFIG += console warn_on
CONFIG -= app_bundle
LIBS += -L../..
QMAKE_CFLAGS_WARN_ON += -Werror -Wall -Wcast-qual -Wextra -Wshadow -Wwrite-strings
QMAKE_CFLAGS_WARN_ON += -Wno-sign-conversion # Many size_t vs. int errors
#QMAKE_CFLAGS_WARN_ON += -Wconversion # no workaround for bit-field conversion errors
build_pass:CONFIG(debug, debug|release):{
   LIBS += libqhulld
   PRE_TARGETDEPS += ../../libqhulld.a
   OBJECTS_DIR = ../../tmp/qvoronoi/Debug
}else:build_pass:CONFIG(release, debug|release):{
   LIBS += libqhull
   PRE_TARGETDEPS += ../../libqhull.a
   OBJECTS_DIR = ../../tmp/qvoronoi/Release
}
QT -= gui
MOC_DIR = ../../tmp/moc
RCC_DIR = ../../tmp/rcc
INCLUDEPATH = ../../tmp
VPATH = ../..
SOURCES += src/qvoronoi.c
HEADERS += src/libqhull.h
