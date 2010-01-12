# -------------------------------------------------
# qhulltest.pro -- Qt project for qhulltest.exe (QTestLib)
# -------------------------------------------------

TARGET = qhulltest
DESTDIR = ../..
TEMPLATE = app
CONFIG += console qtestlib warn_on
CONFIG -= app_bundle
LIBS += -L../..
DEFINES += qh_QHpointer
build_pass:CONFIG(debug, debug|release):{
   LIBS += libqhullcppd
   PRE_TARGETDEPS += ../../libqhullcppd.a
   OBJECTS_DIR = ../../tmp/qhulltest/Debug
}else:build_pass:CONFIG(release, debug|release):{
   LIBS += libqhullcpp
   OBJECTS_DIR = ../../tmp/qhulltest/Release
   PRE_TARGETDEPS += ../../libqhullcpp.a
}
QT -= gui
MOC_DIR = ../../tmp/moc
RCC_DIR = ../../tmp/rcc
INCLUDEPATH = ../../cpp;../../cpp/road;../../tmp
PRECOMPILED_HEADER = cpp/road/RoadTest.h

# MAKEFILE = Makefile.qhulltest -- does  not work (it's ignored)
VPATH = ../..
SOURCES += cpp/road/RoadTest.cpp
SOURCES += cpp/qhulltest/Coordinates_test.cpp
SOURCES += cpp/qhulltest/PointCoordinates_test.cpp
SOURCES += cpp/qhulltest/Qhull_test.cpp
SOURCES += cpp/qhulltest/QhullFacet_test.cpp
SOURCES += cpp/qhulltest/QhullFacetList_test.cpp
SOURCES += cpp/qhulltest/QhullFacetSet_test.cpp
SOURCES += cpp/qhulltest/QhullHyperplane_test.cpp
SOURCES += cpp/qhulltest/QhullLinkedList_test.cpp
SOURCES += cpp/qhulltest/QhullPoint_test.cpp
SOURCES += cpp/qhulltest/QhullPoints_test.cpp
SOURCES += cpp/qhulltest/QhullPointSet_test.cpp
SOURCES += cpp/qhulltest/QhullRidge_test.cpp
SOURCES += cpp/qhulltest/QhullSet_test.cpp
SOURCES += cpp/qhulltest/qhulltest.cpp
SOURCES += cpp/qhulltest/QhullVertex_test.cpp
SOURCES += cpp/qhulltest/qt-qhull.cpp
SOURCES += cpp/qhulltest/UsingLibQhull_test.cpp
SOURCES += cpp/qhulltest/RboxPoints_test.cpp
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
HEADERS += cpp/UsingLibQhull.h
HEADERS += cpp/road/RoadError.h
HEADERS += cpp/road/RoadLogEvent.h
HEADERS += cpp/road/RoadTest.h

