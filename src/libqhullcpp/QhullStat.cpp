/****************************************************************************
**
** Copyright (c) 2008-2015 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullStat.cpp#6 $$Change: 1868 $
** $DateTime: 2015/03/26 20:13:15 $$Author: bbarber $
**
****************************************************************************/

#//! QhullStat -- Qhull's global data structure, statT, as a C++ class


#include "QhullError.h"
#include "QhullStat.h"

#include <sstream>
#include <iostream>

using std::cerr;
using std::string;
using std::vector;
using std::ostream;

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4
#endif

namespace orgQhull {

#//!\name Constructor, destructor, etc.

//! If qh_QHpointer==0, invoke with placement new on qh_stat;
QhullStat::
QhullStat()
{
}//QhullStat

QhullStat::
~QhullStat()
{
}//~QhullStat

}//namespace orgQhull

