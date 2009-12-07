# -------------------------------------------------
# user_eg3.pro -- Qt project file for cpp demonstration program
# -------------------------------------------------
QT -= gui
TARGET = user_eg3
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
DESTDIR = ../..
OBJECTS_DIR = ../../tmp/obj
MOC_DIR = ../../tmp/moc
RCC_DIR = ../../tmp/rcc
INCLUDEPATH = ../../cpp;../../cpp/road;../../tmp
VPATH = ../..
SOURCES += cpp/user_eg3.cpp
SOURCES += cpp/Coordinates.cpp
SOURCES += cpp/QhullVertexSet.cpp
SOURCES += cpp/QhullHyperplane.cpp
SOURCES += cpp/PointCoordinates.cpp
SOURCES += cpp/Qhull.cpp
SOURCES += cpp/QhullError.cpp
SOURCES += cpp/QhullEvent.cpp
SOURCES += cpp/QhullFacet.cpp
SOURCES += cpp/QhullFacetList.cpp
SOURCES += cpp/QhullFacetSet.cpp
SOURCES += cpp/QhullPoint.cpp
SOURCES += cpp/QhullPoints.cpp
SOURCES += cpp/QhullPointSet.cpp
SOURCES += cpp/QhullQh.cpp
SOURCES += cpp/QhullRidge.cpp
SOURCES += cpp/QhullSet.cpp
SOURCES += cpp/QhullStat.cpp
SOURCES += cpp/QhullVertex.cpp
SOURCES += cpp/RboxPoints.cpp
SOURCES += cpp/UsingQhullLib.cpp
SOURCES += cpp/road/RoadError.cpp
SOURCES += cpp/road/RoadLogEvent.cpp

HEADERS += cpp/Coordinates.h
HEADERS += cpp/QhullHyperplane.h
HEADERS += cpp/functionObjects.h
HEADERS += cpp/PointCoordinates.h
HEADERS += cpp/Qhull.h
HEADERS += cpp/QhullError.h
HEADERS += cpp/QhullEvent.h
HEADERS += cpp/QhullFacet.h
HEADERS += cpp/QhullFacetList.h
HEADERS += cpp/QhullFacetSet.h
HEADERS += cpp/QhullIterator.h
HEADERS += cpp/QhullLinkedList.h
HEADERS += cpp/QhullPoint.h
HEADERS += cpp/QhullPoints.h
HEADERS += cpp/QhullPointSet.h
HEADERS += cpp/QhullQh.h
HEADERS += cpp/QhullRidge.h
HEADERS += cpp/QhullSet.h
HEADERS += cpp/QhullSets.h
HEADERS += cpp/QhullStat.h
HEADERS += cpp/QhullVertex.h
HEADERS += cpp/RboxPoints.h
HEADERS += cpp/UsingQhullLib.h
HEADERS += cpp/road/RoadError.h
HEADERS += cpp/road/RoadLogEvent.h

# Add all files explicitly.  The library did not work
# -------------------------------------------------
# qhulllib.pro -- Qt project file
# -------------------------------------------------
# configure -commercial -no-qt3support -no-opengl -no-rtti -qt-style-plastique

SOURCES += src/geom.c
SOURCES += src/geom2.c
SOURCES += src/global.c
SOURCES += src/io.c
SOURCES += src/mem.c
SOURCES += src/merge.c
SOURCES += src/poly2.c
SOURCES += src/poly.c
SOURCES += src/qhulllib.c
SOURCES += src/qset.c
SOURCES += src/random.c
SOURCES += src/rboxlib.c
SOURCES += src/stat.c
SOURCES += src/user.c
SOURCES += src/usermem.c
# SOURCES += src/userprintf.c

HEADERS += src/geom.h
HEADERS += src/io.h
HEADERS += src/mem.h
HEADERS += src/merge.h
HEADERS += src/poly.h

# qhull.h is for backwards compatibility
HEADERS += src/qhulllib.h
HEADERS += src/qhull_a.h
HEADERS += src/qset.h
HEADERS += src/random.h
HEADERS += src/stat.h
HEADERS += src/user.h
