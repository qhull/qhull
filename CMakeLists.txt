# CMakeLists.txt -- CMake configuration file for qhull, qhull6, and related programs
#
# To build Qhull, run cmake twice
#   cd build && cmake .. && cmake ..
#   make
#   make install
#   make help
#
# Visual Studio builds includes debug and release targets
#   Please rename library debug targets to ..._d... (e.g., qhullstatic_d.lib)
#
# $Id: //main/2011/qhull/CMakeLists.txt#6 $$Change: 1367 $
# $DateTime: 2011/04/08 22:21:11 $$Author: bbarber $

project(qhull)
cmake_minimum_required(VERSION 2.6)

# Define qhull_VERSION in CMakeLists.txt, Makefile, qhull-exports.def, and qhull-warn.pri
string(REGEX REPLACE ".* ([0-9]+) .*"
    "6.2.0.\\1"  qhull_VERSION "$Change: 1367 $")

if(INCLUDE_INSTALL_DIR)
else()
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)
endif()
if(LIB_INSTALL_DIR)
else()
set(LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib)
endif()
if(BIN_INSTALL_DIR)
else()
set(BIN_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/bin)
endif()
if(DOC_INSTALL_DIR)
else()
set(DOC_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share/doc/packages/qhull)
endif()

message(STATUS)
message(STATUS "========== qhull Build Information ==========")
message(STATUS "Build Version: 				   ${qhull_VERSION}")
message(STATUS "Install Prefix (CMAKE_INSTALL_PREFIX):     ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Binary Directory (BIN_INSTALL_DIR):        ${BIN_INSTALL_DIR}")
message(STATUS "Library Directory (LIB_INSTALL_DIR):       ${LIB_INSTALL_DIR}")
message(STATUS "Include Directory (INCLUDE_INSTALL_DIR):   ${INCLUDE_INSTALL_DIR}")
message(STATUS "Documentation Directory (DOC_INSTALL_DIR): ${DOC_INSTALL_DIR}")
message(STATUS "Build Type (CMAKE_BUILD_TYPE):             ${CMAKE_BUILD_TYPE}")
message(STATUS "To override these options, add -D{OPTION_NAME}=... to the commandline")
message(STATUS)
message(STATUS "To build and install qhull, enter \"make\" and \"make install\"")
message(STATUS)

# ---------------------------------------
# Define library source files and variables
#   qhull_MAJOR   The major component of qhull_VERSION
#
# Files for individual targets are defined with the target
# ---------------------------------------

# Order libqhull object files by frequency of execution.  Small files at end.
set(
    libqhull_SOURCES
        src/libqhull/rboxlib.c
        src/libqhull/user.c
        src/libqhull/global.c
        src/libqhull/stat.c
        src/libqhull/io.c
        src/libqhull/geom2.c
        src/libqhull/poly2.c
        src/libqhull/merge.c
        src/libqhull/libqhull.c
        src/libqhull/geom.c
        src/libqhull/poly.c
        src/libqhull/qset.c
        src/libqhull/mem.c
        src/libqhull/usermem.c
        src/libqhull/userprintf.c
        src/libqhull/random.c
)
set(
    libqhull_HEADERS
        src/libqhull/libqhull.h
        src/libqhull/geom.h
        src/libqhull/io.h
        src/libqhull/mem.h
        src/libqhull/merge.h
        src/libqhull/poly.h
        src/libqhull/qhull_a.h
        src/libqhull/qset.h
        src/libqhull/random.h
        src/libqhull/stat.h
        src/libqhull/user.h
)


set(
    libqhullcpp_SOURCES
        src/libqhullcpp/Coordinates.cpp
        src/libqhullcpp/PointCoordinates.cpp
        src/libqhullcpp/Qhull.cpp
        src/libqhullcpp/QhullFacet.cpp
        src/libqhullcpp/QhullFacetList.cpp
        src/libqhullcpp/QhullFacetSet.cpp
        src/libqhullcpp/QhullHyperplane.cpp
        src/libqhullcpp/QhullPoint.cpp
        src/libqhullcpp/QhullPointSet.cpp
        src/libqhullcpp/QhullPoints.cpp
        src/libqhullcpp/QhullQh.cpp
        src/libqhullcpp/QhullRidge.cpp
        src/libqhullcpp/QhullSet.cpp
        src/libqhullcpp/QhullStat.cpp
        src/libqhullcpp/QhullVertex.cpp
        src/libqhullcpp/QhullVertexSet.cpp
        src/libqhullcpp/RboxPoints.cpp
        src/libqhullcpp/UsingLibQhull.cpp
        src/road/RoadError.cpp
        src/road/RoadLogEvent.cpp
)
set(
    libqhullcpp_HEADERS
        src/libqhullcpp/Coordinates.h
        src/libqhullcpp/functionObjects.h
        src/libqhullcpp/PointCoordinates.h
        src/libqhullcpp/Qhull.h
        src/libqhullcpp/QhullError.h
        src/libqhullcpp/QhullFacet.h
        src/libqhullcpp/QhullFacetList.h
        src/libqhullcpp/QhullFacetSet.h
        src/libqhullcpp/QhullHyperplane.h
        src/libqhullcpp/QhullIterator.h
        src/libqhullcpp/QhullLinkedList.h
        src/libqhullcpp/QhullPoint.h
        src/libqhullcpp/QhullPoints.h
        src/libqhullcpp/QhullPointSet.h
        src/libqhullcpp/QhullQh.h
        src/libqhullcpp/QhullRidge.h
        src/libqhullcpp/QhullSet.h
        src/libqhullcpp/QhullSets.h
        src/libqhullcpp/QhullStat.h
        src/libqhullcpp/QhullVertex.h
        src/libqhullcpp/QhullVertexSet.h
        src/libqhullcpp/RboxPoints.h
        src/libqhullcpp/UsingLibQhull.h
)
set(
    road_HEADERS
        src/road/RoadError.h
        src/road/RoadLogEvent.h
)

include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/libqhull)

string(REGEX MATCH "[^.]+" qhull_MAJOR "${qhull_VERSION}")
if(CMAKE_BUILD_TYPE MATCHES "[dD]ebug")
    set(qhull_CPP qhullcpp_d)
    set(qhull_SHARED qhull_d${qhull_MAJOR})
    set(qhull_STATIC qhullstatic_d)
    set(qhull_STATICP qhullstatic_pd)
else()
    set(qhull_CPP qhullcpp)
    set(qhull_SHARED qhull${qhull_MAJOR})
    set(qhull_STATIC qhullstatic)
    set(qhull_STATICP qhullstatic_p)
endif()

set(
    qhull_TARGETS 
        ${qhull_CPP} ${qhull_SHARED} ${qhull_STATIC} ${qhull_STATICP} 
        qhull rbox qconvex qdelaunay qvoronoi qhalf
        user_eg user_eg2 user_eg3
)

# ---------------------------------------
# Define shared library qhull with qh_QHpointer
# ---------------------------------------

add_library(${qhull_SHARED} SHARED 
        ${libqhull_SOURCES}
        src/libqhull/qhull-exports.def)
set_target_properties(${qhull_SHARED} PROPERTIES
    COMPILE_DEFINITIONS "qh_QHpointer"
    VERSION ${qhull_VERSION})

#target_link_libraries(${qhull_SHARED} m)

if(UNIX)
    if(APPLE)
        set_target_properties(${qhull_SHARED} PROPERTIES 
            INSTALL_NAME_DIR "${LIB_INSTALL_DIR}")
    else()
        set_target_properties(${qhull_SHARED} PROPERTIES 
            INSTALL_RPATH "${LIB_INSTALL_DIR}"
            INSTALL_RPATH_USE_LINK_PATH TRUE
            BUILD_WITH_INSTALL_RPATH FALSE)
    endif()
endif(UNIX)

# ---------------------------------------
# Define static libraries qhullstatic and qhullstatic_p (qh_QHpointer)
# ---------------------------------------

add_library(${qhull_STATIC} STATIC ${libqhull_SOURCES})
set_target_properties(${qhull_STATIC} PROPERTIES
    VERSION ${qhull_VERSION})

add_library(${qhull_STATICP} STATIC ${libqhull_SOURCES})
set_target_properties(${qhull_STATICP} PROPERTIES
    COMPILE_DEFINITIONS "qh_QHpointer"
    VERSION ${qhull_VERSION})

# ---------------------------------------
# Define C++ static library qhullcpp (qh_QHpointer)
# ---------------------------------------

add_library(${qhull_CPP} STATIC ${libqhullcpp_SOURCES})
set_target_properties(${qhull_CPP} PROPERTIES
    COMPILE_DEFINITIONS "qh_QHpointer"
    VERSION ${qhull_VERSION})

# ---------------------------------------
# Define qhull executables linked to qhullstatic library
# ---------------------------------------

set(qhull_SOURCES       src/qhull/unix.c)
set(rbox_SOURCES        src/rbox/rbox.c)
set(qconvex_SOURCES     src/qconvex/qconvex.c)
set(qdelaunay_SOURCES   src/qdelaunay/qdelaun.c)
set(qvoronoi_SOURCES    src/qvoronoi/qvoronoi.c)
set(qhalf_SOURCES       src/qhalf/qhalf.c)
set(user_eg2_SOURCES    src/user_eg2/user_eg2.c)
if(MSVC)
    set(user_eg_DEFINES qh_QHpointer qh_QHpointer_dllimport)
else()
    set(user_eg_DEFINES qh_QHpointer)
endif()

add_executable(qhull ${qhull_SOURCES})
target_link_libraries(qhull ${qhull_STATIC})
set_target_properties(qhull PROPERTIES 
    VERSION ${qhull_VERSION})

add_executable(rbox ${rbox_SOURCES})
target_link_libraries(rbox ${qhull_STATIC})
set_target_properties(rbox PROPERTIES
    VERSION ${qhull_VERSION})

add_executable(qconvex ${qconvex_SOURCES})
target_link_libraries(qconvex ${qhull_STATIC})
set_target_properties(qconvex PROPERTIES
    VERSION ${qhull_VERSION})

add_executable(qdelaunay ${qdelaunay_SOURCES})
target_link_libraries(qdelaunay ${qhull_STATIC})
set_target_properties(qdelaunay PROPERTIES
    VERSION ${qhull_VERSION})

add_executable(qvoronoi ${qvoronoi_SOURCES})
target_link_libraries(qvoronoi ${qhull_STATIC})
set_target_properties(qvoronoi PROPERTIES
    VERSION ${qhull_VERSION})

add_executable(qhalf ${qhalf_SOURCES})
target_link_libraries(qhalf ${qhull_STATIC})
set_target_properties(qhalf PROPERTIES
    VERSION ${qhull_VERSION})

add_executable(user_eg2 ${user_eg2_SOURCES})
target_link_libraries(user_eg2 ${qhull_STATIC})
set_target_properties(user_eg2 PROPERTIES
    VERSION ${qhull_VERSION})

# ---------------------------------------
# Define qhull executables linked to qhull shared library
# ---------------------------------------

set(user_eg_SOURCES     src/user_eg/user_eg.c)

add_executable(user_eg ${user_eg_SOURCES})
# user_eg may be linked to qhull_STATIC if user_eg_DEFINES is removed
target_link_libraries(user_eg ${qhull_SHARED})
set_target_properties(user_eg PROPERTIES
    COMPILE_DEFINITIONS "${user_eg_DEFINES}"
    VERSION ${qhull_VERSION})

# ---------------------------------------
# Define qhull executables linked to qhullstatic_p and qhullcpp static library
# ---------------------------------------

# libqhullcpp must be before src/libqhull.  The later is not needed.
# Otherwise get error -- user_eg3.cpp:72: error: aggregate 'orgQhull::Qhull qhull' has incomplete type and cannot be defined
include_directories(BEFORE ${CMAKE_SOURCE_DIR}/src/libqhullcpp)

set(user_eg3_SOURCES    src/user_eg3/user_eg3.cpp)

add_executable(user_eg3 ${user_eg3_SOURCES})
# qhull_STATICP must be last, otherwise qh_fprintf,etc. are not loaded from qhull_CPP
target_link_libraries(user_eg3 ${qhull_CPP} ${qhull_STATICP})
set_target_properties(user_eg3 PROPERTIES
    COMPILE_DEFINITIONS "qh_QHpointer"
    VERSION ${qhull_VERSION})

# ---------------------------------------
# Define install
# ---------------------------------------

install(TARGETS ${qhull_TARGETS}
        RUNTIME DESTINATION ${BIN_INSTALL_DIR} 
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR})

install(FILES ${libqhull_HEADERS} DESTINATION ${INCLUDE_INSTALL_DIR}/libqhull)
install(FILES ${libqhullcpp_HEADERS} DESTINATION ${INCLUDE_INSTALL_DIR}/libqhullcpp)
install(FILES ${road_HEADERS} DESTINATION ${INCLUDE_INSTALL_DIR}/road)

install(DIRECTORY html/ DESTINATION ${DOC_INSTALL_DIR})
