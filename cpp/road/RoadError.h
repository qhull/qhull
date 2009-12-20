/****************************************************************************
**
** Copyright (C) 2008-2009 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/road/RoadError.h#16 $$Change: 1111 $
** $DateTime: 2009/12/10 22:15:38 $$Author: bbarber $
**
****************************************************************************/

#ifndef ROADERROR_H
#define ROADERROR_H

#include "RoadLogEvent.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using std::endl;

namespace orgQhull {

#//Types
    //! RoadError -- Report and log errors
    //!  See discussion in Saylan, G., "Practical C++ error handling in hybrid environments," Dr. Dobb's Journal, p. 50-55, March 2007.  
    //!   He uses an auto_ptr to track a stringstream.  It constructs a string on the fly.  RoadError uses the copy constructor to transform RoadLogEvent into a string
    class RoadError;

class RoadError : public std::exception {

private:
#//Fields
    int                 error_code;  //! Non-zero code (not logged), maybe returned as program status
    RoadLogEvent        log_event;   //! Format string w/ arguments
    mutable std::string error_message;  //! Formated error message.  Must be after log_event.

#//Class fields
    static const char  *  ROADtag;
    static std::ostringstream  global_log; //! May be replaced with any ostream object

public:
#//Constants

#//Constructors
    RoadError();
    RoadError(const RoadError &e);  //! Called on throw, generates error_message
    RoadError(int code, const std::string &message);
    RoadError(int code, const char *fmt);
    RoadError(int code, const char *fmt, int d);
    RoadError(int code, const char *fmt, int d, int d2);
    RoadError(int code, const char *fmt, int d, int d2, float f);
    RoadError(int code, const char *fmt, int d, int d2, float f, const char *s);
    RoadError(int code, const char *fmt, int d, int d2, float f, const void *x);
    RoadError(int code, const char *fmt, int d, int d2, float f, int i);
    RoadError(int code, const char *fmt, int d, int d2, float f, long long i);
    RoadError(int code, const char *fmt, int d, int d2, float f, double e);

    RoadError          &operator=(const RoadError&);
                       ~RoadError() throw() {};

#//Class methods

    static void         clearGlobalLog() { global_log.seekp(0); }
    static bool         emptyGlobalLog() { return global_log.tellp()<=0; }
    static const char  *stringGlobalLog() { return global_log.str().c_str(); }

#//Virtual
    virtual const char *what() const throw();

#//GetSet
    bool                defined() const { return log_event.defined(); }
    int                 errorCode() const { return error_code; };
   // FIXUP std::string         errorMessage() const { return error_message; }; //! Populated by throw
    RoadLogEvent        roadLogEvent() const { return log_event; };

#//Update
    void                logError() const;
};//class RoadError

}//namespace orgQhull

#//Global functions

inline std::ostream    &operator<<(std::ostream &os, const orgQhull::RoadError &e) { return os<< e.what(); }

#endif // ROADERROR_H
