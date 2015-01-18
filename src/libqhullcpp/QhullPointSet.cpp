/****************************************************************************
**
** Copyright (c) 2009-2014 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullPointSet.cpp#13 $$Change: 1801 $
** $DateTime: 2014/12/17 22:37:12 $$Author: bbarber $
**
****************************************************************************/

#include "QhullPointSet.h"

#include <iostream>
#include <algorithm>

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4
#endif

namespace orgQhull {

#//!\name Conversions

/************** FIXUP
// See qt-qhull.cpp for QList conversion

#ifndef QHULL_NO_STL
std::vector<QhullPoint> QhullPointSet::
toStdVector() const
{
    QhullPointSetIterator i(*this);
    std::vector<QhullPoint> vs;
    while(i.hasNext()){
        vs.push_back(i.next());
    }
    return vs;
}//toStdVector
#endif //QHULL_NO_STL

#//!\name GetSet

bool QhullPointSet::
operator==(const QhullPointSet &o) const
{
    if(dimension()!=o.dimension() || count()!=o.count()){
        return false;
    }
    QhullPointSetIterator i(*this);
    QhullPointSetIterator j(o);
    while(i.hasNext()){
        if(i.next()!=j.next()){
            return false;
        }
    }
    return true;
}//operator==

//! Derived from QhullSet::value
//! Returns QhullPoint() on error
QhullPoint QhullPointSet::
value(countT idx) const
{
    // Avoid error in qh_setsize() and assert in elementPointer()
    //const T *n= reinterpret_cast<const T *>(&SETelem_(getSetT(), idx));
    void **n= reinterpret_cast<void **>(&SETelem_(getSetT(), idx));
    coordT **n2= reinterpret_cast<coordT **>(n);
    if(idx>=0 && n<endPointer()){
        return QhullPoint(qh(), *n2);
    }else{
        return QhullPoint(qh());
    }
}//value

//! Non-const since copy is an alias
//! Derived from QhullSet::value
QhullPoint QhullPointSet::
value(countT idx, QhullPoint &defaultValue) const
{
    // Avoid call to qh_setsize() and assert in elementPointer()
    void **n= reinterpret_cast<void **>(&SETelem_(getSetT(), idx));
    coordT **n2= reinterpret_cast<coordT **>(n);
    if(idx>=0 && n<endPointer()){
        return QhullPoint(qh(), dimension(), *n2);
    }else{
        return defaultValue;
    }
}//value

#//!\name Methods

bool QhullPointSet::
contains(const QhullPoint &t) const
{
    QhullPointSetIterator i(*this);
    while(i.hasNext()){
        if(i.next()==t){
            return true;
        }
    }
    return false;
}//contains

countT QhullPointSet::
count(const QhullPoint &t) const
{
    countT n= 0;
    QhullPointSetIterator i(*this);
    while(i.hasNext()){
        if(i.next()==t){
            ++n;
        }
    }
    return n;
}//count

countT QhullPointSet::
indexOf(const QhullPoint &t) const
{
    countT idx= 0;
    QhullPointSetIterator i(*this);
    while(i.hasNext()){
        if(i.next()==t){
            return idx;
        }
        ++idx;
    }
    return -1;
}//indexOf

countT QhullPointSet::
lastIndexOf(const QhullPoint &t) const
{
    countT idx= count()-1;
    QhullPointSetIterator i(*this);
    i.toBack();
    while(i.hasPrevious()){
        if(i.previous()==t){
            break;
        }
        --idx;
    }
    return idx;
}//lastIndexOf
*/
/**************** FIXUP
#//QhullPointSetIterator

bool QhullPointSetIterator::
findNext(const QhullPoint &p)
{
    while(i!=c->constEnd()){
        if(*i++ == p){
            return true;
        }
    }
    return false;
}//findNext

bool QhullPointSetIterator::
findPrevious(const QhullPoint &p)
{
    while(i!=c->constBegin()){
        if(*(--i) == p){
            return true;
        }
    }
    return false;
}//findPrevious
*/

}//namespace orgQhull

#//!\name Global functions

using std::endl;
using std::ostream;
using orgQhull::QhullPoint;
using orgQhull::QhullPointSet;
using orgQhull::QhullPointSetIterator;

ostream &
operator<<(ostream &os, const QhullPointSet::PrintIdentifiers &pr)
{
    os << pr.print_message;
    const QhullPointSet s= *pr.point_set;
    QhullPointSetIterator i(s);
    while(i.hasNext()){
        if(i.hasPrevious()){
            os << " ";
        }
        const QhullPoint point= i.next();
        countT id= point.id();
        os << "p" << id;

    }
    os << endl;
    return os;
}//PrintIdentifiers

ostream &
operator<<(ostream &os, const QhullPointSet::PrintPointSet &pr)
{
    os << pr.print_message;
    const QhullPointSet s= *pr.point_set;
    for(QhullPointSet::const_iterator i=s.begin(); i != s.end(); ++i){
        const QhullPoint point= *i;
        os << point;
    }
    return os;
}//printPointSet


