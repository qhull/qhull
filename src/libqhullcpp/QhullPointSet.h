/****************************************************************************
**
** Copyright (c) 2009-2014 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullPointSet.h#14 $$Change: 1801 $
** $DateTime: 2014/12/17 22:37:12 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLPOINTSET_H
#define QHULLPOINTSET_H

#include "QhullSet.h"
#include "QhullPoint.h"
extern "C" {
    #include "libqhullr/qhull_ra.h"
}

#include <ostream>

namespace orgQhull {

#//!\name Used here
    class Qhull;
    class QhullPoint;

#//!\name Defined here
    //! QhullPointSet -- a set of coordinate pointers with input dimension
    // with const_iterator and iterator
    class QhullPointSet;

class QhullPointSet : public QhullSet<QhullPoint> {

private:
#//!\name Fields
    // no fields
public:

#//!\name Construct
                        QhullPointSet(const Qhull &q, setT *s) : QhullSet<QhullPoint>(q, s) {}
                        //Conversion from setT* is not type-safe.  Implicit conversion for void* to T
                        QhullPointSet(QhullQh *qh, setT *s) : QhullSet<QhullPoint>(qh, s) {}
                        //Copy constructor copies pointer but not contents.  Needed for return by value and parameter passing.
                        QhullPointSet(const QhullPointSet &other) : QhullSet<QhullPoint>(other) {}
    QhullPointSet &     operator=(const QhullPointSet &other) { QhullSet<QhullPoint>::operator=(other); }
                        ~QhullPointSet() {}

                        //!Default constructor disabled.
private:
                        QhullPointSet();
public:

#//!\name IO
    struct PrintIdentifiers{
        const QhullPointSet *point_set;
        const char *    print_message;
        PrintIdentifiers(const char *message, const QhullPointSet *s) : point_set(s), print_message(message) {}
    };//PrintIdentifiers
    PrintIdentifiers printIdentifiers(const char *message) const { return PrintIdentifiers(message, this); }

    struct PrintPointSet{
        const QhullPointSet *point_set;
        const char *    print_message;
        PrintPointSet(const char *message, const QhullPointSet &s) : point_set(&s), print_message(message) {}
    };//PrintPointSet
    PrintPointSet       print(const char *message) const { return PrintPointSet(message, *this); }

};//QhullPointSet

typedef QhullSetIterator<QhullPoint>  QhullPointSetIterator;

}//namespace orgQhull

#//!\name Global

std::ostream &operator<<(std::ostream &os, const orgQhull::QhullPointSet::PrintIdentifiers &pr);
std::ostream &operator<<(std::ostream &os, const orgQhull::QhullPointSet::PrintPointSet &pr);

#endif // QHULLPOINTSET_H
