/****************************************************************************
**
** Copyright (C) 2009-2009 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/QhullPoints.h#19 $$Change: 1098 $
** $DateTime: 2009/12/04 22:47:59 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLPOINTS_H
#define QHULLPOINTS_H

#include "QhullPoint.h"
#include <ostream>

extern "C" {
    #include "../src/qhull_a.h"
};

namespace orgQhull {

#//Types
    //! coordinate pointer with dimension
    // with const_iterator and iterator
    class QhullPoints;
    //! Java-style iterator
    class QhullPointsIterator;

class QhullPoints {

public:
#//Types
    // QhullPoints consists of pointers into an array of coordinates.
    class               const_iterator;
    class               iterator;
    typedef QhullPoints::const_iterator ConstIterator;
    typedef QhullPoints::iterator Iterator;

#//Field
    coordT             *point_first;
    coordT             *point_end;  // end>=first.  Trailing coordinates ignored
    int                 point_dimension;  // >= 0

public:
#//Construct
                        QhullPoints() : point_first(0), point_end(0), point_dimension(0) {};
                        QhullPoints(int dimension) : point_first(0), point_end(0), point_dimension(dimension) { QHULL_ASSERT(dimension>=0); }
                        QhullPoints(int dimension, int coordinateCount, coordT *c) : point_first(c), point_end(c+coordinateCount), point_dimension(dimension) { QHULL_ASSERT(dimension>=0 && coordinateCount>=0 ); }
                        QhullPoints(const QhullPoints &other)  : point_first(other.point_first), point_end(other.point_end), point_dimension(other.point_dimension) {}
                       ~QhullPoints() {}

//disabled since p= p2 is ambiguous (coord* vs coord)
private:
    QhullPoints        &operator=(const QhullPoints &other) { point_first= other.point_first; point_end= other.point_end; point_dimension= other.point_dimension; return *this; }
public:
#//Conversion
    const coordT       *constData() const { return coordinates(); }
    // See coordinates()
    coordT             *data() { return coordinates(); }
    const coordT       *data() const { return coordinates(); }
#ifndef QHULL_NO_STL
    std::vector<QhullPoint> toStdVector() const;
#endif //QHULL_NO_STL
#ifdef QHULL_USES_QT
    QList<QhullPoint>   toQList() const;
#endif //QHULL_USES_QT

#//GetSet
    coordT             *coordinates() const { return point_first; }
    int			coordinateCount() const { return (int)(point_end-point_first); } // WARN64
    int		        count() const { return (int)size(); } // WARN64
    void                defineAs(int dimension, int coordinateCount, coordT *c) { QHULL_ASSERT(dimension>=0 && coordinateCount>=0 && c!=0); point_first= c; point_end= c+coordinateCount; point_dimension= dimension; }
    void                defineAs(int coordinateCount, coordT *c) { QHULL_ASSERT((coordinateCount>=0 && c!=0) || (c==0 && coordinateCount==0)); point_first= c; point_end= c+coordinateCount; }
    void                defineAs(const QhullPoints &other) { point_first= other.point_first; point_end= other.point_end; point_dimension= other.point_dimension; }
    int		        dimension() const { return point_dimension; }
    bool                empty() const { return point_end==point_first; }
    coordT             *extraCoordinates() const { return extraCoordinatesCount() ? (point_end-extraCoordinatesCount()) : 0; }
    int			extraCoordinatesCount() const { return point_dimension>0 ? (int)(point_end-point_first)%point_dimension : 0; }  // WARN64
    bool                includesCoordinates(const coordT *coordinates) const { return coordinates>=point_first && coordinates<point_end; }
    bool                isEmpty() const { return empty(); }
    bool                operator==(const QhullPoints &other) const;
    bool                operator!=(const QhullPoints &other) const { return !operator==(other); }
    void                setDimension(int dimension) { QHULL_ASSERT(dimension>=0); point_dimension= dimension; } 
    size_t	        size() const { return (point_dimension ? (point_end-point_first)/point_dimension : 0); }

#//ElementAccess -- can not return references to QhullPoint
    QhullPoint          at(int index) const { coordT *p= point_first+index*point_dimension; QHULL_ASSERT(p<point_end); return QhullPoint(point_dimension, p); }
    QhullPoint          back() const { return last(); }
    QhullPoint          first() const { return QhullPoint(point_dimension, point_first); }
    QhullPoint          front() const { return first(); }
    QhullPoint          last() const { return QhullPoint(point_dimension, point_end - point_dimension); }
    //! Returns a subset of the points, not a copy
    QhullPoints         mid(int index, int length= -1) const;
    QhullPoint          operator[](int index) const { return at(index); }
    QhullPoint          value(int index) const;
    // Non-const since copy is an alias
    QhullPoint          value(int index, QhullPoint &defaultValue) const;

#//Foreach
    ConstIterator       begin() const { return ConstIterator(*this); }
    Iterator            begin() { return Iterator(*this); }
    ConstIterator       constBegin() const { return ConstIterator(*this); }
    ConstIterator       constEnd() const { return ConstIterator(point_dimension, point_end); }
    ConstIterator       end() const { return ConstIterator(point_dimension, point_end); }
    Iterator            end() { return Iterator(point_dimension, point_end); }

#//Search
    bool                contains(const QhullPoint &t) const;
    int                 count(const QhullPoint &t) const;
    int                 indexOf(const coordT *coordinates) const;
    int                 indexOf(const coordT *coordinates, int noThrow) const;
    int                 indexOf(const QhullPoint &t) const;
    int                 lastIndexOf(const QhullPoint &t) const;

#//QhullPoints::iterator -- modeled on qvector.h and qlist.h
    // before const_iterator for conversion with comparison operators
    // See: QhullSet.h
    class iterator : public QhullPoint {

    public:
        typedef std::random_access_iterator_tag  iterator_category;
        typedef ptrdiff_t   difference_type;
        typedef QhullPoint  value_type;
        typedef QhullPoint *pointer;
        typedef QhullPoint &reference;

                        iterator() : QhullPoint() {}
                        iterator(const iterator &o): QhullPoint(*o) {}
        explicit        iterator(const QhullPoints &ps) : QhullPoint(ps.dimension(), ps.coordinates()) {}
        explicit        iterator(int dimension, coordT *c): QhullPoint(dimension, c) {}
        iterator       &operator=(const iterator &o) { defineAs( const_cast<iterator &>(o)); return *this; }
        QhullPoint     *operator->() { return this; }
        // value instead of reference since advancePoint() modifies self
        QhullPoint      operator*() const { return *this; }
        QhullPoint      operator[](int index) const { QhullPoint n= *this; n.advancePoint(index); return n; }
        bool            operator==(const iterator &o) const { QHULL_ASSERT(dimension()==o.dimension()); return coordinates()==o.coordinates(); }
        bool            operator!=(const iterator &o) const { return !operator==(o); }
        bool            operator<(const iterator &o) const  { QHULL_ASSERT(dimension()==o.dimension()); return coordinates() < o.coordinates(); }
        bool            operator<=(const iterator &o) const { QHULL_ASSERT(dimension()==o.dimension()); return coordinates() <= o.coordinates(); }
        bool            operator>(const iterator &o) const  { QHULL_ASSERT(dimension()==o.dimension()); return coordinates() > o.coordinates(); }
        bool            operator>=(const iterator &o) const { QHULL_ASSERT(dimension()==o.dimension()); return coordinates() >= o.coordinates(); }
        // reinterpret_cast to break circular dependency
        bool            operator==(const QhullPoints::const_iterator &o) const { QHULL_ASSERT(dimension()==reinterpret_cast<const iterator &>(o).dimension()); return coordinates()==reinterpret_cast<const iterator &>(o).coordinates(); }
        bool            operator!=(const QhullPoints::const_iterator &o) const { return !operator==(reinterpret_cast<const iterator &>(o)); }
        bool            operator<(const QhullPoints::const_iterator &o) const  { QHULL_ASSERT(dimension()==reinterpret_cast<const iterator &>(o).dimension()); return coordinates() < reinterpret_cast<const iterator &>(o).coordinates(); }
        bool            operator<=(const QhullPoints::const_iterator &o) const { QHULL_ASSERT(dimension()==reinterpret_cast<const iterator &>(o).dimension()); return coordinates() <= reinterpret_cast<const iterator &>(o).coordinates(); }
        bool            operator>(const QhullPoints::const_iterator &o) const  { QHULL_ASSERT(dimension()==reinterpret_cast<const iterator &>(o).dimension()); return coordinates() > reinterpret_cast<const iterator &>(o).coordinates(); }
        bool            operator>=(const QhullPoints::const_iterator &o) const { QHULL_ASSERT(dimension()==reinterpret_cast<const iterator &>(o).dimension()); return coordinates() >= reinterpret_cast<const iterator &>(o).coordinates(); }
        iterator       &operator++() { advancePoint(1); return *this; }
        iterator        operator++(int) { iterator n= *this; operator++(); return iterator(n); }
        iterator       &operator--() { advancePoint(-1); return *this; }
        iterator        operator--(int) { iterator n= *this; operator--(); return iterator(n); }
        iterator       &operator+=(int index) { advancePoint(index); return *this; }
        iterator       &operator-=(int index) { advancePoint(-index); return *this; }
        iterator        operator+(int index) const { iterator n= *this; n.advancePoint(index); return n; }
        iterator        operator-(int index) const { iterator n= *this; n.advancePoint(-index); return n; }
        difference_type operator-(iterator o) const { QHULL_ASSERT(dimension()==o.dimension()); return (coordinates()-o.coordinates())/dimension(); }
    };//QhullPoints::iterator

#//QhullPoints::const_iterator //FIXUP what does const_... mean?
    class const_iterator : public QhullPoint {

    public:
        typedef std::random_access_iterator_tag  iterator_category;
        typedef ptrdiff_t   difference_type;
        typedef QhullPoint *pointer;
        typedef QhullPoint &reference;
        typedef QhullPoint  value_type;

                        const_iterator() : QhullPoint() {}
                        const_iterator(const const_iterator &o) : QhullPoint(*o) {}
                        const_iterator(QhullPoints::iterator &o) : QhullPoint(*o) {}
        explicit        const_iterator(const QhullPoints &ps) : QhullPoint(ps.dimension(), ps.coordinates()) {}
        explicit        const_iterator(int dimension, coordT *c): QhullPoint(dimension, c) {}
        const_iterator &operator=(const const_iterator &o) { defineAs(const_cast<const_iterator &>(o)); return *this; }
        // value/non-const since advancePoint(1), etc. modifies self
        QhullPoint      operator*() const { return *this; }
        QhullPoint     *operator->() { return this; }
        QhullPoint      operator[](int index) const { QhullPoint n= *this; n.advancePoint(index); return n; }
        bool            operator==(const const_iterator &o) const { QHULL_ASSERT(dimension()==o.dimension()); return coordinates()==o.coordinates(); }
        bool            operator!=(const const_iterator &o) const { return !operator==(o); }
        bool            operator<(const const_iterator &o) const  { QHULL_ASSERT(dimension()==o.dimension()); return coordinates() < o.coordinates(); }
        bool            operator<=(const const_iterator &o) const { QHULL_ASSERT(dimension()==o.dimension()); return coordinates() <= o.coordinates(); }
        bool            operator>(const const_iterator &o) const  { QHULL_ASSERT(dimension()==o.dimension()); return coordinates() > o.coordinates(); }
        bool            operator>=(const const_iterator &o) const { QHULL_ASSERT(dimension()==o.dimension()); return coordinates() >= o.coordinates(); }
        const_iterator &operator++() { advancePoint(1); return *this; }
        const_iterator  operator++(int) { const_iterator n= *this; operator++(); return const_iterator(n); }
        const_iterator &operator--() { advancePoint(-1); return *this; }
        const_iterator  operator--(int) { const_iterator n= *this; operator--(); return const_iterator(n); }
        const_iterator &operator+=(int index) { advancePoint(index); return *this; }
        const_iterator &operator-=(int index) { advancePoint(-index); return *this; }
        const_iterator  operator+(int index) const { const_iterator n= *this; n.advancePoint(index); return n; }
        const_iterator  operator-(int index) const { const_iterator n= *this; n.advancePoint(-index); return n; }
        difference_type operator-(const_iterator o) const { QHULL_ASSERT(dimension()==o.dimension()); return (coordinates()-o.coordinates())/dimension(); }
    };//QhullPoints::const_iterator

#//IO
    struct PrintPoints{
        const QhullPoints  *points;    //! FIXUP elsewhere.  const is OK now
        const char     *point_message;
        int             run_id;
        bool            with_identifier;
        PrintPoints(int qhRunId, const char *message, bool withIdentifier, const QhullPoints &ps) : points(&ps), point_message(message), run_id(qhRunId), with_identifier(withIdentifier) {} 
    };//PrintPoints
    PrintPoints          print() const { return  PrintPoints(UsingQhullLib::NOqhRunId, "", false, *this); }
    PrintPoints          print(int qhRunId) const { return PrintPoints(qhRunId, "", true, *this); }
    PrintPoints          print(int qhRunId, const char *message) const { return PrintPoints(qhRunId, message, false, *this); }
    PrintPoints          printWithIdentifier(int qhRunId, const char *message) const { return PrintPoints(qhRunId, message, true, *this); }
    //FIXUP remove message for print()?
};//QhullPoints

// FIXUP -- can't use macro because next(),etc would return a reference to a temporary -- QHULL_DECLARE_SEQUENTIAL_ITERATOR(QhullPoints, QhullPoint)
class QhullPointsIterator 
{ 
    typedef QhullPoints::const_iterator const_iterator; 
#//Fields
    const QhullPoints  *ps; 
    const_iterator      i; 

public: 
                        QhullPointsIterator(const QhullPoints &o) : ps(&o), i(ps->constBegin()) {} 
    QhullPointsIterator &operator=(const QhullPoints &o) { ps = &o; i = ps->constBegin(); return *this; } 
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

#//Global functions

std::ostream           &operator<<(std::ostream &os, const orgQhull::QhullPoints &p);
std::ostream           &operator<<(std::ostream &os, const orgQhull::QhullPoints::PrintPoints &pr);

#endif // QHULLPOINTS_H
