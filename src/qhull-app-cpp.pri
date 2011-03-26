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
QMAKE_CXXFLAGS_WARN_ON += -Waddress
QMAKE_CXXFLAGS_WARN_ON += -Warray-bounds
QMAKE_CXXFLAGS_WARN_ON += -Wc++0x-compat
QMAKE_CXXFLAGS_WARN_ON += -Wchar-subscripts
QMAKE_CXXFLAGS_WARN_ON += -Wclobbered
QMAKE_CXXFLAGS_WARN_ON += -Wcomment
QMAKE_CXXFLAGS_WARN_ON += -Wempty-body
QMAKE_CXXFLAGS_WARN_ON += -Wenum-compare
QMAKE_CXXFLAGS_WARN_ON += -Wformat
QMAKE_CXXFLAGS_WARN_ON += -Wignored-qualifiers
QMAKE_CXXFLAGS_WARN_ON += -Wmain
QMAKE_CXXFLAGS_WARN_ON += -Wmissing-braces
QMAKE_CXXFLAGS_WARN_ON += -Wmissing-field-initializers
QMAKE_CXXFLAGS_WARN_ON += -Wparentheses
QMAKE_CXXFLAGS_WARN_ON += -Wreorder
QMAKE_CXXFLAGS_WARN_ON += -Wreturn-type
QMAKE_CXXFLAGS_WARN_ON += -Wsequence-point
QMAKE_CXXFLAGS_WARN_ON += -Wsign-compare
QMAKE_CXXFLAGS_WARN_ON += -Wsign-compare
QMAKE_CXXFLAGS_WARN_ON += -Wstrict-aliasing
QMAKE_CXXFLAGS_WARN_ON += -Wstrict-overflow=1
QMAKE_CXXFLAGS_WARN_ON += -Wswitch
QMAKE_CXXFLAGS_WARN_ON += -Wtrigraphs
QMAKE_CXXFLAGS_WARN_ON += -Wtype-limits
QMAKE_CXXFLAGS_WARN_ON += -Wuninitialized
QMAKE_CXXFLAGS_WARN_ON += -Wuninitialized
QMAKE_CXXFLAGS_WARN_ON += -Wunknown-pragmas
QMAKE_CXXFLAGS_WARN_ON += -Wunused-function
QMAKE_CXXFLAGS_WARN_ON += -Wunused-label
QMAKE_CXXFLAGS_WARN_ON += -Wunused-parameter
QMAKE_CXXFLAGS_WARN_ON += -Wunused-value
QMAKE_CXXFLAGS_WARN_ON += -Wunused-variable
QMAKE_CXXFLAGS_WARN_ON += -Wvolatile-register-var
}
win32-msvc : QMAKE_LFLAGS += /INCREMENTAL:NO

INCLUDEPATH += ../libqhullcpp
INCLUDEPATH += ../../src # e.g., "road/RoadError.h"
DEFINES += qh_QHpointer
