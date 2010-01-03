/****************************************************************************
**
** Copyright (C) 2008-2010 C. Bradford Barber. All rights reserved.
**
****************************************************************************/

#//! QhullError -- All exceptions thrown by Qhull are QhullErrors

#include "QhullError.h"

#include <memory>
#include <string>
#include <sstream>
#include <iostream>

using std::cout;
using std::ostringstream;
using std::string;

typedef std::auto_ptr<std::stringstream> StringStreamPointer; //! auto_ptr transfers ownership on copy

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4 
#endif

namespace orgQhull {

#//GetSet

}//namespace orgQhull

