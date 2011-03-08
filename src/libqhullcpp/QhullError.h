/****************************************************************************
**
** Copyright (c) 2008-2011 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullError.h#2 $$Change: 1342 $
** $DateTime: 2011/03/07 21:55:47 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLERROR_H
#define QHULLERROR_H

#include "road/RoadError.h"

#include <assert.h>
#include <stdexcept>
#include <string>

namespace orgQhull {

#//Types
    //! QhullError -- std::exception class for Qhull
    class QhullError;

class QhullError : public RoadError {

public:
#//Constants
    enum {
        QHULLfirstError= 10000, //MSG_QHULL_ERROR in Qhull's user.h
        QHULLlastError= 10070,
        NOthrow= 1 //! For flag to UsingLibQhull()
    };

#//Constructors
    // default constructors
    QhullError() : RoadError() {};
    QhullError(int code, const std::string &message) : RoadError(code, message) {};
    QhullError(int code, const char *fmt) : RoadError(code, fmt) {};
    QhullError(int code, const char *fmt, int d) : RoadError(code, fmt, d) {};
    QhullError(int code, const char *fmt, int d, int d2) : RoadError(code, fmt, d, d2) {};
    QhullError(int code, const char *fmt, int d, int d2, float f) : RoadError(code, fmt, d, d2, f) {};
    QhullError(int code, const char *fmt, int d, int d2, float f, const char *s) : RoadError(code, fmt, d, d2, f, s) {};
    QhullError(int code, const char *fmt, int d, int d2, float f, const void *x) : RoadError(code, fmt, d, d2, f, x) {};
    QhullError(int code, const char *fmt, int d, int d2, float f, int i) : RoadError(code, fmt, d, d2, f, i) {};
    QhullError(int code, const char *fmt, int d, int d2, float f, long long i) : RoadError(code, fmt, d, d2, f, i) {};
    QhullError(int code, const char *fmt, int d, int d2, float f, double e) : RoadError(code, fmt, d, d2, f, e) {};

};//class QhullError

#ifndef QHULL_1
    #define QHULL_ASSERT assert

#endif

}//namespace orgQhull

#//Global functions

inline std::ostream &operator<<(std::ostream &os, const orgQhull::QhullError &e) { return os << e.what(); }

#endif // QHULLERROR_H
