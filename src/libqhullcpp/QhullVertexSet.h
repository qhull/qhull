/****************************************************************************
**
** Copyright (c) 2009-2015 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullVertexSet.h#11 $$Change: 1810 $
** $DateTime: 2015/01/17 18:28:15 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLVERTEXSET_H
#define QHULLVERTEXSET_H

#include "QhullSet.h"

#include <ostream>

namespace orgQhull {

#//!\name Used here
    class QhullVertex;

#//!\name Defined here
    //! QhullVertexSet -- a set of Qhull Vertices, as a C++ class.
    //! See Qhull
    class QhullVertexSet;
    typedef QhullSetIterator<QhullVertex> QhullVertexSetIterator;

class QhullVertexSet : public QhullSet<QhullVertex> {

private:
#//!\name Fields
    bool                qhsettemp_defined;  //! Set was allocated with qh_settemp()

public:
#//!\name Constructor
                        QhullVertexSet(const Qhull &q, setT *s) : QhullSet<QhullVertex>(q, s), qhsettemp_defined(false) {}
                        QhullVertexSet(const Qhull &q, facetT *facetlist, setT *facetset, bool allfacets);
                        //Conversion from setT* is not type-safe.  Implicit conversion for void* to T
                        QhullVertexSet(QhullQh *qh, setT *s) : QhullSet<QhullVertex>(qh, s), qhsettemp_defined(false) {}
                        QhullVertexSet(QhullQh *qh, facetT *facetlist, setT *facetset, bool allfacets);
                        //Copy constructor copies pointer but not contents.  Needed for return by value.
                        QhullVertexSet(QhullVertexSet &other);
    QhullVertexSet &    operator=(QhullVertexSet &other);
                        ~QhullVertexSet();

private:
                        //!Default constructor disabled.  Will implement allocation later
                        QhullVertexSet();
public:

#//!\name Destructor
    void                freeQhSetTemp();

#//!\name IO
    struct PrintVertexSet{
        const QhullVertexSet *vertex_set;
        const char *    print_message;
                        
                        PrintVertexSet(const char *message, const QhullVertexSet *s) : vertex_set(s), print_message(message) {}
    };//PrintVertexSet
    const PrintVertexSet print(const char *message) const { return PrintVertexSet(message, this); }

    struct PrintIdentifiers{
        const QhullVertexSet *vertex_set;
        const char *    print_message;
                        PrintIdentifiers(const char *message, const QhullVertexSet *s) : vertex_set(s), print_message(message) {}
    };//PrintIdentifiers
    PrintIdentifiers    printIdentifiers(const char *message) const { return PrintIdentifiers(message, this); }

};//class QhullVertexSet

}//namespace orgQhull

#//!\name Global

std::ostream &operator<<(std::ostream &os, const orgQhull::QhullVertexSet::PrintVertexSet &pr);
std::ostream &operator<<(std::ostream &os, const orgQhull::QhullVertexSet::PrintIdentifiers &p);
inline std::ostream &operator<<(std::ostream &os, const orgQhull::QhullVertexSet &vs) { os << vs.print(""); return os; }

#endif // QHULLVERTEXSET_H
