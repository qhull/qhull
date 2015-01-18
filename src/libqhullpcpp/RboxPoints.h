/****************************************************************************
**
** Copyright (c) 2008-2015 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullpcpp/RboxPoints.h#3 $$Change: 1810 $
** $DateTime: 2015/01/17 18:28:15 $$Author: bbarber $
**
****************************************************************************/

#ifndef RBOXPOINTS_H
#define RBOXPOINTS_H

#include "QhullPoint.h"
#include "PointCoordinates.h"
extern "C" {
#include "libqhull/libqhull.h"
}

#include <stdarg.h>
#include <string>
#include <vector>
#include <istream>
#include <ostream>
#include <sstream>

namespace orgQhull {

#//!\name Types
    //! RboxPoints -- generate random PointCoordinates for Qhull
    class RboxPoints;

class RboxPoints : public PointCoordinates {

private:
#//!\name Fields and friends
    int                 rbox_new_count;     //! Number of points for PointCoordinates
    int                 rbox_status;    //! error status from rboxpoints.  qh_ERRnone if none.
    std::string         rbox_message;   //! stderr from rboxpoints

    friend void ::qh_fprintf_rbox(FILE *fp, int msgcode, const char *fmt, ... );

public:
#//!\name Construct
                        RboxPoints();
    explicit            RboxPoints(const char *rboxCommand);
                        RboxPoints(const RboxPoints &other);
                        RboxPoints &operator=(const RboxPoints &other);
                        ~RboxPoints();

public:
#//!\name GetSet
    void                clearRboxMessage();
    int                 newCount() const { return rbox_new_count; }
    std::string         rboxMessage() const;
    int                 rboxStatus() const;
    bool                hasRboxMessage() const;
    void                setNewCount(int pointCount) { QHULL_ASSERT(pointCount>=0); rbox_new_count= pointCount; }

#//!\name Modify
    void                appendPoints(const char* rboxCommand);
    using               PointCoordinates::appendPoints;
    void                reservePoints() { reserveCoordinates((count()+newCount())*dimension()); }
};//class RboxPoints

}//namespace orgQhull

#endif // RBOXPOINTS_H
