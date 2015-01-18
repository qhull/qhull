/****************************************************************************
**
** Copyright (c) 2008-2014 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullStat.h#8 $$Change: 1707 $
** $DateTime: 2014/03/26 09:42:11 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLSTAT_H
#define QHULLSTAT_H

extern "C" {
    #include "libqhullr/qhull_ra.h"
}

#include <string>
#include <vector>

namespace orgQhull {

#//!\name defined here
    //! QhullStat -- Qhull's statistics, qhstatT, as a C++ class
    //! Statistics defined with zzdef_() control Qhull's behavior, summarize its result, and report precision problems.
    class QhullStat;

class QhullStat : public qhstatT {

private:
#//!\name Fields (empty) -- POD type equivalent to qhstatT.  No data or virtual members

public:
#//!\name Constants

#//!\name class methods
    static void         clearStatistics();

#//!\name constructor, assignment, destructor, invariant
                        QhullStat();
                        ~QhullStat();

private:
    //!disable copy constructor and assignment
                        QhullStat(const QhullStat &);
    QhullStat &         operator=(const QhullStat &);
public:

#//!\name Access
};//class QhullStat

}//namespace orgQhull

#endif // QHULLSTAT_H
