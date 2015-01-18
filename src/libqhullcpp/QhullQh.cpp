/****************************************************************************
**
** Copyright (c) 2008-2014 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullQh.cpp#8 $$Change: 1797 $
** $DateTime: 2014/12/15 17:23:41 $$Author: bbarber $
**
****************************************************************************/

#//! QhullQh -- Qhull's global data structure, qhT, as a C++ class



#include "QhullError.h"
#include "QhullQh.h"
#include "QhullStat.h"
#include "Qhull.h"

#include <sstream>
#include <iostream>

#include <stdarg.h>

using std::cerr;
using std::string;
using std::vector;
using std::ostream;

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4
#pragma warning( disable : 4611)  // interaction between '_setjmp' and C++ object destruction is non-portable
#pragma warning( disable : 4996)  // function was declared deprecated(strcpy, localtime, etc.)
#endif

namespace orgQhull {

#//Global variables
const double QhullQh::
default_factor_epsilon= 1.0;

#//Constructor, destructor, etc.

//! Derived from qh_new_qhull[user.c]
QhullQh::
QhullQh()
: qhull_status(qh_ERRnone)
, qhull_message()
, error_stream(0)
, output_stream(0)
, factor_epsilon(QhullQh::default_factor_epsilon)
, useOutputStream(false)
{
    // NOerrors -- Does not call qh_errexit()
    qh_meminit(this, NULL);
    this->ISqhullQh= True;
    // NOerrors -- Does not call qh_errexit()
    qh_initstatistics(this);
    // NOerrors -- Does not call qh_errexit()
    qh_initqhull_start2(this, NULL, NULL, qh_FILEstderr);
}//QhullQh

QhullQh::
~QhullQh()
{
    qh_freeqhull(this, qh_ALL); // sets qh.NOerrexit. Clears struct *qh_qh including run_id
}//~QhullQh

#//!\name Methods

void QhullQh::
checkAndFreeQhullMemory()
{
#ifdef qh_NOmem
    qh_freeqhull(this, qh_ALL);
#else
    qh_freeqhull(this, !qh_ALL);
    countT curlong;
    countT totlong;
    qh_memfreeshort(this, &curlong, &totlong);
    if (curlong || totlong)
        throw QhullError(10026, "Qhull error: qhull did not free %d bytes of long memory (%d pieces).", totlong, curlong);
#endif
}//checkAndFreeQhullMemory

#//Messaging

void QhullQh::
appendQhullMessage(const string &s)
{
    if(output_stream && useOutputStream && this->USEstdout){ 
        *output_stream << s;
    }else if(error_stream){
        *error_stream << s;
    }else{
        qhull_message += s;
    }
}//appendQhullMessage

//! clearQhullMessage does not throw errors (~Qhull)
void QhullQh::
clearQhullMessage()
{
    qhull_status= qh_ERRnone;
    qhull_message.clear();
    RoadError::clearGlobalLog();
}//clearQhullMessage

//! hasQhullMessage does not throw errors (~Qhull)
bool QhullQh::
hasQhullMessage() const
{
    return (!qhull_message.empty() || qhull_status!=qh_ERRnone);
    //FIXUP QH11006 -- inconsistent usage with Rbox.  hasRboxMessage just tests rbox_status.  No appendRboxMessage()
}

void QhullQh::
maybeThrowQhullMessage(int exitCode)
{
    if(qhull_status==qh_ERRnone){
        qhull_status= exitCode;
    }
    if(qhull_status!=qh_ERRnone){
        QhullError e(qhull_status, qhull_message);
        clearQhullMessage();
        throw e; // FIXUP QH11007: copy constructor is expensive if logging
    }
}//maybeThrowQhullMessage

void QhullQh::
maybeThrowQhullMessage(int exitCode, int noThrow)  throw()
{
    QHULL_UNUSED(noThrow);

    if(qhull_status==qh_ERRnone){
        qhull_status= exitCode;
    }
    if(qhull_status!=qh_ERRnone){
        QhullError e(qhull_status, qhull_message);
        e.logError();
    }
}//maybeThrowQhullMessage

//! qhullMessage does not throw errors (~Qhull)
std::string QhullQh::
qhullMessage() const
{
    if(qhull_message.empty() && qhull_status!=qh_ERRnone){
        return "qhull: no message for error.  Check cerr or error stream\n";
    }else{
        return qhull_message;
    }
}//qhullMessage

int QhullQh::
qhullStatus() const
{
    return qhull_status;
}//qhullStatus

void QhullQh::
setErrorStream(ostream *os)
{
    error_stream= os;
}//setErrorStream

//! Updates useOutputStream
void QhullQh::
setOutputStream(ostream *os)
{
    output_stream= os;
    useOutputStream= (os!=0);
}//setOutputStream

}//namespace orgQhull

/*-<a                             href="qh_qh-user.htm#TOC"
 >-------------------------------</a><a name="qh_fprintf">-</a>

  qh_fprintf(qhT *qh, fp, msgcode, format, list of args )
    FIXUP s_qhull_output vs. fp is ignored (replaces qh_fprintf() in userprintf_r.c)

notes:
    only called from libqhull
    same as fprintf() and RboxPoints.qh_fprintf_rbox()
    fgets() is not trapped like fprintf()
    Do not throw errors from here.  Use qh_errexit;
*/
extern "C"
void qh_fprintf(qhT *qh, FILE *fp, int msgcode, const char *fmt, ... ) {
    va_list args;

    using namespace orgQhull;

    if(!qh->ISqhullQh){
        fprintf(stderr, "QH10025 Qhull error: qh_fprintf called from a Qhull instance without QhullQh defined\n");
        qh_exit(10025);
    }
    QhullQh *qhullQh= static_cast<QhullQh *>(qh);
    va_start(args, fmt);
    if(msgcode<MSG_OUTPUT || fp == qh_FILEstderr){
        if(msgcode>=MSG_ERROR && msgcode<MSG_WARNING){
            if(qhullQh->qhull_status<MSG_ERROR || qhullQh->qhull_status>=MSG_WARNING){
                qhullQh->qhull_status= msgcode;
            }
        }
        char newMessage[MSG_MAXLEN];
        // RoadError will add the message tag
        vsnprintf(newMessage, sizeof(newMessage), fmt, args);
        qhullQh->appendQhullMessage(newMessage);
        va_end(args);
        return;
    }
    if(qhullQh->output_stream && qhullQh->useOutputStream){
        char newMessage[MSG_MAXLEN];
        vsnprintf(newMessage, sizeof(newMessage), fmt, args);
        *qhullQh->output_stream << newMessage;
        va_end(args);
        return;
    }
    // FIXUP QH11008: how do users trap messages and handle input?  A callback?
    char newMessage[MSG_MAXLEN];
    vsnprintf(newMessage, sizeof(newMessage), fmt, args);
    qhullQh->appendQhullMessage(newMessage);
    va_end(args);
} /* qh_fprintf */
