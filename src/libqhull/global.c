
/*<html><pre>  -<a                             href="qh-globa.htm"
  >-------------------------------</a><a name="TOP">-</a>

   global.c
   initializes all the globals of the qhull application

   see README

   see libqhull.h for qh.globals and function prototypes

   see qhull_a.h for internal functions

   Copyright (c) 1993-2020 The Geometry Center.
   $Id: //main/2019/qhull/src/libqhull/global.c#18 $$Change: 3664 $
   $DateTime: 2024/07/22 23:55:01 $$Author: bbarber $
 */

#include "qhull_a.h"

/*========= qh definition -- globals defined in libqhull.h =======================*/

#if qh_QHpointer
qhT *qh_qh= NULL;       /* pointer to all global variables */
#else
qhT qh_qh;              /* all global variables.
                           Add "= {0}" if this causes a compiler error.
                           Also qh_qhstat in stat.c and qhmem in mem.c.  */
#endif

/*-<a                             href  ="qh-globa.htm#TOC"
  >--------------------------------</a><a name="version">-</a>

  qh_version
    version string by year and date
    qh_version2 for Unix users and -V

    the revision increases on code changes only

  notes:
    change date:    Changes.txt, Announce.txt, index.htm, README.txt,
                    qhull-news.html, Eudora signatures, CMakeLists.txt
    change version: README.txt, qh-get.htm, File_id.diz, Makefile.txt, CMakeLists.txt
    check that CMakeLists.txt @version is the same as qh_version2
    change year:    Copying.txt
    check download size
    recompile user_eg.c, rbox.c, libqhull.c, qconvex.c, qdelaun.c qvoronoi.c, qhalf.c, testqset.c
*/

const char qh_version[]= "2020.2 2023/01/02";
const char qh_version2[]= "qhull 8.1-alpha3 (2020.2 2023/01/02)";

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="appendprint">-</a>

  qh_appendprint( printFormat )
    append printFormat to qh.PRINTout unless already defined
*/
void qh_appendprint(qh_PRINT format) {
  int i;

  for (i=0; i < qh_PRINTEND; i++) {
    if (qh PRINTout[i] == format && format != qh_PRINTqhull)
      break;
    if (!qh PRINTout[i]) {
      qh PRINTout[i]= format;
      break;
    }
  }
} /* appendprint */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="checkflags">-</a>

  qh_checkflags( commandStr, hiddenFlags )
    errors if commandStr contains hiddenFlags
    hiddenFlags starts and ends with a space and is space delimited (checked)

  notes:
    ignores first word (e.g., "qconvex i")
    use qh_strtol/strtod since strtol/strtod may or may not skip trailing spaces

  see:
    qh_initflags() initializes Qhull according to commandStr
*/
void qh_checkflags(char *command, char *hiddenflags) {
  char *s= command, *t, *chkerr; /* qh_skipfilename is non-const */
  char key, opt, prevopt;
  char chkkey[]=  "   ";    /* check one character options ('s') */
  char chkopt[]=  "    ";   /* check two character options ('Ta') */
  char chkopt2[]= "     ";  /* check three character options ('Q12') */
  boolT waserr= False;

  if (*hiddenflags != ' ' || hiddenflags[strlen(hiddenflags)-1] != ' ') {
    qh_fprintf(qh ferr, 6026, "qhull internal error (qh_checkflags): hiddenflags must start and end with a space: \"%s\"\n", hiddenflags);
    qh_errexit(qh_ERRqhull, NULL, NULL);
  }
  if (strpbrk(hiddenflags, ",\n\r\t")) {
    qh_fprintf(qh ferr, 6027, "qhull internal error (qh_checkflags): hiddenflags contains commas, newlines, or tabs: \"%s\"\n", hiddenflags);
    qh_errexit(qh_ERRqhull, NULL, NULL);
  }
  while (*s && !isspace(*s))  /* skip program name */
    s++;
  while (*s) {
    while (*s && isspace(*s))
      s++;
    if (*s == '-')
      s++;
    if (!*s)
      break;
    key= *s++;
    chkerr= NULL;
    if (key == 'T' && (*s == 'I' || *s == 'O')) {  /* TI or TO 'file name' */
      s= qh_skipfilename(++s);
      continue;
    }
    chkkey[1]= key;
    if (strstr(hiddenflags, chkkey)) {
      chkerr= chkkey;
    }else if (isupper(key)) {
      opt= ' ';
      prevopt= ' ';
      chkopt[1]= key;
      chkopt2[1]= key;
      while (!chkerr && *s && !isspace(*s)) {
        opt= *s++;
        if (isalpha(opt)) {
          chkopt[2]= opt;
          if (strstr(hiddenflags, chkopt))
            chkerr= chkopt;
          if (prevopt != ' ') {
            chkopt2[2]= prevopt;
            chkopt2[3]= opt;
            if (strstr(hiddenflags, chkopt2))
              chkerr= chkopt2;
          }
        }else if (key == 'Q' && isdigit(opt) && prevopt != 'b'
              && (prevopt == ' ' || islower(prevopt))) {
            if (isdigit(*s)) {  /* Q12 */
              chkopt2[2]= opt;
              chkopt2[3]= *s++;
              if (strstr(hiddenflags, chkopt2))
                chkerr= chkopt2;
            }else {
              chkopt[2]= opt;
              if (strstr(hiddenflags, chkopt))
                chkerr= chkopt;
            }
        }else {
          qh_strtod(s-1, &t);
          if (s < t)
            s= t;
        }
        prevopt= opt;
      }
    }
    if (chkerr) {
      *chkerr= '\'';
      chkerr[strlen(chkerr)-1]=  '\'';
      qh_fprintf(qh ferr, 6029, "qhull option error: option %s is not used with this program.\n             It may be used with qhull.\n", chkerr);
      waserr= True;
    }
  }
  if (waserr)
    qh_errexit(qh_ERRinput, NULL, NULL);
} /* checkflags */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="clear_outputflags">-</a>

  qh_clear_outputflags( )
    Clear output flags for QhullPoints
*/
void qh_clear_outputflags(void) {
  int i,k;

  qh ANNOTATEoutput= False;
  qh DOintersections= False;
  qh DROPdim= -1;
  qh FORCEoutput= False;
  qh GETarea= False;
  qh GOODpoint= 0;
  qh GOODpointp= NULL;
  qh GOODthreshold= False;
  qh GOODvertex= 0;
  qh GOODvertexp= NULL;
  qh IStracing= 0;
  qh KEEParea= False;
  qh KEEPmerge= False;
  qh KEEPminArea= REALmax;
  qh PRINTcentrums= False;
  qh PRINTcoplanar= False;
  qh PRINTdots= False;
  qh PRINTgood= False;
  qh PRINTinner= False;
  qh PRINTneighbors= False;
  qh PRINTnoplanes= False;
  qh PRINToptions1st= False;
  qh PRINTouter= False;
  qh PRINTprecision= True;
  qh PRINTridges= False;
  qh PRINTspheres= False;
  qh PRINTstatistics= False;
  qh PRINTsummary= False;
  qh PRINTtransparent= False;
  qh SPLITthresholds= False;
  qh TRACElevel= 0;
  qh TRInormals= False;
  qh USEstdout= False;
  qh VERIFYoutput= False;
  for (k=qh input_dim+1; k--; ) {  /* duplicated in qh_initqhull_buffers and qh_clear_outputflags */
    qh lower_threshold[k]= -REALmax;
    qh upper_threshold[k]= REALmax;
    qh lower_bound[k]= -REALmax;
    qh upper_bound[k]= REALmax;
  }

  for (i=0; i < qh_PRINTEND; i++) {
    qh PRINTout[i]= qh_PRINTnone;
  }

  if (!qh qhull_commandsiz2)
      qh qhull_commandsiz2= (int)strlen(qh qhull_command); /* WARN64 */
  else {
      qh qhull_command[qh qhull_commandsiz2]= '\0';
  }
  if (!qh qhull_optionsiz2)
    qh qhull_optionsiz2= (int)strlen(qh qhull_options);  /* WARN64 */
  else {
    qh qhull_options[qh qhull_optionsiz2]= '\0';
    qh qhull_optionlen= qh_OPTIONline;  /* start a new line */
  }
} /* clear_outputflags */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="clock">-</a>

  qh_clock()
    return user CPU time in 100ths (qh_SECtick)
    only defined for qh_CLOCKtype == 2

  notes:
    use first value to determine time 0
    from Stevens '92 8.15
*/
unsigned long qh_clock(void) {

#if (qh_CLOCKtype == 2)
  struct tms time;
  static long clktck;  /* initialized first call and never updated */
  double ratio, cpu;
  unsigned long ticks;

  if (!clktck) {
    if ((clktck= sysconf(_SC_CLK_TCK)) < 0) {
      qh_fprintf(qh ferr, 6030, "qhull internal error (qh_clock): sysconf() failed.  Use qh_CLOCKtype 1 in user.h\n");
      qh_errexit(qh_ERRqhull, NULL, NULL);
    }
  }
  if (times(&time) == -1) {
    qh_fprintf(qh ferr, 6031, "qhull internal error (qh_clock): times() failed.  Use qh_CLOCKtype 1 in user.h\n");
    qh_errexit(qh_ERRqhull, NULL, NULL);
  }
  ratio= qh_SECticks / (double)clktck;
  ticks= time.tms_utime * ratio;
  return ticks;
#else
  qh_fprintf(qh ferr, 6032, "qhull internal error (qh_clock): use qh_CLOCKtype 2 in user.h\n");
  qh_errexit(qh_ERRqhull, NULL, NULL); /* never returns */
  return 0;
#endif
} /* clock */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="freebuffers">-</a>

  qh_freebuffers()
    free up global memory buffers

  notes:
    must match qh_initbuffers()
*/
void qh_freebuffers(void) {

  trace5((qh ferr, 5001, "qh_freebuffers: freeing up global memory buffers\n"));
  /* allocated by qh_initqhull_buffers */
  qh_setfree(&qh other_points);
  qh_setfree(&qh del_vertices);
  qh_setfree(&qh coplanarfacetset);
  qh_memfree(qh NEARzero, qh hull_dim * (int)sizeof(realT));
  qh_memfree(qh lower_threshold, (qh input_dim+1) * (int)sizeof(realT));
  qh_memfree(qh upper_threshold, (qh input_dim+1) * (int)sizeof(realT));
  qh_memfree(qh lower_bound, (qh input_dim+1) * (int)sizeof(realT));
  qh_memfree(qh upper_bound, (qh input_dim+1) * (int)sizeof(realT));
  qh_memfree(qh gm_matrix, (qh hull_dim+1) * qh hull_dim * (int)sizeof(coordT));
  qh_memfree(qh gm_row, (qh hull_dim+1) * (int)sizeof(coordT *));
  qh NEARzero= qh lower_threshold= qh upper_threshold= NULL;
  qh lower_bound= qh upper_bound= NULL;
  qh gm_matrix= NULL;
  qh gm_row= NULL;

  if (qh line)                /* allocated by qh_readinput, freed if no error */
    qh_free(qh line);
  if (qh half_space)
    qh_free(qh half_space);
  if (qh temp_malloc)
    qh_free(qh temp_malloc);
  if (qh feasible_point)      /* allocated by qh_readfeasible */
    qh_free(qh feasible_point);
  if (qh feasible_string)     /* allocated by qh_initflags */
    qh_free(qh feasible_string);
  qh line= qh feasible_string= NULL;
  qh half_space= qh feasible_point= qh temp_malloc= NULL;
  /* usually allocated by qh_readinput */
  if (qh first_point && qh POINTSmalloc) {
    qh_free(qh first_point);
    qh first_point= NULL;
  }
  if (qh input_points && qh input_malloc) { /* set by qh_joggleinput */
    qh_free(qh input_points);
    qh input_points= NULL;
  }
  trace5((qh ferr, 5002, "qh_freebuffers: finished\n"));
} /* freebuffers */


/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="freebuild">-</a>

  qh_freebuild( allmem )
    free global memory used by qh_initbuild and qh_buildhull
    if !allmem,
      does not free short memory (e.g., facetT, freed by qh_memfreeshort)

  design:
    free centrums
    free each vertex
    for each facet
      free ridges
      free outside set, coplanar set, neighbor set, ridge set, vertex set
      free facet
    free hash table
    free interior point
    free merge sets
    free temporary sets
*/
void qh_freebuild(boolT allmem) {
  facetT *facet, *previousfacet= NULL;
  vertexT *vertex, *previousvertex= NULL;
  ridgeT *ridge, **ridgep, *previousridge= NULL;
  mergeT *merge, **mergep;
  int newsize;
  boolT freeall;

  /* free qhT global sets first, includes references from qh_buildhull */
  trace5((qh ferr, 5004, "qh_freebuild: free global sets\n"));
  FOREACHmerge_(qh facet_mergeset)  /* usually empty */
    qh_memfree(merge, (int)sizeof(mergeT));
  FOREACHmerge_(qh degen_mergeset)  /* usually empty */
    qh_memfree(merge, (int)sizeof(mergeT));
  FOREACHmerge_(qh vertex_mergeset)  /* usually empty */
    qh_memfree(merge, (int)sizeof(mergeT));
  qh facet_mergeset= NULL;  /* temp set freed by qh_settempfree_all */
  qh degen_mergeset= NULL;  /* temp set freed by qh_settempfree_all */
  qh vertex_mergeset= NULL;  /* temp set freed by qh_settempfree_all */
  qh_setfree(&(qh hash_table));
  trace5((qh ferr, 5003, "qh_freebuild: free temporary sets (qh_settempfree_all)\n"));
  qh_settempfree_all();
  trace1((qh ferr, 1005, "qh_freebuild: free memory from qh_inithull and qh_buildhull\n"));
  if (qh del_vertices)
    qh_settruncate(qh del_vertices, 0);
  if (allmem) {
    while ((vertex= qh vertex_list)) {
      if (vertex->next)
        qh_delvertex(vertex);
      else {
        qh_memfree(vertex, (int)sizeof(vertexT)); /* sentinel */
        qh newvertex_list= qh vertex_list= NULL;
        break;
      }
      previousvertex= vertex; /* in case of memory fault */
      QHULL_UNUSED(previousvertex)
    }
  }else if (qh VERTEXneighbors) {
    FORALLvertices
      qh_setfreelong(&(vertex->neighbors));
  }
  qh VERTEXneighbors= False;
  qh GOODclosest= NULL;
  if (allmem) {
    FORALLfacets {
      FOREACHridge_(facet->ridges)
        ridge->seen= False;
    }
    while ((facet= qh facet_list)) {
      if (!facet->newfacet || !qh NEWtentative || qh_setsize(facet->ridges) > 1) { /* skip tentative horizon ridges */
        trace4((qh ferr, 4095, "qh_freebuild: delete the previously-seen ridges of f%d\n", facet->id));
        FOREACHridge_(facet->ridges) {
          if (ridge->seen)
            qh_delridge(ridge);
          else
            ridge->seen= True;
          previousridge= ridge; /* in case of memory fault */
          QHULL_UNUSED(previousridge)
        }
      }
      qh_setfree(&(facet->outsideset));
      qh_setfree(&(facet->coplanarset));
      qh_setfree(&(facet->neighbors));
      qh_setfree(&(facet->ridges));
      qh_setfree(&(facet->vertices));
      if (facet->next)
        qh_delfacet(facet);
      else {
        qh_memfree(facet, (int)sizeof(facetT));
        qh visible_list= qh newfacet_list= qh facet_list= NULL;
      }
      previousfacet= facet; /* in case of memory fault */
      QHULL_UNUSED(previousfacet)
    }
  }else {
    freeall= True;
    if (qh_setlarger_quick(qh hull_dim + 1, &newsize))
      freeall= False;
    FORALLfacets {
      qh_setfreelong(&(facet->outsideset));
      qh_setfreelong(&(facet->coplanarset));
      if (!facet->simplicial || freeall) {
        qh_setfreelong(&(facet->neighbors));
        qh_setfreelong(&(facet->ridges));
        qh_setfreelong(&(facet->vertices));
      }
    }
  }
  /* qh internal constants */
  qh_memfree(qh interior_point, qh normal_size);
  qh interior_point= NULL;
} /* freebuild */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="freeqhull">-</a>

  qh_freeqhull( allmem )
    see qh_freeqhull2
    if qh_QHpointer, frees qh_qh
*/
void qh_freeqhull(boolT allmem) {
    qh_freeqhull2(allmem);
#if qh_QHpointer
    qh_free(qh_qh);
    qh_qh= NULL;
#endif
}

/*-<a                             href="qh-globa.htm#TOC"
>-------------------------------</a><a name="freeqhull2">-</a>

qh_freeqhull2( allmem )
  free global memory and set qhT to 0
  if !allmem,
    does not free short memory (freed by qh_memfreeshort unless qh_NOmem)

notes:
  sets qh.NOerrexit in case caller forgets to
  Does not throw errors

see:
  see qh_initqhull_start2()

design:
  free global and temporary memory from qh_initbuild and qh_buildhull
  free buffers
  free statistics
*/
void qh_freeqhull2(boolT allmem) {

  qh NOerrexit= True;  /* no more setjmp since called at exit and ~QhullQh */
  trace1((qh ferr, 1006, "qh_freeqhull: free global memory\n"));
  qh_freebuild(allmem);
  qh_freebuffers();
  qh_freestatistics();
#if qh_QHpointer
  memset((char *)qh_qh, 0, sizeof(qhT));
  /* qh_qh freed by caller, qh_freeqhull() */
#else
  memset((char *)&qh_qh, 0, sizeof(qhT));
#endif
  qh NOerrexit= True;
} /* freeqhull2 */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="init_A">-</a>

  qh_init_A( infile, outfile, errfile, argc, argv )
    initialize memory and stdio files
    convert input options to option string (qh.qhull_command)

  notes:
    infile may be NULL if qh_readpoints() is not called

    errfile should always be defined.  It is used for reporting
    errors.  outfile is used for output and format options.

    argc/argv may be 0/NULL

    called before error handling initialized
    qh_errexit() may not be used
*/
void qh_init_A(FILE *infile, FILE *outfile, FILE *errfile, int argc, char *argv[]) {
  qh_meminit(errfile);
  qh_initqhull_start(infile, outfile, errfile);
  qh_init_qhull_command(argc, argv);
} /* init_A */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="init_B">-</a>

  qh_init_B( points, numpoints, dim, ismalloc )
    initialize globals for points array

    points has numpoints dim-dimensional points
      points[0] is the first coordinate of the first point
      points[1] is the second coordinate of the first point
      points[dim] is the first coordinate of the second point

    ismalloc=True
      Qhull will call qh_free(points) on exit or input transformation
    ismalloc=False
      Qhull will allocate a new point array if needed for input transformation

    qh.qhull_command
      is the option string.
      It is defined by qh_init_B(), qh_qhull_command(), or qh_initflags

  returns:
    if qh.PROJECTinput or (qh.DELAUNAY and qh.PROJECTdelaunay)
      projects the input to a new point array

        if qh.DELAUNAY,
          qh.hull_dim is increased by one
        if qh.ATinfinity,
          qh_projectinput adds point-at-infinity for Delaunay tri.

    if qh.SCALEinput
      changes the upper and lower bounds of the input, see qh_scaleinput

    if qh.ROTATEinput
      rotates the input by a random rotation, see qh_rotateinput
      if qh.DELAUNAY
        rotates about the last coordinate

  notes:
    called after points are defined
    qh_errexit() may be used
*/
void qh_init_B(coordT *points, int numpoints, int dim, boolT ismalloc) {
  qh_initqhull_globals(points, numpoints, dim, ismalloc);
  if (qhmem.LASTsize == 0)
    qh_initqhull_mem();
  /* mem.c and qset.c are initialized */
  qh_initqhull_buffers();
  qh_initthresholds(qh qhull_command);
  if (qh PROJECTinput || (qh DELAUNAY && qh PROJECTdelaunay))
    qh_projectinput();
  if (qh SCALEinput)
    qh_scaleinput();
  if (qh ROTATErandom >= 0) {
    qh_randommatrix(qh gm_matrix, qh hull_dim, qh gm_row);
    if (qh DELAUNAY) {
      int k, lastk= qh hull_dim-1;
      for (k=0; k < lastk; k++) {
        qh gm_row[k][lastk]= 0.0;
        qh gm_row[lastk][k]= 0.0;
      }
      qh gm_row[lastk][lastk]= 1.0;
    }
    qh_gram_schmidt(qh hull_dim, qh gm_row);
    qh_rotateinput(qh gm_row);
  }
} /* init_B */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="init_qhull_command">-</a>

  qh_init_qhull_command( argc, argv )
    build qh.qhull_command from argc/argv
    Calls qh_exit if qhull_command is too short

  returns:
    a space-delimited string of options (just as typed)

  notes:
    makes option string easy to input and output

    argc/argv may be 0/NULL
*/
void qh_init_qhull_command(int argc, char *argv[]) {

  if (!qh_argv_to_command(argc, argv, qh qhull_command, (int)sizeof(qh qhull_command))){
    /* Assumes qh.ferr is defined. */
    qh_fprintf(qh ferr, 6033, "qhull input error: more than %d characters in command line.\n",
          (int)sizeof(qh qhull_command));
    qh_exit(qh_ERRinput);  /* error reported, can not use qh_errexit */
  }
} /* init_qhull_command */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="initflags">-</a>

  qh_initflags( commandStr )
    set flags and initialized constants from commandStr
    calls qh_exit() if qh.NOerrexit

  returns:
    sets qh.qhull_command to command if needed

  notes:
    ignores first word (e.g., 'qhull' in "qhull d")
    use qh_strtol/strtod since strtol/strtod may or may not skip trailing spaces

  see:
    qh_initthresholds() continues processing of 'Pdn' and 'PDn'
    'prompt' in unix.c for documentation

  design:
    for each space-delimited option group
      if top-level option
        check syntax
        append appropriate option to option string
        set appropriate global variable or append printFormat to print options
      else
        for each sub-option
          check syntax
          append appropriate option to option string
          set appropriate global variable or append printFormat to print options
*/
void qh_initflags(char *command) {
  int k, i, lastproject;
  char *s= command, *t, *prev_s, *start, key, *lastwarning= NULL;
  boolT isgeom= False, wasproject;
  realT r;

  if(qh NOerrexit){
    qh_fprintf(qh ferr, 6245, "qhull internal error (qh_initflags): qh.NOerrexit was not cleared before calling qh_initflags().  It should be cleared after setjmp().  Exit qhull.\n");
    qh_exit(qh_ERRqhull);
  }
#ifdef qh_RANDOMdist
  qh RANDOMfactor= qh_RANDOMdist;
  qh_option("Random-qh_RANDOMdist", NULL, &qh RANDOMfactor);
  qh RANDOMdist= True;
#endif
  if (command <= &qh qhull_command[0] || command > &qh qhull_command[0] + sizeof(qh qhull_command)) {
    if (command != &qh qhull_command[0]) {
      *qh qhull_command= '\0';
      strncat(qh qhull_command, command, sizeof(qh qhull_command)-strlen(qh qhull_command)-1);
    }
    while (*s && !isspace(*s))  /* skip program name */
      s++;
  }
  if (qh_QHpointer)
    qh_option("qh_QHpointer", NULL, NULL);
  while (*s) {
    while (*s && isspace(*s))
      s++;
    if (*s == '-')
      s++;
    if (!*s)
      break;
    prev_s= s;
    switch (*s++) {
    case 'd':
      qh_option("delaunay", NULL, NULL);
      qh DELAUNAY= True;
      break;
    case 'f':
      qh_option("facets", NULL, NULL);
      qh_appendprint(qh_PRINTfacets);
      break;
    case 'i':
      qh_option("incidence", NULL, NULL);
      qh_appendprint(qh_PRINTincidences);
      break;
    case 'm':
      qh_option("mathematica", NULL, NULL);
      qh_appendprint(qh_PRINTmathematica);
      break;
    case 'n':
      qh_option("normals", NULL, NULL);
      qh_appendprint(qh_PRINTnormals);
      break;
    case 'o':
      qh_option("offFile", NULL, NULL);
      qh_appendprint(qh_PRINToff);
      break;
    case 'p':
      qh_option("points", NULL, NULL);
      qh_appendprint(qh_PRINTpoints);
      break;
    case 's':
      qh_option("summary", NULL, NULL);
      qh PRINTsummary= True;
      break;
    case 'v':
      qh_option("voronoi", NULL, NULL);
      qh VORONOI= True;
      qh DELAUNAY= True;
      break;
    case 'A':
      if (!isdigit(*s) && *s != '.' && *s != '-') {
        qh_fprintf(qh ferr, 7002, "qhull input warning: no maximum cosine angle given for option 'An'.  A1.0 is coplanar\n");
        lastwarning= s-1;
      }else {
        if (*s == '-') {
          qh premerge_cos= -qh_strtod(s, &s);
          qh_option("Angle-premerge-", NULL, &qh premerge_cos);
          qh PREmerge= True;
        }else {
          qh postmerge_cos= qh_strtod(s, &s);
          qh_option("Angle-postmerge", NULL, &qh postmerge_cos);
          qh POSTmerge= True;
        }
        qh MERGING= True;
      }
      break;
    case 'C':
      if (!isdigit(*s) && *s != '.' && *s != '-') {
        qh_fprintf(qh ferr, 7003, "qhull input warning: no centrum radius given for option 'Cn'\n");
        lastwarning= s-1;
      }else {
        if (*s == '-') {
          qh premerge_centrum= -qh_strtod(s, &s);
          qh_option("Centrum-premerge-", NULL, &qh premerge_centrum);
          qh PREmerge= True;
        }else {
          qh postmerge_centrum= qh_strtod(s, &s);
          qh_option("Centrum-postmerge", NULL, &qh postmerge_centrum);
          qh POSTmerge= True;
        }
        qh MERGING= True;
      }
      break;
    case 'E':
      if (*s == '-') {
        qh_fprintf(qh ferr, 6363, "qhull option error: expecting a positive number for maximum roundoff 'En'.  Got '%s'\n", s-1);
        qh_errexit(qh_ERRinput, NULL, NULL);
      }else if (!isdigit(*s)) {
        qh_fprintf(qh ferr, 7005, "qhull option warning: no maximum roundoff given for option 'En'\n");
        lastwarning= s-1;
      }else {
        qh DISTround= qh_strtod(s, &s);
        qh_option("Distance-roundoff", NULL, &qh DISTround);
        qh SETroundoff= True;
      }
      break;
    case 'H':
      start= s;
      qh HALFspace= True;
      qh_strtod(s, &t);
      while (t > s)  {
        if (*t && !isspace(*t)) {
          if (*t == ',')
            t++;
          else {
            qh_fprintf(qh ferr, 6364, "qhull option error: expecting 'Hn,n,n,...' for feasible point of halfspace intersection. Got '%s'\n", start-1);
            qh_errexit(qh_ERRinput, NULL, NULL);
          }
        }
        s= t;
        qh_strtod(s, &t);
      }
      if (start < t) {
        if (!(qh feasible_string= (char *)calloc((size_t)(t-start+1), (size_t)1))) {
          qh_fprintf(qh ferr, 6034, "qhull error: insufficient memory for 'Hn,n,n'\n");
          qh_errexit(qh_ERRmem, NULL, NULL);
        }
        strncpy(qh feasible_string, start, (size_t)(t-start));
        qh_option("Halfspace-about", NULL, NULL);
        qh_option(qh feasible_string, NULL, NULL);
      }else
        qh_option("Halfspace", NULL, NULL);
      break;
    case 'R':
      if (!isdigit(*s)) {
        qh_fprintf(qh ferr, 7007, "qhull option warning: missing random perturbation for option 'Rn'\n");
        lastwarning= s-1;
      }else {
        qh RANDOMfactor= qh_strtod(s, &s);
        qh_option("Random-perturb", NULL, &qh RANDOMfactor);
        qh RANDOMdist= True;
      }
      break;
    case 'V':
      if (!isdigit(*s) && *s != '-') {
        qh_fprintf(qh ferr, 7008, "qhull option warning: missing visible distance for option 'Vn'\n");
        lastwarning= s-1;
      }else {
        qh MINvisible= qh_strtod(s, &s);
        qh_option("Visible", NULL, &qh MINvisible);
      }
      break;
    case 'U':
      if (!isdigit(*s) && *s != '-') {
        qh_fprintf(qh ferr, 7009, "qhull option warning: missing coplanar distance for option 'Un'\n");
        lastwarning= s-1;
      }else {
        qh MAXcoplanar= qh_strtod(s, &s);
        qh_option("U-coplanar", NULL, &qh MAXcoplanar);
      }
      break;
    case 'W':
      if (*s == '-') {
        qh_fprintf(qh ferr, 6365, "qhull option error: expecting a positive number for outside width 'Wn'.  Got '%s'\n", s-1);
        qh_errexit(qh_ERRinput, NULL, NULL);
      }else if (!isdigit(*s)) {
        qh_fprintf(qh ferr, 7011, "qhull option warning: missing outside width for option 'Wn'\n");
        lastwarning= s-1;
      }else {
        qh MINoutside= qh_strtod(s, &s);
        qh_option("W-outside", NULL, &qh MINoutside);
        qh APPROXhull= True;
      }
      break;
    /************  sub menus ***************/
    case 'F':
      while (*s && !isspace(*s)) {
        switch (*s++) {
        case 'a':
          qh_option("Farea", NULL, NULL);
          qh_appendprint(qh_PRINTarea);
          qh GETarea= True;
          break;
        case 'A':
          qh_option("FArea-total", NULL, NULL);
          qh GETarea= True;
          break;
        case 'c':
          qh_option("Fcoplanars", NULL, NULL);
          qh_appendprint(qh_PRINTcoplanars);
          break;
        case 'C':
          qh_option("FCentrums", NULL, NULL);
          qh_appendprint(qh_PRINTcentrums);
          break;
        case 'd':
          qh_option("Fd-cdd-in", NULL, NULL);
          qh CDDinput= True;
          break;
        case 'D':
          qh_option("FD-cdd-out", NULL, NULL);
          qh CDDoutput= True;
          break;
        case 'F':
          qh_option("FFacets-xridge", NULL, NULL);
          qh_appendprint(qh_PRINTfacets_xridge);
          break;
        case 'i':
          qh_option("Finner", NULL, NULL);
          qh_appendprint(qh_PRINTinner);
          break;
        case 'I':
          qh_option("FIDs", NULL, NULL);
          qh_appendprint(qh_PRINTids);
          break;
        case 'm':
          qh_option("Fmerges", NULL, NULL);
          qh_appendprint(qh_PRINTmerges);
          break;
        case 'M':
          qh_option("FMaple", NULL, NULL);
          qh_appendprint(qh_PRINTmaple);
          break;
        case 'n':
          qh_option("Fneighbors", NULL, NULL);
          qh_appendprint(qh_PRINTneighbors);
          break;
        case 'N':
          qh_option("FNeighbors-vertex", NULL, NULL);
          qh_appendprint(qh_PRINTvneighbors);
          break;
        case 'o':
          qh_option("Fouter", NULL, NULL);
          qh_appendprint(qh_PRINTouter);
          break;
        case 'O':
          if (qh PRINToptions1st) {
            qh_option("FOptions", NULL, NULL);
            qh_appendprint(qh_PRINToptions);
          }else
            qh PRINToptions1st= True;
          break;
        case 'p':
          qh_option("Fpoint-intersect", NULL, NULL);
          qh_appendprint(qh_PRINTpointintersect);
          break;
        case 'P':
          qh_option("FPoint-nearest", NULL, NULL);
          qh_appendprint(qh_PRINTpointnearest);
          break;
        case 'Q':
          qh_option("FQhull", NULL, NULL);
          qh_appendprint(qh_PRINTqhull);
          break;
        case 's':
          qh_option("Fsummary", NULL, NULL);
          qh_appendprint(qh_PRINTsummary);
          break;
        case 'S':
          qh_option("FSize", NULL, NULL);
          qh_appendprint(qh_PRINTsize);
          qh GETarea= True;
          break;
        case 't':
          qh_option("Ftriangles", NULL, NULL);
          qh_appendprint(qh_PRINTtriangles);
          break;
        case 'v':
          /* option set in qh_initqhull_globals */
          qh_appendprint(qh_PRINTvertices);
          break;
        case 'V':
          qh_option("FVertex-average", NULL, NULL);
          qh_appendprint(qh_PRINTaverage);
          break;
        case 'x':
          qh_option("Fxtremes", NULL, NULL);
          qh_appendprint(qh_PRINTextremes);
          break;
        default:
          s--;
          qh_fprintf(qh ferr, 7012, "qhull option warning: unknown 'F' output option 'F%c', skip to next space\n", (int)s[0]);
          lastwarning= s-1;
          while (*++s && !isspace(*s));
          break;
        }
      }
      break;
    case 'G':
      isgeom= True;
      qh_appendprint(qh_PRINTgeom);
      while (*s && !isspace(*s)) {
        switch (*s++) {
        case 'a':
          qh_option("Gall-points", NULL, NULL);
          qh PRINTdots= True;
          break;
        case 'c':
          qh_option("Gcentrums", NULL, NULL);
          qh PRINTcentrums= True;
          break;
        case 'h':
          qh_option("Gintersections", NULL, NULL);
          qh DOintersections= True;
          break;
        case 'i':
          qh_option("Ginner", NULL, NULL);
          qh PRINTinner= True;
          break;
        case 'n':
          qh_option("Gno-planes", NULL, NULL);
          qh PRINTnoplanes= True;
          break;
        case 'o':
          qh_option("Gouter", NULL, NULL);
          qh PRINTouter= True;
          break;
        case 'p':
          qh_option("Gpoints", NULL, NULL);
          qh PRINTcoplanar= True;
          break;
        case 'r':
          qh_option("Gridges", NULL, NULL);
          qh PRINTridges= True;
          break;
        case 't':
          qh_option("Gtransparent", NULL, NULL);
          qh PRINTtransparent= True;
          break;
        case 'v':
          qh_option("Gvertices", NULL, NULL);
          qh PRINTspheres= True;
          break;
        case 'D':
          if (!isdigit(*s)) {
            qh_fprintf(qh ferr, 7004, "qhull option warning: missing dimension for option 'GDn'\n");
            lastwarning= s-2;
          }else {
            if (qh DROPdim >= 0) {
              qh_fprintf(qh ferr, 7013, "qhull option warning: can only drop one dimension.  Previous 'GD%d' ignored\n",
                   qh DROPdim);
              lastwarning= s-2;
            }
            qh DROPdim= qh_strtol(s, &s);
            qh_option("GDrop-dim", &qh DROPdim, NULL);
          }
          break;
        default:
          s--;
          qh_fprintf(qh ferr, 7014, "qhull option warning: unknown 'G' geomview option 'G%c', skip to next space\n", (int)s[0]);
          lastwarning= s-1;
          while (*++s && !isspace(*s));
          break;
        }
      }
      break;
    case 'P':
      while (*s && !isspace(*s)) {
        switch (*s++) {
        case 'd': case 'D':  /* see qh_initthresholds() */
          key= s[-1];
          i= qh_strtol(s, &s);
          r= 0;
          if (*s == ':') {
            s++;
            r= qh_strtod(s, &s);
          }
          if (key == 'd')
            qh_option("Pdrop-facets-dim-less", &i, &r);
          else
            qh_option("PDrop-facets-dim-more", &i, &r);
          break;
        case 'g':
          qh_option("Pgood-facets", NULL, NULL);
          qh PRINTgood= True;
          break;
        case 'G':
          qh_option("PGood-facet-neighbors", NULL, NULL);
          qh PRINTneighbors= True;
          break;
        case 'o':
          qh_option("Poutput-forced", NULL, NULL);
          qh FORCEoutput= True;
          break;
        case 'p':
          qh_option("Pprecision-ignore", NULL, NULL);
          qh PRINTprecision= False;
          break;
        case 'A':
          if (!isdigit(*s)) {
            qh_fprintf(qh ferr, 7006, "qhull option warning: missing facet count for keep area option 'PAn'\n");
            lastwarning= s-2;
          }else {
            qh KEEParea= qh_strtol(s, &s);
            qh_option("PArea-keep", &qh KEEParea, NULL);
            qh GETarea= True;
          }
          break;
        case 'F':
          if (!isdigit(*s)) {
            qh_fprintf(qh ferr, 7010, "qhull option warning: missing facet area for option 'PFn'\n");
            lastwarning= s-2;
          }else {
            qh KEEPminArea= qh_strtod(s, &s);
            qh_option("PFacet-area-keep", NULL, &qh KEEPminArea);
            qh GETarea= True;
          }
          break;
        case 'M':
          if (!isdigit(*s)) {
            qh_fprintf(qh ferr, 7090, "qhull option warning: missing merge count for option 'PMn'\n");
            lastwarning= s-2;
          }else {
            qh KEEPmerge= qh_strtol(s, &s);
            qh_option("PMerge-keep", &qh KEEPmerge, NULL);
          }
          break;
        default:
          s--;
          qh_fprintf(qh ferr, 7015, "qhull option warning: unknown 'P' print option 'P%c', skip to next space\n", (int)s[0]);
          lastwarning= s-1;
          while (*++s && !isspace(*s));
          break;
        }
      }
      break;
    case 'Q':
      lastproject= -1;
      while (*s && !isspace(*s)) {
        switch (*s++) {
        case 'a':
          qh_option("Qallow-short", NULL, NULL);
          qh ALLOWshort= True;
          break;
        case 'b': case 'B':  /* handled by qh_initthresholds */
          key= s[-1];
          if (key == 'b' && *s == 'B') {
            s++;
            r= qh_DEFAULTbox;
            qh SCALEinput= True;
            qh_option("QbBound-unit-box", NULL, &r);
            break;
          }
          if (key == 'b' && *s == 'b') {
            s++;
            qh SCALElast= True;
            qh_option("Qbbound-last", NULL, NULL);
            break;
          }
          k= qh_strtol(s, &s);
          r= 0.0;
          wasproject= False;
          if (*s == ':') {
            s++;
            if ((r= qh_strtod(s, &s)) == 0.0) {
              t= s;            /* need true dimension for memory allocation */
              while (*t && !isspace(*t)) {
                if (toupper(*t++) == 'B'
                 && k == qh_strtol(t, &t)
                 && *t++ == ':'
                 && qh_strtod(t, &t) == 0.0) {
                  qh PROJECTinput++;
                  trace2((qh ferr, 2004, "qh_initflags: project dimension %d\n", k));
                  qh_option("Qb-project-dim", &k, NULL);
                  wasproject= True;
                  lastproject= k;
                  break;
                }
              }
            }
          }
          if (!wasproject) {
            if (lastproject == k && r == 0.0)
              lastproject= -1;  /* doesn't catch all possible sequences */
            else if (key == 'b') {
              qh SCALEinput= True;
              if (r == 0.0)
                r= -qh_DEFAULTbox;
              qh_option("Qbound-dim-low", &k, &r);
            }else {
              qh SCALEinput= True;
              if (r == 0.0)
                r= qh_DEFAULTbox;
              qh_option("QBound-dim-high", &k, &r);
            }
          }
          break;
        case 'c':
          qh_option("Qcoplanar-keep", NULL, NULL);
          qh KEEPcoplanar= True;
          break;
        case 'f':
          qh_option("Qfurthest-outside", NULL, NULL);
          qh BESToutside= True;
          break;
        case 'g':
          qh_option("Qgood-facets-only", NULL, NULL);
          qh ONLYgood= True;
          break;
        case 'i':
          qh_option("Qinterior-keep", NULL, NULL);
          qh KEEPinside= True;
          break;
        case 'm':
          qh_option("Qmax-outside-only", NULL, NULL);
          qh ONLYmax= True;
          break;
        case 'r':
          qh_option("Qrandom-outside", NULL, NULL);
          qh RANDOMoutside= True;
          break;
        case 's':
          qh_option("Qsearch-initial-simplex", NULL, NULL);
          qh ALLpoints= True;
          break;
        case 't':
          qh_option("Qtriangulate", NULL, NULL);
          qh TRIangulate= True;
          break;
        case 'T':
          qh_option("QTestPoints", NULL, NULL);
          if (!isdigit(*s)) {
            qh_fprintf(qh ferr, 7091, "qhull option warning: missing number of test points for option 'QTn'\n");
            lastwarning= s-2;
          }else {
            qh TESTpoints= qh_strtol(s, &s);
            qh_option("QTestPoints", &qh TESTpoints, NULL);
          }
          break;
        case 'u':
          qh_option("QupperDelaunay", NULL, NULL);
          qh UPPERdelaunay= True;
          break;
        case 'v':
          qh_option("Qvertex-neighbors-convex", NULL, NULL);
          qh TESTvneighbors= True;
          break;
        case 'x':
          qh_option("Qxact-merge", NULL, NULL);
          qh MERGEexact= True;
          break;
        case 'z':
          qh_option("Qz-infinity-point", NULL, NULL);
          qh ATinfinity= True;
          break;
        case '0':
          qh_option("Q0-no-premerge", NULL, NULL);
          qh NOpremerge= True;
          break;
        case '1':
          if (!isdigit(*s)) {
            qh_option("Q1-angle-merge", NULL, NULL);
            qh ANGLEmerge= True;
            break;
          }
          switch (*s++) {
          case '0':
            qh_option("Q10-no-narrow", NULL, NULL);
            qh NOnarrow= True;
            break;
          case '1':
            qh_option("Q11-trinormals Qtriangulate", NULL, NULL);
            qh TRInormals= True;
            qh TRIangulate= True;
            break;
          case '2':
            qh_option("Q12-allow-wide", NULL, NULL);
            qh ALLOWwide= True;
            break;
          case '4':
#ifndef qh_NOmerge
            qh_option("Q14-merge-pinched-vertices", NULL, NULL);
            qh MERGEpinched= True;
#else
            /* ignore 'Q14' for q_benchmark testing of difficult cases for Qhull */
            qh_fprintf(qh ferr, 7099, "qhull option warning: option 'Q14-merge-pinched' disabled due to qh_NOmerge\n");
#endif
            break;
          case '7':
            qh_option("Q17-check-duplicates", NULL, NULL);
            qh CHECKduplicates= True;
            break;
          default:
            s--;
            qh_fprintf(qh ferr, 7016, "qhull option warning: unknown 'Q' qhull option 'Q1%c', skip to next space\n", (int)s[0]);
            lastwarning= s-1;
            while (*++s && !isspace(*s));
            break;
          }
          break;
        case '2':
          qh_option("Q2-no-merge-independent", NULL, NULL);
          qh MERGEindependent= False;
          goto LABELcheckdigit;
          break; /* no gcc warnings */
        case '3':
          qh_option("Q3-no-merge-vertices", NULL, NULL);
          qh MERGEvertices= False;
        LABELcheckdigit:
          if (isdigit(*s)) {
            qh_fprintf(qh ferr, 7017, "qhull option warning: can not follow '1', '2', or '3' with a digit.  'Q%c%c' skipped\n", *(s-1), *s);
            lastwarning= s-2;
            s++;
          }
          break;
        case '4':
          qh_option("Q4-avoid-old-into-new", NULL, NULL);
          qh AVOIDold= True;
          break;
        case '5':
          qh_option("Q5-no-check-outer", NULL, NULL);
          qh SKIPcheckmax= True;
          break;
        case '6':
          qh_option("Q6-no-concave-merge", NULL, NULL);
          qh SKIPconvex= True;
          break;
        case '7':
          qh_option("Q7-no-breadth-first", NULL, NULL);
          qh VIRTUALmemory= True;
          break;
        case '8':
          qh_option("Q8-no-near-inside", NULL, NULL);
          qh NOnearinside= True;
          break;
        case '9':
          qh_option("Q9-pick-furthest", NULL, NULL);
          qh PICKfurthest= True;
          break;
        case 'G':
          i= qh_strtol(s, &t);
          if (qh GOODpoint) {
            qh_fprintf(qh ferr, 7018, "qhull option warning: good point already defined for option 'QGn'.  Ignored\n");
            lastwarning= s-2;
          }else if (s == t) {
            qh_fprintf(qh ferr, 7019, "qhull option warning: missing good point id for option 'QGn'.  Ignored\n");
            lastwarning= s-2;
          }else if (i < 0 || *s == '-') {
            qh GOODpoint= i-1;
            qh_option("QGood-if-dont-see-point", &i, NULL);
          }else {
            qh GOODpoint= i+1;
            qh_option("QGood-if-see-point", &i, NULL);
          }
          s= t;
          break;
        case 'J':
          if (!isdigit(*s) && *s != '-')
            qh JOGGLEmax= 0.0;
          else {
            qh JOGGLEmax= (realT) qh_strtod(s, &s);
            qh_option("QJoggle", NULL, &qh JOGGLEmax);
          }
          break;
        case 'R':
          if (!isdigit(*s) && *s != '-') {
            qh_fprintf(qh ferr, 7020, "qhull option warning: missing random seed for option 'QRn'\n");
            lastwarning= s-2;
          }else {
            qh ROTATErandom= i= qh_strtol(s, &s);
            if (i > 0)
              qh_option("QRotate-id", &i, NULL );
            else if (i < -1)
              qh_option("QRandom-seed", &i, NULL );
          }
          break;
        case 'V':
          i= qh_strtol(s, &t);
          if (qh GOODvertex) {
            qh_fprintf(qh ferr, 7021, "qhull option warning: good vertex already defined for option 'QVn'.  Ignored\n");
            lastwarning= s-2;
          }else if (s == t) {
            qh_fprintf(qh ferr, 7022, "qhull option warning: no good point id given for option 'QVn'.  Ignored\n");
            lastwarning= s-2;
          }else if (i < 0) {
            qh GOODvertex= i - 1;
            qh_option("QV-good-facets-not-point", &i, NULL);
          }else {
            qh_option("QV-good-facets-point", &i, NULL);
            qh GOODvertex= i + 1;
          }
          s= t;
          break;
        case 'w':
          qh_option("Qwarn-allow", NULL, NULL);
          qh ALLOWwarning= True;
          break;
        default:
          s--;
          qh_fprintf(qh ferr, 7023, "qhull option warning: unknown 'Q' qhull option 'Q%c', skip to next space\n", (int)s[0]);
          lastwarning= s-1;
          while (*++s && !isspace(*s));
          break;
        }
      }
      break;
    case 'T':
      while (*s && !isspace(*s)) {
        if (isdigit(*s) || *s == '-')
          qh IStracing= qh_strtol(s, &s);
        else switch (*s++) {
        case 'a':
          qh_option("Tannotate-output", NULL, NULL);
          qh ANNOTATEoutput= True;
          break;
        case 'c':
          qh_option("Tcheck-frequently", NULL, NULL);
          qh CHECKfrequently= True;
          break;
        case 'f':
          qh_option("Tflush", NULL, NULL);
          qh FLUSHprint= True;
          break;
        case 's':
          qh_option("Tstatistics", NULL, NULL);
          qh PRINTstatistics= True;
          break;
        case 'v':
          qh_option("Tverify", NULL, NULL);
          qh VERIFYoutput= True;
          break;
        case 'z':
          if (qh ferr == qh_FILEstderr) {
            /* The C++ interface captures the output in qh_fprint_qhull() */
            qh_option("Tz-stdout", NULL, NULL);
            qh USEstdout= True;
          }else if (!qh fout) {
            qh_fprintf(qh ferr, 7024, "qhull option warning: output file undefined(stdout).  Option 'Tz' ignored.\n");
            lastwarning= s-2;
          }else {
            qh_option("Tz-stdout", NULL, NULL);
            qh USEstdout= True;
            qh ferr= qh fout;
            qhmem.ferr= qh fout;
          }
          break;
        case 'C':
          if (!isdigit(*s)) {
            qh_fprintf(qh ferr, 7025, "qhull option warning: missing point id for cone for trace option 'TCn'\n");
            lastwarning= s-2;
          }else {
            i= qh_strtol(s, &s);
            qh_option("TCone-stop", &i, NULL);
            qh STOPcone= i + 1;
          }
          break;
        case 'F':
          if (!isdigit(*s)) {
            qh_fprintf(qh ferr, 7026, "qhull option warning: missing frequency count for trace option 'TFn'\n");
            lastwarning= s-2;
          }else {
            qh REPORTfreq= qh_strtol(s, &s);
            qh_option("TFacet-log", &qh REPORTfreq, NULL);
            qh REPORTfreq2= qh REPORTfreq/2;  /* for tracemerging() */
          }
          break;
        case 'I':
          while (isspace(*s))
            s++;
          t= qh_skipfilename(s);
          {
            char filename[qh_FILENAMElen];

            qh_copyfilename(filename, (int)sizeof(filename), s, (int)(t-s));   /* WARN64 */
            s= t;
            if (!freopen(filename, "r", stdin)) {
              qh_fprintf(qh ferr, 6041, "qhull option error: cannot open 'TI' file \"%s\"\n", filename);
              qh_errexit(qh_ERRinput, NULL, NULL);
            }else {
              qh_option("TInput-file", NULL, NULL);
              qh_option(filename, NULL, NULL);
            }
          }
          break;
        case 'O':
          while (isspace(*s))
            s++;
          t= qh_skipfilename(s);
          {
            char filename[qh_FILENAMElen];

            qh_copyfilename(filename, (int)sizeof(filename), s, (int)(t-s));  /* WARN64 */
            if (!qh fout) {
              qh_fprintf(qh ferr, 7092, "qhull option warning: qh.fout was not set by caller of qh_initflags.  Cannot use option 'TO' to redirect output.  Ignoring option 'TO'\n");
              lastwarning= s-2;
            }else if (!freopen(filename, "w", qh fout)) {
              qh_fprintf(qh ferr, 6044, "qhull option error: cannot open file \"%s\" for writing as option 'TO'.  It is already in use or read-only\n", filename);
              qh_errexit(qh_ERRinput, NULL, NULL);
            }else {
              qh_option("TOutput-file", NULL, NULL);
              qh_option(filename, NULL, NULL);
            }
            s= t;
          }
          break;
        case 'A':
          if (!isdigit(*s)) {
            qh_fprintf(qh ferr, 7093, "qhull option warning: missing count of added points for trace option 'TAn'\n");
            lastwarning= s-2;
          }else {
            i= qh_strtol(s, &t);
            qh STOPadd= i + 1;
            qh_option("TA-stop-add", &i, NULL);
          }
          s= t;
          break;
        case 'P':
          if (*s == '-') {
            if (s[1] == '1' && !isdigit(s[2])) {
              s += 2;
              qh TRACEpoint= qh_IDunknown; /* qh_buildhull done */
              qh_option("Trace-point", &qh TRACEpoint, NULL);
            }else {
              qh_fprintf(qh ferr, 7100, "qhull option warning: negative point id for trace option 'TPn'.  Expecting 'TP-1' for tracing after qh_buildhull and qh_postmerge\n");
              lastwarning= s-2;
              while (isdigit(*(++s)))
                ; /* skip digits */
            }
          }else if (!isdigit(*s)) {
            qh_fprintf(qh ferr, 7029, "qhull option warning: missing point id or -1 for trace option 'TPn'\n");
            lastwarning= s-2;
          }else {
            qh TRACEpoint= qh_strtol(s, &s);
            qh_option("Trace-point", &qh TRACEpoint, NULL);
          }
          break;
        case 'M':
          if (!isdigit(*s)) {
            qh_fprintf(qh ferr, 7030, "qhull option warning: missing merge id for trace option 'TMn'\n");
            lastwarning= s-2;
          }else {
            qh TRACEmerge= qh_strtol(s, &s);
            qh_option("Trace-merge", &qh TRACEmerge, NULL);
          }
          break;
        case 'R':
          if (!isdigit(*s)) {
            qh_fprintf(qh ferr, 7031, "qhull option warning: missing rerun count for trace option 'TRn'\n");
            lastwarning= s-2;
          }else {
            qh RERUN= qh_strtol(s, &s);
            qh_option("TRerun", &qh RERUN, NULL);
          }
          break;
        case 'V':
          i= qh_strtol(s, &t);
          if (s == t) {
            qh_fprintf(qh ferr, 7032, "qhull option warning: missing furthest point id for trace option 'TVn'\n");
            lastwarning= s-2;
          }else if (i < 0) {
            qh STOPpoint= i - 1;
            qh_option("TV-stop-before-point", &i, NULL);
          }else {
            qh STOPpoint= i + 1;
            qh_option("TV-stop-after-point", &i, NULL);
          }
          s= t;
          break;
        case 'W':
          if (!isdigit(*s)) {
            qh_fprintf(qh ferr, 7033, "qhull option warning: missing max width for trace option 'TWn'\n");
            lastwarning= s-2;
          }else {
            qh TRACEdist= (realT) qh_strtod(s, &s);
            qh_option("TWide-trace", NULL, &qh TRACEdist);
          }
          break;
        default:
          s--;
          qh_fprintf(qh ferr, 7034, "qhull option warning: unknown 'T' trace option 'T%c', skip to next space\n", (int)s[0]);
          lastwarning= s-2;
          while (*++s && !isspace(*s));
          break;
        }
      }
      break;
    default:
      qh_fprintf(qh ferr, 7094, "qhull option warning: unknown option '%c'(%x)\n",
        (int)s[-1], (int)s[-1]);
      lastwarning= s-2;
      break;
    }
    if (s-1 == prev_s && *s && !isspace(*s)) {
      qh_fprintf(qh ferr, 7036, "qhull option warning: missing space after option '%c'(%x), reserved for sub-options, ignoring '%c' options to next space\n",
               (int)*prev_s, (int)*prev_s, (int)*prev_s);
      lastwarning= s-1;
      while (*s && !isspace(*s))
        s++;
    }
  }
  if (qh STOPcone && qh JOGGLEmax < REALmax/2) {
    qh_fprintf(qh ferr, 7078, "qhull option warning: 'TCn' (stopCone) ignored when used with 'QJn' (joggle)\n");
    lastwarning= command;
  }
  if (isgeom && !qh FORCEoutput && qh PRINTout[1]) {
    qh_fprintf(qh ferr, 7037, "qhull option warning: additional output formats ('Fc',etc.) are not compatible with Geomview ('G').  Use option 'Po' to override\n");
    lastwarning= command;
  }
  if (lastwarning && !qh ALLOWwarning) {
    qh_fprintf(qh ferr, 6035, "qhull option error: see previous warnings, use 'Qw' to override: '%s' (last offset %d)\n",
          command, (int)(lastwarning-command));
    qh_errexit(qh_ERRinput, NULL, NULL);
  }
  trace4((qh ferr, 4093, "qh_initflags: option flags initialized\n"));
  /* set derived values in qh_initqhull_globals */
} /* initflags */


/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="initqhull_buffers">-</a>

  qh_initqhull_buffers( )
    initialize global memory buffers

  notes:
    must match qh_freebuffers()
*/
void qh_initqhull_buffers(void) {
  int k;

  qh TEMPsize= (qhmem.LASTsize - (int)sizeof(setT))/SETelemsize;
  if (qh TEMPsize <= 0 || qh TEMPsize > qhmem.LASTsize)
    qh TEMPsize= 8;  /* e.g., if qh_NOmem */
  qh other_points= qh_setnew(qh TEMPsize);
  qh del_vertices= qh_setnew(qh TEMPsize);
  qh coplanarfacetset= qh_setnew(qh TEMPsize);
  qh NEARzero= (realT *)qh_memalloc(qh hull_dim * (int)sizeof(realT));
  qh lower_threshold= (realT *)qh_memalloc((qh input_dim+1) * (int)sizeof(realT));
  qh upper_threshold= (realT *)qh_memalloc((qh input_dim+1) * (int)sizeof(realT));
  qh lower_bound= (realT *)qh_memalloc((qh input_dim+1) * (int)sizeof(realT));
  qh upper_bound= (realT *)qh_memalloc((qh input_dim+1) * (int)sizeof(realT));
  for (k=qh input_dim+1; k--; ) {  /* duplicated in qh_initqhull_buffers and qh_clear_outputflags */
    qh lower_threshold[k]= -REALmax;
    qh upper_threshold[k]= REALmax;
    qh lower_bound[k]= -REALmax;
    qh upper_bound[k]= REALmax;
  }
  qh gm_matrix= (coordT *)qh_memalloc((qh hull_dim+1) * qh hull_dim * (int)sizeof(coordT));
  qh gm_row= (coordT **)qh_memalloc((qh hull_dim+1) * (int)sizeof(coordT *));
} /* initqhull_buffers */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="initqhull_globals">-</a>

  qh_initqhull_globals( points, numpoints, dim, ismalloc )
    initialize globals
    if ismalloc
      points were malloc'd and qhull should free at end

  returns:
    sets qh.first_point, num_points, input_dim, hull_dim and others
    seeds random number generator (seed=1 if tracing)
    modifies qh.hull_dim if ((qh.DELAUNAY and qh.PROJECTdelaunay) or qh.PROJECTinput)
    adjust user flags as needed
    also checks DIM3 dependencies and constants

  notes:
    do not use qh_point() since an input transformation may move them elsewhere
    qh_initqhull_start() sets default values for non-zero globals
    consider duplicate error checks in qh_readpoints.  It is called before qh_initqhull_globals

  design:
    initialize points array from input arguments
    test for qh.ZEROcentrum
      (i.e., use opposite vertex instead of cetrum for convexity testing)
    initialize qh.CENTERtype, qh.normal_size,
      qh.center_size, qh.TRACEpoint/level,
    initialize and test random numbers
    qh_initqhull_outputflags() -- adjust and test output flags
*/
void qh_initqhull_globals(coordT *points, int numpoints, int dim, boolT ismalloc) {
  int seed, pointsneeded, extra= 0, i, randi, k;
  realT randr;
  realT factorial;

  time_t timedata;

  trace0((qh ferr, 13, "qh_initqhull_globals: for %s | %s\n", qh rbox_command,
      qh qhull_command));
  if (numpoints < 1 || numpoints > qh_POINTSmax) {
    qh_fprintf(qh ferr, 6412, "qhull input error (qh_initqhull_globals): expecting between 1 and %d points.  Got %d %d-d points\n",
      qh_POINTSmax, numpoints, dim);
    qh_errexit(qh_ERRinput, NULL, NULL);
    /* same error message in qh_readpoints */
  }
  qh POINTSmalloc= ismalloc;
  qh first_point= points;
  qh num_points= numpoints;
  qh hull_dim= qh input_dim= dim;
  if (!qh NOpremerge && !qh MERGEexact && !qh PREmerge && qh JOGGLEmax > REALmax/2) {
    qh MERGING= True;
    if (qh hull_dim <= 4) {
      qh PREmerge= True;
      qh_option("_pre-merge", NULL, NULL);
    }else {
      qh MERGEexact= True;
      qh_option("Qxact-merge", NULL, NULL);
    }
  }else if (qh MERGEexact)
    qh MERGING= True;
  if (qh NOpremerge && (qh MERGEexact || qh PREmerge))
    qh_fprintf(qh ferr, 7095, "qhull option warning: 'Q0-no-premerge' ignored due to exact merge ('Qx') or pre-merge ('C-n' or 'A-n')\n");
  if (!qh NOpremerge && qh JOGGLEmax > REALmax/2) {
#ifdef qh_NOmerge
    qh JOGGLEmax= 0.0;
#endif
  }
  if (qh TRIangulate && qh JOGGLEmax < REALmax/2 && !qh PREmerge && !qh POSTmerge && qh PRINTprecision)
    qh_fprintf(qh ferr, 7038, "qhull option warning: joggle ('QJ') produces simplicial output (i.e., triangles in 2-D).  Unless merging is requested, option 'Qt' has no effect\n");
  if (qh JOGGLEmax < REALmax/2 && qh DELAUNAY && !qh SCALEinput && !qh SCALElast) {
    qh SCALElast= True;
    qh_option("Qbbound-last-qj", NULL, NULL);
  }
  if (qh MERGING && !qh POSTmerge && qh premerge_cos > REALmax/2
  && qh premerge_centrum == 0.0) {
    qh ZEROcentrum= True;
    qh ZEROall_ok= True;
    qh_option("_zero-centrum", NULL, NULL);
  }
  if (qh JOGGLEmax < REALmax/2 && REALepsilon > 2e-8 && qh PRINTprecision)
    qh_fprintf(qh ferr, 7039, "qhull warning: real epsilon, %2.2g, is probably too large for joggle('QJn')\nRecompile with double precision reals(see user.h).\n",
          REALepsilon);
#ifdef qh_NOmerge
  if (qh MERGING) {
    qh_fprintf(qh ferr, 6045, "qhull option error: merging not installed (qh_NOmerge) for 'Qx', 'Cn' or 'An')\n");
    qh_errexit(qh_ERRinput, NULL, NULL);
  }
#endif
  if (qh DELAUNAY && qh KEEPcoplanar && !qh KEEPinside) {
    qh KEEPinside= True;
    qh_option("Qinterior-keep", NULL, NULL);
  }
  if (qh VORONOI && !qh DELAUNAY) {
    qh_fprintf(qh ferr, 6038, "qhull internal error (qh_initqhull_globals): if qh.VORONOI is set, qh.DELAUNAY must be set.  Qhull constructs the Delaunay triangulation in order to compute the Voronoi diagram\n");
    qh_errexit(qh_ERRqhull, NULL, NULL);
  }
  if (qh DELAUNAY && qh HALFspace) {
    qh_fprintf(qh ferr, 6046, "qhull option error: can not use Delaunay('d') or Voronoi('v') with halfspace intersection('H')\n");
    qh_errexit(qh_ERRinput, NULL, NULL);
    /* same error message in qh_readpoints */
  }
  if (!qh DELAUNAY && (qh UPPERdelaunay || qh ATinfinity)) {
    qh_fprintf(qh ferr, 6047, "qhull option error: use upper-Delaunay('Qu') or infinity-point('Qz') with Delaunay('d') or Voronoi('v')\n");
    qh_errexit(qh_ERRinput, NULL, NULL);
  }
  if (qh UPPERdelaunay && qh ATinfinity) {
    qh_fprintf(qh ferr, 6048, "qhull option error: can not use infinity-point('Qz') with upper-Delaunay('Qu')\n");
    qh_errexit(qh_ERRinput, NULL, NULL);
  }
  if (qh MERGEpinched && qh ONLYgood) {
    qh_fprintf(qh ferr, 6362, "qhull option error: can not use merge-pinched-vertices ('Q14') with good-facets-only ('Qg')\n");
    qh_errexit(qh_ERRinput, NULL, NULL);
  }
  if (qh MERGEpinched && qh hull_dim == 2) {
    trace2((qh ferr, 2108, "qh_initqhull_globals: disable qh.MERGEpinched for 2-d.  It has no effect"))
    qh MERGEpinched= False;
  }
  if (qh SCALElast && !qh DELAUNAY && qh PRINTprecision)
    qh_fprintf(qh ferr, 7040, "qhull option warning: option 'Qbb' (scale-last-coordinate) is normally used with 'd' or 'v'\n");
  qh DOcheckmax= (!qh SKIPcheckmax && (qh MERGING || qh APPROXhull));
  qh KEEPnearinside= (qh DOcheckmax && !(qh KEEPinside && qh KEEPcoplanar)
                          && !qh NOnearinside);
  if (qh MERGING)
    qh CENTERtype= qh_AScentrum;
  else if (qh VORONOI)
    qh CENTERtype= qh_ASvoronoi;
  if (qh TESTvneighbors && !qh MERGING) {
    qh_fprintf(qh ferr, 6049, "qhull option error: test vertex neighbors('Qv') needs a merge option\n");
    qh_errexit(qh_ERRinput, NULL ,NULL);
  }
  if (qh PROJECTinput || (qh DELAUNAY && qh PROJECTdelaunay)) {
    qh hull_dim -= qh PROJECTinput;
    if (qh DELAUNAY) {
      qh hull_dim++;
      if (qh ATinfinity)
        extra= 1;
    }
  }
  if (qh hull_dim <= 1) {
    qh_fprintf(qh ferr, 6050, "qhull error: dimension %d must be > 1\n", qh hull_dim);
    qh_errexit(qh_ERRinput, NULL, NULL);
  }
  for (k=2, factorial=1.0; k < qh hull_dim; k++)
    factorial *= k;
  qh AREAfactor= 1.0 / factorial;
  trace2((qh ferr, 2005, "qh_initqhull_globals: initialize globals.  input_dim %d, numpoints %d, malloc? %d, projected %d to hull_dim %d\n",
        qh input_dim, numpoints, ismalloc, qh PROJECTinput, qh hull_dim));
  qh normal_size= qh hull_dim * (int)sizeof(coordT);
  qh center_size= qh normal_size - (int)sizeof(coordT);
  pointsneeded= qh hull_dim+1;
  if (qh hull_dim > qh_DIMmergeVertex) {
    qh MERGEvertices= False;
    qh_option("Q3-no-merge-vertices-dim-high", NULL, NULL);
  }
  if (qh GOODpoint)
    pointsneeded++;
#ifdef qh_NOtrace
  if (qh IStracing || qh TRACEmerge || qh TRACEpoint != qh_IDnone || qh TRACEdist < REALmax/2) {
      qh_fprintf(qh ferr, 6051, "qhull option error: tracing is not installed (qh_NOtrace in user.h).  Trace options 'Tn', 'TMn', 'TPn' and 'TWn' mostly removed.  Continue with 'Qw' (allow warning)\n");
      if (!qh ALLOWwarning)
        qh_errexit(qh_ERRinput, NULL, NULL);
  }
#endif
  if (qh RERUN > 1) {
    qh TRACElastrun= qh IStracing; /* qh_build_withrestart duplicates next conditional */
    if (qh IStracing && qh IStracing != -1) {
      qh_fprintf(qh ferr, 8162, "qh_initqhull_globals: trace last of TR%d runs at level %d\n", qh RERUN, qh IStracing);
      qh IStracing= 0;
    }
  }else if (qh TRACEpoint != qh_IDnone || qh TRACEdist < REALmax/2 || qh TRACEmerge) {
    qh TRACElevel= (qh IStracing ? qh IStracing : 3);
    qh IStracing= 0;
  }
  if (qh ROTATErandom == 0 || qh ROTATErandom == -1) {
    seed= (int)time(&timedata);
    if (qh ROTATErandom  == -1) {
      seed= -seed;
      qh_option("QRandom-seed", &seed, NULL );
    }else
      qh_option("QRotate-random", &seed, NULL);
    qh ROTATErandom= seed;
  }
  seed= qh ROTATErandom;
  if (seed == INT_MIN)    /* default value */
    seed= 1;
  else if (seed < 0)
    seed= -seed;
  qh_RANDOMseed_(seed);
  randr= 0.0;
  for (i=1000; i--; ) {
    randi= qh_RANDOMint;
    randr += randi;
    if (randi > qh_RANDOMmax) {
      qh_fprintf(qh ferr, 8036, "\
qhull configuration error (qh_RANDOMmax in user.h): random integer %d > qh_RANDOMmax (%.8g)\n",
               randi, qh_RANDOMmax);
      qh_errexit(qh_ERRinput, NULL, NULL);
    }
  }
  qh_RANDOMseed_(seed);
  randr= randr/1000;
  if (randr < qh_RANDOMmax * 0.1
  || randr > qh_RANDOMmax * 0.9)
    qh_fprintf(qh ferr, 8037, "\
qhull configuration warning (qh_RANDOMmax in user.h): average of 1000 random integers (%.2g) is much different than expected (%.2g).  Is qh_RANDOMmax (%.2g) wrong?\n",
             randr, qh_RANDOMmax * 0.5, qh_RANDOMmax);
  qh RANDOMa= 2.0 * qh RANDOMfactor/qh_RANDOMmax;
  qh RANDOMb= 1.0 - qh RANDOMfactor;
  if (qh_HASHfactor < 1.1) {
    qh_fprintf(qh ferr, 6052, "qhull internal error (qh_initqhull_globals): qh_HASHfactor %d must be at least 1.1.  Qhull uses linear hash probing\n",
      qh_HASHfactor);
    qh_errexit(qh_ERRqhull, NULL, NULL);
  }
  if (numpoints+extra < pointsneeded) {
    qh_fprintf(qh ferr, 6214, "qhull input error: not enough points(%d) to construct initial simplex (need %d)\n",
            numpoints, pointsneeded);
    qh_errexit(qh_ERRinput, NULL, NULL);
  }
  qh_initqhull_outputflags();
} /* initqhull_globals */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="initqhull_mem">-</a>

  qh_initqhull_mem( )
    initialize mem.c for qhull
    qh.hull_dim and qh.normal_size determine some of the allocation sizes
    if qh.MERGING,
      includes ridgeT
    calls qh_user_memsizes (user.c) to add up to 10 additional sizes for quick allocation
      (see numsizes below)

  returns:
    mem.c already for qh_memalloc/qh_memfree (errors if called beforehand)

  notes:
    qh_produceoutput() prints memsizes

*/
void qh_initqhull_mem(void) {
  int numsizes;
  int i;

  numsizes= 8+10;
  qh_meminitbuffers(qh IStracing, qh_MEMalign, numsizes,
                     qh_MEMbufsize, qh_MEMinitbuf);
  qh_memsize((int)sizeof(vertexT));
  if (qh MERGING) {
    qh_memsize((int)sizeof(ridgeT));
    qh_memsize((int)sizeof(mergeT));
  }
  qh_memsize((int)sizeof(facetT));
  i= (int)sizeof(setT) + (qh hull_dim - 1) * SETelemsize;  /* ridge.vertices */
  qh_memsize(i);
  qh_memsize(qh normal_size);        /* normal */
  i += SETelemsize;                 /* facet.vertices, .ridges, .neighbors */
  qh_memsize(i);
  qh_user_memsizes();
  qh_memsetup();
} /* initqhull_mem */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="initqhull_outputflags">-</a>

  qh_initqhull_outputflags
    initialize flags concerned with output

  returns:
    adjust user flags as needed

  see:
    qh_clear_outputflags() resets the flags

  design:
    test for qh.PRINTgood (i.e., only print 'good' facets)
    check for conflicting print output options
*/
void qh_initqhull_outputflags(void) {
  boolT printgeom= False, printmath= False, printcoplanar= False;
  int i;

  trace3((qh ferr, 3024, "qh_initqhull_outputflags: %s\n", qh qhull_command));
  if (!(qh PRINTgood || qh PRINTneighbors)) {
    if (qh DELAUNAY || qh KEEParea || qh KEEPminArea < REALmax/2 || qh KEEPmerge
        || (!qh ONLYgood && (qh GOODvertex || qh GOODpoint))) {
      qh PRINTgood= True;
      qh_option("Pgood", NULL, NULL);
    }
  }
  if (qh PRINTtransparent) {
    if (qh hull_dim != 4 || !qh DELAUNAY || qh VORONOI || qh DROPdim >= 0) {
      qh_fprintf(qh ferr, 6215, "qhull option error: transparent Delaunay('Gt') needs 3-d Delaunay('d') w/o 'GDn'\n");
      qh_errexit(qh_ERRinput, NULL, NULL);
    }
    qh DROPdim= 3;
    qh PRINTridges= True;
  }
  for (i=qh_PRINTEND; i--; ) {
    if (qh PRINTout[i] == qh_PRINTgeom)
      printgeom= True;
    else if (qh PRINTout[i] == qh_PRINTmathematica || qh PRINTout[i] == qh_PRINTmaple)
      printmath= True;
    else if (qh PRINTout[i] == qh_PRINTcoplanars)
      printcoplanar= True;
    else if (qh PRINTout[i] == qh_PRINTpointnearest)
      printcoplanar= True;
    else if (qh PRINTout[i] == qh_PRINTpointintersect && !qh HALFspace) {
      qh_fprintf(qh ferr, 6053, "qhull option error: option 'Fp' is only used for \nhalfspace intersection('Hn,n,n').\n");
      qh_errexit(qh_ERRinput, NULL, NULL);
    }else if (qh PRINTout[i] == qh_PRINTtriangles && (qh HALFspace || qh VORONOI)) {
      qh_fprintf(qh ferr, 6054, "qhull option error: option 'Ft' is not available for Voronoi vertices ('v') or halfspace intersection ('H')\n");
      qh_errexit(qh_ERRinput, NULL, NULL);
    }else if (qh PRINTout[i] == qh_PRINTcentrums && qh VORONOI) {
      qh_fprintf(qh ferr, 6055, "qhull option error: option 'FC' is not available for Voronoi vertices('v')\n");
      qh_errexit(qh_ERRinput, NULL, NULL);
    }else if (qh PRINTout[i] == qh_PRINTvertices) {
      if (qh VORONOI)
        qh_option("Fvoronoi", NULL, NULL);
      else
        qh_option("Fvertices", NULL, NULL);
    }
  }
  if (printcoplanar && qh DELAUNAY && qh JOGGLEmax < REALmax/2) {
    if (qh PRINTprecision)
      qh_fprintf(qh ferr, 7041, "qhull option warning: 'QJ' (joggle) will usually prevent coincident input sites for options 'Fc' and 'FP'\n");
  }
  if (printmath && (qh hull_dim > 3 || qh VORONOI)) {
    qh_fprintf(qh ferr, 6056, "qhull option error: Mathematica and Maple output is only available for 2-d and 3-d convex hulls and 2-d Delaunay triangulations\n");
    qh_errexit(qh_ERRinput, NULL, NULL);
  }
  if (printgeom) {
    if (qh hull_dim > 4) {
      qh_fprintf(qh ferr, 6057, "qhull option error: Geomview output is only available for 2-d, 3-d and 4-d\n");
      qh_errexit(qh_ERRinput, NULL, NULL);
    }
    if (qh PRINTnoplanes && !(qh PRINTcoplanar + qh PRINTcentrums
     + qh PRINTdots + qh PRINTspheres + qh DOintersections + qh PRINTridges)) {
      qh_fprintf(qh ferr, 6058, "qhull option error: no output specified for Geomview\n");
      qh_errexit(qh_ERRinput, NULL, NULL);
    }
    if (qh VORONOI && (qh hull_dim > 3 || qh DROPdim >= 0)) {
      qh_fprintf(qh ferr, 6059, "qhull option error: Geomview output for Voronoi diagrams only for 2-d\n");
      qh_errexit(qh_ERRinput, NULL, NULL);
    }
    /* can not warn about furthest-site Geomview output: no lower_threshold */
    if (qh hull_dim == 4 && qh DROPdim == -1 &&
        (qh PRINTcoplanar || qh PRINTspheres || qh PRINTcentrums)) {
      qh_fprintf(qh ferr, 7042, "qhull option warning: coplanars, vertices, and centrums output not available for 4-d output(ignored).  Could use 'GDn' instead.\n");
      qh PRINTcoplanar= qh PRINTspheres= qh PRINTcentrums= False;
    }
  }
  if (!qh KEEPcoplanar && !qh KEEPinside && !qh ONLYgood) {
    if ((qh PRINTcoplanar && qh PRINTspheres) || printcoplanar) {
      if (qh QHULLfinished) {
        qh_fprintf(qh ferr, 7072, "qhull output warning: ignoring coplanar points, option 'Qc' was not set for the first run of qhull.\n");
      }else {
        qh KEEPcoplanar= True;
        qh_option("Qcoplanar", NULL, NULL);
      }
    }
  }
  qh PRINTdim= qh hull_dim;
  if (qh DROPdim >=0) {    /* after Geomview checks */
    if (qh DROPdim < qh hull_dim) {
      qh PRINTdim--;
      if (!printgeom || qh hull_dim < 3)
        qh_fprintf(qh ferr, 7043, "qhull option warning: drop dimension 'GD%d' is only available for 3-d/4-d Geomview\n", qh DROPdim);
    }else
      qh DROPdim= -1;
  }else if (qh VORONOI) {
    qh DROPdim= qh hull_dim-1;
    qh PRINTdim= qh hull_dim-1;
  }
} /* qh_initqhull_outputflags */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="initqhull_start">-</a>

  qh_initqhull_start( infile, outfile, errfile )
    allocate memory if needed and call qh_initqhull_start2()
*/
void qh_initqhull_start(FILE *infile, FILE *outfile, FILE *errfile) {

#if qh_QHpointer
  if (qh_qh) {
    qh_fprintf(errfile, 6205, "qhull error (qh_initqhull_start): qh_qh already defined.  Call qh_save_qhull() first\n");
    qh_exit(qh_ERRqhull);  /* no error handler */
  }
  if (!(qh_qh= (qhT *)qh_malloc(sizeof(qhT)))) {
    qh_fprintf(errfile, 6060, "qhull error (qh_initqhull_start): insufficient memory\n");
    qh_exit(qh_ERRmem);  /* no error handler */
  }
#endif
  qh_initstatistics();
  qh_initqhull_start2(infile, outfile, errfile);
} /* initqhull_start */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="initqhull_start2">-</a>

  qh_initqhull_start2( infile, outfile, errfile )
    start initialization of qhull
    initialize statistics, stdio, default values for global variables
    assumes qh_qh is defined
  notes:
    report errors elsewhere, error handling and g_qhull_output [Qhull.cpp, QhullQh()] not in initialized
  see:
    qh_maxmin() determines the precision constants
    qh_freeqhull2()
*/
void qh_initqhull_start2(FILE *infile, FILE *outfile, FILE *errfile) {
  time_t timedata;
  int seed;

  qh_CPUclock; /* start the clock(for qh_clock).  One-shot. */
#if qh_QHpointer
  memset((char *)qh_qh, 0, sizeof(qhT));   /* every field is 0, FALSE, NULL */
#else
  memset((char *)&qh_qh, 0, sizeof(qhT));
#endif
  qh NOerrexit= True;
  qh DROPdim= -1;
  qh ferr= errfile;
  qh fin= infile;
  qh fout= outfile;
  qh furthest_id= qh_IDunknown;
#ifndef qh_NOmerge
  qh JOGGLEmax= REALmax;
#else
  qh JOGGLEmax= 0.0;  /* Joggle ('QJ') if qh_NOmerge */
#endif
  qh KEEPminArea= REALmax;
  qh last_low= REALmax;
  qh last_high= REALmax;
  qh last_newhigh= REALmax;
  qh lastcpu= 0.0;
  qh max_outside= 0.0;
  qh max_vertex= 0.0;
  qh MAXabs_coord= 0.0;
  qh MAXsumcoord= 0.0;
  qh MAXwidth= -REALmax;
  qh MERGEindependent= True;
  qh MINdenom_1= fmax_(1.0/REALmax, REALmin); /* used by qh_scalepoints */
  qh MINoutside= 0.0;
  qh MINvisible= REALmax;
  qh MAXcoplanar= REALmax;
  qh outside_err= REALmax;
  qh premerge_centrum= 0.0;
  qh premerge_cos= REALmax;
  qh PRINTprecision= True;
  qh PRINTradius= 0.0;
  qh postmerge_cos= REALmax;
  qh postmerge_centrum= 0.0;
  qh ROTATErandom= INT_MIN;
  qh MERGEvertices= True;
  qh totarea= 0.0;
  qh totvol= 0.0;
  qh TRACEdist= REALmax;
  qh TRACEpoint= qh_IDnone;    /* recompile to trace a point, or use 'TPn' */
  qh tracefacet_id= UINT_MAX;  /* recompile to trace a facet, set to UINT_MAX when done, see userprintf.c/qh_fprintf */
  qh traceridge_id= UINT_MAX;  /* recompile to trace a ridge, set to UINT_MAX when done, see userprintf.c/qh_fprintf */
  qh tracevertex_id= UINT_MAX; /* recompile to trace a vertex, set to UINT_MAX when done, see userprintf.c/qh_fprintf */
  seed= (int)time(&timedata);
  qh_RANDOMseed_(seed);
  qh run_id= qh_RANDOMint;
  if(!qh run_id)
      qh run_id++;  /* guarantee non-zero */
  qh_option("run-id", &qh run_id, NULL);
  strcat(qh qhull, "qhull");
} /* initqhull_start2 */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="initthresholds">-</a>

  qh_initthresholds( commandString )
    set thresholds for printing and scaling from commandString

  returns:
    sets qh.GOODthreshold or qh.SPLITthreshold if 'Pd0D1' used

  see:
    qh_initflags(), 'Qbk' 'QBk' 'Pdk' and 'PDk'
    qh_inthresholds()

  design:
    for each 'Pdn' or 'PDn' option
      check syntax
      set qh.lower_threshold or qh.upper_threshold
    set qh.GOODthreshold if an unbounded threshold is used
    set qh.SPLITthreshold if a bounded threshold is used
*/
void qh_initthresholds(char *command) {
  realT value;
  int idx, maxdim, k;
  char *s= command; /* non-const due to strtol */
  char *lastoption, *lastwarning= NULL;
  char key;

  maxdim= qh input_dim;
  if (qh DELAUNAY && (qh PROJECTdelaunay || qh PROJECTinput))
    maxdim++;
  while (*s) {
    if (*s == '-')
      s++;
    if (*s == 'P') {
      lastoption= s++;
      while (*s && !isspace(key= *s++)) {
        if (key == 'd' || key == 'D') {
          if (!isdigit(*s)) {
            qh_fprintf(qh ferr, 7044, "qhull option warning: no dimension given for Print option 'P%c' at: %s.  Ignored\n",
                    key, s-1);
            lastwarning= lastoption;
            continue;
          }
          idx= qh_strtol(s, &s);
          if (idx >= qh hull_dim) {
            qh_fprintf(qh ferr, 7045, "qhull option warning: dimension %d for Print option 'P%c' is >= %d.  Ignored\n",
                idx, key, qh hull_dim);
            lastwarning= lastoption;
            continue;
          }
          if (*s == ':') {
            s++;
            value= qh_strtod(s, &s);
            if (fabs((double)value) > 1.0) {
              qh_fprintf(qh ferr, 7046, "qhull option warning: value %2.4g for Print option 'P%c' is > +1 or < -1.  Ignored\n",
                      value, key);
              lastwarning= lastoption;
              continue;
            }
          }else
            value= 0.0;
          if (key == 'd')
            qh lower_threshold[idx]= value;
          else
            qh upper_threshold[idx]= value;
        }
      }
    }else if (*s == 'Q') {
      lastoption= s++;
      while (*s && !isspace(key= *s++)) {
        if (key == 'b' && *s == 'B') {
          s++;
          for (k=maxdim; k--; ) {
            qh lower_bound[k]= -qh_DEFAULTbox;
            qh upper_bound[k]= qh_DEFAULTbox;
          }
        }else if (key == 'b' && *s == 'b')
          s++;
        else if (key == 'b' || key == 'B') {
          if (!isdigit(*s)) {
            qh_fprintf(qh ferr, 7047, "qhull option warning: no dimension given for Qhull option 'Q%c'\n",
                    key);
            lastwarning= lastoption;
            continue;
          }
          idx= qh_strtol(s, &s);
          if (idx >= maxdim) {
            qh_fprintf(qh ferr, 7048, "qhull option warning: dimension %d for Qhull option 'Q%c' is >= %d.  Ignored\n",
                idx, key, maxdim);
            lastwarning= lastoption;
            continue;
          }
          if (*s == ':') {
            s++;
            value= qh_strtod(s, &s);
          }else if (key == 'b')
            value= -qh_DEFAULTbox;
          else
            value= qh_DEFAULTbox;
          if (key == 'b')
            qh lower_bound[idx]= value;
          else
            qh upper_bound[idx]= value;
        }
      }
    }else {
      while (*s && !isspace(*s))
        s++;
    }
    while (isspace(*s))
      s++;
  }
  for (k=qh hull_dim; k--; ) {
    if (qh lower_threshold[k] > -REALmax/2) {
      qh GOODthreshold= True;
      if (qh upper_threshold[k] < REALmax/2) {
        qh SPLITthresholds= True;
        qh GOODthreshold= False;
        break;
      }
    }else if (qh upper_threshold[k] < REALmax/2)
      qh GOODthreshold= True;
  }
  if (lastwarning && !qh ALLOWwarning) {
    qh_fprintf(qh ferr, 6036, "qhull option error: see previous warnings, use 'Qw' to override: '%s' (last offset %d)\n",
      command, (int)(lastwarning-command));
    qh_errexit(qh_ERRinput, NULL, NULL);
  }
} /* initthresholds */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="lib_check">-</a>

  qh_lib_check( qhullLibraryType, qhTsize, vertexTsize, ridgeTsize, facetTsize, setTsize, qhmemTsize )
    Report error if library does not agree with caller

  notes:
    NOerrors -- qh_lib_check can not call qh_errexit()
*/
void qh_lib_check(int qhullLibraryType, int qhTsize, int vertexTsize, int ridgeTsize, int facetTsize, int setTsize, int qhmemTsize) {
    int last_errcode= qh_ERRnone;

#if defined(_MSC_VER) && defined(_DEBUG) && defined(QHULL_CRTDBG)  /* user.h */
    /*_CrtSetBreakAlloc(744);*/  /* Break at memalloc {744}, or 'watch' _crtBreakAlloc */
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_DELAY_FREE_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) );
    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG );
    _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDERR );
    _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG );
    _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDERR );
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG );
    _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDERR );
#endif

    if (qhullLibraryType==QHULL_NON_REENTRANT) { /* 0 */
      if (qh_QHpointer) {
        qh_fprintf_stderr(6246, "qh_lib_check: Incorrect qhull library called.  Caller uses a static qhT while library uses a dynamic qhT via qh_QHpointer.  Both caller and qhull library are non-reentrant.\n");
        last_errcode= 6246;
      }
    }else if (qhullLibraryType==QHULL_QH_POINTER) { /* 1 */
      if (!qh_QHpointer) {
        qh_fprintf_stderr(6247, "qh_lib_check: Incorrect qhull library called.  Caller uses a dynamic qhT via qh_QHpointer while qhull library uses a static qhT.  Both caller and qhull library are non-reentrant.\n");
        last_errcode= 6247;
      }
    }else if (qhullLibraryType == QHULL_REENTRANT) { /* 2 */
      qh_fprintf_stderr(6248, "qh_lib_check: Incorrect qhull library called.  Caller uses reentrant Qhull while qhull library is non-reentrant\n");
      last_errcode= 6248;
    }else {
      qh_fprintf_stderr(6262, "qh_lib_check: Expecting qhullLibraryType QHULL_NON_REENTRANT(0), QHULL_QH_POINTER(1), or QHULL_REENTRANT(2).  Got %d\n", qhullLibraryType);
      last_errcode= 6262;
    }
    if (qhTsize != (int)sizeof(qhT)) {
      qh_fprintf_stderr(6249, "qh_lib_check: Incorrect qhull library called.  Size of qhT for caller is %d, but for qhull library is %d.\n", qhTsize, (int)sizeof(qhT));
      last_errcode= 6249;
    }
    if (vertexTsize != (int)sizeof(vertexT)) {
      qh_fprintf_stderr(6250, "qh_lib_check: Incorrect qhull library called.  Size of vertexT for caller is %d, but for qhull library is %d.\n", vertexTsize, (int)sizeof(vertexT));
      last_errcode= 6250;
    }
    if (ridgeTsize != (int)sizeof(ridgeT)) {
      qh_fprintf_stderr(6251, "qh_lib_check: Incorrect qhull library called.  Size of ridgeT for caller is %d, but for qhull library is %d.\n", ridgeTsize, (int)sizeof(ridgeT));
      last_errcode= 6251;
    }
    if (facetTsize != (int)sizeof(facetT)) {
      qh_fprintf_stderr(6252, "qh_lib_check: Incorrect qhull library called.  Size of facetT for caller is %d, but for qhull library is %d.\n", facetTsize, (int)sizeof(facetT));
      last_errcode= 6252;
    }
    if (setTsize && setTsize != (int)sizeof(setT)) {
      qh_fprintf_stderr(6253, "qh_lib_check: Incorrect qhull library called.  Size of setT for caller is %d, but for qhull library is %d.\n", setTsize, (int)sizeof(setT));
      last_errcode= 6253;
    }
    if (qhmemTsize && qhmemTsize != sizeof(qhmemT)) {
      qh_fprintf_stderr(6254, "qh_lib_check: Incorrect qhull library called.  Size of qhmemT for caller is %d, but for qhull library is %d.\n", qhmemTsize, sizeof(qhmemT));
      last_errcode= 6254;
    }
    if (last_errcode) {
      if(qh_QHpointer){
        qh_fprintf_stderr(6255, "qhull internal error (qh_lib_check): Cannot continue due to QH%d.  Library '%s' should use a dynamic qhT via qh_QHpointer (e.g., qhull_p.so).  It may be out-of-date.  Exit with %d\n",
              last_errcode, qh_version2, last_errcode - 6200);
      }else {
        qh_fprintf_stderr(6256, "qhull internal error (qh_lib_check): Cannot continue due to QH%d..  Library '%s' should use a static qhT (e.g., libqhull.so).  It may be out-of-date.  Exit with %d\n",
              last_errcode, qh_version2, last_errcode - 6200);
      }
      qh_exit(last_errcode - 6200);  /* can not use qh_errexit(), must be less than 255 */
    }
} /* lib_check */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="option">-</a>

  qh_option( option, intVal, realVal )
    add an option description to qh.qhull_options

  notes:
    NOerrors -- qh_option can not call qh_errexit() [qh_initqhull_start2]
    will be printed with statistics ('Ts') and errors
    strlen(option) < 40
*/
void qh_option(const char *option, int *i, realT *r) {
  char buf[200];
  int buflen, remainder;

  if (strlen(option) > sizeof(buf)-30-30) {
    qh_fprintf(qh ferr, 6408, "qhull internal error (qh_option): option (%d chars) has more than %d chars.  May overflow temporary buffer.  Option '%s'\n",
        (int)strlen(option), (int)sizeof(buf)-30-30, option);
    qh_errexit(qh_ERRqhull, NULL, NULL);
  }
  sprintf(buf, "  %s", option);
  if (i)
    sprintf(buf+strlen(buf), " %d", *i);
  if (r)
    sprintf(buf+strlen(buf), " %2.2g", *r);
  buflen= (int)strlen(buf);   /* WARN64 */
  qh qhull_optionlen += buflen;
  remainder= (int)(sizeof(qh qhull_options) - strlen(qh qhull_options)) - 1;    /* WARN64 */
  maximize_(remainder, 0);
  if (qh qhull_optionlen >= qh_OPTIONline && remainder > 0) {
    strncat(qh qhull_options, "\n", (unsigned int)remainder);
    --remainder;
    qh qhull_optionlen= buflen;
  }
  if (buflen > remainder) {
    trace1((qh ferr, 1058, "qh_option: option would overflow qh.qhull_options. Truncated '%s'\n", buf));
  }
  strncat(qh qhull_options, buf, (unsigned int)remainder);
} /* option */

#if qh_QHpointer
/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="restore_qhull">-</a>

  qh_restore_qhull( oldqh )
    restores a previously saved qhull
    also restores qh_qhstat and qhmem.tempstack
    Sets *oldqh to NULL
  notes:
    errors if current qhull hasn't been saved or freed
    uses qhmem for error reporting

  NOTE 1998/5/11:
    Freeing memory after qh_save_qhull and qh_restore_qhull
    is complicated.  The procedures will be redesigned.

  see:
    qh_save_qhull(), UsingLibQhull
*/
void qh_restore_qhull(qhT **oldqh) {

  if (*oldqh && strcmp((*oldqh)->qhull, "qhull")) {
    qh_fprintf(qhmem.ferr, 6061, "qhull internal error (qh_restore_qhull): %p is not a qhull data structure\n",
                  *oldqh);
    qh_errexit(qh_ERRqhull, NULL, NULL);
  }
  if (qh_qh) {
    qh_fprintf(qhmem.ferr, 6062, "qhull internal error (qh_restore_qhull): did not save or free existing qhull\n");
    qh_errexit(qh_ERRqhull, NULL, NULL);
  }
  if (!*oldqh || !(*oldqh)->old_qhstat) {
    qh_fprintf(qhmem.ferr, 6063, "qhull internal error (qh_restore_qhull): did not previously save qhull %p\n",
                  *oldqh);
    qh_errexit(qh_ERRqhull, NULL, NULL);
  }
  qh_qh= *oldqh;
  *oldqh= NULL;
  qh_qhstat= qh old_qhstat;
  qhmem.tempstack= qh old_tempstack;
  qh old_qhstat= 0;
  qh old_tempstack= 0;
  trace1((qh ferr, 1007, "qh_restore_qhull: restored qhull from %p\n", *oldqh));
} /* restore_qhull */

/*-<a                             href="qh-globa.htm#TOC"
  >-------------------------------</a><a name="save_qhull">-</a>

  qh_save_qhull(  )
    saves qhull for a later qh_restore_qhull
    also saves qh_qhstat and qhmem.tempstack

  returns:
    qh_qh=NULL

  notes:
    need to initialize qhull or call qh_restore_qhull before continuing

  NOTE 1998/5/11:
    Freeing memory after qh_save_qhull and qh_restore_qhull
    is complicated.  The procedures will be redesigned.

  see:
    qh_restore_qhull()
*/
qhT *qh_save_qhull(void) {
  qhT *oldqh;

  trace1((qhmem.ferr, 1045, "qh_save_qhull: save qhull %p\n", qh_qh));
  if (!qh_qh) {
    qh_fprintf(qhmem.ferr, 6064, "qhull internal error (qh_save_qhull): qhull not initialized\n");
    qh_errexit(qh_ERRqhull, NULL, NULL);
  }
  qh old_qhstat= qh_qhstat;
  qh_qhstat= NULL;
  qh old_tempstack= qhmem.tempstack;
  qhmem.tempstack= NULL;
  oldqh= qh_qh;
  qh_qh= NULL;
  return oldqh;
} /* save_qhull */

#endif

