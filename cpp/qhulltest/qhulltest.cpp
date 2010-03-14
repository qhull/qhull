/****************************************************************************
**
** Copyright (C) 2008-2010 C.B. Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/qhulltest/qhulltest.cpp#55 $$Change: 1179 $
** $DateTime: 2010/01/12 19:53:15 $$Author: bbarber $
**
****************************************************************************/

//pre-compiled headers
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "../road/RoadTest.h"

#include "../road/RoadError.h"

using std::cout;
using std::endl;

namespace orgQhull {

void addQhullTests(QStringList &args)
{
    TESTadd_(add_QhullVertex_test); //copy

    if(args.contains("--all")){
        args.removeAll("--all");
        // up-to-date
        TESTadd_(add_Coordinates_test);
        TESTadd_(add_PointCoordinates_test);
        TESTadd_(add_QhullFacet_test);
        TESTadd_(add_QhullFacetList_test);
        TESTadd_(add_QhullFacetSet_test);
        TESTadd_(add_QhullHyperplane_test);
        TESTadd_(add_QhullLinkedList_test);
        TESTadd_(add_QhullPoint_test);
        TESTadd_(add_QhullPoints_test);
        TESTadd_(add_QhullPointSet_test);
        TESTadd_(add_QhullRidge_test);
        TESTadd_(add_QhullSet_test);
        TESTadd_(add_QhullVertex_test);
        TESTadd_(add_RboxPoints_test);
        TESTadd_(add_UsingLibQhull_test);
        // needs review
        // qhullStat
        TESTadd_(add_Qhull_test);
    }//--all
}//addQhullTests

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QStringList args= app.arguments();
    addQhullTests(args);
    int status=1010;
    try{
        status= RoadTest::runTests(args);
    }catch(const std::exception &e){
        cout << "FAIL!  : runTests() did not catch error\n";
        cout << e.what() << endl;
        if(!RoadError::emptyGlobalLog()){
            cout << RoadError::stringGlobalLog() << endl;
            RoadError::clearGlobalLog();
        }
    }
    if(!RoadError::emptyGlobalLog()){
        cout << RoadError::stringGlobalLog() << endl;
        RoadError::clearGlobalLog();
    }
    return status;
}

}//orgQhull

int main(int argc, char *argv[])
{
    return orgQhull::main(argc, argv); // Needs RoadTest:: for TESTadd_() linkage
}

