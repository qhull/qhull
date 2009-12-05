/****************************************************************************
**
** Copyright (C) 2009-2009 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/Coordinates.cpp#13 $$Change: 1087 $
** $DateTime: 2009/11/22 23:02:55 $$Author: bbarber $
**
****************************************************************************/

#include <algorithm>
#include <iostream>

#include "Coordinates.h"
#include "functionObjects.h"
#include "QhullError.h"

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4
#endif

namespace orgQhull {

#//! Coordinates -- vector of coordT (normally double)

#//Element access

// Inefficient without result-value-optimization or implicitly shared object
Coordinates Coordinates::
mid(int index, int length) const
{
    int newLength= length;
    if(length<0 || index+length > count()){
        newLength= count()-index;
    }
    Coordinates result;
    if(newLength>0){
        copy(begin()+index, begin()+(index+newLength), back_inserter(result));
    }
    return result;
}//mid

coordT Coordinates::
value(int index, const coordT &defaultValue) const
{
    return ((index < 0 || index >= count()) ? defaultValue : (*this)[index]);
}//value

#//Operator

Coordinates Coordinates::
operator+(const Coordinates &other) const
{
    Coordinates result(*this);
    copy(other.begin(), other.end(), back_inserter(result));
    return result;
}//operator+

Coordinates & Coordinates::
operator+=(const Coordinates &other)
{
    if(&other==this){
        Coordinates clone(other);
        copy(clone.begin(), clone.end(), back_inserter(*this));
    }else{
        copy(other.begin(), other.end(), back_inserter(*this));
    }
    return *this;
}//operator+=

#//Read-write

coordT Coordinates::
takeAt(int index)
{
    coordT c= at(index);
    erase(begin()+index);
    return c;
}//takeAt

coordT Coordinates::
takeLast()
{
    coordT c= last();
    removeLast();
    return c;
}//takeLast

void Coordinates::
swap(int index, int other)
{
    coordT c= at(index);
    at(index)= at(other);
    at(other)= c;
}//swap

#//Search

bool Coordinates::
contains(const coordT &t) const
{
    CoordinatesIterator i(*this);
    return i.findNext(t);
}//contains

int Coordinates::
count(const coordT &t) const
{
    CoordinatesIterator i(*this);
    int result= 0;
    while(i.findNext(t)){
        ++result;
    }
    return result;
}//count

int Coordinates::
indexOf(const coordT &t, int from) const
{
    if(from<0){
        from += count();
        if(from<0){
            from= 0;
        }
    }
    if(from<count()){
        const_iterator i= begin()+from;
        while(i!=constEnd()){
            if(*i==t){
                return (static_cast<int>(i-begin())); // WARN64
            }
            ++i;
        }
    }
    return -1;
}//indexOf

int Coordinates::
lastIndexOf(const coordT &t, int from) const
{
    if(from<0){
        from += count();
    }else if(from>=count()){
        from= count()-1;
    }
    if(from>=0){
        const_iterator i= begin()+from+1;
        while(i-- != constBegin()){
            if(*i==t){
                return (static_cast<int>(i-begin())); // WARN64
            }
        }
    }
    return -1;
}//lastIndexOf

void Coordinates::
removeAll(const coordT &t)
{
    MutableCoordinatesIterator i(*this);
    while(i.findNext(t)){
        i.remove();
    }
}//removeAll

}//namespace orgQhull

#//Global functions

using std::endl;
using std::istream;
using std::ostream;
using std::string;
using std::ws;
using orgQhull::Coordinates;

ostream &
operator<<(ostream &os, const Coordinates &cs)
{
    Coordinates::const_iterator c= cs.begin();
    for(int i=cs.count(); i--; ){
        os<< *c++ << " ";
    }
    return os;
}//operator<<

