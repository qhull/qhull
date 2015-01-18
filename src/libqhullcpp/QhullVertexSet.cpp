/****************************************************************************
**
** Copyright (c) 2009-2014 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullVertexSet.cpp#11 $$Change: 1799 $
** $DateTime: 2014/12/17 16:17:40 $$Author: bbarber $
**
****************************************************************************/

#//! QhullVertexSet -- Qhull's linked Vertexs, as a C++ class

#include "QhullVertex.h"
#include "QhullVertexSet.h"
#include "QhullPoint.h"
#include "QhullRidge.h"
#include "QhullVertex.h"
#include "Qhull.h"

#include "UsingLibQhull.h"

using std::string;
using std::vector;

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4
#pragma warning( disable : 4611)  /* interaction between '_setjmp' and C++ object destruction is non-portable */
                                    /* setjmp should not be implemented with 'catch' */
#endif

namespace orgQhull {

QhullVertexSet::
QhullVertexSet(const Qhull &q, facetT *facetlist, setT *facetset, bool allfacets)
: QhullSet<QhullVertex>(q.qh(), 0)
, qhsettemp_defined(false)
{
    QH_TRY_(q.qh()){ // no object creation -- destructors skipped on longjmp()
        setT *vertices= qh_facetvertices(q.qh(), facetlist, facetset, allfacets);
        defineAs(vertices);
        qhsettemp_defined= true;
    }
    q.qh()->maybeThrowQhullMessage(QH_TRY_status);
}//QhullVertexSet facetlist facetset

QhullVertexSet::
QhullVertexSet(QhullQh *qh, facetT *facetlist, setT *facetset, bool allfacets)
: QhullSet<QhullVertex>(qh, 0)
, qhsettemp_defined(false)
{
    QH_TRY_(qh){ // no object creation -- destructors skipped on longjmp()
        setT *vertices= qh_facetvertices(qh, facetlist, facetset, allfacets);
        defineAs(vertices);
        qhsettemp_defined= true;
    }
    qh->maybeThrowQhullMessage(QH_TRY_status);
}//QhullVertexSet facetlist facetset

//! Copy constructor for argument passing and returning a result
//! Only copies a pointer to the set.
//! If qhsettemp_defined, transfers ownership to destination, otherwise the set will be freed twice
//! If qhsettemp_defined and passed by value, the set will be empty on return to caller
QhullVertexSet::
QhullVertexSet(QhullVertexSet &other) 
: QhullSet<QhullVertex>(other)
, qhsettemp_defined(other.qhsettemp_defined)
{
    other.qhsettemp_defined= false;
    other.forceEmpty();
}//copy constructor

//! Copy assignment only copies a pointer to the set.
//! If qhsettemp_defined, transfers ownership to destination, otherwise the set will be freed twice
//! If qhsettemp_defined and passed by value, the set will be empty on return to caller
//! 'other' is not 'const' due to ownership transfer
QhullVertexSet & QhullVertexSet::
operator=(QhullVertexSet &other) 
{
    QhullSet<QhullVertex>::operator=(other);
    qhsettemp_defined= other.qhsettemp_defined;
    other.qhsettemp_defined= false;
    other.forceEmpty();
    return *this;
}//copy constructor

void QhullVertexSet::
freeQhSetTemp()
{
    if(qhsettemp_defined){
        qhsettemp_defined= false;
        QH_TRY_(qh()){ // no object creation -- destructors skipped on longjmp()
            qh_settempfree(qh(), referenceSetT()); // errors if not top of tempstack or if qhmem corrupted
        }
        qh()->maybeThrowQhullMessage(QH_TRY_status, QhullError::NOthrow);
    }
}//freeQhSetTemp

QhullVertexSet::
~QhullVertexSet()
{
    freeQhSetTemp();
}//~QhullVertexSet

}//namespace orgQhull

#//!\name Global functions

using std::endl;
using std::ostream;
using orgQhull::QhullPoint;
using orgQhull::QhullVertex;
using orgQhull::QhullVertexSet;
using orgQhull::QhullVertexSetIterator;
using orgQhull::UsingLibQhull;

//! Print Vertex identifiers to stream.  Space prefix.  From qh_printVertexheader [io_r.c]
ostream &
operator<<(ostream &os, const QhullVertexSet::PrintIdentifiers &pr)
{
    if(pr.print_message && *pr.print_message){
        os << pr.print_message;
    }
    for(QhullVertexSet::const_iterator i= pr.vertex_set->begin(); i!=pr.vertex_set->end(); ++i){
        const QhullVertex v= *i;
        os << " v" << v.id();
    }
    os << endl;
    return os;
}//<<QhullVertexSet::PrintIdentifiers

//! Duplicate of printvertices [io_r.c]
ostream &
operator<<(ostream &os, const QhullVertexSet::PrintVertexSet &pr){

    os << pr.print_message;
    const QhullVertexSet *vs= pr.vertex_set;
    QhullVertexSetIterator i= *vs;
    while(i.hasNext()){
        const QhullVertex v= i.next();
        const QhullPoint p= v.point();
        os << " p" << p.id() << "(v" << v.id() << ")";
    }
    os << endl;

    return os;
}//<< PrintVertexSet


