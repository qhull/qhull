/****************************************************************************
**
** Copyright (c) 2008-2012 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullpcpp/QhullQh.h#2 $$Change: 1675 $
** $DateTime: 2014/02/01 09:38:20 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLQH_H
#define QHULLQH_H

extern "C" {
    #include "libqhull/qhull_a.h"
}

#include <string>
#include <vector>

namespace orgQhull {

#//!\name defined here
    //! QhullQh -- Qhull's global data structure, qhT, as a C++ class
    //! See UsingLibQhull.h for C++/C interface to qhT
    class QhullQh;

class QhullQh : public qhT {

#//!\name Constants
    // Set ignored.  PointSet needs explicit dimension
    // Facet from vertices or ridges.vertices.count
    // Ridge from vertices.count
    // Vertex stored in vertexT?  1->16?
    // QhullPoint needs explicit dimension

#//!\name Fields
    //! No fields       POD type equivalent to qhT.  No data or virtual members

public:
#//!\name Constructors
    QhullQh();
    ~QhullQh();

private:
    //!disable copy constructor and assignment
                        QhullQh(const QhullQh &);
    QhullQh &           operator=(const QhullQh &);

};//class QhullQh

}//namespace orgQhull

#endif // QHULLQH_H
