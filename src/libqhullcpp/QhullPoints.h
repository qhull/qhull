/****************************************************************************
**
** Copyright (c) 2009-2014 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullPoints.h#11 $$Change: 1712 $
** $DateTime: 2014/03/30 22:34:33 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLPOINTS_H
#define QHULLPOINTS_H

#include "QhullPoint.h"
extern "C" {
    #include "libqhullr/qhull_ra.h"
}

#include <ostream>

namespace orgQhull {

#//!\name Defined here
    class QhullPoints;          //!< One or more points Coordinate pointers with dimension and iterators
    class QhullPointsIterator;  //!< Java-style iterator

class QhullPoints {

private:
#//!\name Fields
    coordT *            point_first; //!< First coordinate of an array of points of point_dimension
    coordT *            point_end;   //!< End of point coordinates (end>=first).  Trailing coordinates ignored
    QhullQh *           qh_qh;       //!< Maybe initialized NULL to allow ownership by RboxPoints
    int                 point_dimension;  //!< Dimension, >=0

public:
#//!\name Subtypes
    class const_iterator;
    class iterator;
    typedef QhullPoints::const_iterator ConstIterator;
    typedef QhullPoints::iterator       Iterator;

#//!\name Construct
    explicit            QhullPoints(const Qhull &q);
                        QhullPoints(const Qhull &q, int pointDimension);
                        QhullPoints(const Qhull &q, int pointDimension, countT coordinateCount2, coordT *c);
    explicit            QhullPoints(QhullQh *qh) : point_first(0), point_end(0), qh_qh(qh), point_dimension(qh ? qh->hull_dim : 0) {}
                        QhullPoints(QhullQh *qh, int pointDimension) : point_first(0), point_end(0), qh_qh(qh), point_dimension(pointDimension) { QHULL_ASSERT(pointDimension>=0); }
                        QhullPoints(QhullQh *qh, int pointDimension, countT coordinateCount2, coordT *c);
                        //! Copy constructor copies pointers but not contents.  Needed for return by value and parameter passing.
                        QhullPoints(const QhullPoints &other)  : point_first(other.point_first), point_end(other.point_end), qh_qh(other.qh_qh), point_dimension(other.point_dimension) {}
    QhullPoints &       operator=(const QhullPoints &other) { point_first= other.point_first; point_end= other.point_end; qh_qh= other.qh_qh; point_dimension= other.point_dimension; return *this; }
                        ~QhullPoints() {}

public:

#//!\name Conversion

#ifndef QHULL_NO_STL
    std::vector<QhullPoint> toStdVector() const;
#endif //QHULL_NO_STL
#ifdef QHULL_USES_QT
    QList<QhullPoint>   toQList() const;
#endif //QHULL_USES_QT

#//!\name GetSet
    QhullPoint          at(countT idx) const { /* point_first==0 caught by point_end assert */ coordT *p= point_first+idx*point_dimension; QHULL_ASSERT(p<point_end); return QhullPoint(qh_qh, point_dimension, p); }
    QhullPoint          back() const { return last(); }
    ConstIterator       begin() const { return ConstIterator(*this); }
    Iterator            begin() { return Iterator(*this); }
    ConstIterator       constBegin() const { return ConstIterator(*this); }
    const coordT *      constData() const { return point_first; }
    ConstIterator       constEnd() const { return ConstIterator(qh_qh, point_end); }
    coordT *            coordinates() const { return point_first; }
    countT              coordinateCount() const { return (countT)(point_end-point_first); } // WARN64
    countT              count() const { return (countT)size(); } // WARN64
    coordT *            data() { return point_first; }
    const coordT *      data() const { return point_first; }
    void                defineAs(countT coordinatesCount, coordT *c) { QHULL_ASSERT((coordinatesCount>=0 && c!=0) || (c==0 && coordinatesCount==0)); point_first= c; point_end= c+coordinatesCount; }
    void                defineAs(const QhullPoints &other) { point_first= other.point_first; point_end= other.point_end; qh_qh= other.qh_qh; point_dimension= other.point_dimension; }
    int                 dimension() const { return point_dimension; }
    ConstIterator       end() const { return ConstIterator(qh_qh, point_end); }
    Iterator            end() { return Iterator(qh_qh, point_end); }
    coordT *            extraCoordinates() const { return extraCoordinatesCount() ? (point_end-extraCoordinatesCount()) : 0; }
    countT              extraCoordinatesCount() const;  // WARN64
    QhullPoint          first() const { return QhullPoint(qh_qh, point_dimension, point_first); }
    QhullPoint          front() const { return first(); }
    bool                includesCoordinates(const coordT *c) const { return c>=point_first && c<point_end; }
    bool                isEmpty() const { return point_end==point_first; }
    QhullPoint          last() const { QHULL_ASSERT(point_first!=0); return QhullPoint(qh_qh, point_dimension, point_end - point_dimension); }
    bool                operator==(const QhullPoints &other) const;
    bool                operator!=(const QhullPoints &other) const { return !operator==(other); }
    QhullPoint          operator[](countT idx) const { return at(idx); }
    QhullQh *           qh() const { return qh_qh; }
    void                setDimension(int d) { point_dimension= d; }
    void                setQhullQh(QhullQh *qh);
    size_t              size() const { return point_dimension ? (point_end-point_first)/point_dimension : 0; }
    QhullPoint          value(countT idx) const;
    // Non-const since copy is an alias
    QhullPoint          value(countT idx, QhullPoint &defaultValue) const;

#//!\name Methods
    bool                contains(const QhullPoint &t) const;
    countT              count(const QhullPoint &t) const;
    countT              indexOf(const coordT *pointCoordinates) const;
    countT              indexOf(const coordT *pointCoordinates, int noThrow) const;
    countT              indexOf(const QhullPoint &t) const;
    countT              lastIndexOf(const QhullPoint &t) const;
    //! Returns a subset of the points, not a copy
    QhullPoints         mid(countT idx, countT length= -1) const;

#//!\name QhullPoints::iterator
    // Modeled on qvector.h and qlist.h
    // before const_iterator for conversion with comparison operators
    // See: QhullSet.h
    class iterator : public QhullPoint {

    public:
        typedef std::random_access_iterator_tag  iterator_category;
        typedef QhullPoint      value_type;
        typedef value_type *    pointer;
        typedef value_type &    reference;
        typedef ptrdiff_t       difference_type;

        explicit        iterator(const QhullPoints &ps) : QhullPoint(ps.qh(), ps.dimension(), ps.coordinates()) {}
                        iterator(const Qhull &q, coordT *c): QhullPoint(q, c) {}
                        iterator(const Qhull &q, int pointDimension, coordT *c): QhullPoint(q, pointDimension, c) {}
                        iterator(QhullQh *qh, coordT *c): QhullPoint(qh, c) {}
                        iterator(QhullQh *qh, int pointDimension, coordT *c): QhullPoint(qh, pointDimension, c) {}
                        iterator(const iterator &other): QhullPoint(*other) {}
        iterator &      operator=(const iterator &other) { defineAs( const_cast<iterator &>(other)); return *this; }
 
        QhullPoint *    operator->() { return this; }
        // value instead of reference since advancePoint() modifies self
        QhullPoint      operator*() const { return *this; }
        QhullPoint      operator[](countT idx) const { QhullPoint n= *this; n.advancePoint(idx); return n; }
        bool            operator==(const iterator &o) const { return point_coordinates==o.point_coordinates; }
        bool            operator!=(const iterator &o) const { return !operator==(o); }
        bool            operator<(const iterator &o) const  { return point_coordinates < o.point_coordinates; }
        bool            operator<=(const iterator &o) const { return point_coordinates <= o.point_coordinates; }
        bool            operator>(const iterator &o) const  { return point_coordinates > o.point_coordinates; }
        bool            operator>=(const iterator &o) const { return point_coordinates >= o.point_coordinates; }
        // reinterpret_cast to break circular dependency
        bool            operator==(const QhullPoints::const_iterator &o) const { QHULL_ASSERT(qh_qh==reinterpret_cast<const iterator &>(o).qh_qh); return point_coordinates==reinterpret_cast<const iterator &>(o).point_coordinates; }
        bool            operator!=(const QhullPoints::const_iterator &o) const { return !operator==(reinterpret_cast<const iterator &>(o)); }
        bool            operator<(const QhullPoints::const_iterator &o) const  { QHULL_ASSERT(qh_qh==reinterpret_cast<const iterator &>(o).qh_qh); return point_coordinates < reinterpret_cast<const iterator &>(o).point_coordinates; }
        bool            operator<=(const QhullPoints::const_iterator &o) const { QHULL_ASSERT(qh_qh==reinterpret_cast<const iterator &>(o).qh_qh); return point_coordinates <= reinterpret_cast<const iterator &>(o).point_coordinates; }
        bool            operator>(const QhullPoints::const_iterator &o) const  { QHULL_ASSERT(qh_qh==reinterpret_cast<const iterator &>(o).qh_qh); return point_coordinates > reinterpret_cast<const iterator &>(o).point_coordinates; }
        bool            operator>=(const QhullPoints::const_iterator &o) const { QHULL_ASSERT(qh_qh==reinterpret_cast<const iterator &>(o).qh_qh); return point_coordinates >= reinterpret_cast<const iterator &>(o).point_coordinates; }
        iterator &      operator++() { advancePoint(1); return *this; }
        iterator        operator++(int) { iterator n= *this; operator++(); return iterator(n); }
        iterator &      operator--() { advancePoint(-1); return *this; }
        iterator        operator--(int) { iterator n= *this; operator--(); return iterator(n); }
        iterator &      operator+=(countT idx) { advancePoint(idx); return *this; }
        iterator &      operator-=(countT idx) { advancePoint(-idx); return *this; }
        iterator        operator+(countT idx) const { iterator n= *this; n.advancePoint(idx); return n; }
        iterator        operator-(countT idx) const { iterator n= *this; n.advancePoint(-idx); return n; }
        difference_type operator-(iterator o) const { QHULL_ASSERT(qh_qh==o.qh_qh && point_dimension==o.point_dimension); return (point_dimension ? (point_coordinates-o.point_coordinates)/point_dimension : 0); }
    };//QhullPoints::iterator

#//!\name QhullPoints::const_iterator
    //!\todo FIXUP QH11018 const_iterator same as iterator
    class const_iterator : public QhullPoint {

    public:
        typedef std::random_access_iterator_tag  iterator_category;
        typedef QhullPoint          value_type;
        typedef const value_type *  pointer;
        typedef const value_type &  reference;
        typedef ptrdiff_t           difference_type;

                        const_iterator(const QhullPoints::iterator &o) : QhullPoint(*o) {}
        explicit        const_iterator(const QhullPoints &ps) : QhullPoint(ps.qh(), ps.dimension(), ps.coordinates()) {}
                        const_iterator(const Qhull &q, coordT *c): QhullPoint(q, c) {}
                        const_iterator(const Qhull &q, int pointDimension, coordT *c): QhullPoint(q, pointDimension, c) {}
                        const_iterator(QhullQh *qh, coordT *c): QhullPoint(qh, c) {}
                        const_iterator(QhullQh *qh, int pointDimension, coordT *c): QhullPoint(qh, pointDimension, c) {}
                        const_iterator(const const_iterator &o) : QhullPoint(*o) {}
        const_iterator &operator=(const const_iterator &o) { defineAs(const_cast<const_iterator &>(o)); return *this; }

        // value/non-const since advancePoint(1), etc. modifies self
        QhullPoint      operator*() const { return *this; }
        QhullPoint *    operator->() { return this; }
        QhullPoint      operator[](countT idx) const { QhullPoint n= *this; n.advancePoint(idx); return n; }
        bool            operator==(const const_iterator &o) const { return point_coordinates==o.point_coordinates; }
        bool            operator!=(const const_iterator &o) const { return !operator==(o); }
        bool            operator<(const const_iterator &o) const  { return point_coordinates < o.point_coordinates; }
        bool            operator<=(const const_iterator &o) const { return point_coordinates <= o.point_coordinates; }
        bool            operator>(const const_iterator &o) const  { return point_coordinates > o.point_coordinates; }
        bool            operator>=(const const_iterator &o) const { return point_coordinates >= o.point_coordinates; }
        const_iterator &operator++() { advancePoint(1); return *this; }
        const_iterator  operator++(int) { const_iterator n= *this; operator++(); return const_iterator(n); }
        const_iterator &operator--() { advancePoint(-1); return *this; }
        const_iterator  operator--(int) { const_iterator n= *this; operator--(); return const_iterator(n); }
        const_iterator &operator+=(countT idx) { advancePoint(idx); return *this; }
        const_iterator &operator-=(countT idx) { advancePoint(-idx); return *this; }
        const_iterator  operator+(countT idx) const { const_iterator n= *this; n.advancePoint(idx); return n; }
        const_iterator  operator-(countT idx) const { const_iterator n= *this; n.advancePoint(-idx); return n; }
        difference_type operator-(const_iterator o) const { QHULL_ASSERT(qh_qh==o.qh_qh && point_dimension==o.point_dimension); return (point_dimension ? (point_coordinates-o.point_coordinates)/point_dimension : 0); }
    };//QhullPoints::const_iterator

#//!\name IO
    struct PrintPoints{
        const QhullPoints  *points;
        const char *    point_message;
        bool            with_identifier;
        PrintPoints(const char *message, bool withIdentifier, const QhullPoints &ps) : points(&ps), point_message(message), with_identifier(withIdentifier) {}
    };//PrintPoints
    PrintPoints          print() const { return  PrintPoints("", false, *this); }
    PrintPoints          print(const char *message) const { return PrintPoints(message, false, *this); }
    PrintPoints          printWithIdentifier(const char *message) const { return PrintPoints(message, true, *this); }
    //FIXUP remove message for print()?
};//QhullPoints

// Instead of QHULL_DECLARE_SEQUENTIAL_ITERATOR because next(),etc would return a reference to a temporary
class QhullPointsIterator
{
    typedef QhullPoints::const_iterator const_iterator;

#//!\name Fields
private:
    const QhullPoints  *ps;
    const_iterator      i;

public:
                        QhullPointsIterator(const QhullPoints &other) : ps(&other), i(ps->constBegin()) {}
    QhullPointsIterator &operator=(const QhullPoints &other) { ps = &other; i = ps->constBegin(); return *this; }

    bool                findNext(const QhullPoint &t);
    bool                findPrevious(const QhullPoint &t);
    bool                hasNext() const { return i != ps->constEnd(); }
    bool                hasPrevious() const { return i != ps->constBegin(); }
    QhullPoint          next() { return *i++; }
    QhullPoint          peekNext() const { return *i; }
    QhullPoint          peekPrevious() const { const_iterator p = i; return *--p; }
    QhullPoint          previous() { return *--i; }
    void                toBack() { i = ps->constEnd(); }
    void                toFront() { i = ps->constBegin(); }
};//QhullPointsIterator

}//namespace orgQhull

#//!\name Global

std::ostream &          operator<<(std::ostream &os, const orgQhull::QhullPoints &p);
std::ostream &          operator<<(std::ostream &os, const orgQhull::QhullPoints::PrintPoints &pr);

#endif // QHULLPOINTS_H
