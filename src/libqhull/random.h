/*<html><pre>  -<a                             href="qh-geom.htm"
  >-------------------------------</a><a name="TOP">-</a>

  random.h
    header file for random routines

   see qh-geom.htm and random.c

   Copyright (c) 1993-2011 The Geometry Center.
   $Id: //main/2011/qhull/src/libqhull/random.h#2 $$Change: 1342 $
   $DateTime: 2011/03/07 21:55:47 $$Author: bbarber $
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



