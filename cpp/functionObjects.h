/****************************************************************************
**
** Copyright (C) 2008-2009 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/functionObjects.h#4 $$Change: 1114 $
** $DateTime: 2009/12/12 13:49:07 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHFUNCTIONOBJECTS_H
#define QHFUNCTIONOBJECTS_H

#include <stdlib.h> // abs()

namespace orgQhull {
#//Type

    //! Sum of absolute values of the elements in a container
    class AbsoluteSumOf; 
    //! Sum of the elements in a container
    class SumOf; 
    //! Sum of squares of the elements in a container
    class SumSquaresOf; 

#//Class

//! Absolute sum of the elements in a container
class AbsoluteSumOf
{
private:
    double sum;
public:
    inline AbsoluteSumOf() : sum(0.0) {}
    inline void operator()(double v) { sum += abs(v); }
    inline operator double() { return sum; }
};//AbsoluteSumOf

//! Sum of the elements in a container
class SumOf
{
private:
    double sum;
public:
    inline SumOf() : sum(0.0) {}
    inline void operator()(double v) { sum += v; }
    inline operator double() { return sum; }
};//SumOf


//! Sum of squares of the elements in a container
class SumSquaresOf
{
private:
    double sum;
public:
    inline SumSquaresOf() : sum(0.0) {}
    inline void operator()(double v) { sum += v*v; }
    inline operator double() { return sum; }
};//SumSquaresOf


}//orgQhull


#endif //QHFUNCTIONOBJECTS_H

