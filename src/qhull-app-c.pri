DESTDIR = ../../bin
TEMPLATE = app
CONFIG += console warn_on
CONFIG -= qt
LIBS += -L../../lib
build_pass:CONFIG(debug, debug|release){
   LIBS += -lqhull-d
   OBJECTS_DIR = Debug
}else:build_pass:CONFIG(release, debug|release){
   LIBS += -lqhull
   OBJECTS_DIR = Release
}
*g++ {
    QMAKE_CFLAGS_WARN_ON += -Werror -Wcast-qual -Wextra -Wshadow -Wwrite-strings
    QMAKE_CFLAGS_WARN_ON += -Wno-sign-conversion
    QMAKE_CFLAGS_WARN_ON += -Wconversion
QMAKE_CFLAGS_WARN_ON += -Waddress
QMAKE_CFLAGS_WARN_ON += -Warray-bounds
QMAKE_CFLAGS_WARN_ON += -Wchar-subscripts
QMAKE_CFLAGS_WARN_ON += -Wclobbered
QMAKE_CFLAGS_WARN_ON += -Wcomment
QMAKE_CFLAGS_WARN_ON += -Wempty-body
QMAKE_CFLAGS_WARN_ON += -Wformat
QMAKE_CFLAGS_WARN_ON += -Wignored-qualifiers
QMAKE_CFLAGS_WARN_ON += -Wimplicit-function-declaration
QMAKE_CFLAGS_WARN_ON += -Wimplicit-int
QMAKE_CFLAGS_WARN_ON += -Wmain
QMAKE_CFLAGS_WARN_ON += -Wmissing-braces
QMAKE_CFLAGS_WARN_ON += -Wmissing-field-initializers
QMAKE_CFLAGS_WARN_ON += -Wmissing-parameter-type
QMAKE_CFLAGS_WARN_ON += -Wnonnull
QMAKE_CFLAGS_WARN_ON += -Wold-style-declaration
QMAKE_CFLAGS_WARN_ON += -Woverride-init
QMAKE_CFLAGS_WARN_ON += -Wparentheses
QMAKE_CFLAGS_WARN_ON += -Wpointer-sign
QMAKE_CFLAGS_WARN_ON += -Wreturn-type
QMAKE_CFLAGS_WARN_ON += -Wsequence-point
QMAKE_CFLAGS_WARN_ON += -Wsign-compare
QMAKE_CFLAGS_WARN_ON += -Wsign-compare
QMAKE_CFLAGS_WARN_ON += -Wstrict-aliasing
QMAKE_CFLAGS_WARN_ON += -Wstrict-overflow=1
QMAKE_CFLAGS_WARN_ON += -Wswitch
QMAKE_CFLAGS_WARN_ON += -Wtrigraphs
QMAKE_CFLAGS_WARN_ON += -Wtype-limits
QMAKE_CFLAGS_WARN_ON += -Wuninitialized
QMAKE_CFLAGS_WARN_ON += -Wuninitialized
QMAKE_CFLAGS_WARN_ON += -Wunknown-pragmas
QMAKE_CFLAGS_WARN_ON += -Wunused-function
QMAKE_CFLAGS_WARN_ON += -Wunused-label
QMAKE_CFLAGS_WARN_ON += -Wunused-parameter
QMAKE_CFLAGS_WARN_ON += -Wunused-value
QMAKE_CFLAGS_WARN_ON += -Wunused-variable
QMAKE_CFLAGS_WARN_ON += -Wvolatile-register-var
}
win32-msvc* : QMAKE_LFLAGS += /INCREMENTAL:NO

INCLUDEPATH += ../libqhull
