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

add_library(qhull ${qhull_src})
target_link_libraries(qhull m)

set(qhullcmd_SOURCES  unix.c)
set(rbox_SOURCES  rbox.c)
set(qconvex_SOURCES  qconvex.c)
set(qdelaunay_SOURCES  qdelaun.c)
set(qvoronoi_SOURCES  qvoronoi.c)
set(qhalf_SOURCES  qhalf.c)


add_executable(qhullcmd ${qhullcmd_SOURCES})
target_link_libraries(qhullcmd qhull)

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

