# -------------------------------------------------
# qhull-all.pro -- Qt project to build executables and static libraries
#
# To build with Qt on mingw
#   Download Qt SDK, install Perl
#   /c/qt/2010.05/qt> ./configure -static -platform win32-g++ -fast -no-qt3support
#
# To build DevStudio sln and proj files
# qmake is in Qt's bin directory
# ../build> qmake -tp vc -r ../src/qhull-all.pro
# -------------------------------------------------

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += libqhull
SUBDIRS += qhull
SUBDIRS += qconvex
SUBDIRS += qdelaunay
SUBDIRS += qhalf
SUBDIRS += qvoronoi
SUBDIRS += rbox
SUBDIRS += user_eg
SUBDIRS += user_eg2

SUBDIRS += libqhullp  #qh_QHpointer
SUBDIRS += libqhullcpp
SUBDIRS += user_eg3
SUBDIRS += qhulltest

OTHER_FILES += CMakeLists.txt
OTHER_FILES += Make-config.sh
OTHER_FILES += ../Announce.txt
OTHER_FILES += ../COPYING.txt
OTHER_FILES += ../File_id.diz
OTHER_FILES += ../index.htm
OTHER_FILES += ../README.txt
OTHER_FILES += ../REGISTER.txt
OTHER_FILES += ../Changes.txt
OTHER_FILES += ../CMakeLists.txt
OTHER_FILES += ../eg/q_eg
OTHER_FILES += ../eg/q_egtest
OTHER_FILES += ../eg/q_test
OTHER_FILES += ../html/index.htm
OTHER_FILES += ../html/qconvex.htm
OTHER_FILES += ../html/qdelau_f.htm
OTHER_FILES += ../html/qdelaun.htm
OTHER_FILES += ../html/qhalf.htm
OTHER_FILES += ../html/qh-code.htm
OTHER_FILES += ../html/qh-eg.htm
OTHER_FILES += ../html/qh-faq.htm
OTHER_FILES += ../html/qh-get.htm
OTHER_FILES += ../html/qh-impre.htm
OTHER_FILES += ../html/qh-optc.htm
OTHER_FILES += ../html/qh-optf.htm
OTHER_FILES += ../html/qh-optg.htm
OTHER_FILES += ../html/qh-opto.htm
OTHER_FILES += ../html/qh-optp.htm
OTHER_FILES += ../html/qh-optq.htm
OTHER_FILES += ../html/qh-optt.htm
OTHER_FILES += ../html/qh-quick.htm
OTHER_FILES += ../html/qhull.htm
OTHER_FILES += ../html/qhull.man
OTHER_FILES += ../html/qhull.txt
OTHER_FILES += ../html/qhull-cpp.xml
OTHER_FILES += ../html/qvoron_f.htm
OTHER_FILES += ../html/qvoronoi.htm
OTHER_FILES += ../html/rbox.htm
OTHER_FILES += ../html/rbox.man
OTHER_FILES += ../html/rbox.txt
