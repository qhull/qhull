/****************************************************************************
**
** Copyright (C) 2009-2009 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/QhullPoints.cpp#15 $$Change: 1111 $
** $DateTime: 2009/12/10 22:15:38 $$Author: bbarber $
**
****************************************************************************/

#include "QhullPoints.h"

#include <iostream>
#include <algorithm>

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4
#endif

namespace orgQhull {

#//Read-only

bool QhullPoints::
operator==(const QhullPoints &other) const
{
    if(point_dimension!=other.point_dimension || (point_end-point_first) != (other.point_end-other.point_first)){
        return false;
    }
    const coordT *c= point_first;
    const coordT *c2= other.point_first;
    while(c<point_end){
        if(*c++!=*c2++){
            return false;
        }
    }
    return true;
}//operator==


#//ElementAccess
QhullPoints QhullPoints::
mid(int index, int length) const
{
    int n= count();
    if(index<0 || index>=n){
        n= 0;
    }else if(length<0 || index+length>=n){
        n -= index;
    }else{
        n -= index+length;
    }
    return QhullPoints(point_dimension, n*point_dimension, point_first+index*point_dimension);
}//mid

QhullPoint QhullPoints::
value(int index) const
{
    QhullPoint p;
    if(index>=0 && index<count()){
        p.defineAs(point_dimension, point_first+index*point_dimension);
    }
    return p;
}//value

QhullPoint QhullPoints::
value(int index, QhullPoint &defaultValue) const
{
    QhullPoint p;
    if(index>=0 && index<count()){
        p.defineAs(point_dimension, point_first+index*point_dimension);
    }else{
        p.defineAs(defaultValue);
    }
    return p;
}//value

#//Search

bool QhullPoints::
contains(const QhullPoint &t) const
{
    const_iterator i= begin();
    while(i != end()){
        if(*i==t){
            return true;
        }
        i++;
    }
    return false;
}//contains

int QhullPoints::
count(const QhullPoint &t) const
{
    int n= 0;
    const_iterator i= begin();
    while(i != end()){
        if(*i==t){
            ++n;
        }
        i++;
    }
    return n;
}//count

int QhullPoints::
indexOf(const coordT *coordinates) const
{
    if(!includesCoordinates(coordinates) || dimension()==0){
        return -1;
    }
    size_t offset= coordinates-point_first;
    int index= (int)offset/dimension(); // int for error reporting
    int extra= (int)offset%dimension();
    if(extra!=0){
        throw QhullError(10066, "Qhull error: coordinates %x are not at point boundary (extra %d at index %d)", extra, index, 0.0, coordinates);
    }
    return index;
}//indexOf coordT

int QhullPoints::
indexOf(const coordT *coordinates, int noThrow) const
{
    size_t extra= 0;
    if(noThrow){
        if(!includesCoordinates(coordinates)||dimension()==0){
            return -1;
        }
        extra= (coordinates-point_first)%dimension();
    }
    return indexOf(coordinates-extra);
}//indexOf coordT noThrow

int QhullPoints::
indexOf(const QhullPoint &t) const
{
    int j=0;
    const_iterator i= begin();
    while(i!=end()){
        if(*i==t){
            return j;
        }
        ++i;
        ++j;
    }
    return -1;
}//indexOf

int QhullPoints::
lastIndexOf(const QhullPoint &t) const
{
    int j=count();
    const_iterator i= end();
    while(i != begin()){
        --i;
        --j;
        if(*i==t){
            return j;
        }
    }
    return -1;
}//lastIndexOf

#//QhullPointsIterator

bool QhullPointsIterator::
findNext(const QhullPoint &p)
{
    while(i!=ps->constEnd()){
        if(*i++ == p){
            return true;
        }
    }
    return false;
}//findNext

bool QhullPointsIterator::
findPrevious(const QhullPoint &p)
{
    while(i!=ps->constBegin()){
        if(*--i == p){
            return true;
        }
    }
    return false;
}//findPrevious

}//namespace orgQhull

#//Global functions

using std::ostream;
using orgQhull::QhullPoint;
using orgQhull::QhullPoints;
using orgQhull::QhullPointsIterator;

ostream &
operator<<(ostream &os, const QhullPoints &p)
{
    QhullPointsIterator i(p);
    while(i.hasNext()){
        os<< i.next();
    }
    return os;
}//operator<<QhullPoints

ostream &
operator<<(ostream &os, const QhullPoints::PrintPoints &pr)
{
    os<< pr.point_message;
    QhullPoints ps= *pr.points;
    for(QhullPoints::iterator i=ps.begin(); i != ps.end(); ++i){
        QhullPoint p= *i;
        if(pr.with_identifier){
            os<< p.printWithIdentifier(pr.run_id, "");
        }else{
            os<< p.print(pr.run_id, "");
        }
    }
    return os;
}//<<PrintPoints
