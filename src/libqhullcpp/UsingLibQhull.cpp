/****************************************************************************
**
** Copyright (c) 2008-2015 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/UsingLibQhull.cpp#8 $$Change: 1810 $
** $DateTime: 2015/01/17 18:28:15 $$Author: bbarber $
**
****************************************************************************/

#//! UsingLibQhull -- Set up qhull C code from C++

#include "Qhull.h"
#include "UsingLibQhull.h"
#include "QhullError.h"
#include "QhullQh.h"

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4
#endif

namespace orgQhull {

#//Class objects

const double UsingLibQhull::
DEFAULTdistanceEpsilon= 1e-15*FACTORepsilon; //! ~DISTround*FACTORepsilon for unit cube

const double UsingLibQhull::
DEFAULTangleEpsilon= 1e-15*FACTORepsilon; //! ~ANGLEround*FACTORepsilon for unit cube

    //! Global pointer to Qhull for qh_fprintf callback and QhullError
Qhull *
s_qhull_output= 0;

double UsingLibQhull::
s_angle_epsilon= 0;

double UsingLibQhull::
s_distance_epsilon= 0;

//! For QhullPoint.id() w/o qhRunId.  Initialized by Qhull
const coordT *UsingLibQhull::
s_points_begin= 0;
const coordT *UsingLibQhull::
s_points_end= 0;
int UsingLibQhull::
s_points_dimension= 0;

int UsingLibQhull::
s_vertex_dimension= 0;  // FIXUP QH11023: s_vertex_dimension is required if dimension>15.  Cannot store in QhullVertex

bool UsingLibQhull::
s_has_points= false;

bool UsingLibQhull::
s_has_angle_epsilon= false;

bool UsingLibQhull::
s_has_vertex_dimension= false;

bool UsingLibQhull::
s_has_distance_epsilon= false;

bool UsingLibQhull::
s_using_libqhull= false;

#//Constructors

//! Grabs global state (qh_qh, qh_qhstat, qhmem.tempstack)
//! Follow immediately with setjmp(qh->errexit), otherwise errors in libqhull are not caught properly
//! See qh_restore_qhull [global.c]
UsingLibQhull::
UsingLibQhull(Qhull *q)
: my_qhull(q)
, qh_exitcode(0)
{
    checkUsingLibQhull();
    QhullQh *qhullqh= q->qhullQh();
    if(!qhullqh){
        throw QhullError(10014, "Qhull internal error: Qhull.qhullQh() not defined. initializeQhull() not called.");
    }
    s_qhull_output= q;      // set s_qhull_output for qh_fprintf()
    qh->NOerrexit= False;   // assumes setjmp called next
}//UsingLibQhull qhull

//! Same as UsingLibQhull but does not throw exceptions
//! !defined() on failure.  For use in destructors
UsingLibQhull::
UsingLibQhull(Qhull *q, int noThrow)
: my_qhull(0)  // Fail by default
, qh_exitcode(0)
{
    QHULL_UNUSED(noThrow);

    QhullQh *qhullqh= q->qhullQh();
        my_qhull= q;
        s_qhull_output= q;          // set s_qhull_output for qh_fprintf()
        qh NOerrexit= False;   // assumes setjmp called next
    }
}//UsingLibQhull qhull noThrow

//! Reuses current global state (qh_qh) from prior UsingQhull
//! Errors if runId is not the same
UsingLibQhull::
UsingLibQhull(int qhRunId)
: my_qhull(0)
, qh_exitcode(0)
{
    checkUsingLibQhull();
#if qh_QHpointer
    if(!qh_qh || !qh_qhstat){
        throw QhullError(10024, "Qhull error: UsingLibQhull is not active (qh_qh %x or qh_qhstat is not defined)", 0,0,0.0, qh_qh);
    }
#endif
    if(qh run_id!=qhRunId){
        throw QhullError(10036, "Qhull error: qhRunId %d != qh_qh.runId %d.  Is another Qhull active?", qhRunId, qh run_id);
    }
    if(!s_qhull_output){
        throw QhullError(10037, "Qhull error: UsingLibQhull not active(s_qhull_output undefined).  Invoke UsingLibQhull before this call");
    }
    if(s_qhull_output->qhull_run_id!=qhRunId){
        throw QhullError(10046, "Qhull error: qhRunId %d != s_qhull_output.runId %d.  Is another Qhull active", qhRunId, s_qhull_output->qhull_run_id);
    }
    my_qhull= s_qhull_output;
    qh NOerrexit= False;   // assumes setjmp called next
}//UsingLibQhull runId

//Leaves libqhull active for runId access
UsingLibQhull::
~UsingLibQhull()
{
    QhullError e= checkRunId();
    if(e.isDefined()){
        e.logError();
    }else{
#if qh_QHpointer
        if(qh_qh){
            qh NOerrexit= true;
        }
#else
        qh NOerrexit= true;
#endif
    }
    s_using_libqhull= false;
}//~UsingLibQhull

#//Class methods

void UsingLibQhull::
setGlobals()
{
    if(s_qhull_output && s_qhull_output->initialized()){
        QhullQh *qqh= s_qhull_output->qhullQh();
        s_angle_epsilon= qqh->ANGLEround*FACTORepsilon;
        s_distance_epsilon= qqh->DISTround*FACTORepsilon;
        s_points_begin= qqh->first_point;
        s_points_dimension= qqh->hull_dim;
        s_points_end= s_points_begin+qqh->num_points*s_points_dimension;
        s_vertex_dimension= qqh->hull_dim;
        s_has_angle_epsilon= true;
        s_has_distance_epsilon= true;
        s_has_points= true;
        s_has_vertex_dimension= true;
    }else{
        throw QhullError(10058, "Qhull error: setGlobals can only be called for currentQhull().  Run qhull first.");
    }
 }//setGlobals

void UsingLibQhull::
unsetGlobals()
{
    s_has_angle_epsilon= false;
    s_has_distance_epsilon= false;
    s_has_points= false;
    s_has_vertex_dimension= false;
}//unsetGlobals

#//Helpers

}//namespace orgQhull

