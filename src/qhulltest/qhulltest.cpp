/****************************************************************************
**
** Copyright (c) 2008-2015 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/qhulltest/qhulltest.cpp#19 $$Change: 1951 $
** $DateTime: 2015/08/30 21:30:30 $$Author: bbarber $
**
****************************************************************************/

//pre-compiled headers
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "RoadTest.h"

#include "libqhullcpp/RoadError.h"
extern "C" {
#include "libqhull_r/qhull_ra.h"
}

using std::cout;
using std::endl;

namespace orgQhull {

void addQhullTests(QStringList &args)
{
    TESTadd_(add_QhullVertexSet_test); //copied from below

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
        TESTadd_(add_QhullVertexSet_test);
        TESTadd_(add_RboxPoints_test);
        // qhullStat
        TESTadd_(add_Qhull_test);
    }//--all
}//addQhullTests

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QStringList args= app.arguments();
    bool isAll= args.contains("--all");

    QHULL_LIB_CHECK

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
    if(isAll){
        cout << "Finished test of libqhullcpp.  Test libqhull_r with eg/q_test after building libqhull_r/Makefile" << endl;
    }else{
        cout << "Finished test of one class.  Test all classes with 'qhulltest --all'" << endl;
    }
    return status;
}

}//orgQhull

int main(int argc, char *argv[])
{
    return orgQhull::main(argc, argv); // Needs RoadTest:: for TESTadd_() linkage
}

