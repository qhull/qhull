# -------------------------------------------------
# rbox.pro -- Qt project for rbox.exe
# -------------------------------------------------
TARGET = rbox
DESTDIR = ../..
TEMPLATE = app
CONFIG += console warn_on
LIBS += -L../..
QMAKE_CFLAGS_WARN_ON += -Werror -Wall -Wcast-qual -Wextra -Wshadow -Wwrite-strings
QMAKE_CFLAGS_WARN_ON += -Wno-sign-conversion # Many size_t vs. int warnings
#QMAKE_CFLAGS_WARN_ON += -Wconversion # No workaround for bit-field conversions
build_pass:CONFIG(debug, debug|release):{
   LIBS += libqhulld
   PRE_TARGETDEPS += ../../libqhulld.a
   OBJECTS_DIR = ../../tmp/rbox/Debug
}else:build_pass:CONFIG(release, debug|release):{
   LIBS += libqhull
   PRE_TARGETDEPS += ../../libqhull.a
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
