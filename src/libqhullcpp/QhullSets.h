/****************************************************************************
**
** Copyright (c) 2008-2019 C.B. Barber. All rights reserved.
** $Id: //main/2019/qhull/src/libqhullcpp/QhullSets.h#1 $$Change: 2661 $
** $DateTime: 2019/05/24 20:09:58 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLSETS_H
#define QHULLSETS_H

#include "libqhullcpp/QhullSet.h"

namespace orgQhull {

    //See: QhullFacetSet.h
    //See: QhullPointSet.h
    //See: QhullVertexSet.h

    // Avoid circular references between QhullFacet, QhullRidge, and QhullVertex
    class QhullRidge;
    typedef QhullSet<QhullRidge>  QhullRidgeSet;
    typedef QhullSetIterator<QhullRidge>  QhullRidgeSetIterator;

}//namespace orgQhull

#endif // QHULLSETS_H
