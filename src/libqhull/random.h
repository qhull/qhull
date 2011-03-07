/*<html><pre>  -<a                             href="qh-geom.htm"
  >-------------------------------</a><a name="TOP">-</a>

  random.h
    header file for random routines

   see qh-geom.htm and random.c

   copyright (c) 1993-2010 The Geometry Center.
   $Id: //main/2011/qhull/src/libqhull/random.h#1 $$Change: 1330 $
   $DateTime: 2011/03/06 21:30:00 $$Author: bbarber $
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



