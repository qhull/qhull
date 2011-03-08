/****************************************************************************
**
** Copyright (c) 2008-2011 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullFacet.h#3 $$Change: 1342 $
** $DateTime: 2011/03/07 21:55:47 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLFACET_H
#define QHULLFACET_H

#include "Coordinates.h"
#include "QhullHyperplane.h"
#include "QhullPoint.h"
#include "QhullSet.h"
#include "QhullPointSet.h"
extern "C" {
    #include "libqhull/qhull_a.h"
};

#include <string>
#include <vector>
#include <ostream>

namespace orgQhull {

#//ClassRef
    class QhullFacetSet;
    class QhullRidge;
    typedef QhullSet<QhullRidge>  QhullRidgeSet;
    class QhullVertex;
    class QhullVertexSet;

#//Types
    //! QhullFacet -- Qhull's facet structure, facetT [libqhull.h], as a C++ class
    class QhullFacet;

//! A QhullFacet is the C++ equivalent to Qhull's facetT*
class QhullFacet {

private:
#//Fields -- no additions (QhullFacetSet of facetT*)
    facetT             *qh_facet;  //! May be 0 (!isDefined) for corner cases (e.g., *facetSet.end()==0) and tricoplanarOwner()

#//Class objects
    static facetT       s_empty_facet; // needed for shallow copy

public:
#//Constants

#//Constructors
                        QhullFacet() : qh_facet(&s_empty_facet) {}
                        // Creates an alias.  Does not copy QhullFacet.  Needed for return by value and parameter passing
                        QhullFacet(const QhullFacet &o) : qh_facet(o.qh_facet ? o.qh_facet : &s_empty_facet) {}
                        // Creates an alias.  Does not copy QhullFacet.  Needed for vector<QhullFacet>
    QhullFacet         &operator=(const QhullFacet &o) { qh_facet= o.qh_facet ? o.qh_facet : &s_empty_facet; return *this; }
                       ~QhullFacet() {}

#//Conversion
                        //Implicit conversion from facetT
                        QhullFacet(facetT *f) : qh_facet(f ? f : &s_empty_facet) {}
                        // Do not define facetT().  It conflicts with return type facetT*
    facetT             *getFacetT() const { return qh_facet; }

#//QhullSet<QhullFacet>
    facetT             *getBaseT() const { return getFacetT(); }

#//getSet
    int                 dimension() const;
    int                 id() const { return qh_facet ? qh_facet->id : -1; }
    bool                isDefined() const { return qh_facet && qh_facet != &s_empty_facet; }
    bool                isGood() const { return qh_facet && qh_facet->good; }
    QhullFacet          next() const { return qh_facet->next; }
    bool                operator==(const QhullFacet &o) const { return qh_facet==o.qh_facet; }
    bool                operator!=(const QhullFacet &o) const { return !operator==(o); }
    QhullFacet          previous() const { return qh_facet->previous; }
    QhullFacet          tricoplanarOwner() const;

    QhullPoint          getCenter(int qhRunId) { return getCenter(qhRunId, qh_PRINTpoints); }
    QhullPoint          getCenter(int qhRunId, qh_PRINT printFormat);
    QhullHyperplane     hyperplane() const { return QhullHyperplane(dimension(), qh_facet->normal, qh_facet->offset); }
    QhullHyperplane     innerplane(int qhRunId) const;
    QhullHyperplane     outerplane(int qhRunId) const;
    QhullPoint          voronoiVertex(int qhRunId);

#//value
    //! Undefined if c.size() != dimension()
    double              distance(const Coordinates &c) const { return distance(c.data()); }
    double              distance(const pointT *p) const { return distance(QhullPoint(dimension(), const_cast<coordT *>(p))); }
    double              distance(const QhullPoint &p) const { return hyperplane().distance(p); }
    double              facetArea(int qhRunId);

#//foreach
    // Can not inline.  Otherwise circular reference
    QhullPointSet       coplanarPoints() const;
    QhullFacetSet       neighborFacets() const;
    QhullPointSet       outsidePoints() const;
    QhullRidgeSet       ridges() const;
    QhullVertexSet      vertices() const;

#//IO
    struct PrintCenter{
        QhullFacet     *facet;  // non-const due to facet.center()
        const char     *message;
        int             run_id;
        qh_PRINT        print_format;
                        PrintCenter(int qhRunId, QhullFacet &f, qh_PRINT printFormat, const char * s) : facet(&f), message(s), run_id(qhRunId), print_format(printFormat){}
    };//PrintCenter
    PrintCenter         printCenter(int qhRunId, qh_PRINT printFormat, const char *message) { return PrintCenter(qhRunId, *this, printFormat, message); }

    struct PrintFacet{
        QhullFacet     *facet;  // non-const due to f->center()
        int             run_id;
                        PrintFacet(int qhRunId, QhullFacet &f) : facet(&f), run_id(qhRunId) {}
    };//PrintFacet
    PrintFacet          print(int qhRunId) { return PrintFacet(qhRunId, *this); }

    struct PrintFlags{
        const QhullFacet *facet;
        const char     *message;
                        PrintFlags(const QhullFacet &f, const char *s) : facet(&f), message(s) {}
    };//PrintFlags
    PrintFlags          printFlags(const char *message) const { return PrintFlags(*this, message); }

    struct PrintHeader{
        QhullFacet     *facet;  // non-const due to f->center()
        int             run_id;
                        PrintHeader(int qhRunId, QhullFacet &f) : facet(&f), run_id(qhRunId) {}
    };//PrintHeader
    PrintHeader         printHeader(int qhRunId) { return PrintHeader(qhRunId, *this); }

    struct PrintRidges{
        const QhullFacet *facet;
        int             run_id;
                        PrintRidges(int qhRunId, QhullFacet &f) : facet(&f), run_id(qhRunId) {}
    };//PrintRidges
    PrintRidges         printRidges(int qhRunId) { return PrintRidges(qhRunId, *this); }

};//class QhullFacet

}//namespace orgQhull

#//Global functions

std::ostream &operator<<(std::ostream &os, const orgQhull::QhullFacet::PrintCenter &pr);
std::ostream &operator<<(std::ostream &os, const orgQhull::QhullFacet::PrintFlags &pr);
std::ostream &operator<<(std::ostream &os, const orgQhull::QhullFacet::PrintHeader &pr);
std::ostream &operator<<(std::ostream &os, const orgQhull::QhullFacet::PrintRidges &pr);
std::ostream &operator<<(std::ostream &os, const orgQhull::QhullFacet::PrintFacet &pr);
std::ostream &operator<<(std::ostream &os, orgQhull::QhullFacet &f); // non-const due to qh_getcenter()

#endif // QHULLFACET_H
