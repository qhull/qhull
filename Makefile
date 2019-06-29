# Unix Makefile for reentrant libqhull, qhull, and rbox (default gcc/g++)
#
#   make help
#   See README.txt
#   For qhulltest of the C++ interface, use Qt project file at src/qhull-all.pro
#   For static builds, a simple alternative is src/libqhull_r/Makefile
#   
# Variables
#   DESTDIR        destination directory for 'make install'.
#   BINDIR         directory where to copy executables
#   DOCDIR         directory where to copy html documentation
#   INCDIR         directory where to copy headers
#   LIBDIR         directory where to copy libraries
#   MANDIR         directory where to copy manual pages
#   PRINTMAN       command for printing manual pages
#   PRINTC         command for printing C files
#   CC             ANSI C or C++ compiler
#   CC_OPTS1       options used to compile .c files
#   CC_OPTS2       options used to link .o files
#   CC_OPTS3       options to build shared libraries
#   CXX            ANSI C++ compiler
#   CXX_OPTS1      options used to compile .cpp files
#   CXX_OPTS2      options used to link .o files
#   CC_WARNINGS    warnings for .c programs
#   CXX_WARNINGS   warnings for .cpp programs
#
#   LIBQHULLS_RBOX_OBJS .o files for linking
#   LIBQHULLR_HDRS  non-reentrant .h files
#   LIBQHULLR_HDRS reentrant .h files
#   CFILES         .c files for printing
#   CXXFILES       .cpp files for printing
#   TESTFILES      .cpp test files for printing
#   DOCFILES       documentation files
#   FILES          miscellaneous files for printing
#   HTMFILES       documentation source files
#   TFILES         .txt versions of html files
#   FILES          all other files
#   LIBQHULLS_RBOX_OBJS specifies the object files of libqhullstatic.a
#
# Results
#   rbox           Generates points sets for qhull, qconvex, etc.
#   qhull          Computes convex hull and related structures with reentrant libqhullstatic_r
#   qconvex, qdelaunay, qhalf, qvoronoi
#                  Specializations of qhull for each geometric structure
#                  Built with non-reentrant libqhullstatic (somewhat faster)
#   libqhull_r.so  Shared library with reentrant code
#   libqhullstatic.a Non-reentrant static library with static qh_qh struct
#                  Called 'static' to avoid naming conflicts
#   libqhullstatic_r.a Reentrant, static library
#   libqhullcpp.a  C++ static library with libqhullstatic_r.a
#   testqset       Standalone test program for non-reentrant qset.c with mem.c
#   testqset_r     Standalone test program for reentrant qset_r.c with mem_r.c
#   user_eg        An example of the reentrant, shared library qhull_r
#   user_eg2       An example of the reentrant, static library libqhullstatic_r
#   user_eg3       An example of the C++ interface with libqhullcpp and libqhullstatic_r
#
# Targets
#   make           Build results using gcc or another compiler
#   make all
#   make SO=dll    For mingw on Windows, use SO=dll. It builds dlls
#   make bin/qvoronoi  Produce bin/qvoronoi (etc.)
#   make qhullx    Produce qhull, qconvex etc. without using library
#
#   make benchmark Benchmark of qhull precision and performance
#                  make benchmark 2>&1 | tee eg/q_benchmark.x
#   make clean     Remove object files
#   make cleanall  Remove generated files, build/*.dlr/, buildqt/, and buildvc/
#   make doc       Print documentation
#   make help
#   make install   Copy qhull, rbox, qhull.1, rbox.1 to BINDIR, MANDIR
#   make new       Rebuild qhull and rbox from source
#   make printall  Print all files
#   make qtest     Quick test of rbox and qhull
#   make test      Quick test of qhull programs
#   make testall   Test programs for manual review with eg/q_test-ok.txt
#                  Windows --  make cleanall SO=dll all; cp lib/libqhull*.dll bin/
#                  make testall >eg/q_test.x 2>&1
#                  make testall 2>&1 | tee eg/q_test.x
#                  Build the C++ qhulltest with Qt
#
# $Id: //main/2019/qhull/Makefile#19 $

# Do not replace tabs with spaces.  Needed for build rules
# Unix line endings (\n)

DESTDIR = /usr/local
BINDIR  = $(DESTDIR)/bin
INCDIR  = $(DESTDIR)/include
LIBDIR  = $(DESTDIR)/lib
DOCDIR  = $(DESTDIR)/share/doc/qhull
MANDIR  = $(DESTDIR)/share/man/man1

# if you do not have enscript, try a2ps or just use lpr.  The files are text.
PRINTMAN = enscript -2rl
PRINTC = enscript -2r
# PRINTMAN = lpr
# PRINTC = lpr

#for Gnu's gcc compiler, -O3 for optimization, -g for debugging, -pg for profiling
# Qhull uses less memory with 32-bit builds (-m32), override with 'make M32='
# -fpic needed for gcc x86_64-linux-gnu.  Not needed for mingw
# see below for gcc's CC_WARNINGS and CXX_WARNINGS
M32       = -m32
CC        = gcc
CC_OPTS1  = -O3 -ansi -Isrc -fpic $(CC_WARNINGS) ${M32}
CXX       = g++

# libqhullcpp must be before libqhull_r
CXX_OPTS1 = -O3 -Isrc/ $(CXX_WARNINGS) ${M32}

# for shared library link
CC_OPTS3  =

# Define qhull_VERSION in CMakeLists.txt, Makefile, and qhull-warn.pri
# Truncated version in qhull-exports.def, qhull_p-exports.def, qhull_r-exports.def
#  libqhull_r.so -- reentrant Qhull with qh_qhT passed as an argument.
qhull_SOVERSION=7
SO  = so.7.3.2

# On MinGW, 
#   make SO=dll
#   Copy lib/libqhull_r.dll to bin/

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

# Warnings for gcc
# [gcc 8.1 from may'2018] Compiles without error (-Werror)
CC_WARNINGS  = -Wall -Wcast-qual -Wextra -Wwrite-strings -Wshadow -Wsign-conversion -Wconversion
CXX_WARNINGS = -Wall -Wcast-qual -Wextra -Wwrite-strings -Wno-sign-conversion -Wshadow -Wconversion 

# All warnings for gcc
# Ignore these gcc warnings (-f*, Fortran only, Go only, ObjC only, Qhull issues)
##Ignore warnings that occur in Qhull and appear to be OK
#   NOT_QHULL_WARN="aggregate-return|float-equal|format-nonliteral|format-signedness|old-style-cast|padded|redundant-decls|long-long|strict-overflow|switch-enum|traditional|traditional-conversion|unsafe-loop-optimizations|unsuffixed-float-constants|useless-cast|zero-as-null-pointer-constant"
##Ignore warnings that require an operand.  Include them specifically if needed.  Pattern may be a substring
#   NOT_EQUAL_WARN="format-overflow<|normalized=[^> ]*>|larger-than=|larger-than-|abi=|array-bounds=|aligned-new=|catch-value=|format=|format-overflow=|format-truncation=|implicit-fallthrough=|normalized=[^.]|placement-new=[^.]|shift-overflow=[^.]|stack-usage=|strict-aliasing=|strict-overflow=|stringop-overflow=[^.]|unused-const-variable=[^.]"
##Ignore warnings that are GCC specific and occur in Qhull
#   NOT_GCC_WARN="abi-tag|effc[+][+]|missing-format-attribute|missing-noreturn|namespaces|suggest-attribute|suggest-attribute=(format|malloc|noreturn|pure)|suggest-final-methods|suggest-final-types|suggest-override|templates"
##  -Wstringop-truncation -- known issue Bug c++/85700
##Ignore the above warnings and warnings specific to Fortran, ObjC, etc
#   NOT_CC_CXX_WARN="$NOT_GCC_WARN|$NOT_QHULL_WARN|aliasing|align-commons|ampersand|argument-mismatch|array-temporaries|assign-intercept|c-binding-type|character-truncation|compare-reals|conversion-extra|do-subscript|function-elimination|implicit-interface|implicit-procedure|integer-division|intrinsic-shadow|intrinsics-std|line-truncation|property-assign-default|protocol|real-q-constant|realloc-lhs|realloc-lhs-all|selector|shadow-ivar|strict-selector-match|surprising|tabs|target-lifetime|undeclared-selector|undefined-do-loop|underflow|unused-dummy-argument|use-without-only|zerotrip"
##Ignore these warnings and warnings for CC but not CXX and vice versa
#   NOT_CC_WARNINGS="$NOT_CC_CXX_WARN|c[+][+][0-9xz]*-compat|abi-tag|argument-mismatch|catch-value|class-memaccess|conditionally-supported|conversion-null|ctor-dtor-privacy|delete-incomplete|delete-non-virtual-dtor|effc++|extra-semi|inherited-variadic-ctor|invalid-offsetof|literal-suffix|multiple-inheritance|namespaces|noexcept|noexcept-type|non-template-friend|non-virtual-dtor|overloaded-virtual|placement-new|pmf-conversions|register|reorder|sign-promo|sized-deallocation|strict-null-sentinel|subobject-linkage|suggest-override|synth|templates|terminate|useless-cast|virtual-inheritance|virtual-move-assign|zero-as-null-pointer-constant"
#   NOT_CXX_WARNINGS="$NOT_CC_CXX_WARN|c[+][+]-compat|bad-function-cast|c90-c99-compat|c99-c11-compat|declaration-after-statement|designated-init|discarded-array-qualifiers|discarded-qualifiers|duplicate-decl-specifier|implicit|implicit-function-declaration|implicit-int|incompatible-pointer-types|int-conversion|jump-misses-init|missing-parameter-type|missing-prototypes|nested-externs|old-style-declaration|old-style-definition|override-init|override-init-side-effects|pointer-sign|pointer-to-int-cast|strict-prototypes"
#   NOT_CXX_WARNINGS="$NOT_CXX_WARNINGS|sign-conversion"
##List of gcc warnings for CC_WARNINGS, excluding NOT_CC_WARNINGS and NOT_EQUAL_WARN, to bin/x.cc
#   (echo -n -Wformat-overflow; echo " "; gcc --help=warnings) | sed -nr 's/^ *(-W[^ ]*) .*/\1/p' | sort -u | grep -vE "[-]W\$|-W(all|extra|$NOT_CC_WARNINGS)\$|$NOT_EQUAL_WARN" >bin/x.cc
##List gcc warnings for CXX_WARNINGS, excluding NOT_CXX_WARNINGS and NOT_EQUAL_WARN, bin/x.ccx
##  -Wno-sign-conversion due to 'int' vs. 'size_t' for indexing, boolT, countT, and size_t returns
##..-Wno-old-style-cast due to warnings for libqhull_r macros
##  Test CXX_WARNINGS with -Wsign-conversion and -Wold-style-cast
#   (echo -n -Wno-old-style-cast -Wno-sign-conversion -Wformat-overflow; echo " "; gcc --help=warnings) | sed -nr 's/^ *(-W[^ ]*) .*/\1/p' | sort -u | grep -vE "[-]W\$|-W(all|extra|sign-conversion|$NOT_CXX_WARNINGS)\$|$NOT_EQUAL_WARN" >bin/x.cxx
##List of mismatched gcc warnings for NOT_CC_CXX_WARN, NOT_CC_WARNINGS, and NOT_CXX_WARNINGS to bin/x.1
#   make cleanall SO=dll qhullx 2>&1 | grep "not for C" | sort -u > bin/x.1
##Test gcc warnings on Windows with mingw gcc to bin/x.2
#   make cleanall SO=dll qhullx >bin/x.2 2>&1		# libqhull and libqhull_r
#   make cleanall SO=dll bin/user_eg3 >bin/x.2 2>&1     # libqhullcpp
#   make cleanall SO=dll all >bin/x.2 2>&1
##Summary list of warnings to bin/x.1 for review
#   grep -vE 'Tools/mingw|mingw-w64|short unsigned int:9|string length .([0-9][0-9][0-9]|1[0-7][0-9][0-9]). is greater|from src/' bin/x.2 | grep -E -A6 'warning:|: error:' >bin/x.1
## [gcc 8.1 from may'2018] Compiles OK with these CC_WARNINGS and CXX_WARNINGS
# CC_WARNINGS = -Wformat-overflow -Wabi -Waddress -Waggressive-loop-optimizations -Walloc-zero -Walloca -Warray-bounds -Wattribute-alias -Wattributes -Wbad-function-cast -Wbool-compare -Wbool-operation -Wbuiltin-declaration-mismatch -Wbuiltin-macro-redefined -Wc90-c99-compat -Wc99-c11-compat -Wcast-align -Wcast-align=strict -Wcast-function-type -Wcast-qual -Wchar-subscripts -Wchkp -Wclobbered -Wcomment -Wcomments -Wconversion -Wcoverage-mismatch -Wcpp -Wdangling-else -Wdate-time -Wdeclaration-after-statement -Wdeprecated -Wdeprecated-declarations -Wdesignated-init -Wdisabled-optimization -Wdiscarded-array-qualifiers -Wdiscarded-qualifiers -Wdiv-by-zero -Wdouble-promotion -Wduplicate-decl-specifier -Wduplicated-branches -Wduplicated-cond -Wempty-body -Wendif-labels -Wenum-compare -Werror-implicit-function-declaration -Werror=implicit-function-declaration -Wexpansion-to-defined -Wfloat-conversion -Wformat -Wformat-contains-nul -Wformat-extra-args -Wformat-security -Wformat-truncation -Wformat-y2k -Wformat-zero-length -Wframe-address -Wfree-nonheap-object -Whsa -Wif-not-aligned -Wignored-attributes -Wignored-qualifiers -Wimplicit -Wimplicit-fallthrough -Wimplicit-function-declaration -Wimplicit-int -Wincompatible-pointer-types -Winit-self -Winline -Wint-conversion -Wint-in-bool-context -Wint-to-pointer-cast -Winvalid-memory-model -Winvalid-pch -Wjump-misses-init -Wlogical-not-parentheses -Wlogical-op -Wlto-type-mismatch -Wmain -Wmaybe-uninitialized -Wmemset-elt-size -Wmemset-transposed-args -Wmisleading-indentation -Wmissing-attributes -Wmissing-braces -Wmissing-declarations -Wmissing-field-initializers -Wmissing-include-dirs -Wmissing-parameter-type -Wmissing-prototypes -Wmultichar -Wmultistatement-macros -Wnarrowing -Wnested-externs -Wnonnull -Wnonnull-compare -Wnormalized -Wnull-dereference -Wodr -Wold-style-declaration -Wold-style-definition -Wopenmp-simd -Woverflow -Woverlength-strings -Woverride-init -Woverride-init-side-effects -Wpacked -Wpacked-bitfield-compat -Wpacked-not-aligned -Wparentheses -Wpedantic -Wpedantic-ms-format -Wpointer-arith -Wpointer-compare -Wpointer-sign -Wpointer-to-int-cast -Wpragmas -Wpsabi -Wrestrict -Wreturn-local-addr -Wreturn-type -Wscalar-storage-order -Wsequence-point -Wshadow -Wshadow-compatible-local -Wshadow-local -Wshadow=compatible-local -Wshadow=global -Wshadow=local -Wshift-count-negative -Wshift-count-overflow -Wshift-negative-value -Wshift-overflow -Wsign-compare -Wsign-conversion -Wsizeof-array-argument -Wsizeof-pointer-div -Wsizeof-pointer-memaccess -Wstack-protector -Wstrict-aliasing -Wstrict-prototypes -Wstringop-overflow -Wstringop-truncation -Wsuggest-attribute=cold -Wsuggest-attribute=const -Wswitch -Wswitch-bool -Wswitch-default -Wswitch-unreachable -Wsync-nand -Wsystem-headers -Wtautological-compare -Wtrampolines -Wtrigraphs -Wtype-limits -Wundef -Wuninitialized -Wunknown-pragmas -Wunreachable-code -Wunused -Wunused-but-set-parameter -Wunused-but-set-variable -Wunused-const-variable -Wunused-function -Wunused-label -Wunused-local-typedefs -Wunused-macros -Wunused-parameter -Wunused-result -Wunused-value -Wunused-variable -Wvarargs -Wvariadic-macros -Wvector-operation-performance -Wvla -Wvolatile-register-var -Wwrite-strings
# CXX_WARNINGS = -Wno-old-style-cast -Wno-sign-conversion -Wformat-overflow -Wabi -Waddress -Waggressive-loop-optimizations -Walloc-zero -Walloca -Warray-bounds -Wattribute-alias -Wattributes -Wbool-compare -Wbool-operation -Wbuiltin-declaration-mismatch -Wbuiltin-macro-redefined -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Wc++17-compat -Wc++1z-compat -Wcast-align -Wcast-align=strict -Wcast-function-type -Wcast-qual -Wcatch-value -Wchar-subscripts -Wchkp -Wclass-memaccess -Wclobbered -Wcomment -Wcomments -Wconditionally-supported -Wconversion -Wconversion-null -Wcoverage-mismatch -Wcpp -Wctor-dtor-privacy -Wdangling-else -Wdate-time -Wdelete-incomplete -Wdelete-non-virtual-dtor -Wdeprecated -Wdeprecated-declarations -Wdisabled-optimization -Wdiv-by-zero -Wdouble-promotion -Wduplicated-branches -Wduplicated-cond -Wempty-body -Wendif-labels -Wenum-compare -Werror-implicit-function-declaration -Werror=implicit-function-declaration -Wexpansion-to-defined -Wextra-semi -Wfloat-conversion -Wformat -Wformat-contains-nul -Wformat-extra-args -Wformat-security -Wformat-truncation -Wformat-y2k -Wformat-zero-length -Wframe-address -Wfree-nonheap-object -Whsa -Wif-not-aligned -Wignored-attributes -Wignored-qualifiers -Wimplicit-fallthrough -Winherited-variadic-ctor -Winit-self -Winline -Wint-in-bool-context -Wint-to-pointer-cast -Winvalid-memory-model -Winvalid-offsetof -Winvalid-pch -Wliteral-suffix -Wlogical-not-parentheses -Wlogical-op -Wlto-type-mismatch -Wmain -Wmaybe-uninitialized -Wmemset-elt-size -Wmemset-transposed-args -Wmisleading-indentation -Wmissing-attributes -Wmissing-braces -Wmissing-declarations -Wmissing-field-initializers -Wmissing-include-dirs -Wmultichar -Wmultiple-inheritance -Wmultistatement-macros -Wnarrowing -Wnoexcept -Wnoexcept-type -Wnon-template-friend -Wnon-virtual-dtor -Wnonnull -Wnonnull-compare -Wnormalized -Wnull-dereference -Wodr -Wopenmp-simd -Woverflow -Woverlength-strings -Woverloaded-virtual -Wpacked -Wpacked-bitfield-compat -Wpacked-not-aligned -Wparentheses -Wpedantic -Wpedantic-ms-format -Wplacement-new -Wpmf-conversions -Wpointer-arith -Wpointer-compare -Wpragmas -Wpsabi -Wregister -Wreorder -Wrestrict -Wreturn-local-addr -Wreturn-type -Wscalar-storage-order -Wsequence-point -Wshadow -Wshadow-compatible-local -Wshadow-local -Wshadow=compatible-local -Wshadow=global -Wshadow=local -Wshift-count-negative -Wshift-count-overflow -Wshift-negative-value -Wshift-overflow -Wsign-compare -Wsign-promo -Wsized-deallocation -Wsizeof-array-argument -Wsizeof-pointer-div -Wsizeof-pointer-memaccess -Wstack-protector -Wstrict-aliasing -Wstrict-null-sentinel -Wstringop-overflow -Wstringop-truncation -Wsubobject-linkage -Wsuggest-attribute=cold -Wsuggest-attribute=const -Wswitch -Wswitch-bool -Wswitch-default -Wswitch-unreachable -Wsync-nand -Wsynth -Wsystem-headers -Wtautological-compare -Wterminate -Wtrampolines -Wtrigraphs -Wtype-limits -Wundef -Wuninitialized -Wunknown-pragmas -Wunreachable-code -Wunused -Wunused-but-set-parameter -Wunused-but-set-variable -Wunused-const-variable -Wunused-function -Wunused-label -Wunused-local-typedefs -Wunused-macros -Wunused-parameter -Wunused-result -Wunused-value -Wunused-variable -Wvarargs -Wvariadic-macros -Wvector-operation-performance -Wvirtual-inheritance -Wvirtual-move-assign -Wvla -Wvolatile-register-var -Wwrite-strings

# Default targets for make

all: bin-lib bin/rbox bin/qconvex bin/qdelaunay bin/qhalf bin/qvoronoi bin/qhull bin/testqset \
     bin/testqset_r qtest bin/user_eg2 bin/user_eg3 bin/user_eg qconvex-prompt

help:
	head -n 80 Makefile

bin-lib:
	mkdir -p bin
	mkdir -p lib
	@echo "if gcc fails with -- bits/predefs.h: No such file"
	@echo "  install a 32-bit build environment, or"
	@echo "  make M32="

# Remove intermediate files for all builds
# Deletes eg/*.x, *.x, and *.tmp
clean:
	rm -f src/*/*.o src/qhulltest/RoadTest.h.cpp build/*/*/*.o  build/*/*.o
	rm -f src/*/*.obj build/*/*/*.obj build/*/*/*/*/*.obj build/*/*.obj 
	rm -f src/*/gmon.out bin/*.idb lib/*.idb build-cmake/*/*.idb
	rm -f eg/*.x *.x *.tmp
	rm -f build/*/*/*.a build/*/*/*.rsp build/moc/*.moc
	rm -f build-cmake/*/*.obj build-cmake/*/*/*.obj build-cmake/*/*.ilk
	@echo Remove linked C files from libqhull/ and libqhull_r/
	rm -f src/libqhull/rbox.c src/libqhull/qconvex.c src/libqhull/qdelaun.c
	rm -f src/libqhull/qhalf.c src/libqhull/qvoronoi.c src/libqhull/testqset.c
	rm -f src/libqhull/unix.c src/libqhull/user_eg.c src/libqhull/user_eg2.c
	rm -f src/libqhull_r/rbox_r.c src/libqhull_r/qconvex_r.c src/libqhull_r/qdelaun_r.c
	rm -f src/libqhull_r/qhalf_r.c src/libqhull_r/qvoronoi_r.c src/libqhull_r/testqset_r.c
	rm -f src/libqhull_r/unix_r.c src/libqhull_r/user_eg_r.c src/libqhull_r/user_eg2_r.c
	rm -f src/libqhull_r/user_eg3_r.c

# Remove intermediate files and targets for all builds
# DevStudio prevents build/qhull.ncb deletes
cleanall: clean
	rm -rf build/*.dir/ 
	-rm -rf build/qhull.ncb
	rm -rf buildvc/
	rm -rf buildqt/
	rm -rf build-qhull-all*/
	rm -rf src/qhull_qh/
	rm -rf gmon.out bin/gmon.out
	rm -f bin/qconvex bin/qdelaunay bin/qhalf bin/qvoronoi bin/qhull
	rm -f bin/rbox core bin/core bin/user_eg bin/user_eg2 bin/user_eg3
	rm -f bin/testqset bin/testqset_r bin/qhulltest
	rm -f bin/libqhull* bin/qhull*.dll bin/*.exe bin/*.pdb lib/*.pdb
	rm -f build/*.dll build/*.exe build/*.a build/*.exp 
	rm -f build/*.lib build/*.pdb build/*.idb build/qhull-no-qt.sln
	rm -f build-cmake/*/*.dll build-cmake/*/*.exe build-cmake/*/*.exp 
	rm -f build-cmake/*/*.lib build-cmake/*/*.pdb
	rm -f eg/eg.* eg/t*.tmp
	rm -f lib/libqhull* lib/qhull*.lib lib/qhull*.exp  lib/qhull*.dll
	rm -f src/libqhull*/*.exe  src/libqhull*/libqhullstatic.a src/libqhull*/core
	rm -f src/libqhull*/qconvex src/libqhull*/qdelaunay src/libqhull*/qhalf 
	rm -f src/libqhull*/qvoronoi src/libqhull*/qhull src/libqhull*/rbox
	rm -f src/libqhull*/user_eg src/libqhull*/user_eg2 src/libqhull*/user_eg3

doc: 
	$(PRINTMAN) $(TXTFILES) $(DOCFILES)

install: bin/qconvex bin/qdelaunay bin/qhalf bin/qhull bin/qvoronoi bin/rbox
	mkdir -p $(BINDIR)
	mkdir -p $(DOCDIR)
	mkdir -p $(INCDIR)/libqhull
	mkdir -p $(INCDIR)/libqhull_r
	mkdir -p $(INCDIR)/libqhullcpp
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
	cp src/libqhull/DEPRECATED.txt src/libqhull/*.h src/libqhull/*.htm $(INCDIR)/libqhull
	cp src/libqhull_r/*.h src/libqhull_r/*.htm $(INCDIR)/libqhull_r
	cp src/libqhullcpp/*.h $(INCDIR)/libqhullcpp
	cp src/qhulltest/*.h $(INCDIR)/libqhullcpp

new:	cleanall all

printall: doc printh printc printf

printh:
	$(PRINTC) $(LIBQHULL_HDRS)
	$(PRINTC) $(LIBQHULLR_HDRS)
	$(PRINTC) $(LIBQHULLCPP_HDRS)

printc:
	$(PRINTC) $(CFILES)
	$(PRINTC) $(CXXFILES)
	$(PRINTC) $(TESTFILES)

printf:
	$(PRINTC) $(FILES)

# for Windows, do not depend on bin/qhull,etc.
qtest:
	@echo ============================================
	@echo == make qtest ==============================
	@echo ============================================
	@echo -n "== "
	@date
	@echo
	@echo ============================================
	@echo == Test non-reentrant qset.c with mem.c ====
	@echo ============================================
	-bin/testqset 10000
	@echo
	@echo ============================================
	@echo == Test reentrant qset_r.c with mem_r.c ====
	@echo ============================================
	-bin/testqset_r 10000
	@echo
	@echo ============================================
	@echo == Run the qhull smoketest              ====
	@echo ============================================
	-bin/rbox D4 | bin/qhull Tv
	
# for Windows, do not depend on bin/qhull,etc.
test: qtest
	@echo ============================================
	@echo == make test, after running qtest ==========
	@echo ============================================
	@echo
	@echo ==============================
	@echo ========= rbox/qhull =======
	@echo ==============================
	-bin/rbox D4 | bin/qhull Tv
	@echo
	@echo ==============================
	@echo ========= qconvex ============
	@echo ==============================
	-bin/rbox 10 | bin/qconvex Tv 
	@echo
	@echo ==============================
	@echo ========= qdelaunay ==========
	@echo ==============================
	-bin/rbox 10 | bin/qdelaunay Tv 
	@echo
	@echo ==============================
	@echo ========= qhalf ==============
	@echo ==============================
	-bin/rbox 10 | bin/qconvex FQ FV n Tv | bin/qhalf Tv
	@echo
	@echo ==============================
	@echo ========= qvoronoi ===========
	@echo ==============================
	-bin/rbox 10 | bin/qvoronoi Tv
	@echo
	@echo =================================
	@echo ========= user_eg ===============
	@echo == if fails under Windows =======
	@echo ==  cp lib/libqhull_r.dll bin/ ==
	@echo =================================
	-bin/user_eg
	@echo
	@echo ==============================
	@echo ========= user_eg2 ===========
	@echo ==============================
	-bin/user_eg2
	@echo
	@echo ==============================
	@echo ========= user_eg3 ===========
	@echo ==============================
	-bin/user_eg3
	-bin/user_eg3 rbox "10 D2"  "2 D2" qhull "s p" facets

# make testall >eg/q_test.x 2>&1
testall: test 
	@echo ================================================
	@echo == make testall, after running qtest and test ==
	@echo ================================================
	@echo -n "== "
	@date
	@echo
	-eg/q_eg
	-eg/q_egtest
	-eg/q_test
	-eg/q_benchmark test 1 1 1 1

# make benchmark >eg/q_benchmark.x 2>&1
benchmark: 
	@echo ============================================
	@echo == make benchmark ==========================
	@echo == eg/qtest.sh    ==========================
	@echo ============================================
	@echo -n "== "
	@date
	@echo
	-eg/q_benchmark -10 -10 -10 -10

# last command for 'make all'
qconvex-prompt: bin/qconvex bin/rbox 
	bin/qconvex -?
	@echo
	@echo ============================================
	@echo == Run the qconvex smoketest
	@echo ============================================
	bin/rbox D4 | bin/qconvex Tv
	@echo
	@echo ============================================
	@echo == To enable user_eg
	@echo ==
	@echo == Windows -- make SO=dll
	@echo '==     cp -p lib/libqhull*.dll bin'
	@echo ==
	@echo == Unix/Macintosh -- make
	@echo '==     export LD_LIBRARY_PATH=$$PWD/lib:$$LD_LIBRARY_PATH'
	@echo ============================================
	@echo
	@echo ============================================
	@echo == To smoketest qhull programs
	@echo '==     make test'
	@echo ============================================
	@echo
	@echo ============================================
	@echo == To run qhull tests for manual review with eg/q_test-ok.txt
	@echo '==     make testall >eg/q_test.x 2>&1'
	@echo '==     make testall 2>&1 | tee eg/q_test.x'
	@echo ============================================
	@echo
	@echo ============================================
	@echo == To show all make targets
	@echo '==     make help'
	@echo ============================================
	@echo

# libqhull is source files for non-reentrant Qhull
# libqhull_r is source files and a shared library for reentrant Qhull
L=    src/libqhull
LR=   src/libqhull_r

# libqhullstatic is a static library for non-reentrant Qhull
# libqhullstatic_r is a static library for reentrant Qhull
LS=   src/libqhullstatic
LSR=  src/libqhullstatic_r

# libqhullcpp is a static library for C++ files and libqhull_r
# qhulltest is a Qt test of libqhullcpp
LCPP= src/libqhullcpp
TCPP= src/qhulltest

LIBQHULL_HDRS = $(L)/user.h $(L)/libqhull.h $(L)/qhull_a.h $(L)/geom.h \
	$(L)/io.h $(L)/mem.h $(L)/merge.h $(L)/poly.h $(L)/random.h \
	$(L)/qset.h $(L)/stat.h

LIBQHULLR_HDRS = $(LR)/user_r.h $(LR)/libqhull_r.h $(LR)/qhull_ra.h $(LR)/geom_r.h \
	$(LR)/io_r.h $(LR)/mem_r.h $(LR)/merge_r.h $(LR)/poly_r.h $(LR)/random_r.h \
	$(LR)/qset_r.h $(LR)/stat_r.h

# LIBQHULLS_OBJS and LIBQHULLSR_OBJS ordered by frequency of execution with
# small files at end.  Better locality.

LIBQHULLS_OBJS= $(LS)/global.o $(LS)/stat.o $(LS)/geom2.o $(LS)/poly2.o \
	$(LS)/merge.o $(LS)/libqhull.o $(LS)/geom.o $(LS)/poly.o \
	$(LS)/qset.o $(LS)/mem.o $(LS)/random.o 

LIBQHULLS_USER_OBJS = $(LIBQHULLS_OBJS) $(LS)/usermem.o $(LS)/userprintf.o \
	$(LS)/io.o $(LS)/user.o

LIBQHULLS_RBOX_OBJS = $(LIBQHULLS_USER_OBJS) $(LS)/rboxlib.o $(LS)/userprintf_rbox.o

LIBQHULLSR_OBJS = $(LSR)/global_r.o $(LSR)/stat_r.o $(LSR)/geom2_r.o $(LSR)/poly2_r.o \
	$(LSR)/merge_r.o $(LSR)/libqhull_r.o $(LSR)/geom_r.o $(LSR)/poly_r.o \
	$(LSR)/qset_r.o $(LSR)/mem_r.o $(LSR)/random_r.o

LIBQHULLSR_USER_OBJS = $(LIBQHULLSR_OBJS) $(LSR)/usermem_r.o $(LSR)/userprintf_r.o \
	$(LSR)/io_r.o $(LSR)/user_r.o

LIBQHULLSR_RBOX_OBJS = $(LIBQHULLSR_USER_OBJS) $(LSR)/rboxlib_r.o $(LSR)/userprintf_rbox_r.o

LIBQHULLCPP_HDRS = $(LCPP)/RoadError.h $(LCPP)/RoadLogEvent.h $(LCPP)/Coordinates.h \
	$(LCPP)/QhullHyperplane.h $(LCPP)/functionObjects.h $(LCPP)/PointCoordinates.h \
	$(LCPP)/Qhull.h $(LCPP)/QhullError.h $(LCPP)/QhullFacet.h \
	$(LCPP)/QhullFacetList.h $(LCPP)/QhullFacetSet.h $(LCPP)/QhullIterator.h \
	$(LCPP)/QhullLinkedList.h $(LCPP)/QhullPoint.h $(LCPP)/QhullPoints.h \
	$(LCPP)/QhullPointSet.h $(LCPP)/QhullQh.h $(LCPP)/QhullRidge.h \
	$(LCPP)/QhullSet.h $(LCPP)/QhullSets.h $(LCPP)/QhullStat.h \
	$(LCPP)/QhullVertex.h $(LCPP)/RboxPoints.h

LIBQHULLCPP_OBJS = $(LCPP)/RoadError.o $(LCPP)/RoadLogEvent.o $(LCPP)/Coordinates.o \
	$(LCPP)/PointCoordinates.o $(LCPP)/Qhull.o $(LCPP)/QhullFacet.o \
	$(LCPP)/QhullFacetList.o $(LCPP)/QhullFacetSet.o \
	$(LCPP)/QhullHyperplane.o $(LCPP)/QhullPoint.o \
	$(LCPP)/QhullPoints.o $(LCPP)/QhullPointSet.o $(LCPP)/QhullQh.o \
	$(LCPP)/QhullRidge.o $(LCPP)/QhullSet.o $(LCPP)/QhullStat.o \
	$(LCPP)/QhullVertex.o $(LCPP)/QhullVertexSet.o $(LCPP)/RboxPoints.o

# CFILES for non-reentrant Qhull, ordered alphabetically after libqhull.c
CFILES= src/qhull/unix.c $(L)/libqhull.c $(L)/geom.c $(L)/geom2.c $(L)/global.c $(L)/io.c \
	$(L)/mem.c $(L)/merge.c $(L)/poly.c $(L)/poly2.c $(L)/random.c $(L)/rboxlib.c \
	$(L)/qset.c $(L)/stat.c $(L)/user.c $(L)/usermem.c $(L)/userprintf.c $(L)/userprintf_rbox.c \
	src/qconvex/qconvex.c src/qdelaunay/qdelaun.c src/qhalf/qhalf.c src/qvoronoi/qvoronoi.c

# CFILESR for reentrant Qhull, ordered alphabetically after libqhull.c
CFILESR= src/qhull/unix_r.c $(LSR)/libqhull_r.c $(LSR)/geom_r.c $(LSR)/geom2_r.c $(LSR)/global_r.c $(LSR)/io_r.c \
	$(LSR)/mem_r.c $(LSR)/merge_r.c $(LSR)/poly_r.c $(LSR)/poly2_r.c $(LSR)/random_r.c $(LSR)/rboxlib_r.c \
	$(LSR)/qset_r.c $(LSR)/stat_r.c $(LSR)/user_r.c $(LSR)/usermem_r.c $(LSR)/userprintf_r.c $(LSR)/userprintf_rbox_r.c \
	src/qconvex/qconvex_r.c src/qdelaunay/qdelaun_r.c src/qhalf/qhalf_r.c src/qvoronoi/qvoronoi_r.c

# CXXFILES for C++ sources using libqhull_r (reentrant qhull), alphabetical
CXXFILES=  $(LCPP)/Coordinates.cpp $(LCPP)/PointCoordinates.cpp \
	$(LCPP)/Qhull.cpp $(LCPP)/QhullFacet.cpp \
	$(LCPP)/QhullFacetList.cpp $(LCPP)/QhullFacetSet.cpp \
	$(LCPP)/QhullHyperplane.cpp $(LCPP)/QhullPoint.cpp \
	$(LCPP)/QhullPoints.cpp $(LCPP)/QhullPointSet.cpp $(LCPP)/QhullQh.cpp \
	$(LCPP)/QhullRidge.cpp $(LCPP)/QhullSet.cpp $(LCPP)/QhullStat.cpp \
	$(LCPP)/QhullVertex.cpp $(LCPP)/QhullVertexSet.cpp $(LCPP)/RboxPoints.cpp \
	$(LCPP)/RoadError.cpp $(LCPP)/RoadLogEvent.cpp src/user_eg3/user_eg3_r.cpp
	
# TESTFILES for Qt test of C++ sources using libqhull_r (reentrant qhull), alphabetical after qhulltest.cpp
TESTFILES= $(TCPP)/qhulltest.cpp $(TCPP)/Coordinates_test.cpp $(TCPP)/PointCoordinates_test.cpp \
	$(TCPP)/Qhull_test.cpp $(TCPP)/QhullFacet_test.cpp $(TCPP)/QhullFacetList_test.cpp \
	$(TCPP)/QhullFacetSet_test.cpp $(TCPP)/QhullHyperplane_test.cpp $(TCPP)/QhullLinkedList_test.cpp \
	$(TCPP)/QhullPoint_test.cpp $(TCPP)/QhullPoints_test.cpp \
	$(TCPP)/QhullPointSet_test.cpp $(TCPP)/QhullRidge_test.cpp \
	$(TCPP)/QhullSet_test.cpp $(TCPP)/QhullVertex_test.cpp $(TCPP)/QhullVertexSet_test.cpp \
	$(TCPP)/RboxPoints_test.cpp


TXTFILES= Announce.txt REGISTER.txt COPYING.txt README.txt src/Changes.txt
DOCFILES= html/rbox.txt html/qhull.txt
FILES=	Makefile src/rbox/rbox.c src/user_eg/user_eg.c src/user_eg2/user_eg2.c \
	src/testqset/testqset.c eg/q_test eg/q_egtest eg/q_eg
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
qhull/unix_r.o:          $(LR)/libqhull_r.h $(LR)/user_r.h $(LR)/mem_r.h
qconvex/qconvex_r.o:     $(LR)/libqhull_r.h $(LR)/user_r.h $(LR)/mem_r.h
qdelanay/qdelaun_r.o:    $(LR)/libqhull_r.h $(LR)/user_r.h $(LR)/mem_r.h
qhalf/qhalf_r.o:         $(LR)/libqhull_r.h $(LR)/user_r.h $(LR)/mem_r.h
qvoronoi/qvoronoi_r.o:   $(LR)/libqhull_r.h $(LR)/user_r.h $(LR)/mem_r.h
$(LS)/libqhull.o: $(LIBQHULL_HDRS)
$(LS)/geom.o:     $(LIBQHULL_HDRS)
$(LS)/geom2.o:    $(LIBQHULL_HDRS)
$(LS)/global.o:   $(LIBQHULL_HDRS)
$(LS)/io.o:       $(LIBQHULL_HDRS)
$(LS)/mem.o:      $(L)/mem.h
$(LS)/merge.o:    $(LIBQHULL_HDRS)
$(LS)/poly.o:     $(LIBQHULL_HDRS)
$(LS)/poly2.o:    $(LIBQHULL_HDRS)
$(LS)/random.o:   $(L)/libqhull.h $(L)/random.h $(L)/user.h
$(LS)/rboxlib.o:  $(L)/libqhull.h $(L)/random.h $(L)/user.h
$(LS)/qset.o:     $(L)/qset.h $(L)/mem.h
$(LS)/stat.o:     $(LIBQHULL_HDRS)
$(LS)/user.o:     $(LIBQHULL_HDRS)
$(LSR)/libqhull_r.o: $(LIBQHULLR_HDRS)
$(LSR)/geom_r.o:     $(LIBQHULLR_HDRS)
$(LSR)/geom2_r.o:    $(LIBQHULLR_HDRS)
$(LSR)/global_r.o:   $(LIBQHULLR_HDRS)
$(LSR)/io_r.o:       $(LIBQHULLR_HDRS)
$(LSR)/mem_r.o:      $(LR)/mem_r.h
$(LSR)/merge_r.o:    $(LIBQHULLR_HDRS)
$(LSR)/poly_r.o:     $(LIBQHULLR_HDRS)
$(LSR)/poly2_r.o:    $(LIBQHULLR_HDRS)
$(LSR)/random_r.o:   $(LR)/libqhull_r.h $(LR)/random_r.h $(LR)/user_r.h $(LR)/mem_r.h
$(LSR)/rboxlib_r.o:  $(LR)/libqhull_r.h $(LR)/random_r.h $(LR)/user_r.h $(LR)/mem_r.h
$(LSR)/qset_r.o:     $(LR)/qset_r.h $(LR)/mem_r.h
$(LSR)/stat_r.o:     $(LIBQHULLR_HDRS)
$(LSR)/user_r.o:     $(LIBQHULLR_HDRS)
$(LCPP)/RoadError.o:        $(LCPP)/RoadError.h $(LCPP)/RoadLogEvent.h
$(LCPP)/RoadLogEvent.o:     $(LCPP)/RoadError.h                  
$(LCPP)/Coordinates.o:      $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)
$(LCPP)/PointCoordinates.o: $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)
$(LCPP)/Qhull.o:            $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)
$(LCPP)/QhullFacet.o:       $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)
$(LCPP)/QhullFacetList.o:   $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)
$(LCPP)/QhullFacetSet.o:    $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)
$(LCPP)/QhullHyperplane.o:  $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)
$(LCPP)/QhullPoint.o:       $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)
$(LCPP)/QhullPoints.o:      $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)
$(LCPP)/QhullPointSet.o:    $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)
$(LCPP)/QhullQh.o:          $(LIBQHULLR_HDRS)
$(LCPP)/QhullRidge.o:       $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)
$(LCPP)/QhullSet.o:         $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)
$(LCPP)/QhullStat.o:        $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)
$(LCPP)/QhullVertex.o:      $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)
$(LCPP)/QhullVertexSet.o:   $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)
$(LCPP)/RboxPoints.o:       $(LIBQHULLCPP_HDRS) $(LIBQHULLR_HDRS)

.c.o:
	$(CC) -c $(CC_OPTS1) -o $@ $<

.cpp.o:
	$(CXX) -c $(CXX_OPTS1) -o $@ $<

# qhullx -- Compile qhull without using a qhull library.  Must be after LIBQHULLS_RBOX_OBJS
# For qconvex, rbox, and other programs, qhullx produces the same results as libqhull/Makefile
# For qhull, 'make qhullx' produces the same results as libqhull_r/Makefile
qhullx: src/qconvex/qconvex.o src/qdelaunay/qdelaun.o src/qhalf/qhalf.o src/qvoronoi/qvoronoi.o\
	    src/qhull/unix_r.o src/rbox/rbox.o src/testqset/testqset.o src/testqset_r/testqset_r.o\
	    $(LIBQHULLS_RBOX_OBJS) $(LIBQHULLSR_USER_OBJS) $(LS)/mem.o $(LS)/qset.o $(LS)/usermem.o
	mkdir -p bin/
	$(CC) -o bin/qconvex $(CC_OPTS2) -lm $(LIBQHULLS_USER_OBJS) src/qconvex/qconvex.o
	$(CC) -o bin/qdelaunay $(CC_OPTS2) -lm $(LIBQHULLS_USER_OBJS) src/qdelaunay/qdelaun.o
	$(CC) -o bin/qhalf $(CC_OPTS2) -lm $(LIBQHULLS_USER_OBJS) src/qhalf/qhalf.o
	$(CC) -o bin/qvoronoi $(CC_OPTS2) -lm $(LIBQHULLS_USER_OBJS) src/qvoronoi/qvoronoi.o
	$(CC) -o bin/qhull $(CC_OPTS2) -lm $(LIBQHULLSR_USER_OBJS) src/qhull/unix_r.o
	$(CC) -o bin/rbox $(CC_OPTS2) -lm $(LIBQHULLS_RBOX_OBJS) src/rbox/rbox.o
	$(CC) -o bin/testqset $(CC_OPTS2) -lm $(LS)/mem.o $(LS)/qset.o $(LS)/usermem.o src/testqset/testqset.o
	$(CC) -o bin/testqset_r $(CC_OPTS2) -lm $(LSR)/mem_r.o $(LSR)/qset_r.o $(LSR)/usermem_r.o src/testqset_r/testqset_r.o
	-bin/testqset 10000
	-bin/testqset_r 10000
	-bin/rbox D4 | bin/qhull

# The static library, libqhullstatic, contains non-reentrant code for Qhull.  It is somewhat faster than reentrant libqhullstatic_r

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
$(LS)/userprintf_rbox.o:  $(L)/userprintf_rbox.c
	$(CC) -c $(CC_OPTS1) -o $@ $<

# The static library, libqhullstatic_r, contains reentrant code with the same behavior as libqhullstatic

$(LSR)/libqhull_r.o: $(LR)/libqhull_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/geom_r.o:     $(LR)/geom_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/geom2_r.o:    $(LR)/geom2_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/global_r.o:   $(LR)/global_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/io_r.o:       $(LR)/io_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/mem_r.o:      $(LR)/mem_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/merge_r.o:    $(LR)/merge_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/poly_r.o:     $(LR)/poly_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/poly2_r.o:    $(LR)/poly2_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/random_r.o:   $(LR)/random_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/rboxlib_r.o:   $(LR)/rboxlib_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/qset_r.o:     $(LR)/qset_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/stat_r.o:     $(LR)/stat_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/user_r.o:     $(LR)/user_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/usermem_r.o:     $(LR)/usermem_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/userprintf_r.o:     $(LR)/userprintf_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<
$(LSR)/userprintf_rbox_r.o:     $(LR)/userprintf_rbox_r.c
	$(CC) -c $(CC_OPTS1) -o $@ $<

lib/libqhullstatic.a: $(LIBQHULLS_RBOX_OBJS)
	@echo ==========================================
	@echo ==== If 'ar' fails, try 'make qhullx' ====
	@echo ==========================================
	ar -rs $@ $^
	#If 'ar -rs' fails try using 'ar -s' with 'ranlib'
	#ranlib $@

lib/libqhullstatic_r.a: $(LIBQHULLSR_RBOX_OBJS)
	ar -rs $@ $^
	#ranlib $@

# Do not create libqhullcpp as a shared library.  Qhull C++ classes may change layout and size. 
lib/libqhullcpp.a: $(LIBQHULLCPP_OBJS)
	ar -rs $@ $^
	#ranlib $@

lib/libqhull_r.$(SO): $(LIBQHULLSR_RBOX_OBJS)
	$(CC) -shared -o $@ $(CC_OPTS3) $^
	# the following line fails under MSYS, not needed for SO=dll
	-(cd lib/ && ln -f -s libqhull_r.$(SO) libqhull_r.so)

# don't use ../qconvex.	 Does not work on Red Hat Linux
bin/qconvex: src/qconvex/qconvex.o lib/libqhullstatic.a
	$(CC) -o $@ $< $(CC_OPTS2) -Llib -lqhullstatic -lm

bin/qdelaunay: src/qdelaunay/qdelaun.o lib/libqhullstatic.a
	$(CC) -o $@ $< $(CC_OPTS2) -Llib -lqhullstatic -lm

bin/qhalf: src/qhalf/qhalf.o lib/libqhullstatic.a
	$(CC) -o $@ $< $(CC_OPTS2) -Llib -lqhullstatic -lm

bin/qvoronoi: src/qvoronoi/qvoronoi.o lib/libqhullstatic.a
	$(CC) -o $@ $< $(CC_OPTS2) -Llib -lqhullstatic -lm

bin/qhull: src/qhull/unix_r.o lib/libqhullstatic_r.a
	$(CC) -o $@ $< $(CC_OPTS2) -Llib -lqhullstatic_r -lm
	-chmod +x eg/q_test eg/q_eg eg/q_egtest

bin/rbox: src/rbox/rbox.o lib/libqhullstatic.a
	$(CC) -o $@ $< $(CC_OPTS2) -Llib -lqhullstatic -lm

bin/testqset: src/testqset/testqset.o src/libqhull/qset.o src/libqhull/mem.o src/libqhull/usermem.o
	$(CC) -o $@ $^ $(CC_OPTS2) -lm

bin/testqset_r: src/testqset_r/testqset_r.o src/libqhull_r/qset_r.o src/libqhull_r/mem_r.o src/libqhull_r/usermem_r.o
	$(CC) -o $@ $^ $(CC_OPTS2) -lm

# You may use  -lqhullstatic_r instead of -lqhull_r
bin/user_eg: src/user_eg/user_eg_r.o lib/libqhull_r.$(SO)
	@echo -e '\n\n==================================================='
	@echo -e '== If user_eg fails to link on a Windows host, use'
	@echo -e '==   "make SO=dll" and copy lib/libqhull_r.dll to bin/'
	@echo -e '== Otherwise if user_eg fails to link, switch to -lqhullstatic_r'
	@echo -e '===================================================\n'
	$(CC) -o $@ $< $(CC_OPTS1) $(CC_OPTS3) -Llib -lqhull_r -lm

bin/user_eg2: src/user_eg2/user_eg2_r.o lib/libqhullstatic_r.a
	@echo -e '\n\n==================================================='
	@echo -e '== user_eg2 links to  qhullstatic_r.  It may use libqhull_r instead.'
	@echo -e '===================================================\n'
	$(CC) -o $@ $< $(CC_OPTS2) -Llib -lqhullstatic_r -lm

bin/user_eg3: src/user_eg3/user_eg3_r.o lib/libqhullstatic_r.a lib/libqhullcpp.a
	$(CXX) -o $@ $< $(CXX_OPTS2) -Llib -lqhullcpp -lqhullstatic_r -lm

# end of Makefile
