# Unix Makefile for qhull and rbox (default gcc/g++)
#
#       see README.txt  
#       Qt project file at src/qhull-all.pro
#       
# Results
#	qhull 		 Computes convex hulls and related structures (libqhullstatic)
#       qconvex, qdelaunay, qhalf, qvoronoi
#                        Specializations of qhull for each geometric structure (libqhullstatic)
#       qhull.so  (or, SO=dll)   Shared library with a static qh_qh struct
#       qhull-p.so  (or, SO=dll) Shared library with a malloc'd qh_qh struct
#       libqhullstatic.a         Static library with a static qh_qh struct
#       libqhullstatic-p.a       Static library with a malloc'd qh_qh struct
#       libqhullcpp.a            Static library using a malloc'd qh_qh struct
#	user_eg	         An example of calling qhull from a program (libqhullstatic)
#       user_eg2	 Another example (libqhull)
#	user_eg3	 An example of the C++ interface to qhull (libqhullcpp, libqhullstatic-p)
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
#       make clean       Remove object files and core
#       make cleanall    Remove generated files
#
#       BINDIR           directory where to copy executables
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

BINDIR	= /usr/local/bin
MANDIR	= /usr/local/man/man1

# if you do not have enscript, try a2ps or just use lpr.  The files are text.
PRINTMAN = enscript -2rl
PRINTC = enscript -2r
# PRINTMAN = lpr
# PRINTC = lpr

#for Gnu's gcc compiler, -O2 for optimization, -g for debugging
#   -fno-strict-aliasing not needed for gcc 4.4+ (segfault in qset.c)
#for CXX_OPTS1, libqhullcpp must be before libqhull
CC        = gcc
CC_OPTS1  = -O2 -ansi -fno-strict-aliasing -Isrc/libqhull $(CC_WARNINGS)
CXX       = g++
CXX_OPTS1 = -O2 -Dqh_QHpointer -Isrc/ -Isrc/libqhullcpp -Isrc/libqhull $(CXX_WARNINGS)
SO	  = so  # Extension for shared libraries
# On MinGW, 
#   SO= dll  # make SO=dll
#   CC_OPTS3= -Wl,-s -Wl,--out-implib,bin/libqhull.a -Wl,-enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc

# for Sun's cc compiler, -fast or O2 for optimization, -g for debugging, -Xc for ANSI
#CC       = cc
#CC_OPTS1 = -Xc -v -fast

# for Silicon Graphics cc compiler, -O2 for optimization, -g for debugging
#CC       = cc
#CC_OPTS1 = -ansi -O2

# for Next cc compiler with fat executable
#CC       = cc
#CC_OPTS1 = -ansi -O2 -arch m68k -arch i386 -arch hppa

# for loader, ld
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
     
all: bin/rbox bin/qconvex bin/qdelaunay bin/qhalf bin/qvoronoi bin/qhull qtest \
     bin/user_eg bin/user_eg2 bin/user_eg3 bin/qhull-p.$(SO) qhull-prompt

# LIBQHULL_OBJS ordered by frequency of execution with small files at end.  Better locality.

L=    src/libqhull
LP=   src/libqhullp
LS=   src/libqhullstatic
LSP=  src/libqhullstaticp
LCPP= src/libqhullcpp
TCPP= src/qhulltest

LIBQHULL_OBJS = $(L)/rboxlib.o $(L)/user.o $(L)/global.o $(L)/stat.o \
	$(L)/io.o $(L)/geom2.o $(L)/poly2.o $(L)/merge.o \
	$(L)/libqhull.o $(L)/geom.o $(L)/poly.o $(L)/qset.o \
	$(L)/mem.o $(L)/usermem.o $(L)/userprintf.o $(L)/random.o

LIBQHULL_HDRS = $(L)/user.h $(L)/libqhull.h $(L)/qhull_a.h $(L)/geom.h \
        $(L)/io.h $(L)/mem.h $(L)/merge.h $(L)/poly.h $(L)/random.h \
        $(L)/qset.h $(L)/stat.h

LIBQHULLP_OBJS = $(LP)/rboxlib.o $(LP)/user.o $(LP)/global.o $(LP)/stat.o \
	$(LP)/io.o $(LP)/geom2.o $(LP)/poly2.o $(LP)/merge.o \
	$(LP)/libqhull.o $(LP)/geom.o $(LP)/poly.o $(LP)/qset.o \
	$(LP)/mem.o $(LP)/usermem.o $(LP)/userprintf.o $(LP)/random.o

LIBQHULLS_OBJS = $(LS)/rboxlib.o $(LS)/user.o $(LS)/global.o $(LS)/stat.o \
        $(LS)/io.o $(LS)/geom2.o $(LS)/poly2.o $(LS)/merge.o \
        $(LS)/libqhull.o $(LS)/geom.o $(LS)/poly.o $(LS)/qset.o \
        $(LS)/mem.o $(LS)/usermem.o $(LS)/userprintf.o $(LS)/random.o

LIBQHULLSP_OBJS = $(LS)/rboxlib.o $(LS)/user.o $(LS)/global.o $(LS)/stat.o \
        $(LS)/io.o $(LS)/geom2.o $(LS)/poly2.o $(LS)/merge.o \
        $(LS)/libqhull.o $(LS)/geom.o $(LS)/poly.o $(LS)/qset.o \
        $(LS)/mem.o $(LS)/usermem.o $(LS)/userprintf.o $(LS)/random.o

LIBQHULLCPP_OBJS = src/road/RoadError.o src/road/RoadLogEvent.o $(LCPP)/Coordinates.o \
	$(LCPP)/PointCoordinates.o $(LCPP)/Qhull.o $(LCPP)/QhullFacet.o \
	$(LCPP)/QhullFacetList.o $(LCPP)/QhullFacetSet.o \
	$(LCPP)/QhullHyperplane.o $(LCPP)/QhullPoint.o \
	$(LCPP)/QhullPoints.o $(LCPP)/QhullPointSet.o $(LCPP)/QhullQh.o \
	$(LCPP)/QhullRidge.o $(LCPP)/QhullSet.o $(LCPP)/QhullStat.o \
	$(LCPP)/QhullVertex.o $(LCPP)/QhullVertexSet.o $(LCPP)/RboxPoints.o \
	$(LCPP)/UsingLibQhull.o src/user_eg3/user_eg3.o 

LIBQHULLCPP_HDRS = src/road/RoadError.h src/road/RoadLogEvent.h $(LCPP)/Coordinates.h \
	$(LCPP)/QhullHyperplane.h $(LCPP)/functionObjects.h $(LCPP)/PointCoordinates.h \
	$(LCPP)/Qhull.h $(LCPP)/QhullError.h $(LCPP)/QhullFacet.h \
	$(LCPP)/QhullFacetList.h $(LCPP)/QhullFacetSet.h $(LCPP)/QhullIterator.h \
	$(LCPP)/QhullLinkedList.h $(LCPP)/QhullPoint.h $(LCPP)/QhullPoints.h \
	$(LCPP)/QhullPointSet.h $(LCPP)/QhullQh.h $(LCPP)/QhullRidge.h \
	$(LCPP)/QhullSet.h $(LCPP)/QhullSets.h $(LCPP)/QhullStat.h \
	$(LCPP)/QhullVertex.h $(LCPP)/RboxPoints.h $(LCPP)/UsingLibQhull.h
       
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
HTMFILES= html/qhull.man html/rbox.man $(L)/qh-code.htm $(L)/qh-optg.htm $(L)/qh-optt.htm \
	html/index.htm html/qh-quick.htm html/qh-impre.htm html/qh-eg.htm \
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
$(L)/libqhull.o:  $(LIBQHULL_HDRS)
$(L)/geom.o:      $(LIBQHULL_HDRS)
$(L)/geom2.o:     $(LIBQHULL_HDRS)
$(L)/global.o:    $(LIBQHULL_HDRS)
$(L)/io.o:        $(LIBQHULL_HDRS)
$(L)/mem.o:       $(L)/mem.h 
$(L)/merge.o:     $(LIBQHULL_HDRS)
$(L)/poly.o:      $(LIBQHULL_HDRS)
$(L)/poly2.o:     $(LIBQHULL_HDRS)
$(L)/random.o:    $(L)/libqhull.h $(L)/random.h
$(L)/rboxlib.o:   $(L)/libqhull.h $(L)/random.h $(L)/user.h
$(L)/qset.o:      $(L)/qset.h $(L)/mem.h 
$(L)/stat.o:      $(LIBQHULL_HDRS)
$(L)/user.o:      $(LIBQHULL_HDRS)
$(L)/usermem.o:   $(L)/libqhull.h $(L)/user.h
$(L)/userprintf.o: $(L)/libqhull.h $(L)/user.h
$(LP)/libqhull.o: $(LIBQHULL_HDRS)
$(LP)/geom.o:     $(LIBQHULL_HDRS)
$(LP)/geom2.o:    $(LIBQHULL_HDRS)
$(LP)/global.o:   $(LIBQHULL_HDRS)
$(LP)/io.o:       $(LIBQHULL_HDRS)
$(LP)/mem.o:      $(L)/mem.h 
$(LP)/merge.o:    $(LIBQHULL_HDRS)
$(LP)/poly.o:     $(LIBQHULL_HDRS)
$(LP)/poly2.o:    $(LIBQHULL_HDRS)
$(LP)/random.o:   $(L)/libqhull.h $(L)/random.h
$(LP)/rboxlib.o:  $(L)/libqhull.h $(L)/random.h $(L)/user.h
$(LP)/qset.o:     $(L)/qset.h $(L)/mem.h 
$(LP)/stat.o:     $(LIBQHULL_HDRS)
$(LP)/user.o:     $(LIBQHULL_HDRS)
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

# The shared library, qhull-p.$(SO), is defined with qh_QHpointer (user.h).

$(LP)/libqhull.o: $(L)/libqhull.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LP)/geom.o:     $(L)/geom.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LP)/geom2.o:    $(L)/geom2.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LP)/global.o:   $(L)/global.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LP)/io.o:       $(L)/io.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LP)/mem.o:      $(L)/mem.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LP)/merge.o:    $(L)/merge.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LP)/poly.o:     $(L)/poly.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LP)/poly2.o:    $(L)/poly2.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LP)/random.o:   $(L)/random.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LP)/rboxlib.o:   $(L)/rboxlib.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LP)/qset.o:     $(L)/qset.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LP)/stat.o:     $(L)/stat.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LP)/user.o:     $(L)/user.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LP)/usermem.o:     $(L)/usermem.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<
$(LP)/userprintf.o:     $(L)/userprintf.c
	$(CC) -c -Dqh_QHpointer $(CC_OPTS1) -o $@ $<

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


# The static library, libqhullstatic-p, is defined with qh_QHpointer (user.h).

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

clean:
	rm -f src/libqhull/*.o src/libqhullp/*.o src/libqhullcpp/*.o 
	rm -f src/libqhullstatic/*.o src/libqhullstaticp/*.o src/qconvex/*.o
	rm -f src/qdelaunay/*.o src/qhalf/*.o src/qvoronoi/*.o src/qhull/*.o src/rbox/*.o
	rm -f src/road/*.o src/user_eg/*.o src/user_eg2/*.o src/user_eg3/*.o

cleanall: clean
	rm -f bin/qconvex bin/qdelaunay bin/qhalf bin/qvoronoi bin/qhull bin/*.exe
	rm -f core bin/core bin/user_eg bin/user_eg2 bin/user_eg3 
	rm -f bin/libqhull* bin/qhull*.so bin/qhull*.dll lib/libqhull* lib/qhull*.lib 

doc: 
	$(PRINTMAN) $(TXTFILES) $(DOCFILES)

install:  
	cp bin/qconvex $(BINDIR)/qconvex
	cp bin/qdelaunay $(BINDIR)/qdelaunay
	cp bin/qhalf $(BINDIR)/qhalf
	cp bin/qhull $(BINDIR)/qhull
	cp bin/qvoronoi $(BINDIR)/qvoronoi
	cp bin/rbox $(BINDIR)/rbox
	cp html/qhull.man $(MANDIR)/qhull.1
	cp html/rbox.man $(MANDIR)/rbox.1

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

lib/libqhullstatic.a: $(LIBQHULL_OBJS)
	@echo ==========================================
	@echo ==== If 'ar' fails, try 'make qhullx' ====
	@echo ==========================================
	ar -rs $@ $^
	#If 'ar -rs' fails try using 'ar -s' with 'ranlib'
	#ranlib $@

lib/libqhullstatic-p.a: $(LIBQHULLP_OBJS)
	ar -rs $@ $^
	#ranlib $@

bin/qhull.$(SO): $(LIBQHULL_OBJS)
	$(CC) -shared -o $@ $(CC_OPTS2) $^

bin/qhull-p.$(SO): $(LIBQHULLP_OBJS)
	$(CC) -shared -o $@ $(CC_OPTS2) $^

lib/libqhullcpp.a: $(LIBQHULLCPP_OBJS)
	ar -rs $@ $^
	#ranlib $@

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

bin/user_eg: src/user_eg/user_eg.o lib/libqhullstatic.a 
	$(CC) -o $@ $< $(CC_OPTS2) -Llib -lqhullstatic -lm

bin/user_eg2: src/user_eg2/user_eg2.o bin/qhull.$(SO)
	$(CC) -o $@ $< $(CC_OPTS2) -Lbin -lqhull -lm

bin/user_eg3: src/user_eg3/user_eg3.o lib/libqhullstatic-p.a lib/libqhullcpp.a
	$(CXX) -o $@ $< $(CXX_OPTS2) -Llib -lqhullcpp -lqhullstatic-p -lm

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

qhull-prompt:
	-bin/qhull
	
# end of Makefile
