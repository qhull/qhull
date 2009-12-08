# -------------------------------------------------
# qhulllib.pro -- Qt project file
# -------------------------------------------------
# configure -commercial -no-qt3support -no-opengl -no-rtti -qt-style-plastique
QT -= gui
TARGET = ../../qhull
CONFIG += staticlib
CONFIG -= app_bundle qt
TEMPLATE = lib
DESTDIR = ../../tmp/lib
OBJECTS_DIR = ../../tmp/obj
MOC_DIR = ../../tmp/moc
RCC_DIR = ../../tmp/rcc
# INCLUDEPATH = ../src
VPATH= ../..
SOURCES += src/geom.c
SOURCES += src/geom2.c
SOURCES += src/global.c
SOURCES += src/io.c
SOURCES += src/mem.c
SOURCES += src/merge.c
SOURCES += src/poly2.c
SOURCES += src/poly.c
SOURCES += src/libqhull.c
SOURCES += src/qset.c
SOURCES += src/random.c
SOURCES += src/rboxlib.c
SOURCES += src/stat.c
SOURCES += src/user.c
SOURCES += src/usermem.c
SOURCES += src/userprintf.c
OTHER_FILES += src/Changes.txt
OTHER_FILES += src/index.htm
OTHER_FILES += src/Make-config.sh
OTHER_FILES += src/Makefile.txt
OTHER_FILES += src/Mborland
OTHER_FILES += src/qh-geom.htm
OTHER_FILES += src/qh-globa.htm
OTHER_FILES += src/qh-io.htm
OTHER_FILES += src/qh-mem.htm
OTHER_FILES += src/qh-merge.htm
OTHER_FILES += src/qh-poly.htm
OTHER_FILES += src/qh-qhull.htm
OTHER_FILES += src/qh-set.htm
OTHER_FILES += src/qh-stat.htm
OTHER_FILES += src/qh-user.htm
HEADERS += src/geom.h
HEADERS += src/io.h
HEADERS += src/mem.h
HEADERS += src/merge.h
HEADERS += src/poly.h

# qhull.h is for backwards compatibility
HEADERS += src/libqhull.h
HEADERS += src/qhull_a.h
HEADERS += src/qset.h
HEADERS += src/random.h
HEADERS += src/stat.h
HEADERS += src/user.h
