/*<html><pre>  -<a                             href="qh-geom.htm"
  >-------------------------------</a><a name="TOP">-</a>

  random.h
    header file for random and utility routines

   see qh-geom.htm and random.c

   Copyright (c) 1993-2018 The Geometry Center.
   $Id: //main/2015/qhull/src/libqhull/random.h#4 $$Change: 2549 $
   $DateTime: 2018/12/28 22:24:20 $$Author: bbarber $
*/

#ifndef qhDEFrandom
#define qhDEFrandom 1

#include "libqhull.h"

/*============= prototypes in alphabetical order ======= */


int     qh_argv_to_command(int argc, char *argv[], char* command, int max_size);
int     qh_argv_to_command_size(int argc, char *argv[]);
int     qh_rand( void);
void    qh_srand( int seed);
realT   qh_randomfactor(realT scale, realT offset);
void    qh_randommatrix(realT *buffer, int dim, realT **row);
int     qh_strtol(const char *s, char **endp);
double  qh_strtod(const char *s, char **endp);

#endif /* qhDEFrandom */



