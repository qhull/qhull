/****************************************************************************
**
** Copyright (C) 2008-2010 C.B. Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/QhullQh.h#19 $$Change: 1139 $
** $DateTime: 2010/01/03 11:20:29 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLQH_H
#define QHULLQH_H

extern "C" {
    #include "../src/qhull_a.h"
};

#include <string>
#include <vector>

namespace orgQhull {

#//defined here
    //! QhullQh -- Qhull's global data structure, qhT, as a C++ class
    //! See UsingLibQhull.h for C++/C interface to qhT
    class QhullQh;

class QhullQh : public qhT {

#//Constants
    // Set ignored.  PointSet needs explicit dimension
    // Facet from vertices or ridges.vertices.count
    // Ridge from vertices.count
    // Vertex stored in vertexT?  1->16?
    // QhullPoint needs explicit dimension

#//members (empty) -- POD type equivalent to qhT.  No data or virtual members

public:
#//constructor, assignment, destructor, invariant
    QhullQh();
    ~QhullQh();

private: 
    //!disable copy constructor and assignment
                        QhullQh(const QhullQh &);
    QhullQh            &operator=(const QhullQh &);

};//class QhullQh

}//namespace orgQhull

#endif // QHULLQH_H
