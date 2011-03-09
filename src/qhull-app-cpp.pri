DESTDIR = ../../bin
TEMPLATE = app
CONFIG += console warn_on
CONFIG -= rtti
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
*g++ {
    #QMAKE_CXXFLAGS_WARN_ON += -Wshadow # Shadowing in Qt, e.g., nested foreach
    #QMAKE_CXXFLAGS_WARN_ON += -Wconversion # Conversion errors in Qt for qbitarray and qpalette
    QMAKE_CXXFLAGS_WARN_ON += -Werror # Treat warnings as errors
    QMAKE_CXXFLAGS_WARN_ON += -Wcast-qual -Wextra -Wwrite-strings
    QMAKE_CXXFLAGS_WARN_ON += -Wno-sign-conversion
}
win32-msvc : QMAKE_LFLAGS += /INCREMENTAL:NO

INCLUDEPATH += ../libqhullcpp
INCLUDEPATH += ../../src # e.g., "road/RoadError.h"
DEFINES += qh_QHpointer
