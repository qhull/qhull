/****************************************************************************
**
** Copyright (C) 2009-2009 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/Coordinates.h#23 $$Change: 1096 $
** $DateTime: 2009/12/04 21:52:01 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHCOORDINATES_H
#define QHCOORDINATES_H

#include "QhullError.h"
#include "QhullIterator.h"

#include <ostream>
#include <vector>

extern "C" {
    #include "../src/qhull_a.h"
};

namespace orgQhull {

#//Types
    //! an allocated vector of point coordinates
    //!  Used by PointCoordinates for RboxPoints
    //!  A QhullPoint refers to previously allocated coordinates
    class  Coordinates;


class Coordinates : public std::vector<coordT> {

#//Types
    // inherited types -- const_iterator, const_pointer, const_reference, iterator, iterator_category, pointer, reference, size_type, value_type
public:
    typedef Coordinates::iterator Iterator;
    typedef Coordinates::const_iterator ConstIterator;

#//Construct
                        Coordinates() {};
    explicit            Coordinates(const std::vector<coordT> &other) : std::vector<coordT>(other) {}
                        Coordinates(const Coordinates &other) : std::vector<coordT>(other) {}
    Coordinates        &operator=(const Coordinates &other) { std::vector<coordT>::operator=(other); return *this; }
    Coordinates        &operator=(const std::vector<coordT> &other) { std::vector<coordT>::operator=(other); return *this; }
                       ~Coordinates() {}
 
#//Conversion

                       coordT             *data() { return isEmpty() ? 0 : &at(0); }
    const coordT       *data() const { return const_cast<const pointT*>(isEmpty() ? 0 : &at(0)); }

#ifndef QHULL_NO_STL
    std::vector<coordT> toStdVector() const { return static_cast< std::vector<coordT> >(*this); }
#endif //QHULL_NO_STL
#ifdef QHULL_USES_QT
    QList<coordT>      toQList() const;
#endif //QHULL_USES_QT

#//GetSet
    // std::vector -- empty, size 
    int                count() const { return static_cast<int>(size()); }
    bool               isEmpty() const { return empty(); }

#//Element access
    // std::vector -- at (const& only), back, front, []
    coordT             &first() { return front(); }
    const coordT       &first() const { return front(); }
    coordT             &last() { return back(); }
    const coordT       &last() const { return back(); }
    Coordinates        mid(int index, int length= -1) const;
    coordT             value(int index, const coordT &defaultValue) const;

#//Operator
    // std::vector -- ==, !=
    Coordinates         operator+(const Coordinates &other) const;
    Coordinates        &operator+=(const Coordinates &other);
    Coordinates        &operator+=(const coordT &c) { append(c); return *this; }
    Coordinates        &operator<<(const Coordinates &other) { return *this += other; }
    Coordinates        &operator<<(const coordT &c) { return *this += c; }

#//Iterator
    // std::vector -- begin, end, *, [], ->, ++, --, +, -, ==, !=, <, <=, >, >=
    inline const_iterator constBegin() const { return begin(); }
    inline const_iterator constEnd() const { return end(); }

#//Read-write
    // std::vector -- clear, erase, insert, pop_back, push_back
    void                append(const coordT &c) { push_back(c); }
    void                insert(int before, const coordT &c) { insert(begin()+before, c); }
    using               std::vector<coordT>::insert;
    void                move(int from, int to) { insert(to, takeAt(from)); }
    void                pop_front() { removeFirst(); }
    void                prepend(const coordT &c) { insert(begin(), c); }
    void                push_front(const coordT &c) { insert(begin(), c); }
                        //removeAll below
    void                removeAt(int index) { erase(begin()+index); }
    void                removeFirst() { erase(begin()); }
    void                removeLast() { erase(--end()); }
    void                replace(int index, const coordT &c) { (*this)[index]= c; }
    void                swap(int index, int other);
    coordT              takeAt(int index);
    coordT              takeFirst() { return takeAt(0); }
    coordT              takeLast();

#//Search
    bool                contains(const coordT &t) const;
    int                 count(const coordT &t) const;
    int                 indexOf(const coordT &t, int from = 0) const;
    int                 lastIndexOf(const coordT &t, int from = -1) const;
    void                removeAll(const coordT &t);

};//Coordinates

//class CoordinatesIterator
QHULL_DECLARE_SEQUENTIAL_ITERATOR(Coordinates, coordT)
//class MutableCoordinatesIterator
QHULL_DECLARE_MUTABLE_SEQUENTIAL_ITERATOR(Coordinates, coordT)

}//namespace orgQhull

#//Global functions

std::ostream &operator<<(std::ostream &os, const orgQhull::Coordinates &c);

#endif // QHCOORDINATES_H
