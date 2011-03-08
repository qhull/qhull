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
}
win32-msvc* : QMAKE_LFLAGS += /INCREMENTAL:NO

INCLUDEPATH += ../libqhull
