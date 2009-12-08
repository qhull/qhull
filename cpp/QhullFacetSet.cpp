/****************************************************************************
**
** Copyright (C) 2008-2009 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/QhullFacetSet.cpp#16 $$Change: 1102 $
** $DateTime: 2009/12/07 20:26:04 $$Author: bbarber $
**
****************************************************************************/

#//! QhullFacetSet -- Qhull's linked facets, as a C++ class

#include "QhullFacet.h"
#include "QhullFacetSet.h"
#include "QhullPoint.h"
#include "QhullRidge.h"
#include "QhullVertex.h"

using std::string;
using std::vector;

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4
#pragma warning( disable : 4611)  // interaction between '_setjmp' and C++ object destruction is non-portable
#pragma warning( disable : 4996)  // function was declared deprecated(strcpy, localtime, etc.)
#endif

namespace orgQhull {

#//Read-only

bool QhullFacetSet::
contains(const QhullFacet &facet) const
{
    if(isSelectAll()){
        return QhullSet<QhullFacet>::contains(facet);
    }
    for(QhullFacetSet::const_iterator i=begin(); i != end(); ++i){
        QhullFacet f= *i;
        if(f==facet && f.isGood()){
            return true;
        }
    }
    return false;
}//contains

int QhullFacetSet::
count() const
{
    if(isSelectAll()){
        return QhullSet<QhullFacet>::count();
    }
    int counter= 0;
    for(QhullFacetSet::const_iterator i=begin(); i != end(); ++i){
        QhullFacet f= *i;
        if(f.isGood()){
            counter++;
        }
    }
    return counter;
}//count

int QhullFacetSet::
count(const QhullFacet &facet) const
{
    if(isSelectAll()){
        return QhullSet<QhullFacet>::count(facet);
    }
    int counter= 0;
    for(QhullFacetSet::const_iterator i=begin(); i != end(); ++i){
        QhullFacet f= *i;
        if(f==facet && f.isGood()){
            counter++;
        }
    }
    return counter;
}//count

}//namespace orgQhull

#//Global functions

using std::endl;
using std::ostream;
using orgQhull::QhullFacet;
using orgQhull::QhullFacetSet;
using orgQhull::UsingLibQhull;

ostream &
operator<<(ostream &os, const QhullFacetSet &fs)
{
    os<< fs.print(UsingLibQhull::NOqhRunId, "");
    return os;
}//<<QhullFacetSet

ostream &

operator<<(ostream &os, const QhullFacetSet::PrintFacetSet &pr)
{
    QhullFacetSet fs= *pr.facet_set;
    for(QhullFacetSet::iterator i=fs.begin(); i != fs.end(); ++i){
        QhullFacet f= *i;
        if(fs.isSelectAll() || f.isGood()){
            os<< f.print(pr.run_id);
        }
    }
    return os;
}//<< QhullFacetSet::PrintFacetSet

//! Print facet identifiers to stream.  Space prefix.  From qh_printfacetheader [io.c]
ostream &
operator<<(ostream &os, const QhullFacetSet::PrintIdentifiers &p)
{
    os<< p.message;
    for(QhullFacetSet::const_iterator i=p.facet_set->begin(); i!=p.facet_set->end(); ++i){
        const QhullFacet f= *i;
        if(f.getFacetT()==qh_MERGEridge){
            os<< " MERGE";
        }else if(f.getFacetT()==qh_DUPLICATEridge){
            os<< " DUP";
        }else if(p.facet_set->isSelectAll() || f.isGood()){
            os<< " f" << f.id();
        }
    }
    os<< endl;
    return os;
}//<<QhullFacetSet::PrintIdentifiers

