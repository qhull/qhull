/****************************************************************************
**
** Copyright (C) 2008-2010 C.B. Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/QhullStat.cpp#9 $$Change: 1164 $
** $DateTime: 2010/01/07 21:52:00 $$Author: bbarber $
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

#//Constructor, destructor, etc.

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

