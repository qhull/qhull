# -------------------------------------------------
# libqhull.pro -- Qt project for Qhull static library
#   Built with qh_QHpointer=0.  See libqhullp.pro
# -------------------------------------------------

DESTDIR = ../..
TEMPLATE = lib
CONFIG += staticlib warn_on
CONFIG -= app_bundle qt
# Appears to be needed for gcc 4.1, 4.2, and 4.3 with -O2
#QMAKE_CFLAGS += -fno-strict-aliasing
QMAKE_CFLAGS_WARN_ON += -Werror -Wall -Wcast-qual -Wextra -Wshadow -Wwrite-strings
QMAKE_CFLAGS_WARN_ON += -Wno-sign-conversion # Many size_t vs. int errors
#QMAKE_CFLAGS_WARN_ON += -Wconversion # no workaround for bit-field conversion errors
build_pass:CONFIG(debug, debug|release):{
    TARGET = qhulld
    OBJECTS_DIR = ../../tmp/libqhull/Debug
}else:build_pass:CONFIG(release, debug|release):{
    TARGET = qhull
    OBJECTS_DIR = ../../tmp/libqhull/Release
}
MOC_DIR = ../../tmp/moc
RCC_DIR = ../../tmp/rcc

# libqhull.pro and libqhullp.pro are the same for SOURCES and HEADERS
# Order object files by frequency of execution.  Small files at end.
VPATH= ../..
SOURCES += src/rboxlib.c
SOURCES += src/user.c
SOURCES += src/global.c
SOURCES += src/stat.c
SOURCES += src/io.c
SOURCES += src/geom2.c
SOURCES += src/poly2.c
SOURCES += src/merge.c
SOURCES += src/libqhull.c
SOURCES += src/geom.c
SOURCES += src/poly.c
SOURCES += src/qset.c
SOURCES += src/mem.c
SOURCES += src/usermem.c
SOURCES += src/userprintf.c
SOURCES += src/random.c
HEADERS += src/geom.h
HEADERS += src/io.h
HEADERS += src/libqhull.h
HEADERS += src/mem.h
HEADERS += src/merge.h
HEADERS += src/poly.h
HEADERS += src/random.h
# qhull.h is for backwards compatibility
HEADERS += src/qhull_a.h
HEADERS += src/qset.h
HEADERS += src/stat.h
HEADERS += src/user.h

OTHER_FILES += Announce.txt
OTHER_FILES += CMakeLists.txt
OTHER_FILES += COPYING.txt
OTHER_FILES += File_id.diz
OTHER_FILES += html/index.htm
OTHER_FILES += html/qconvex.htm
OTHER_FILES += html/qdelau_f.htm
OTHER_FILES += html/qdelaun.htm
OTHER_FILES += html/qhalf.htm
OTHER_FILES += html/qh-code.htm
OTHER_FILES += html/qh-eg.htm
OTHER_FILES += html/qh-faq.htm
OTHER_FILES += html/qh-get.htm
OTHER_FILES += html/qh-impre.htm
OTHER_FILES += html/qh-optc.htm
OTHER_FILES += html/qh-optf.htm
OTHER_FILES += html/qh-optg.htm
OTHER_FILES += html/qh-opto.htm
OTHER_FILES += html/qh-optp.htm
OTHER_FILES += html/qh-optq.htm
OTHER_FILES += html/qh-optt.htm
OTHER_FILES += html/qh-quick.htm
OTHER_FILES += html/qhull.htm
OTHER_FILES += html/qhull.man
OTHER_FILES += html/qhull.txt
OTHER_FILES += html/qhull-cpp.xml
OTHER_FILES += html/qvoron_f.htm
OTHER_FILES += html/qvoronoi.htm
OTHER_FILES += html/rbox.htm
OTHER_FILES += html/rbox.man
OTHER_FILES += html/rbox.txt
OTHER_FILES += index.htm
OTHER_FILES += README.txt
OTHER_FILES += REGISTER.txt
OTHER_FILES += src/Changes.txt
OTHER_FILES += src/CMakeLists.txt
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

