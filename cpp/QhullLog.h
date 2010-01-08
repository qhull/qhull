/****************************************************************************
**
** Copyright (C) 2008-2010 C.B. Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/QhullLog.h#12 $$Change: 1164 $
** $DateTime: 2010/01/07 21:52:00 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLLOG_H
#define QHULLLOG_H

#include "QhullEvent.h"
extern "C" {
    #include "../src/qhull_a.h"
};

#include <string>
#include <vector>

namespace orgQhull {

#//Types
    //! QhullLog -- Report errors in Qhull
    class QhullLog;

class QhullLog {

private:
#//Fields

public:
#//Constants

#//Class global
    static std::vector<std::string>
                            a_log;
    static std::vector<QhullEvent>
                           a_events;
    static int             a_head;     //! Head of event queue.  Multiple threads may simultaneously increment a_head
    static int             a_tail;     //! Tail of event queue.

    static int             a_head_gap;      //! Gap between tail and head.
    static int             a_tail_end;      //! End of event queue.  Additional elements allocated to avoid buffer overflow
    static int             a_max_overrun; //! Maximum overrun due to multiple threads (a_head-a_end)

    static int              a_call_depth;  //! Current call depth
    static int              a_min_call_depth;  //! Minimum call depth since last cull

    static time_t           a_start_time_s;    //! UTC seconds at start of logging
    static int              a_logging_enabled; //! True only if '1'

#//Constructors
     QhullLog(int level, const char *message);
     QhullLog(int level, const char *message, int arg1);
     QhullLog(int level, const char *message, int arg1, int arg2);
     QhullLog(int level, const char *message, int arg1, const char *arg3);
     QhullLog(int level, const char *message, int arg1, int arg2, const char *arg3);
    ~QhullLog();

private:
    QhullLog() {};  // disabled

#//Update
    void        log(int level, const char *message);
    void        log(int level, const char *message, int arg1);
    void        log(int level, const char *message, int arg1, const char *arg3);
    void        log(int level, const char *message, int arg1, int arg2);
    void        log(int level, const char *message, int arg1, int arg2, const char *arg3);

#//Helper
private:
    void cullEvents();
    void        log(QhullEvent::EventTypes t, int level, const char *message, int arg1, int arg2, const char *arg3);
    void maybeCullEvents();

};//QhullLog

#if 0
.what is the last error message
.where is the stack + execution log
messageLength()
on ERROR dump log to FILE
log all the time
shadow log?
elide history RELATIVE level, n-back
messageCount, maxCount
#endif


}//namespace orgQhull

#//Global functions

std::ostream &operator<<(std::ostream &os, const orgQhull::QhullLog *f);

#endif // QHULLLOG_H
