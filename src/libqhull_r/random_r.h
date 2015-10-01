/*<html><pre>  -<a                             href="qh-geom.htm"
  >-------------------------------</a><a name="TOP">-</a>

  random.h
    header file for random routines

   see qh-geom.htm and random_r.c

   Copyright (c) 1993-2015 The Geometry Center.
   $Id: //main/2015/qhull/src/libqhull_r/random_r.h#1 $$Change: 1981 $
   $DateTime: 2015/09/28 20:26:32 $$Author: bbarber $
*/

#ifndef qhDEFrandom
#define qhDEFrandom 1

#include "libqhull_r.h"

/*============= prototypes in alphabetical order ======= */


int     qh_argv_to_command(int argc, char *argv[], char* command, int max_size);
int     qh_argv_to_command_size(int argc, char *argv[]);
int     qh_rand(qhT *qh);
void    qh_srand(qhT *qh, int seed);
realT   qh_randomfactor(qhT *qh, realT scale, realT offset);
void    qh_randommatrix(qhT *qh, realT *buffer, int dim, realT **row);
int     qh_strtol(const char *s, char **endp);
double  qh_strtod(const char *s, char **endp);

#endif /* qhDEFrandom */



