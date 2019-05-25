/****************************************************************************
**
** Copyright (c) 2008-2019 C.B. Barber. All rights reserved.
** $Id: //main/2019/qhull/src/libqhullcpp/QhullStat.cpp#1 $$Change: 2661 $
** $DateTime: 2019/05/24 20:09:58 $$Author: bbarber $
**
****************************************************************************/

#//! QhullStat -- Qhull's global data structure, statT, as a C++ class

#include "libqhullcpp/QhullStat.h"

#include "libqhullcpp/QhullError.h"

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

