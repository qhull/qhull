/****************************************************************************
**
** Copyright (c) 2008-2015 C.B. Barber. All rights reserved.
** $Id: //main/2015/qhull/src/libqhullcpp/QhullSets.h#1 $$Change: 1981 $
** $DateTime: 2015/09/28 20:26:32 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLSETS_H
#define QHULLSETS_H

#include "QhullSet.h"

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
