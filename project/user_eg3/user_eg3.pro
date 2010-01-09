# -------------------------------------------------
# user_eg3.pro -- Qt project for cpp demonstration user_eg3.exe
# -------------------------------------------------
TARGET = user_eg3
DESTDIR = ../..
TEMPLATE = app
CONFIG += console warn_on
LIBS += -L../..
DEFINES += qh_QHpointer
build_pass:CONFIG(debug, debug|release):{
   LIBS += libqhullcppd
   PRE_TARGETDEPS += ../../libqhullcppd.a
   OBJECTS_DIR = ../../tmp/user_eg3/Debug
}else:build_pass:CONFIG(release, debug|release):{
   LIBS += libqhullcpp
   PRE_TARGETDEPS += ../../libqhullcpp.a
   OBJECTS_DIR = ../../tmp/user_eg3/Release
}
QT -= gui
CONFIG -= app_bundle
MOC_DIR = ../../tmp/moc
RCC_DIR = ../../tmp/rcc
INCLUDEPATH = ../../cpp;../../cpp/road;../../tmp

VPATH = ../..
SOURCES += cpp/user_eg3.cpp

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
