#!/bin/sh

html=htm
dir=$1
mkdir -p $1
src= \

for i in geom.h     \
         mem.h      \
         merge.h    \
         poly.h     \
         io.h       \
         qhull_a.h  \
         qhull.h    \
         qset.h     \
         stat.h     \
         user.h     \
         geom2.c    \
         geom.c     \
         global.c   \
         io.c       \
         mem.c      \
         merge.c    \
         poly2.c    \
         poly.c     \
         qconvex.c  \
         qdelaun.c  \
         qhalf.c    \
         qhull.c    \
         qset.c     \
         qvoronoi.c \
         stat.c     \
         unix.c     \
         user.c     \
         user_eg.c ; do

    cp src/$i $dir/$i.$html
    perl -pi -e 'BEGIN{$f=1} if ($f) {s:^/\*::; $f=0}' $dir/$i.$html

done

for i in index.htm    \
         qh-geom.htm  \
         qh-globa.htm \
         qh-io.htm    \
         qh-mem.htm   \
         qh-merge.htm \
         qh-poly.htm  \
         qh-qhull.htm \
         qh-set.htm   \
         qh-stat.htm  \
         qh-user.htm ; do

    cp src/$i $dir

done

for i in $dir/*.htm ; do

    perl -pi -e 's/(href="[a-z2_]+.)(c|h)/$1$2.'$html'/' $i

done
