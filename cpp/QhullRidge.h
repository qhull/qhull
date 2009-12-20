/****************************************************************************
**
** Copyright (C) 2008-2009 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/QhullRidge.h#19 $$Change: 1111 $
** $DateTime: 2009/12/10 22:15:38 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLRIDGE_H
#define QHULLRIDGE_H

#include "QhullSet.h"
#include "QhullVertex.h"
#include "QhullVertexSet.h"
#include "QhullFacet.h"
extern "C" {
    #include "../src/qhull_a.h"
};

#include <ostream>

namespace orgQhull {

#//ClassRef
    class QhullVertex;
    class QhullVertexSet;
    class QhullFacet;

#//Types
    //! QhullRidge -- Qhull's ridge structure, ridgeT [libqhull.h], as a C++ class
    class QhullRidge;
    typedef QhullSet<QhullRidge>  QhullRidgeSet;
    typedef QhullSetIterator<QhullRidge>  QhullRidgeSetIterator;

    // see QhullSets.h for QhullRidgeSet and QhullRidgeSetIterator -- avoids circular references
   
/************************
a ridge is hull_dim-1 simplex between two neighboring facets.  If the
facets are non-simplicial, there may be more than one ridge between
two facets.  E.G. a 4-d hypercube has two triangles between each pair
of neighboring facets.

topological information:
    vertices            a set of vertices
    top,bottom          neighboring facets with orientation

geometric information:
    tested              True if ridge is clearly convex
    nonconvex           True if ridge is non-convex
*/

class QhullRidge {

#//Fields
    ridgeT             *qh_ridge;

#//Class objects
    static ridgeT       s_empty_ridge;

public:
#//Constants

#//Constructors
                        QhullRidge() : qh_ridge(&s_empty_ridge) {} 
                        //! Shallow copy
                        QhullRidge(const QhullRidge &o) : qh_ridge(o.qh_ridge) {}
    QhullRidge         &operator=(const QhullRidge &o) { qh_ridge= o.qh_ridge; return *this; }
                       ~QhullRidge() {}

#//Conversion
                        //Implicit conversion from ridgeT
                        QhullRidge(ridgeT *r) : qh_ridge(r ? r : &s_empty_ridge) {}
    ridgeT             *getRidgeT() const { return qh_ridge; }

#//QhullSet<QhullRidge>
    ridgeT             *getBaseT() const { return getRidgeT(); }

#//getSet
    QhullFacet          bottomFacet() const { return QhullFacet(qh_ridge->bottom); }
    int                 dimension() const { return QhullSetBase::count(qh_ridge->vertices); }
    int                 id() const { return qh_ridge->id; }
    bool                isDefined() const { return qh_ridge != &s_empty_ridge; }
    bool                operator==(const QhullRidge &o) const { return qh_ridge==o.qh_ridge; }
    bool                operator!=(const QhullRidge &o) const { return !operator==(o); }
    QhullFacet          otherFacet(QhullFacet f) const { return QhullFacet(qh_ridge->top==f.getFacetT() ? qh_ridge->bottom : qh_ridge->top); }
    QhullFacet          topFacet() const { return QhullFacet(qh_ridge->top); }

#//forEach
    QhullRidge          nextRidge3d(const QhullFacet f) const { return nextRidge3d(f, 0); }
    QhullRidge          nextRidge3d(const QhullFacet f, QhullVertex *nextVertex) const;
    QhullVertexSet      vertices() const { return QhullVertexSet(qh_ridge->vertices); }

#//IO

    struct PrintRidge{
        const QhullRidge *ridge; 
        int             run_id;
                        PrintRidge(int qhRunId, const QhullRidge &r) : ridge(&r), run_id(qhRunId) {} 
    };//PrintRidge
    PrintRidge          print(int qhRunId) const { return PrintRidge(qhRunId, *this); }
};//class QhullRidge

}//namespace orgQhull

std::ostream &operator<<(std::ostream &os, const orgQhull::QhullRidge &r); //FIXUP no conversion.  OK in .cpp  { os<< r.print(orgQhull::UsingLibQhull::NOqhRunId); return os; }
std::ostream &operator<<(std::ostream &os, const orgQhull::QhullRidge::PrintRidge &pr);

#endif // QHULLRIDGE_H
