/****************************************************************************
**
** Copyright (c) 2008-2011 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullSets.h#2 $$Change: 1342 $
** $DateTime: 2011/03/07 21:55:47 $$Author: bbarber $
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
