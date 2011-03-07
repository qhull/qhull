/****************************************************************************
**
** Copyright (C) 2008-2010 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullStat.h#1 $$Change: 1330 $
** $DateTime: 2011/03/06 21:30:00 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLSTAT_H
#define QHULLSTAT_H

extern "C" {
    #include "../src/qhull_a.h"
};

#include <string>
#include <vector>

namespace orgQhull {

#//defined here
    //! QhullStat -- Qhull's statistics, qhstatT, as a C++ class
    //! Statistics defined with zzdef_() control Qhull's behavior, summarize its result, and report precision problems.
    class QhullStat;

class QhullStat : public qhstatT {

private:
#//Fields (empty) -- POD type equivalent to qhstatT.  No data or virtual members

public:
#//Constants

#//class methods
    static void         clearStatistics();

#//constructor, assignment, destructor, invariant
                        QhullStat();
                       ~QhullStat();

private:
    //!disable copy constructor and assignment
                        QhullStat(const QhullStat &);
    QhullStat          &operator=(const QhullStat &);
public:

#//Access
};//class QhullStat

}//namespace orgQhull

#endif // QHULLSTAT_H
