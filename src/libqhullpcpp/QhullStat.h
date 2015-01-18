/****************************************************************************
**
** Copyright (c) 2008-2012 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullpcpp/QhullStat.h#2 $$Change: 1675 $
** $DateTime: 2014/02/01 09:38:20 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLSTAT_H
#define QHULLSTAT_H

extern "C" {
    #include "libqhull/qhull_a.h"
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
#//!\name Fields
    //! No fields       POD type equivalent to qhstatT.  No data or virtual members

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
