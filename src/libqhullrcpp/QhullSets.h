/****************************************************************************
**
** Copyright (c) 2008-2012 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullrcpp/QhullSets.h#1 $$Change: 1640 $
** $DateTime: 2014/01/15 09:12:08 $$Author: bbarber $
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
