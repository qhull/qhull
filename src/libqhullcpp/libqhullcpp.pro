# -------------------------------------------------
# libqhullcpp.pro -- Qt project for Qhull cpp shared library
# -------------------------------------------------


DESTDIR = ../../lib
TEMPLATE = lib
CONFIG += staticlib warn_on
CONFIG -= qt rtti
build_pass:CONFIG(debug, debug|release):{
   TARGET = qhullcpp-d
   OBJECTS_DIR = Debug
}else:build_pass:CONFIG(release, debug|release):{
   TARGET = qhullcpp
   OBJECTS_DIR = Release
}
MOC_DIR = moc

DEFINES += qh_QHpointer
INCLUDEPATH += ../../src
INCLUDEPATH += $$PWD # for MOC_DIR
*g++ {
    QMAKE_CXXFLAGS_WARN_ON += -Werror # Treat warnings as errors
    QMAKE_CXXFLAGS_WARN_ON += -Wshadow -Wconversion
    QMAKE_CXXFLAGS_WARN_ON += -Wcast-qual -Wextra -Wshadow -Wwrite-strings
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

SOURCES += ../road/RoadError.cpp
SOURCES += ../road/RoadLogEvent.cpp
SOURCES += Coordinates.cpp
SOURCES += QhullVertexSet.cpp
SOURCES += QhullHyperplane.cpp
SOURCES += PointCoordinates.cpp
SOURCES += Qhull.cpp
SOURCES += QhullFacet.cpp
SOURCES += QhullFacetList.cpp
SOURCES += QhullFacetSet.cpp
SOURCES += QhullPoint.cpp
SOURCES += QhullPoints.cpp
SOURCES += QhullPointSet.cpp
SOURCES += QhullQh.cpp
SOURCES += QhullRidge.cpp
SOURCES += QhullSet.cpp
SOURCES += QhullStat.cpp
SOURCES += QhullVertex.cpp
SOURCES += RboxPoints.cpp
SOURCES += UsingLibQhull.cpp

HEADERS += ../road/RoadError.h
HEADERS += ../road/RoadLogEvent.h
HEADERS += Coordinates.h
HEADERS += QhullHyperplane.h
HEADERS += functionObjects.h
HEADERS += PointCoordinates.h
HEADERS += Qhull.h
HEADERS += QhullError.h
HEADERS += QhullFacet.h
HEADERS += QhullFacetList.h
HEADERS += QhullFacetSet.h
HEADERS += QhullIterator.h
HEADERS += QhullLinkedList.h
HEADERS += QhullPoint.h
HEADERS += QhullPoints.h
HEADERS += QhullPointSet.h
HEADERS += QhullQh.h
HEADERS += QhullRidge.h
HEADERS += QhullSet.h
HEADERS += QhullSets.h
HEADERS += QhullStat.h
HEADERS += QhullVertex.h
HEADERS += RboxPoints.h
HEADERS += UsingLibQhull.h
