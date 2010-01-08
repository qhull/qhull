/****************************************************************************
**
** Copyright (C) 2008-2010 C.B. Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/QhullLog.cpp#10 $$Change: 1164 $
** $DateTime: 2010/01/07 21:52:00 $$Author: bbarber $
**
****************************************************************************/

#//! QhullLog -- A recorded event in a circular buffer

#include "QhullLog.h"

#include <time.h>

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4
#endif

namespace orgQhull {

#//Class global
std::vector<std::string>         a_log;
std::vector<QhullEvent>   a_events;
int             a_head= 0;
int             a_tail= 0;
int             a_head_gap= 0;
int             a_tail_end= 0;
int             a_max_overrun= 0;
int             a_call_depth= 0;
int              a_min_call_depth= 0;
time_t           a_start_time_s= 0;
int              a_logging_enabled= 0;

#//Constructor, destructor, etc.
QhullLog::
QhullLog(int level, const char *message)
{
    a_call_depth++;
    log(QhullEvent::CallEvent, level, message, 0, 0, 0);
}

QhullLog::
QhullLog(int level, const char *message, int arg1)
{
    a_call_depth++;
    log(QhullEvent::CallEvent, level, message, arg1, 0, 0);
}

QhullLog::
QhullLog(int level, const char *message, int arg1, int arg2)
{
    a_call_depth++;
    log(QhullEvent::CallEvent, level, message, arg1, arg2, 0);
}

QhullLog::
QhullLog(int level, const char *message, int arg1, const char* arg3)
{
    a_call_depth++;
    log(QhullEvent::CallEvent, level, message, arg1, 0, arg3);
}

QhullLog::
QhullLog(int traceLevel, const char *message, int arg1, int arg2, const char* arg3)
{
    a_call_depth++;
    log(QhullEvent::CallEvent, traceLevel, message, arg1, arg2, arg3);
}

QhullLog::
~QhullLog()
{
    if(--a_call_depth < a_min_call_depth){
        a_min_call_depth= a_call_depth;
    }
    if(a_events[a_tail].event_type & QhullEvent::ReturnEvent){
        log(QhullEvent::ReturnEvent, 0, 0, 0, 0, 0);
    }else{
        a_events[a_tail++].event_type |= QhullEvent::ReturnEvent;
    }
}

#//GetSet

#//Modify

void QhullLog::
log(int level, const char *message)
{
    log(QhullEvent::LogEvent, level, message, 0, 0, 0);
}

void QhullLog::
log(int level, const char *message, int arg1)
{
    log(QhullEvent::LogEvent, level, message, arg1, 0, 0);
}

void QhullLog::
log(int level, const char *message, int arg1, int arg2)
{
    log(QhullEvent::LogEvent, level, message, arg1, arg2, 0);
}

void QhullLog::
log(int level, const char *message, int arg1, const char* arg3)
{
    log(QhullEvent::LogEvent, level, message, arg1, 0, arg3);
}


#//Helper

void QhullLog::
cullEvents()
{

}//cullEvents

//! May be called by multiple threads
void QhullLog::
log(QhullEvent::EventTypes e, int traceLevel, const char *message, int arg1, int arg2, const char* arg3)
{
    traceLevel= traceLevel;  // Ignore traceLevel for now
    if(a_logging_enabled != 1){
        return;
    }
    int t= (int)(time(0) - a_start_time_s); // Conversion OK, seconds since starts
    a_events[a_tail++]= QhullEvent(t, e, traceLevel, message, arg1, arg2, arg3);
    a_call_depth++;
    if(a_tail-a_head_gap < a_head || a_tail >= a_tail_end){
        maybeCullEvents();
    }
}

void QhullLog::
maybeCullEvents()
{
    if(a_tail>=a_tail_end){
        if(a_tail-a_tail_end > a_max_overrun){
            a_max_overrun= a_tail-a_tail_end; //FIXUP -- race condition
        }
        a_tail= 0;
    }
    if(a_head<a_head_gap){
        if(a_tail<a_head_gap || a_tail_end-a_tail+a_head < a_head_gap){
            cullEvents();
        }
    }else if(a_head>a_tail && a_head-a_tail < a_head_gap){
        cullEvents();
    }
}//maybeCullEvents


}//namespace orgQhull

