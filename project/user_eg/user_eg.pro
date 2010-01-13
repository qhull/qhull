# -------------------------------------------------
# user_eg.pro -- Qt project for Qhull demonstration
# -------------------------------------------------
TARGET = user_eg
DESTDIR = ../..
TEMPLATE = app
CONFIG += console warn_on
CONFIG -= app_bundle
LIBS += -L../..
DEFINES += qh_QHpointer
QMAKE_CFLAGS_WARN_ON += -Werror -Wall -Wcast-qual -Wextra -Wshadow -Wwrite-strings
QMAKE_CFLAGS_WARN_ON += -Wno-sign-conversion # Many size_t vs. int errors
#QMAKE_CFLAGS_WARN_ON += -Wconversion # no workaround for bit-field conversion errors
build_pass:CONFIG(debug, debug|release):{
   LIBS += libqhullpd
   PRE_TARGETDEPS += ../../libqhullpd.a
   OBJECTS_DIR = ../../tmp/user_eg/Debug
}else:build_pass:CONFIG(release, debug|release):{
   LIBS += libqhullp
   PRE_TARGETDEPS += ../../libqhullp.a
   OBJECTS_DIR = ../../tmp/user_eg/Release
}
QT -= gui
CONFIG -= app_bundle
INCLUDEPATH = ../../tmp
VPATH = ../..
SOURCES += src/user_eg.c
HEADERS += src/qhull_a.h
