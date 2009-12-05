/****************************************************************************
**
** Copyright (C) 2008-2009 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/QhullQh.h#14 $$Change: 1053 $
** $DateTime: 2009/10/02 22:00:28 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLQH_H
#define QHULLQH_H

#include <string>
#include <vector>

extern "C" {
    #include "../src/qhull_a.h"
};

namespace orgQhull {

#//defined here
    //! QhullQh -- Qhull's global data structure, qhT, as a C++ class
    //! See UsingQhullLib.h for C++/C interface to qhT
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

public:
#//Access
    void checkIfQhullRan();
    void errorAnotherUser();
    void startQhullAccess();
    void stopQhullAccess();
};//class QhullQh

}//namespace orgQhull

#endif // QHULLQH_H
