# -------------------------------------------------
# user_eg2.pro -- Qt project for Qhull demonstration
# -------------------------------------------------
TARGET = user_eg2
DESTDIR = ../..
TEMPLATE = app
CONFIG += console warn_on
CONFIG -= app_bundle
LIBS += -L../..
!win32-msvc2003:!win32-msvc2005:!win32-msvc2008:!win32-msvc2010 {
    QMAKE_CFLAGS_WARN_ON += -Werror -Wall -Wcast-qual -Wextra -Wshadow -Wwrite-strings
    QMAKE_CFLAGS_WARN_ON += -Wno-sign-conversion # Many size_t vs. int warnings
    #QMAKE_CFLAGS_WARN_ON += -Wconversion # No workaround for bit-field conversions
}
build_pass:CONFIG(debug, debug|release):{
   LIBS += libqhulld
   PRE_TARGETDEPS += ../../libqhulld.a
   OBJECTS_DIR = ../../tmp/user_eg2/Debug
}else:build_pass:CONFIG(release, debug|release):{
   LIBS += libqhull
   PRE_TARGETDEPS += ../../libqhull.a
   OBJECTS_DIR = ../../tmp/user_eg2/Release
}
QT -= gui
CONFIG -= app_bundle
INCLUDEPATH = ../../tmp
VPATH = ../..
SOURCES += src/user_eg2.c
HEADERS += src/libqhull.h
