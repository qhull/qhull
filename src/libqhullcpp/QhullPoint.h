/****************************************************************************
**
** Copyright (c) 2009-2014 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullPoint.h#15 $$Change: 1800 $
** $DateTime: 2014/12/17 21:46:45 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHPOINT_H
#define QHPOINT_H

#include "QhullError.h"
#include "QhullIterator.h"
#include "QhullQh.h"
#include "Coordinates.h"
extern "C" {
    #include "libqhullr/qhull_ra.h"
}

#include <ostream>

namespace orgQhull {

#//!\name Defined here
    class QhullPoint;  //!<  QhullPoint as a pointer and dimension to shared memory
    class QhullPointIterator; //!< Java-style iterator for QhullPoint coordinates

#//!\name Used here
    class Qhull;

//! A point in Qhull is an array of coordinates.
class QhullPoint {

#//!\name Iterators
public:
    typedef coordT *                    base_type;  // for QhullPointSet
    typedef const coordT *              iterator;
    typedef const coordT *              const_iterator;
    typedef QhullPoint::iterator        Iterator;
    typedef QhullPoint::const_iterator  ConstIterator;

#//!\name Fields
protected: // For QhullPoints::iterator, QhullPoints::const_iterator
    coordT *            point_coordinates;  //!< Pointer to first coordinate,   0 if undefined
    QhullQh *           qh_qh;              //!< qhT for this instance of Qhull. 0 if undefined.  Used by id() and operator=()
    int                 point_dimension;    //!< Default dimension is qh_qh->hull_dim
public:

#//!\name Constructors
                        QhullPoint() : point_coordinates(0), qh_qh(0), point_dimension(0) {}
    explicit            QhullPoint(const Qhull &q);
                        QhullPoint(const Qhull &q, int pointDimension, coordT *c);
                        QhullPoint(const Qhull &q, coordT *c);
                        QhullPoint(const Qhull &q, Coordinates &c);
    explicit            QhullPoint(QhullQh *qh) : point_coordinates(0), qh_qh(qh), point_dimension(qh->hull_dim) {}
                        QhullPoint(QhullQh *qh, int pointDimension, coordT *c) : point_coordinates(c), qh_qh(qh), point_dimension(pointDimension) {}
                        QhullPoint(QhullQh *qh, coordT *c) : point_coordinates(c), qh_qh(qh), point_dimension(qh->hull_dim) {}
                        QhullPoint(QhullQh *qh, Coordinates &c) : point_coordinates(c.data()), qh_qh(qh), point_dimension(c.count()) {}
                        // Creates an alias.  Does not copy the point.  Needed for return by value and parameter passing.
                        QhullPoint(const QhullPoint &other) : point_coordinates(other.point_coordinates), point_dimension(other.point_dimension), qh_qh(other.qh_qh) {}
                        // Creates an alias.  Does not copy the point.  Needed for vector<QhullPoint>
    QhullPoint &        operator=(const QhullPoint &other) { point_coordinates= other.point_coordinates; point_dimension= other.point_dimension; qh_qh= other.qh_qh; return *this; }
                        ~QhullPoint() {}


#//!\name Conversions

#ifndef QHULL_NO_STL
    std::vector<coordT> toStdVector() const;
#endif //QHULL_NO_STL
#ifdef QHULL_USES_QT
    QList<coordT>       toQList() const;
#endif //QHULL_USES_QT

#//!\name GetSet
public:
    const coordT *      coordinates() const { return point_coordinates; }  //!< 0 if undefined
    coordT *            coordinates() { return point_coordinates; }        //!< 0 if undefined
    void                defineAs(int pointDimension, coordT *c) { QHULL_ASSERT(pointDimension>=0); point_coordinates= c; point_dimension= pointDimension; }
    //! Creates an alias, but does not change qh()
    void                defineAs(QhullPoint &other) { point_coordinates= other.point_coordinates; point_dimension= other.point_dimension; }
    int                 dimension() const { return point_dimension; }
    coordT *            getBaseT() const { return point_coordinates; } // for QhullSet<QhullPoint>
    countT              id() const { return qh_pointid(qh_qh, point_coordinates); } // NOerrors
    bool                isDefined() const { return (point_coordinates!=0 && point_dimension>0); };
    bool                operator==(const QhullPoint &other) const;
    bool                operator!=(const QhullPoint &other) const { return !operator==(other); }
    const coordT &      operator[](int idx) const { QHULL_ASSERT(point_coordinates!=0 && idx>=0 && idx<point_dimension); return *(point_coordinates+idx); } //!< 0 to hull_dim-1
    coordT &            operator[](int idx) { QHULL_ASSERT(point_coordinates!=0 && idx>=0 && idx<point_dimension); return *(point_coordinates+idx); } //!< 0 to hull_dim-1
    QhullQh *           qh() { return qh_qh; }
    void                setCoordinates(coordT *c) { point_coordinates= c; }
    void                setDimension(int pointDimension) { point_dimension= pointDimension; }

#//!\name foreach
    iterator            begin() { return point_coordinates; }
    const_iterator      begin() const { return point_coordinates; }
    const_iterator      constBegin() const { return point_coordinates; }
    const_iterator      constEnd() const { return (point_coordinates ? point_coordinates+point_dimension : 0); }
    int                 count() { return (point_coordinates ? point_dimension : 0); }
    iterator            end() { return (point_coordinates ? point_coordinates+point_dimension : 0); }
    const_iterator      end() const { return (point_coordinates ? point_coordinates+point_dimension : 0); }
    size_t              size() { return (size_t)(point_coordinates ? point_dimension : 0); }

#//!\name Methods
    void                advancePoint(countT idx) { if(point_coordinates) { point_coordinates += idx*point_dimension; } }
    double              distance(const QhullPoint &p) const;

#//!\name IO

    struct PrintPoint{
        const QhullPoint *point;
        const char *    point_message;
        bool            with_identifier;
                        PrintPoint(const char *message, bool withIdentifier, const QhullPoint &p) : point(&p), point_message(message), with_identifier(withIdentifier) {}
    };//PrintPoint
    PrintPoint          print(const char *message) const { return PrintPoint(message, false, *this); }
    PrintPoint          printWithIdentifier(const char *message) const { return PrintPoint(message, true, *this); }

};//QhullPoint

QHULL_DECLARE_SEQUENTIAL_ITERATOR(QhullPoint, coordT)

}//namespace orgQhull

#//!\name Global

std::ostream &operator<<(std::ostream &os, const orgQhull::QhullPoint::PrintPoint &pr);
std::ostream &operator<<(std::ostream &os, const orgQhull::QhullPoint &p);

#endif // QHPOINT_H

