# -------------------------------------------------
# qhull-all.pro -- Qt project to build all files
# -------------------------------------------------

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += libqhull
SUBDIRS += libqhullp  #qh_QHpointer
SUBDIRS += user_eg
SUBDIRS += user_eg2
SUBDIRS += qhull
SUBDIRS += qconvex
SUBDIRS += qdelaunay
SUBDIRS += qhalf
SUBDIRS += qvoronoi
SUBDIRS += rbox
SUBDIRS += libqhullcpp
SUBDIRS += user_eg3
SUBDIRS += qhulltest
