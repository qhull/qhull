# -------------------------------------------------
# libqhullpcpp.pro -- Qt project for Qhull cpp shared library based on libqhullp
# -------------------------------------------------

include(../qhull-warn.pri)

DESTDIR = ../../lib
TEMPLATE = lib
CONFIG += staticlib warn_on
CONFIG -= qt rtti
build_pass:CONFIG(debug, debug|release):{
   TARGET = qhullcpp_pd
   OBJECTS_DIR = Debug
}else:build_pass:CONFIG(release, debug|release):{
   TARGET = qhullcpp_p
   OBJECTS_DIR = Release
}
MOC_DIR = moc

DEFINES += qh_QHpointer # libqhull/user.h

INCLUDEPATH += ../../src
INCLUDEPATH += $$PWD # for MOC_DIR

CONFIG += qhull_warn_shadow qhull_warn_conversion

SOURCES += ../libqhullpcpp/Coordinates.cpp
SOURCES += ../libqhullpcpp/PointCoordinates.cpp
SOURCES += ../libqhullpcpp/Qhull.cpp
SOURCES += ../libqhullpcpp/QhullFacet.cpp
SOURCES += ../libqhullpcpp/QhullFacetList.cpp
SOURCES += ../libqhullpcpp/QhullFacetSet.cpp
SOURCES += ../libqhullpcpp/QhullHyperplane.cpp
SOURCES += ../libqhullpcpp/QhullPoint.cpp
SOURCES += ../libqhullpcpp/QhullPoints.cpp
SOURCES += ../libqhullpcpp/QhullPointSet.cpp
SOURCES += ../libqhullpcpp/QhullQh.cpp
SOURCES += ../libqhullpcpp/QhullRidge.cpp
SOURCES += ../libqhullpcpp/QhullSet.cpp
SOURCES += ../libqhullpcpp/QhullStat.cpp
SOURCES += ../libqhullpcpp/QhullVertex.cpp
SOURCES += ../libqhullpcpp/QhullVertexSet.cpp
SOURCES += ../libqhullpcpp/RboxPoints.cpp
SOURCES += ../libqhullpcpp/RoadError.cpp
SOURCES += ../libqhullpcpp/RoadLogEvent.cpp
SOURCES += ../libqhullpcpp/UsingLibQhull.cpp

HEADERS += ../libqhullpcpp/Coordinates.h
HEADERS += ../libqhullpcpp/functionObjects.h
HEADERS += ../libqhullpcpp/PointCoordinates.h
HEADERS += ../libqhullpcpp/Qhull.h
HEADERS += ../libqhullpcpp/QhullError.h
HEADERS += ../libqhullpcpp/QhullFacet.h
HEADERS += ../libqhullpcpp/QhullFacetList.h
HEADERS += ../libqhullpcpp/QhullFacetSet.h
HEADERS += ../libqhullpcpp/QhullHyperplane.h
HEADERS += ../libqhullpcpp/QhullIterator.h
HEADERS += ../libqhullpcpp/QhullLinkedList.h
HEADERS += ../libqhullpcpp/QhullPoint.h
HEADERS += ../libqhullpcpp/QhullPoints.h
HEADERS += ../libqhullpcpp/QhullPointSet.h
HEADERS += ../libqhullpcpp/QhullQh.h
HEADERS += ../libqhullpcpp/QhullRidge.h
HEADERS += ../libqhullpcpp/QhullSet.h
HEADERS += ../libqhullpcpp/QhullSets.h
HEADERS += ../libqhullpcpp/QhullStat.h
HEADERS += ../libqhullpcpp/QhullVertex.h
HEADERS += ../libqhullpcpp/QhullVertexSet.h
HEADERS += ../libqhullpcpp/RboxPoints.h
HEADERS += ../libqhullpcpp/RoadError.h
HEADERS += ../libqhullpcpp/RoadLogEvent.h
HEADERS += ../libqhullpcpp/UsingLibQhull.h
