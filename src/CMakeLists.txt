project(qhull_lib)

# Order object files by frequency of execution.  Small files at end.
set(
    qhull_src
        rboxlib.c
        user.c
        global.c
        stat.c
        io.c
        geom2.c
        poly2.c
        merge.c
        libqhull.c
        geom.c
        poly.c
        qset.c
        mem.c
        usermem.c
        userprintf.c
        random.c
)

file(GLOB qhull_hdr *.h)

add_library(qhull SHARED ${qhull_src})
target_link_libraries(qhull m)
if(UNIX)
    if(APPLE)
        set_target_properties(qhull PROPERTIES set(qhullcmd_SOURCES  unix.c)
                INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib")set(rbox_SOURCES  rbox.c)
    else(APPLE)set(qconvex_SOURCES  qconvex.c)
        set_target_properties(qhull PROPERTIES set(qdelaunay_SOURCES  qdelaun.c)
                INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib"set(qvoronoi_SOURCES  qvoronoi.c)
                INSTALL_RPATH_USE_LINK_PATH TRUEset(qhalf_SOURCES  qhalf.c)
                BUILD_WITH_INSTALL_RPATH FALSE)
    endif(APPLE)
endif(UNIX)
add_library(qhullstatic STATIC ${qhull_src})
set_property(TARGET qhullstatic PROPERTY OUTPUT_NAME "qhull")

add_executable(qhullcmd ${qhullcmd_SOURCES})
target_link_libraries(qhullcmd qhull)
set_property(TARGET qhullcmd PROPERTY OUTPUT_NAME "qhull")

add_executable(rbox ${rbox_SOURCES})
target_link_libraries(rbox qhull)

add_executable(qconvex ${qconvex_SOURCES})
target_link_libraries(qconvex qhull)

add_executable(qdelaunay ${qdelaunay_SOURCES})
target_link_libraries(qdelaunay qhull)

add_executable(qvoronoi ${qvoronoi_SOURCES})
target_link_libraries(qvoronoi qhull)

add_executable(qhalf ${qhalf_SOURCES})
target_link_libraries(qhalf qhull)

install(TARGETS qhull qhullstatic qhullcmd rbox qconvex qdelaunay qvoronoi qhalf
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES libqhull.h DESTINATION include)
