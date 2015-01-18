/****************************************************************************
**
** Copyright (c) 2008-2015 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullRidge.h#12 $$Change: 1810 $
** $DateTime: 2015/01/17 18:28:15 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLRIDGE_H
#define QHULLRIDGE_H

#include "QhullSet.h"
#include "QhullVertex.h"
#include "QhullVertexSet.h"
#include "QhullFacet.h"
extern "C" {
    #include "libqhullr/qhull_ra.h"
}

#include <ostream>

namespace orgQhull {

#//!\name Used here
    class Qhull;
    class QhullVertex;
    class QhullVertexSet;
    class QhullFacet;

#//!\name Defined here
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

#//!\name Defined here
public:
    typedef ridgeT *   base_type;  // for QhullRidgeSet

#//!\name Fields
private:
    ridgeT *            qh_ridge;
    QhullQh *           qh_qh;

#//!\name Class objects
    static ridgeT       s_empty_ridge;

public:
#//!\name Constants

#//!\name Constructors
    explicit            QhullRidge(const Qhull &q);
                        QhullRidge(const Qhull &q, ridgeT *r);
    explicit            QhullRidge(QhullQh *qh) : qh_ridge(&s_empty_ridge), qh_qh(qh) {}
                        QhullRidge(QhullQh *qh, ridgeT *r) : qh_ridge(r ? r : &s_empty_ridge), qh_qh(qh) {}
                        // Creates an alias.  Does not copy QhullRidge.  Needed for return by value and parameter passing
                        QhullRidge(const QhullRidge &other) : qh_ridge(other.qh_ridge), qh_qh(other.qh_qh) {}
                        // Creates an alias.  Does not copy QhullRidge.  Needed for vector<QhullRidge>
    QhullRidge &        operator=(const QhullRidge &other) { qh_ridge= other.qh_ridge; qh_qh= other.qh_qh; return *this; }
                        ~QhullRidge() {}

#//!\name GetSet
    QhullFacet          bottomFacet() const { return QhullFacet(qh_qh, qh_ridge->bottom); }
    int                 dimension() const { return qh_qh->hull_dim; }
    ridgeT *            getBaseT() const { return getRidgeT(); } //!< For QhullSet<QhullRidge>
    ridgeT *            getRidgeT() const { return qh_ridge; }
    countT              id() const { return qh_ridge->id; }
    bool                isDefined() const { return qh_ridge != &s_empty_ridge; }
    bool                operator==(const QhullRidge &other) const { return qh_ridge==other.qh_ridge; }
    bool                operator!=(const QhullRidge &other) const { return !operator==(other); }
    QhullFacet          otherFacet(const QhullFacet &f) const { return QhullFacet(qh_qh, (qh_ridge->top==f.getFacetT() ? qh_ridge->bottom : qh_ridge->top)); }
    QhullFacet          topFacet() const { return QhullFacet(qh_qh, qh_ridge->top); }

#//!\name foreach
    bool                hasNextRidge3d(const QhullFacet &f) const;
    QhullRidge          nextRidge3d(const QhullFacet &f) const { return nextRidge3d(f, 0); }
    QhullRidge          nextRidge3d(const QhullFacet &f, QhullVertex *nextVertex) const;
    QhullVertexSet      vertices() const { return QhullVertexSet(qh_qh, qh_ridge->vertices); }

#//!\name IO

    struct PrintRidge{
        const QhullRidge *ridge;
        const char *    print_message;
                        PrintRidge(const char *message, const QhullRidge &r) : ridge(&r), print_message(message) {}
    };//PrintRidge
    PrintRidge          print(const char* s) const { return PrintRidge(s, *this); }
};//class QhullRidge

}//namespace orgQhull

std::ostream &operator<<(std::ostream &os, const orgQhull::QhullRidge &r); 
std::ostream &operator<<(std::ostream &os, const orgQhull::QhullRidge::PrintRidge &pr);

#endif // QHULLRIDGE_H
