/****************************************************************************
**
** Copyright (c) 2008-2012 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullpcpp/QhullFacetSet.h#2 $$Change: 1675 $
** $DateTime: 2014/02/01 09:38:20 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLFACETSET_H
#define QHULLFACETSET_H

#include "QhullSet.h"

#include <ostream>

namespace orgQhull {

#//!\name ClassRef
    class QhullFacet;

#//!\name Types
    //! QhullFacetSet -- a set of Qhull facets, as a C++ class.  See QhullFacetList.h
    class QhullFacetSet;
    typedef QhullSetIterator<QhullFacet>
                        QhullFacetSetIterator;

class QhullFacetSet : public QhullSet<QhullFacet> {

private:
#//!\name Fields
    bool                select_all;   //! True if include bad facets.  Default is false.

public:
#//!\name Constructor
                        //Conversion from setT* is not type-safe.  Implicit conversion for void* to T
   explicit             QhullFacetSet(setT *s) : QhullSet<QhullFacet>(s), select_all(false) {}
                        //Copy constructor copies pointer but not contents.  Needed for return by value and parameter passing.
                        QhullFacetSet(const QhullFacetSet &o) : QhullSet<QhullFacet>(o), select_all(o.select_all) {}

private:
                        //!Disable default constructor and copy assignment.  See QhullSetBase
                        QhullFacetSet();
    QhullFacetSet &     operator=(const QhullFacetSet &);
public:

#//!\name Conversion
#ifndef QHULL_NO_STL
    std::vector<QhullFacet> toStdVector() const;
#endif //QHULL_NO_STL
#ifdef QHULL_USES_QT
    QList<QhullFacet>   toQList() const;
#endif //QHULL_USES_QT

#//!\name GetSet
    bool                isSelectAll() const { return select_all; }
    void                selectAll() { select_all= true; }
    void                selectGood() { select_all= false; }

#//!\name Read-only
                        //! Filtered by facet.isGood().  May be 0 when !isEmpty().
    int                 count() const;
    bool                contains(const QhullFacet &f) const;
    int                 count(const QhullFacet &f) const;
                        //! operator==() does not depend on isGood()

#//!\name IO
    // Not same as QhullFacetList#IO.  A QhullFacetSet is a component of a QhullFacetList.

    struct PrintFacetSet{
        const QhullFacetSet *facet_set;
        const char *    print_message;
        int             run_id;
                        PrintFacetSet(int qhRunId, const char *message, const QhullFacetSet *s) : facet_set(s), print_message(message), run_id(qhRunId) {}
    };//PrintFacetSet
    const PrintFacetSet       print(int qhRunId, const char *message) const { return PrintFacetSet(qhRunId, message, this); }

    struct PrintIdentifiers{
        const QhullFacetSet *facet_set;
        const char *    print_message;
                        PrintIdentifiers(const char *message, const QhullFacetSet *s) : facet_set(s), print_message(message) {}
    };//PrintIdentifiers
    PrintIdentifiers    printIdentifiers(const char *message) const { return PrintIdentifiers(message, this); }

};//class QhullFacetSet

}//namespace orgQhull

#//!\name Global

std::ostream &operator<<(std::ostream &os, const orgQhull::QhullFacetSet &fs);
std::ostream &operator<<(std::ostream &os, const orgQhull::QhullFacetSet::PrintFacetSet &pr);
std::ostream &operator<<(std::ostream &os, const orgQhull::QhullFacetSet::PrintIdentifiers &p);

#endif // QHULLFACETSET_H
