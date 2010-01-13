/****************************************************************************
**
** Copyright (C) 2008-2010 C.B. Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/QhullVertex.cpp#24 $$Change: 1167 $
** $DateTime: 2010/01/08 19:03:17 $$Author: bbarber $
**
****************************************************************************/

#//! QhullVertex -- Qhull's vertex structure, vertexT, as a C++ class

#include "UsingLibQhull.h"
#include "QhullPoint.h"
#include "QhullFacetSet.h"
#include "QhullVertex.h"
#include "QhullVertexSet.h"
#include "QhullFacet.h"

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4
#pragma warning( disable : 4611)  // interaction between '_setjmp' and C++ object destruction is non-portable
#pragma warning( disable : 4996)  // function was declared deprecated(strcpy, localtime, etc.)
#endif

namespace orgQhull {

#//class statics
vertexT QhullVertex::
s_empty_vertex= {0,0,0,0,0,
                 0,0,0,0,0,
                 0,0};

#//ForEach
QhullFacetSet QhullVertex::
neighborFacets() const
{
    if(!qh_vertex->neighbors){
        throw QhullError(10034, "Qhull error: neighbors of vertex %d not defined.  Need to call defineVertexNeighbors().", id());
    }
    return QhullFacetSet(qh_vertex->neighbors);
}//neighborFacets

}//namespace orgQhull

#//Global functions

using std::endl;
using std::ostream;
using std::string;
using std::vector;
using orgQhull::QhullPoint;
using orgQhull::QhullFacet;
using orgQhull::QhullFacetSet;
using orgQhull::QhullFacetSetIterator;
using orgQhull::QhullVertex;
using orgQhull::UsingLibQhull;

//! Duplicate of qh_printvertex [io.c]
ostream &
operator<<(ostream &os, const QhullVertex::PrintVertex &pr)
{
    QhullVertex v= *pr.vertex;
    QhullPoint p= v.point();
    os << "- p" << p.id(pr.run_id) << " (v" << v.id() << "): ";
    const realT *c= p.coordinates();
    for(int k= p.dimension(); k--; ){
        os << " " << *c++; // FIXUP QH10010 %5.2g
    }
    if(v.getVertexT()->deleted){
        os << " deleted";
    }
    if(v.getVertexT()->delridge){
        os << " ridgedeleted";
    }
    os << endl;
    QhullFacetSetIterator i= v.neighborFacets();
    if(i.hasNext()){
        os << " neighborFacets:";
        int count= 0;
        while(i.hasNext()){
            if(++count % 100 == 0){
                os << endl << "     ";
            }
            QhullFacet f= i.next();
            os << " f" << f.id();
        }
        os << endl;
    }
    return os;
}//<< PrintVertex

