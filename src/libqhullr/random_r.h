/*<html><pre>  -<a                             href="qh-geom.htm"
  >-------------------------------</a><a name="TOP">-</a>

  random.h
    header file for random routines

   see qh-geom.htm and random.c

   Copyright (c) 1993-2014 The Geometry Center.
   $Id: //main/2011/qhull/src/libqhullr/random_r.h#2 $$Change: 1645 $
   $DateTime: 2014/01/15 12:51:30 $$Author: bbarber $
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



