/****************************************************************************
**
** Copyright (C) 2008-2009 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/QhullStat.h#7 $$Change: 1053 $
** $DateTime: 2009/10/02 22:00:28 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLSTAT_H
#define QHULLSTAT_H

#include <string>
#include <vector>

extern "C" {
    #include "../src/qhull_a.h"
};

namespace orgQhull {

#//defined here
    //! QhullStat -- Qhull's statistics, qhstatT, as a C++ class
    //! Statistics defined with zzdef_() control Qhull's behavior, summarize its result, and report precision problems.
    class QhullStat;

class QhullStat : public qhstatT {

public:
#//class methods
    static void         clearStatistics();
                    
#//Constants

#//Fields (empty) -- POD type equivalent to qhstatT.  No data or virtual members

public:
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
