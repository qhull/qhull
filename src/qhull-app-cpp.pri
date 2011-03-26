# -------------------------------------------------
# qhull-app-cpp.pri -- Qt include project for CPP qhull applications using Qt
#   libqhull.pro, libqhullp.pro, and libqhulldll.pro are the same for SOURCES and HEADERS
# -------------------------------------------------

DESTDIR = ../../bin
TEMPLATE = app
CONFIG += console warn_on
CONFIG -= rtti incremental
LIBS += -L../../lib
build_pass:CONFIG(debug, debug|release){
   LIBS += -lqhullcpp-d
   LIBS += -lqhull-pd  # Must be last, otherwise qh_fprintf,etc. are loaded from here instead of qhullcpp-d.lib
   OBJECTS_DIR = Debug
}else:build_pass:CONFIG(release, debug|release){
   LIBS += -lqhullcpp
   LIBS += -lqhull-p  # Must be last, otherwise qh_fprintf,etc. are loaded from here instead of qhullcpp.lib
   OBJECTS_DIR = Release
}

DEFINES += qh_QHpointer # libqhull/user.h

include(qhull-warn.pri)

INCLUDEPATH += ../libqhullcpp
INCLUDEPATH += ../../src # e.g., "road/RoadError.h"
