/****************************************************************************
**
** Copyright (C) 2008-2009 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/UsingQhullLib.cpp#16 $$Change: 1087 $
** $DateTime: 2009/11/22 23:02:55 $$Author: bbarber $
**
****************************************************************************/

#//! UsingQhullLib -- Set up qhull C code from C++

#include "Qhull.h"
#include "UsingQhullLib.h"
#include "QhullError.h"
#include "QhullQh.h"

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4 
#endif

namespace orgQhull {

#//Class objects

const double UsingQhullLib::
DEFAULTdistanceEpsilon= 1e-15*FACTORepsilon; //! ~DISTround*FACTORepsilon for unit cube

const double UsingQhullLib::
DEFAULTangleEpsilon= 1e-15*FACTORepsilon; //! ~ANGLEround*FACTORepsilon for unit cube

    //! Global pointer to Qhull for qh_fprintf callback and QhullError
Qhull *
s_qhull_output= 0;

double UsingQhullLib::
s_angle_epsilon= 0;

double UsingQhullLib::
s_distance_epsilon= 0;

//! For QhullPoint.id() w/o qhRunId.  Initialized by Qhull
const coordT *UsingQhullLib::
s_points_begin= 0;
const coordT *UsingQhullLib::
s_points_end= 0;
int UsingQhullLib::
s_points_dimension= 0;

int UsingQhullLib::
s_vertex_dimension= 0;  // FIXUP: required if dimension>15

bool UsingQhullLib::
s_has_points= false;

bool UsingQhullLib::
s_has_angle_epsilon= false;

bool UsingQhullLib::
s_has_vertex_dimension= false;

bool UsingQhullLib::
s_has_distance_epsilon= false;

bool UsingQhullLib::
s_using_qhulllib= false; 

#//Constructors

//! Grabs global state (qh_qh, qh_qhstat, qhmem.tempstack)
//! Follow immediately with setjmp(qh errexit), otherwise errors in qhulllib are not caught properly
//! See qh_restore_qhull [global.c]
UsingQhullLib::
UsingQhullLib(Qhull *q)
: my_qhull(q)
, qh_exitcode(0)
{
    checkUsingQhullLib();
    QhullQh *qhullqh= q->qhullQh();
    if(!qhullqh){
        throw QhullError(10014, "Qhull internal error: Qhull.qhullQh() not defined. initializeQhull() not called.");
    }
    if(qhullqh->run_id != q->qhull_run_id){
        throw QhullError(10015, "Qhull error: QhullQh.runId %d != Qhull.runId %d.  Overwritten?", qhullqh->run_id, q->qhull_run_id);
    }
    // qh.old_qhstat is zero at initialization
    // qh.old_tempstack is zero when empty
    // QhullQh() and UsingQhullLib() are the same
#if qh_QHpointer
    if(qh_qh){
        qh old_qhstat= qh_qhstat;
        qh old_tempstack= static_cast<setT *>(qhmem.tempstack);
    }
    qh_qh= qhullqh;
    qh_qhstat= static_cast<qhstatT *>(qhullqh->old_qhstat);
    qhmem.tempstack=  qhullqh->old_tempstack;
    qhullqh->old_qhstat= 0;
    qhullqh->old_tempstack= 0;
#else
    #error FIXUP static qh_qh not tested.  Delete the line to try.
    if(qhullqh!=&qh_qh){
        throw QhullError(10040, "Qhull internal error: Qhull.qhullQh() is not qh_qh (%x, static).  Overwrite?", 0,0,0.0, &qh_qh);
    }
#endif
    s_qhull_output= q;	    // set s_qhull_output for qh_fprintf()
    qh NOerrexit= False;   // assumes setjmp called next
}//UsingQhullLib qhull

//! Same as UsingQhullLib but does not throw exceptions
//! !defined() on failure.  For use in destructors
UsingQhullLib::
UsingQhullLib(Qhull *q, int noThrow)
: my_qhull(0)  // Fail by default
, qh_exitcode(0)
{
    QhullQh *qhullqh= q->qhullQh();
    if(s_using_qhulllib){
        QhullError e(10050, "Qhull error: UsingQhullLib already in use");
        e.logError();
    }else if(!qhullqh || qhullqh->run_id != q->qhull_run_id){
        QhullError e(10051, "Qhull error: Qhull.qhullQh (%x) undefined or QhullQh.runId %d != Qhull.runId %d.  Overwritten?", (qhullqh ? qhullqh->run_id : -1), q->qhull_run_id, 0.0, qhullqh);
        e.logError();
    }else{
        // qh.old_qhstat is zero at initialization
        // qh.old_tempstack is zero when empty
        // QhullQh() and UsingQhullLib() are the same
#if qh_QHpointer
        if(qh_qh){
            qh old_qhstat= qh_qhstat;
            qh old_tempstack= static_cast<setT *>(qhmem.tempstack);
        }
        qh_qh= qhullqh;
        qh_qhstat= static_cast<qhstatT *>(qhullqh->old_qhstat);
        qhmem.tempstack=  qhullqh->old_tempstack;
        qhullqh->old_qhstat= 0;
        qhullqh->old_tempstack= 0;
#endif
        my_qhull= q;
        s_qhull_output= q;	    // set s_qhull_output for qh_fprintf()
        qh NOerrexit= False;   // assumes setjmp called next
    }
}//UsingQhullLib qhull noThrow

//! Reuses current global state (qh_qh) from prior UsingQhull
//! Errors if runId is not the same
UsingQhullLib::
UsingQhullLib(int qhRunId)
: my_qhull(0)
, qh_exitcode(0)
{
    checkUsingQhullLib();
#if qh_QHpointer
    if(!qh_qh || !qh_qhstat){
	throw QhullError(10024, "Qhull error: UsingQhullLIb is not active (qh_qh %x or qh_qhstat is not defined)", 0,0,0.0, qh_qh);
    }
#endif
    if(qh run_id!=qhRunId){
        throw QhullError(10036, "Qhull error: qhRunId %d != qh_qh.runId %d.  Is another Qhull active?", qhRunId, qh run_id);
    }
    if(!s_qhull_output){
	throw QhullError(10037, "Qhull error: UsingQhullLib not active(s_qhull_output undefined).  Invoke UsingQhullLIb before this call");
    }
    if(s_qhull_output->qhull_run_id!=qhRunId){
	throw QhullError(10046, "Qhull error: qhRunId %d != s_qhull_output.runId %d.  Is another Qhull active", qhRunId, s_qhull_output->qhull_run_id);
    }
    my_qhull= s_qhull_output;
    qh NOerrexit= False;   // assumes setjmp called next
}//UsingQhullLib runId

//Leaves QHullLib active for runId access
UsingQhullLib::
~UsingQhullLib()
{
    QhullError e= checkRunId();
    if(e.defined()){
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
    s_using_qhulllib= false;
}//~UsingQhullLib

#//Class methods

void UsingQhullLib::
checkQhullMemoryEmpty()
{
    int curlong, totlong, curshort, totshort, maxlong, totbuffer;
    // qh_memtotal does not error
    qh_memtotal(&curlong, &totlong, &curshort, &totshort, &maxlong, &totbuffer);
    if (curlong || totlong){
        throw QhullError(10026, "Qhull error: qhull did not free %d bytes of long memory (%d pieces).", totlong, curlong); 
    }
    if (curshort || totshort){
        throw QhullError(10035, "Qhull error: qhull did not free %d bytes of short memory (%d pieces).", totshort, curshort); 
    }
}//checkQhullMemoryEmpty

double UsingQhullLib::
currentAngleEpsilon() 
{ 
    if(s_qhull_output && s_qhull_output->defined()){
        return s_qhull_output->qhullQh()->ANGLEround*FACTORepsilon;
    }else if(s_has_angle_epsilon){
        return s_angle_epsilon;
    }
    return UsingQhullLib::DEFAULTangleEpsilon;
}//currentAngleEpsilon

double UsingQhullLib::
currentDistanceEpsilon() 
{ 
    if(s_qhull_output && s_qhull_output->defined()){
        return s_qhull_output->qhullQh()->DISTround*FACTORepsilon;
    }else if(s_has_distance_epsilon){
        return s_distance_epsilon;
    }
    return UsingQhullLib::DEFAULTdistanceEpsilon;
}//currentDistanceEpsilon

const coordT *UsingQhullLib::
currentPoints(int *dimension, const coordT **pointsEnd)
{
    if(s_qhull_output && s_qhull_output->defined()){
        *dimension= qh hull_dim;
        *pointsEnd= qh first_point+qh num_points*qh hull_dim;
        return qh first_point;
    }else if(s_has_points){
        *dimension= s_points_dimension; 
        *pointsEnd= s_points_end; 
        return s_points_begin; 
    }
    throw QhullError(10059, "Qhull error: missing definition for currentPoints().  Need currentQhull() or setGlobalDistanceEpsilon()");
}//globalPoints

Qhull &UsingQhullLib::
currentQhull()
{
    if(!s_qhull_output){
        throw QhullError(10055, "Qhull error: currentQhull not defined.  Run qhull first."); 
    }
    return *s_qhull_output;
}//currentQhull

int UsingQhullLib::
currentVertexDimension() 
{ 
    if(s_qhull_output && s_qhull_output->defined()){
        return s_qhull_output->dimension();
    }else if(s_has_vertex_dimension){
        return s_vertex_dimension;
    }
    throw QhullError(10057, "Qhull error: missing definition for currentVertexDimension().  Need currentQhull() or setGlobalVertexDimension()");
}//currentVertexDimension

const coordT *UsingQhullLib::
globalPoints(int *dimension, const coordT **pointsEnd)
{
    if(s_has_points){
        *dimension= s_points_dimension; 
        *pointsEnd= s_points_end; 
        return s_points_begin; 
    }else{
        return currentPoints(dimension, pointsEnd);
    }
}//globalPoints

bool UsingQhullLib::
hasPoints() 
{ 
    return s_has_points || (s_qhull_output && s_qhull_output->defined());
}

bool UsingQhullLib::
hasVertexDimension() 
{ 
    return s_has_vertex_dimension || (s_qhull_output && s_qhull_output->defined());
}

void UsingQhullLib::
setGlobals() 
{ 
    if(s_qhull_output && s_qhull_output->defined()){
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

void UsingQhullLib::
unsetGlobals() 
{ 
    s_has_angle_epsilon= false;
    s_has_distance_epsilon= false;
    s_has_points= false;
    s_has_vertex_dimension= false;
}//unsetGlobals

#// Methods

void UsingQhullLib::
maybeThrowQhullMessage(int exitCode) const
{
    my_qhull->maybeThrowQhullMessage(exitCode);
    QhullError e= checkRunId(); // Check for qhRunId after qhulllib returns. For convenience, ought to be at end of qhulllib try block
    if(e.defined()){
        throw e;
    }
}//maybeThrowQhullMessage


void UsingQhullLib::
maybeThrowQhullMessage(int exitCode, int noThrow) const
{
    my_qhull->maybeThrowQhullMessage(exitCode, noThrow);
    QhullError e= checkRunId(); // Check for qhRunId after qhulllib returns. For convenience, ought to be at end of qhulllib try block
    if(e.defined()){
        e.logError();
    }
}//maybeThrowQhullMessage


#//Helpers

//! Return QhullError for maybeThrowFromDestructor()
QhullError UsingQhullLib::
checkRunId() const
{
    // Predeclaring QhullError results in four copy constructors, none used here
#if qh_QHpointer
    if(qh_qh){ // 0 if ~Qhull
        if(my_qhull->qhull_run_id!=qh run_id){
            return QhullError(10047, "Qhull internal error: Global state (qh_qh, run_id %d) changed.  Should be runId %d.  Another thread?", qh run_id, my_qhull->qhull_run_id);
        }
    }
#else
    if(qh run_id!=0 && my_qhull->qhull_run_id!=qh run_id){
        return QhullError(10048, "Qhull internal error: Global state (qh_qh, run_id %d) changed.  Should be runId %d.  Another thread?", qh run_id, my_qhull->qhull_run_id);
    }
#endif
    return QhullError();
}//checkRunId

//! Can not embed UsingQhullLib.  Otherwise allocated a C++ object missed by qh_errexit
void UsingQhullLib::
checkUsingQhullLib() const
{
    if(s_using_qhulllib){
        if(s_qhull_output){
            throw QhullError(10049, "Qhull error: UsingQhullLib already in use by QhullQh.runId %d", s_qhull_output->qhull_run_id);
        }else{
            throw QhullError(10050, "Qhull error: UsingQhullLib already in use.  No s_qhull_output");
        }
    }
    s_using_qhulllib= true;
}//checkUsingQhullLib

}//namespace orgQhull

