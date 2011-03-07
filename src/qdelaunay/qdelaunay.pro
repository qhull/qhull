# -------------------------------------------------
# qdelaunay.pro -- Qt project file for qvoronoi.exe
# -------------------------------------------------

TARGET = qdelaunay
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
   OBJECTS_DIR = ../../tmp/qdelaunay/Debug
}else:build_pass:CONFIG(release, debug|release):{
   LIBS += libqhull
   PRE_TARGETDEPS += ../../libqhull.a
   OBJECTS_DIR = ../../tmp/qdelaunay/Release
}
QT -= gui
MOC_DIR = ../../tmp/moc
RCC_DIR = ../../tmp/rcc
INCLUDEPATH = ../../tmp
VPATH = ../..
SOURCES += src/qdelaun.c
HEADERS += src/libqhull.h
