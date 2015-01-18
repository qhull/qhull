/****************************************************************************
**
** Copyright (c) 2009-2015 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullpcpp/QhullVertexSet.h#3 $$Change: 1810 $
** $DateTime: 2015/01/17 18:28:15 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLVERTEXSET_H
#define QHULLVERTEXSET_H

#include "QhullSet.h"

#include <ostream>

namespace orgQhull {

#//!\name ClassRef
    class QhullVertex;

#//!\name Types
    //! QhullVertexSet -- a set of Qhull Vertices, as a C++ class.
    //! See Qhull
    class QhullVertexSet;
    typedef QhullSetIterator<QhullVertex>
                        QhullVertexSetIterator;

class QhullVertexSet : public QhullSet<QhullVertex> {

private:
#//!\name Fields
    Qhull *             qhsettemp_qhull; //! For sets allocated with qh_settemp()
    bool                qhsettemp_defined;  //! Set was allocated with q_memalloc()

public:
#//!\name Constructor
                        //Conversion from setT* is not type-safe.  Implicit conversion for void* to T
   explicit             QhullVertexSet(setT *s) : QhullSet<QhullVertex>(s), qhsettemp_qhull(0), qhsettemp_defined(false) {}
                        QhullVertexSet(int qhRunId, facetT *facetlist, setT *facetset, bool allfacets);
                        //Copy constructor copies pointer but not contents.  Needed for return by value.
                        QhullVertexSet(const QhullVertexSet &o) : QhullSet<QhullVertex>(o), qhsettemp_qhull(o.qhsettemp_qhull), qhsettemp_defined(o.qhsettemp_defined) {}
                        ~QhullVertexSet();

private:
                        //!Disable default constructor and copy assignment.  See QhullSetBase
                        QhullVertexSet();
    QhullVertexSet &     operator=(const QhullVertexSet &);
public:

#//!\name Constructor, destructor
    void                freeQhSetTemp();

#//!\name IO
    struct PrintVertexSet{
        const QhullVertexSet *Vertex_set;
        const char *    print_message;
        int             run_id;
                        PrintVertexSet(int qhRunId, const char *message, const QhullVertexSet *s) : Vertex_set(s), print_message(message), run_id(qhRunId) {}
    };//PrintVertexSet
    const PrintVertexSet       print(int qhRunId, const char *message) const { return PrintVertexSet(qhRunId, message, this); }

    struct PrintIdentifiers{
        const QhullVertexSet *Vertex_set;
        const char *    print_message;
                        PrintIdentifiers(const char *message, const QhullVertexSet *s) : Vertex_set(s), print_message(message) {}
    };//PrintIdentifiers
    PrintIdentifiers    printIdentifiers(const char *message) const { return PrintIdentifiers(message, this); }

};//class QhullVertexSet

}//namespace orgQhull

#//!\name Global

std::ostream &operator<<(std::ostream &os, const orgQhull::QhullVertexSet::PrintVertexSet &pr);
std::ostream &operator<<(std::ostream &os, const orgQhull::QhullVertexSet::PrintIdentifiers &p);
inline std::ostream &operator<<(std::ostream &os, const orgQhull::QhullVertexSet &vs) { os << vs.print(orgQhull::UsingLibQhull::NOqhRunId, ""); return os; }

#endif // QHULLVERTEXSET_H
