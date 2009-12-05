/****************************************************************************
**
** Copyright (C) 2008-2008 C. Bradford Barber. All rights reserved.
**
****************************************************************************/

#//! QhullError -- All exceptions thrown by Qhull are QhullErrors

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "QhullError.h"

using std::cout;
using std::ostringstream;
using std::string;

typedef std::auto_ptr<std::stringstream> StringStreamPointer; //! auto_ptr transfers ownership on copy

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4 
#endif

namespace orgQhull {

#//GetSet

}//namespace orgQhull

