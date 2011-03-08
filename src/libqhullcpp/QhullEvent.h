/****************************************************************************
**
** Copyright (c) 2008-2011 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullEvent.h#3 $$Change: 1342 $
** $DateTime: 2011/03/07 21:55:47 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLEVENT_H
#define QHULLEVENT_H

extern "C" {
    #include "libqhull/qhull_a.h"
};

#include <string>

namespace orgQhull {

#//Types
    //! QhullEvent -- Circular array of Qhull execution events
    class QhullEvent;

class QhullEvent {

#//Types
    friend class QhullLog;

#//Constants
public:
    enum EventTypes {
        LogEvent= 0x0,
        CallEvent= 0x1,
        ReturnEvent= 0x2
    };

private:
#//Fields
    unsigned int    time_s:24;
    unsigned int    event_type:2;
    unsigned int    trace_level:3;
    unsigned int    unused_bits:3;
    const char     *event_message;
    int             int_arg1;
    int             int_arg2;
    const char     *cstr_arg3;


public:
#//Constructor, destructor
    QhullEvent() : time_s(0), event_type(0), trace_level(0), unused_bits(0), event_message(0), int_arg1(0), int_arg2(0), cstr_arg3(0) {};
    QhullEvent(int timeSeconds, EventTypes e, int traceLevel, const char *message, int arg1, int arg2, const char *arg3) : time_s(timeSeconds), event_type(e), trace_level(traceLevel), unused_bits(0), event_message(message), int_arg1(arg1), int_arg2(arg2), cstr_arg3(arg3) {};
    ~QhullEvent() {};
};//QhullEvent

inline QhullEvent::EventTypes operator&(QhullEvent::EventTypes a, QhullEvent::EventTypes b) { return static_cast<QhullEvent::EventTypes>(int(a) & int(b)); };

#if 0
error messages start with "Error" -- may be translated
.what is the last error message
messageLength()
on ERROR dump log to FILE
shadow log?
messageCount, maxCount
#endif

}//namespace orgQhull

#//Global functions

#endif // QHULLEVENT_H
