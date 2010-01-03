/****************************************************************************
**
** Copyright (C) 2008-2010 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/QhullSets.h#5 $$Change: 1137 $
** $DateTime: 2010/01/02 21:58:11 $$Author: bbarber $
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
