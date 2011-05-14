# Unix Makefile for qhull and rbox (default gcc/g++)
#
#       see README.txt  
#       For qhulltest, use Qt project file at src/qhull-all.pro
#       
# Results
#	qhull 		 Computes convex hulls and related structures (libqhullstatic)
#       qconvex, qdelaunay, qhalf, qvoronoi
#                        Specializations of qhull for each geometric structure (libqhullstatic)
#       libqhull6.so (SO=dll) Shared library with a malloc'd qh_qh struct
#       libqhullstatic.a      Static library with a static qh_qh struct
#       libqhullstatic_p.a    Static library with a malloc'd qh_qh struct
#       libqhullcpp.a         Static library using a malloc'd qh_qh struct
#	user_eg	         An example of calling qhull from a program with libqhullstatic
#       user_eg2	 Another example with the shared library, libqhull
#	user_eg3	 An example of the C++ interface to qhull (libqhullcpp, libqhullstatic_p)
#
# Make targets
#       make             Produce all of the results
#       make qhullx      Produce qhull qconvex etc. w/o libqhullstatic
#       make qtest       Quick test of rbox and qhull (bin/rbox D4 | bin/qhull)
#       make test        Test of rbox and qhull
#       make bin/qvoronoi  Produce bin/qvoronoi (etc.)
#       make doc         Print documentation
#       make install     Copy qhull, rbox, qhull.1, rbox.1 to BINDIR, MANDIR
#       make new         Rebuild qhull and rbox from source
#
#       make printall    Print all files
#       make clean       Remove object files
#       make cleanall    Remove generated files
#
#       BINDIR           directory where to copy executables
#       DESTDIR          destination directory
#       DOCDIR           directory where to copy html documentation
#       INCDIR           directory where to copy headers
#       LIBDIR           directory where to copy libraries
#       MANDIR           directory where to copy manual pages
#       PRINTMAN         command for printing manual pages
#       PRINTC           command for printing C files
#       CC               ANSI C or C++ compiler
#       CC_OPTS1         options used to compile .c files
#       CC_OPTS2         options used to link .o files
#       CC_OPTS3         options to build shared libraries
#       CXX              ANSI C++ compiler
#       CXX_OPTS1        options used to compile .cpp files
#       CXX_OPTS2        options used to link .o files
#	CC_WARNINGS	 warnings for .c programs
#	CXX_WARNINGS	 warnings for .cpp programs
#
#       LIBQHULL_OBJS    .o files for linking
#       LIBQHULL_HDRS    .h files for printing
#       CFILES           .c files for printing
#       CXXFILES         .cpp files for printing
#       TESTFILES        .cpp test files for printing
#       DOCFILES         documentation files
#       FILES            miscellaneous files for printing
#       HTMFILES         documentation source files
#       TFILES           .txt versions of html files
#       FILES            all other files
#       LIBQHULL_OBJS    specifies the object files of libqhullstatic.a
#
# Do not replace tabs with spaces.  Needed by 'make' for build rules

# You may build the qhull programs without using a library
# make qhullx

DESTDIR = /usr/local
BINDIR	= $(DESTDIR)/bin
DOCDIR	= $(DESTDIR)/share/doc/packages/qhull
INCDIR	= $(DESTDIR)/include
LIBDIR	= $(DESTDIR)/lib
MANDIR	= $(DESTDIR)/man/man1

# if you do not have enscript, try a2ps or just use lpr.  The files are text.
PRINTMAN = enscript -2rl
PRINTC = enscript -2r
# PRINTMAN = lpr
# PRINTC = lpr

#for Gnu's gcc compiler, -O2 for optimization, -g for debugging
#   -fno-strict-aliasing not needed for gcc 4.4+ (segfault in qset.c)
CC        = gcc
CC_OPTS1  = -O2 -fPIC -ansi -fno-strict-aliasing -Isrc/libqhull $(CC_WARNINGS)
CXX       = g++
# libqhullcpp must be before libqhull
CXX_OPTS1 = -O2 -Dqh_QHpointer -Isrc/ -Isrc/libqhullcpp -Isrc/libqhull $(CXX_WARNINGS)

# for shared library link
CC_OPTS3  =
# Define qhull_VERSION in CMakeLists.txt, Makefile, qhull-exports.def, and qhull-warn.pri
qhull_VERSION_MAJOR=6
SO  = so.6.2.0

# On MinGW, 
#   make SO=dll
#   Copy lib/libqhull6.dll to bin/

# for Sun's cc compiler, -fast or O2 for optimization, -g for debugging, -Xc for ANSI
#CC       = cc
#CC_OPTS1 = -Xc -v -fast

# for Silicon Graphics cc compiler, -O2 for optimization, -g for debugging
#CC       = cc
#CC_OPTS1 = -ansi -O2

# for Next cc compiler with fat executable
#CC       = cc
#CC_OPTS1 = -ansi -O2 -arch m68k -arch i386 -arch hppa

# For loader, ld, 
CC_OPTS2 = $(CC_OPTS1)
CXX_OPTS2 = $(CXX_OPTS1)

# [gcc 4.4] Compiles without error (-Werror)
CC_WARNINGS  = -Wall -Wcast-qual -Wextra -Wwrite-strings -Wshadow
CXX_WARNINGS = -Wall -Wcast-qual -Wextra -Wwrite-strings -Wno-sign-conversion -Wshadow -Wconversion 

# Compiles OK with all gcc warnings except for -Wno-sign-conversion and -Wconversion
# Compiles OK with all g++ warnings except Qt source errors on -Wshadow and -Wconversion
#    -Waddress -Warray-bounds -Wchar-subscripts -Wclobbered -Wcomment -Wunused-variable
#    -Wempty-body -Wformat -Wignored-qualifiers -Wimplicit-function-declaration -Wimplicit-int
#    -Wmain -Wmissing-braces -Wmissing-field-initializers -Wmissing-parameter-type -Wnonnull
#    -Wold-style-declaration -Woverride-init -Wparentheses -Wpointer-sign -Wreturn-type
#    -Wsequence-point -Wsign-compare -Wsign-compare -Wstrict-aliasing -Wstrict-overflow=1
#    -Wswitch -Wtrigraphs -Wtype-limits -Wuninitialized -Wuninitialized -Wvolatile-register-var
#    -Wunknown-pragmas -Wunused-function -Wunused-label -Wunused-parameter -Wunused-value

# Default targets for make
     
all: bin-lib bin/rbox bin/qconvex bin/qdelaunay bin/qhalf bin/qvoronoi \
     bin/qhull qtest bin/user_eg2 bin/user_eg3 bin/user_eg qconvex-prompt

bin-lib:
	mkdir -p bin lib
     
clean:
	rm -f src/*/*.o src/road/RoadTest.h.cpp build/*/*/*.o  build/*/*.o
	rm -f src/*/*.obj build/*/*/*.obj  build/*/*.obj
	rm -f bin/*.idb bin/*.pdb

cleanall: clean
	rm -f bin/qconvex bin/qdelaunay bin/qhalf bin/qvoronoi bin/qhull
	rm -f core bin/core bin/user_eg bin/user_eg2 bin/user_eg3
	rm -f lib/libqhull* lib/qhull*.lib lib/qhull*.exp  lib/qhull*.dll
	rm -f bin/libqhull* bin/qhull*.dll bin/*.exe

doc: 
	$(PRINTMAN) $(TXTFILES) $(DOCFILES)

install:
	mkdir -p $(BINDIR)
	mkdir -p $(DOCDIR)
	mkdir -p $(INCDIR)/libqhull
	mkdir -p $(INCDIR)/libqhullcpp
	mkdir -p $(INCDIR)/road
	mkdir -p $(LIBDIR)
	mkdir -p $(MANDIR)
	cp bin/qconvex $(BINDIR)
	cp bin/qdelaunay $(BINDIR)
	cp bin/qhalf $(BINDIR)
	cp bin/qhull $(BINDIR)
	cp bin/qvoronoi $(BINDIR)
	cp bin/rbox $(BINDIR)
	cp html/qhull.man $(MANDIR)/qhull.1
	cp html/rbox.man $(MANDIR)/rbox.1
	cp html/* $(DOCDIR)
	cp -P lib/* $(LIBDIR)
	cp src/libqhull/*.h $(INCDIR)/libqhull
	cp src/libqhullcpp/*.h $(INCDIR)/libqhullcpp
	cp src/road/*.h $(INCDIR)/road

new:	cleanall all

printall: doc printh printc printf

printh:
	$(PRINTC) $(LIBQHULL_HDRS)
	$(PRINTC) $(LIBQHULLCPP_HDRS)

printc:
	$(PRINTC) $(CFILES)
	$(PRINTC) $(CXXFILES)
	$(PRINTC) $(TESTFILES)

printf:
	$(PRINTC) $(FILES)

# compile qhull without using bin/libqhull.a
qhullx: src/qconvex/qconvex.o src/qdelaunay/qdelaun.o src/qhalf/qhalf.o \
            src/qvoronoi/qvoronoi.o src/qhull/unix.o src/rbox/rbox.o $(LIBQHULLS_OBJS)
	$(CC) -o bin/qconvex $(CC_OPTS2) -lm $(LIBQHULLS_OBJS) src/qconvex/qconvex.o 
	$(CC) -o bin/qdelaunay $(CC_OPTS2) -lm $(LIBQHULLS_OBJS) src/qdelaunay/qdelaun.o
	$(CC) -o bin/qhalf $(CC_OPTS2) -lm $(LIBQHULLS_OBJS) src/qhalf/qhalf.o 
	$(CC) -o bin/qvoronoi $(CC_OPTS2) -lm $(LIBQHULLS_OBJS) src/qvoronoi/qvoronoi.o 
	$(CC) -o bin/qhull $(CC_OPTS2) -lm $(LIBQHULLS_OBJS) src/qhull/unix.o 
	$(CC) -o bin/rbox $(CC_OPTS2) -lm $(LIBQHULLS_OBJS) src/rbox/rbox.o 

qtest:
	-bin/rbox D4 | bin/qhull
	
test:
	-eg/q_eg
	-eg/q_egtest
	-eg/q_test

qconvex-prompt:
	-bin/qconvex
	@echo 'For libqhull6.so -- export LD_LIBRARY_PATH=$$PWD/lib:$$LD_LIBRARY_PATH'

# LIBQHULL_OBJS ordered by frequency of execution with small files at end.  Better locality.

L=    src/libqhull
LS=   src/libqhullstatic
LSP=  src/libqhullstaticp
LCPP= src/libqhullcpp
TCPP= src/qhulltest

LIBQHULL_HDRS = $(L)/user.h $(L)/libqhull.h $(L)/qhull_a.h $(L)/geom.h \
        $(L)/io.h $(L)/mem.h $(L)/merge.h $(L)/poly.h $(L)/random.h \
        $(L)/qset.h $(L)/stat.h

LIBQHULLS_OBJS = $(LS)/rboxlib.o $(LS)/user.o $(LS)/global.o $(LS)/stat.o \
        $(LS)/io.o $(LS)/geom2.o $(LS)/poly2.o $(LS)/merge.o \
        $(LS)/libqhull.o $(LS)/geom.o $(LS)/poly.o $(LS)/qset.o \
        $(LS)/mem.o $(LS)/usermem.o $(LS)/userprintf.o $(LS)/random.o

LIBQHULLSP_OBJS = $(LSP)/rboxlib.o $(LSP)/user.o $(LSP)/global.o $(LSP)/stat.o \
        $(LSP)/io.o $(LSP)/geom2.o $(LSP)/poly2.o $(LSP)/merge.o \
        $(LSP)/libqhull.o $(LSP)/geom.o $(LSP)/poly.o $(LSP)/qset.o \
        $(LSP)/mem.o $(LSP)/usermem.o $(LSP)/userprintf.o $(LSP)/random.o

LIBQHULLCPP_HDRS = src/road/RoadError.h src/road/RoadLogEvent.h $(LCPP)/Coordinates.h \
	$(LCPP)/QhullHyperplane.h $(LCPP)/functionObjects.h $(LCPP)/PointCoordinates.h \
	$(LCPP)/Qhull.h $(LCPP)/QhullError.h $(LCPP)/QhullFacet.h \
	$(LCPP)/QhullFacetList.h $(LCPP)/QhullFacetSet.h $(LCPP)/QhullIterator.h \
	$(LCPP)/QhullLinkedList.h $(LCPP)/QhullPoint.h $(LCPP)/QhullPoints.h \
	$(LCPP)/QhullPointSet.h $(LCPP)/QhullQh.h $(LCPP)/QhullRidge.h \
	$(LCPP)/QhullSet.h $(LCPP)/QhullSets.h $(LCPP)/QhullStat.h \
	$(LCPP)/QhullVertex.h $(LCPP)/RboxPoints.h $(LCPP)/UsingLibQhull.h
       
LIBQHULLCPP_OBJS = src/road/RoadError.o src/road/RoadLogEvent.o $(LCPP)/Coordinates.o \
	$(LCPP)/PointCoordinates.o $(LCPP)/Qhull.o $(LCPP)/QhullFacet.o \
	$(LCPP)/QhullFacetList.o $(LCPP)/QhullFacetSet.o \
	$(LCPP)/QhullHyperplane.o $(LCPP)/QhullPoint.o \
	$(LCPP)/QhullPoints.o $(LCPP)/QhullPointSet.o $(LCPP)/QhullQh.o \
	$(LCPP)/QhullRidge.o $(LCPP)/QhullSet.o $(LCPP)/QhullStat.o \
	$(LCPP)/QhullVertex.o $(LCPP)/QhullVertexSet.o $(LCPP)/RboxPoints.o \
	$(LCPP)/UsingLibQhull.o src/user_eg3/user_eg3.o 

# CFILES ordered alphabetically after libqhull.c 
CFILES= src/qhull/unix.c $(L)/libqhull.c $(L)/geom.c $(L)/geom2.c $(L)/global.c $(L)/io.c \
	$(L)/mem.c $(L)/merge.c $(L)/poly.c $(L)/poly2.c $(L)/random.c $(L)/rboxlib.c \
	$(L)/qset.c $(L)/stat.c $(L)/user.c $(L)/usermem.c $(L)/userprintf.c \
	src/qconvex/qconvex.c src/qdelaunay/qdelaun.c src/qhalf/qhalf.c src/qvoronoi/qvoronoi.c

CXXFILES= src/road/RoadError.cpp src/road/RoadLogEvent.cpp $(LCPP)/Coordinates.cpp \
	$(LCPP)/PointCoordinates.cpp $(LCPP)/Qhull.cpp $(LCPP)/QhullFacet.cpp \
	$(LCPP)/QhullFacetList.cpp $(LCPP)/QhullFacetSet.cpp \
	$(LCPP)/QhullHyperplane.cpp $(LCPP)/QhullPoint.cpp \
	$(LCPP)/QhullPoints.cpp $(LCPP)/QhullPointSet.cpp $(LCPP)/QhullQh.cpp \
	$(LCPP)/QhullRidge.cpp $(LCPP)/QhullSet.cpp $(LCPP)/QhullStat.cpp \
	$(LCPP)/QhullVertex.cpp $(LCPP)/QhullVertexSet.cpp $(LCPP)/RboxPoints.cpp \
	$(LCPP)/UsingLibQhull.cpp src/user_eg3/user_eg3.cpp 
	
TESTFILES= $(TCPP)/qhulltest.cpp $(TCPP)/Coordinates_test.cpp $(TCPP)/Point_test.cpp $(TCPP)/PointCoordinates_test.cpp \
	$(TCPP)/Qhull_test.cpp $(TCPP)/QhullFacet_test.cpp $(TCPP)/QhullFacetList_test.cpp \
	$(TCPP)/QhullFacetSet_test.cpp $(TCPP)/QhullHyperplane_test.cpp $(TCPP)/QhullLinkedList_test.cpp \
	$(TCPP)/QhullPoint_test.cpp $(TCPP)/QhullPoints_test.cpp \
	$(TCPP)/QhullPointSet_test.cpp $(TCPP)/QhullRidge_test.cpp \
	$(TCPP)/QhullSet_test.cpp $(TCPP)/QhullVertex_test.cpp $(TCPP)/QhullVertexSet_test.cpp \
	$(TCPP)/RboxPoints_test.cpp $(TCPP)/UsingLibQhull_test.cpp 


TXTFILES= Announce.txt REGISTER.txt COPYING.txt README.txt src/Changes.txt
DOCFILES= html/rbox.txt html/qhull.txt
FILES=	Makefile src/rbox/rbox.c src/user_eg/user_eg.c src/user_eg2/user_eg2.c eg/q_test eg/q_egtest eg/q_eg
MANFILES= html/qhull.man html/rbox.man 
# Source code is documented by src/libqhull/*.htm
HTMFILES= html/index.htm html/qh-quick.htm html/qh-impre.htm html/qh-eg.htm \
	html/qh-optc.htm html/qh-opto.htm html/qh-optf.htm  html/qh-optp.htm html/qh-optq.htm \
	html/qh-c.htm html/qh-faq.htm html/qhull.htm html/qconvex.htm html/qdelaun.htm \
	html/qh-geom.htm html/qh-globa.htm html/qh-io.htm html/qh-mem.htm html/qh-merge.htm \
	html/qh-poly.htm html/qh-qhull.htm html/qh-set.htm html/qh-stat.htm html/qh-user.htm \
	html/qconvex.htm html/qdelau_f.htm html/qdelaun.htm html/qhalf.htm html/qvoronoi.htm \
	html/qvoron_f.htm html/rbox.htm 

qhull/unix.o:            $(L)/libqhull.h $(L)/user.h $(L)/mem.h
qconvex/qconvex.o:       $(L)/libqhull.h $(L)/user.h $(L)/mem.h
qdelanay/qdelaun.o:      $(L)/libqhull.h $(L)/user.h $(L)/mem.h
qhalf/qhalf.o:           $(L)/libqhull.h $(L)/user.h $(L)/mem.h
qvoronoi/qvoronoi.o:     $(L)/libqhull.h $(L)/user.h $(L)/mem.h
$(LS)/libqhull.o: $(LIBQHULL_HDRS)
$(LS)/geom.o:     $(LIBQHULL_HDRS)
$(LS)/geom2.o:    $(LIBQHULL_HDRS)
$(LS)/global.o:   $(LIBQHULL_HDRS)
$(LS)/io.o:       $(LIBQHULL_HDRS)
$(LS)/mem.o:      $(L)/mem.h
$(LS)/merge.o:    $(LIBQHULL_HDRS)
$(LS)/poly.o:     $(LIBQHULL_HDRS)
$(LS)/poly2.o:    $(LIBQHULL_HDRS)
$(LS)/random.o:   $(L)/libqhull.h $(L)/random.h
$(LS)/rboxlib.o:  $(L)/libqhull.h $(L)/random.h $(L)/user.h
$(LS)/qset.o:     $(L)/qset.h $(L)/mem.h
$(LS)/stat.o:     $(LIBQHULL_HDRS)
$(LS)/user.o:     $(LIBQHULL_HDRS)
$(LSP)/libqhull.o: $(LIBQHULL_HDRS)
$(LSP)/geom.o:     $(LIBQHULL_HDRS)
$(LSP)/geom2.o:    $(LIBQHULL_HDRS)
$(LSP)/global.o:   $(LIBQHULL_HDRS)
$(LSP)/io.o:       $(LIBQHULL_HDRS)
$(LSP)/mem.o:      $(L)/mem.h
$(LSP)/merge.o:    $(LIBQHULL_HDRS)
$(LSP)/poly.o:     $(LIBQHULL_HDRS)
$(LSP)/poly2.o:    $(LIBQHULL_HDRS)
$(LSP)/random.o:   $(L)/libqhull.h $(L)/random.h
$(LSP)/rboxlib.o:  $(L)/libqhull.h $(L)/random.h $(L)/user.h
$(LSP)/qset.o:     $(L)/qset.h $(L)/mem.h
$(LSP)/stat.o:     $(LIBQHULL_HDRS)
$(LSP)/user.o:     $(LIBQHULL_HDRS)
src/road/RoadError.o:       src/road/RoadError.h src/road/RoadLogEvent.h
src/road/RoadLogEvent.o:    src/road/RoadError.h                  
$(LCPP)/Coordinates.o:      $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/PointCoordinates.o: $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/Qhull.o:            $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/QhullFacet.o:       $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/QhullFacetList.o:   $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/QhullFacetSet.o:    $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/QhullHyperplane.o:  $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/QhullPoint.o:       $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/QhullPoints.o:      $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/QhullPointSet.o:    $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/QhullQh.o:          $(LIBQHULL_HDRS)
$(LCPP)/QhullRidge.o:       $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/QhullSet.o:         $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/QhullStat.o:        $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/QhullVertex.o:      $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/QhullVertexSet.o:   $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/RboxPoints.o:       $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)
$(LCPP)/UsingLibQhull.o:    $(LIBQHULLCPP_HDRS) $(LIBQHULL_HDRS)

.c.o:
	$(CC) -c $(CC_OPTS1) -o $@ $<

.cpp.o:
	$(CXX) -c $(CXX_OPTS1) -o $@ $<

# The static library, libqhullstatic, is defined without qh_QHpointer.

$(LS)/libqhull.o: $(L)/libqhull.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LS)/geom.o:     $(L)/geom.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LS)/geom2.o:    $(L)/geom2.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LS)/global.o:   $(L)/global.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LS)/io.o:       $(L)/io.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LS)/mem.o:      $(L)/mem.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LS)/merge.o:    $(L)/merge.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LS)/poly.o:     $(L)/poly.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LS)/poly2.o:    $(L)/poly2.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LS)/random.o:   $(L)/random.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LS)/rboxlib.o:   $(L)/rboxlib.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LS)/qset.o:     $(L)/qset.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LS)/stat.o:     $(L)/stat.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LS)/user.o:     $(L)/user.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LS)/usermem.o:     $(L)/usermem.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LS)/userprintf.o:  $(L)/userprintf.c
	$(CC) -c $(CC_OPTS1) -o $@ $<

# The static library, libqhullstatic_p, is defined with qh_QHpointer (user.h).

$(LSP)/libqhull.o: $(L)/libqhull.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LSP)/geom.o:     $(L)/geom.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LSP)/geom2.o:    $(L)/geom2.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LSP)/global.o:   $(L)/global.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LSP)/io.o:       $(L)/io.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LSP)/mem.o:      $(L)/mem.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LSP)/merge.o:    $(L)/merge.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LSP)/poly.o:     $(L)/poly.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LSP)/poly2.o:    $(L)/poly2.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LSP)/random.o:   $(L)/random.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LSP)/rboxlib.o:   $(L)/rboxlib.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LSP)/qset.o:     $(L)/qset.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LSP)/stat.o:     $(L)/stat.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LSP)/user.o:     $(L)/user.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LSP)/usermem.o:     $(L)/usermem.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LSP)/userprintf.o:     $(L)/userprintf.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<

lib/libqhullstatic.a: $(LIBQHULLS_OBJS)
	@echo ==========================================
	@echo ==== If 'ar' fails, try 'make qhullx' ====
	@echo ==========================================
	ar -rs $@ $^
	#If 'ar -rs' fails try using 'ar -s' with 'ranlib'
	#ranlib $@

lib/libqhullstatic_p.a: $(LIBQHULLSP_OBJS)
	ar -rs $@ $^
	#ranlib $@

lib/libqhullcpp.a: $(LIBQHULLCPP_OBJS)
	ar -rs $@ $^
	#ranlib $@

lib/libqhull$(qhull_VERSION_MAJOR).$(SO): $(LIBQHULLSP_OBJS)
	$(CC) -shared -o $@ $(CC_OPTS3) $^
	cd lib && ln -f -s libqhull$(qhull_VERSION_MAJOR).$(SO) libqhull$(qhull_VERSION_MAJOR).so

# don't use ../qconvex.	 Does not work on Red Hat Linux
bin/qconvex: src/qconvex/qconvex.o lib/libqhullstatic.a
	$(CC) -o $@ $< $(CC_OPTS2) -Llib -lqhullstatic -lm

bin/qdelaunay: src/qdelaunay/qdelaun.o lib/libqhullstatic.a
	$(CC) -o $@ $< $(CC_OPTS2) -Llib -lqhullstatic -lm

bin/qhalf: src/qhalf/qhalf.o lib/libqhullstatic.a
	$(CC) -o $@ $< $(CC_OPTS2) -Llib -lqhullstatic -lm

bin/qvoronoi: src/qvoronoi/qvoronoi.o lib/libqhullstatic.a
	$(CC) -o $@ $< $(CC_OPTS2) -Llib -lqhullstatic -lm

bin/qhull: src/qhull/unix.o lib/libqhullstatic.a
	$(CC) -o $@ $< $(CC_OPTS2) -Llib -lqhullstatic -lm
	-chmod +x eg/q_test eg/q_eg eg/q_egtest

bin/rbox: src/rbox/rbox.o lib/libqhullstatic.a
	$(CC) -o $@ $< $(CC_OPTS2) -Llib -lqhullstatic -lm

bin/user_eg: src/user_eg/user_eg.c lib/libqhull$(qhull_VERSION_MAJOR).$(SO)
	echo -e '\n== If user_eg fails to link, switch to -lqhullstatic_p.\n== On MinGW/Cygwin, use "make SO=dll"'
	echo -e "\\n==  and copy lib/libqhull$(qhull_VERSION_MAJOR).$(SO) to bin\\n\\n"
	$(CC) -o $@ $< -Dqh_QHpointer  $(CC_OPTS1) $(CC_OPTS3) -Llib -lqhull$(qhull_VERSION_MAJOR) -lm

bin/user_eg2: src/user_eg2/user_eg2.o lib/libqhullstatic.a 
	$(CC) -o $@ $< $(CC_OPTS2) -Llib -lqhullstatic -lm

bin/user_eg3: src/user_eg3/user_eg3.o lib/libqhullstatic_p.a lib/libqhullcpp.a
	$(CXX) -o $@ $< $(CXX_OPTS2) -Llib -lqhullcpp -lqhullstatic_p -lm

# end of Makefile
