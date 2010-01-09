/****************************************************************************
**
** Copyright (C) 2009-2010 C.B. Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/QhullHyperplane.h#12 $$Change: 1167 $
** $DateTime: 2010/01/08 19:03:17 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHHYPERPLANE_H
#define QHHYPERPLANE_H

#include "QhullError.h"
#include "QhullIterator.h"
#include "UsingLibQhull.h"
extern "C" {
    #include "../src/qhull_a.h"
};

#include <ostream>

namespace orgQhull {
#//ClassRef
    class QhullPoint;

#//Types
    //! QhullHyperplane as an offset, dimension, and pointer to coordinates
    class QhullHyperplane;
    //! Java-style iterator for QhullHyperplane coordinates
    class QhullHyperplaneIterator;

class QhullHyperplane { // Similar to QhullPoint

private:
#//Fields
    coordT             *hyperplane_coordinates;  // Keep pointers aligned
    int                 hyperplane_dimension;
    coordT              hyperplane_offset;

public:
#//Subtypes
    typedef const coordT *                  iterator;
    typedef const coordT *                  const_iterator;
    typedef QhullHyperplane::iterator       Iterator;
    typedef QhullHyperplane::const_iterator ConstIterator;

#//Construct
                        QhullHyperplane() : hyperplane_coordinates(0), hyperplane_dimension(0), hyperplane_offset(0.0) {};
                        QhullHyperplane(int dimension, coordT *c, coordT offset) : hyperplane_coordinates(c), hyperplane_dimension(dimension), hyperplane_offset(offset) {}
                        // Creates an alias.  Does not copy the point.  Needed for parameter passing
                        QhullHyperplane(const QhullHyperplane &other)  : hyperplane_coordinates(other.hyperplane_coordinates), hyperplane_dimension(other.hyperplane_dimension), hyperplane_offset(other.hyperplane_offset) {}
                        // Creates an alias.  Does not copy the point.  Needed for vector<QhullHyperplane>
    QhullHyperplane    &operator=(const QhullHyperplane &other) { hyperplane_coordinates= other.hyperplane_coordinates; hyperplane_dimension= other.hyperplane_dimension; hyperplane_offset= other.hyperplane_offset; return *this; }
                       ~QhullHyperplane() {}

#//Conversions --
//! Includes offset at end
#ifndef QHULL_NO_STL
    std::vector<coordT> toStdVector() const;
#endif //QHULL_NO_STL
#ifdef QHULL_USES_QT
    QList<coordT>       toQList() const;
#endif //QHULL_USES_QT

#//Read-only
public:
    const coordT       *coordinates() const { return hyperplane_coordinates; }
    coordT             *coordinates() { return hyperplane_coordinates; }
    int                 dimension() const { return hyperplane_dimension; }
    bool                isDefined() const { return hyperplane_coordinates!=0 && hyperplane_dimension>0; }
    coordT              offset() const { return hyperplane_offset; }

#//Define
    void                defineAs(int dimension, coordT *c, coordT offset) { QHULL_ASSERT(dimension>=0); hyperplane_coordinates= c; hyperplane_dimension= dimension; hyperplane_offset= offset; }
    //! Creates an alias to other
    void                defineAs(QhullHyperplane &other) { hyperplane_coordinates= other.coordinates(); hyperplane_dimension= other.dimension();  hyperplane_offset= other.offset(); }
    void                setCoordinates(coordT *c) { hyperplane_coordinates= c; }
    void                setDimension(int dimension) { hyperplane_dimension= dimension; }
    void                setOffset(coordT c) { hyperplane_offset= c; }

#//value
    double              distance(const QhullPoint &p) const;
    double              norm() const;

#//iterator
    iterator            begin() { return hyperplane_coordinates; }
    const_iterator      begin() const { return hyperplane_coordinates; }
    const_iterator      constBegin() const { return hyperplane_coordinates; }
    const_iterator      constEnd() const { return hyperplane_coordinates+hyperplane_dimension; }
    int                 count() { return dimension(); }
    iterator            end() { return hyperplane_coordinates+hyperplane_dimension; }
    const_iterator      end() const { return hyperplane_coordinates+hyperplane_dimension; }
    size_t              size() { return (size_t)dimension(); }

#//Operator
    bool                operator==(const QhullHyperplane &other) const;
    bool                operator!=(const QhullHyperplane &other) const { return !operator==(other); }
    const coordT       &operator[](int idx) const { QHULL_ASSERT(idx>=0 && idx<hyperplane_dimension); return *(hyperplane_coordinates+idx); }
    coordT             &operator[](int idx) { QHULL_ASSERT(idx>=0 && idx<hyperplane_dimension); return *(hyperplane_coordinates+idx); }

#//IO
    struct PrintHyperplane{
        const QhullHyperplane  *hyperplane;  
        const char     *hyperplane_message;
        const char     *hyperplane_offset_message;
                        PrintHyperplane(const char *message, const char *offsetMessage, const QhullHyperplane &p) : hyperplane(&p), hyperplane_message(message), hyperplane_offset_message(offsetMessage) {}
    };//PrintHyperplane
    PrintHyperplane          print() const { return  PrintHyperplane(0, 0, *this); }
    PrintHyperplane          print(const char *message, const char *offsetMessage) const { return PrintHyperplane(message, offsetMessage, *this); }

};//QhullHyperplane

QHULL_DECLARE_SEQUENTIAL_ITERATOR(QhullHyperplane, coordT)

}//namespace orgQhull

#//Global functions

std::ostream &operator<<(std::ostream &os, const orgQhull::QhullHyperplane::PrintHyperplane &pr);
std::ostream &operator<<(std::ostream &os, const orgQhull::QhullHyperplane &p); //FIXUP QH10000 -- multiple instances if define here

#endif // QHHYPERPLANE_H

