DESTDIR = ../../bin
TEMPLATE = app
CONFIG += console warn_on
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
*xxg++ {
    QMAKE_CXXFLAGS_WARN_ON += -Werror -Wcast-qual -Wextra -Wshadow -Wwrite-strings
    QMAKE_CXXFLAGS_WARN_ON += -Wno-sign-conversion
    QMAKE_CXXFLAGS_WARN_ON += -Wconversion
    QMAKE_CXXFLAGS_WARN_ON += -pendantic
}
win32-msvc : QMAKE_LFLAGS += /INCREMENTAL:NO

INCLUDEPATH += ../libqhullcpp
INCLUDEPATH += ../../src # e.g., "road/RoadError.h"
DEFINES += qh_QHpointer
