/****************************************************************************
**
** Copyright (C) 2008-2009 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/qhulltest/UsingQhullLib_test.cpp#11 $$Change: 1091 $
** $DateTime: 2009/11/23 22:13:59 $$Author: bbarber $
**
****************************************************************************/

#include <iostream>
#include "../road/RoadTest.h" // QT_VERSION

#include "Qhull.h"
#include "QhullError.h"
#include "UsingQhullLib.h"

using std::cout;
using std::endl;
using std::string;

namespace orgQhull {

//! Test C++ interface to Qhull
//! See eg/q_test for tests of Qhull commands
class UsingQhullLib_test : public RoadTest
{
    Q_OBJECT

#//Test slots
private slots:
    void cleanup();
    void t_classMembers();
    void t_globalPoints();
    void t_UsingQhullLib();
    void t_methods();
    void t_cleanuptestcase();
};//UsingQhullLib_test

void
add_UsingQhullLib_test()
{
    new UsingQhullLib_test();
}

//Executed after each testcase
void UsingQhullLib_test::
cleanup()
{
    UsingQhullLib::checkQhullMemoryEmpty();
    RoadTest::cleanup();
}

void UsingQhullLib_test::
t_classMembers()
{
    {
        //checkQhullMemoryEmpty tested by cleanup()
        QCOMPARE(UsingQhullLib::globalMachineEpsilon()+1.0, 1.0);
        RboxPoints r10("10");
        Qhull q(r10,"v");  // voronoi diagram of 10 points
        UsingQhullLib::unsetGlobalAngleEpsilon();
        UsingQhullLib::unsetGlobalDistanceEpsilon();
        cout << "MachineEpsilon " << UsingQhullLib::globalMachineEpsilon()
            << " angleEpsilon " << UsingQhullLib::globalAngleEpsilon()
            << " distanceEpsilon " << UsingQhullLib::globalDistanceEpsilon()
            << endl;
        QCOMPARE(UsingQhullLib::currentAngleEpsilon()+1.0, 1.0);
        QVERIFY(UsingQhullLib::currentAngleEpsilon() > UsingQhullLib::globalMachineEpsilon());
        QCOMPARE(UsingQhullLib::currentDistanceEpsilon()+1.0, 1.0);
        QVERIFY(UsingQhullLib::currentDistanceEpsilon() >= UsingQhullLib::currentAngleEpsilon());
        QCOMPARE(UsingQhullLib::currentQhull().runId(), q.runId());
        QCOMPARE(UsingQhullLib::globalAngleEpsilon()+1.0, UsingQhullLib::currentAngleEpsilon()+1.0);
        QCOMPARE(UsingQhullLib::currentVertexDimension(), q.dimension());
        QCOMPARE(UsingQhullLib::globalDistanceEpsilon()+1.0, UsingQhullLib::currentDistanceEpsilon()+1.0);
        UsingQhullLib::setGlobalAngleEpsilon(1.0);
        UsingQhullLib::setGlobalDistanceEpsilon(1.0);
        cout << " Global angleEpsilon " << UsingQhullLib::globalAngleEpsilon()
            << " distanceEpsilon " << UsingQhullLib::globalDistanceEpsilon()
            << endl;
        QCOMPARE(UsingQhullLib::globalAngleEpsilon(), UsingQhullLib::globalDistanceEpsilon());
        QVERIFY(UsingQhullLib::currentAngleEpsilon() != UsingQhullLib::globalAngleEpsilon());
        UsingQhullLib::setGlobalVertexDimension(3);
        QCOMPARE(UsingQhullLib::globalVertexDimension(), UsingQhullLib::currentVertexDimension());
        UsingQhullLib::setGlobalVertexDimension(2);
        QCOMPARE(UsingQhullLib::globalVertexDimension(), 2);
        QCOMPARE(UsingQhullLib::currentVertexDimension(), q.dimension());
        QVERIFY(UsingQhullLib::currentDistanceEpsilon() != UsingQhullLib::globalDistanceEpsilon());
        UsingQhullLib::unsetGlobalAngleEpsilon();
        UsingQhullLib::unsetGlobalVertexDimension();
        UsingQhullLib::unsetGlobalDistanceEpsilon();
        QCOMPARE(UsingQhullLib::currentAngleEpsilon()+1.0, UsingQhullLib::globalAngleEpsilon()+1.0);
        QCOMPARE(UsingQhullLib::globalVertexDimension(), UsingQhullLib::currentVertexDimension());
        QCOMPARE(UsingQhullLib::currentDistanceEpsilon()+1.0, UsingQhullLib::globalDistanceEpsilon()+1.0);
        UsingQhullLib::setGlobals();
    }
    QCOMPARE(UsingQhullLib::globalAngleEpsilon()+1.0, 1.0);
    QCOMPARE(UsingQhullLib::globalVertexDimension(), 4); // 'v'.  VertexDimension is only used for QhullVertex where dim>15
    QCOMPARE(UsingQhullLib::globalDistanceEpsilon()+1.0, 1.0);
    UsingQhullLib::unsetGlobals();
    try{
        cout<< UsingQhullLib::globalVertexDimension();
        QFAIL("Did not throw error for undefined dimension.");
    }catch(const std::exception &e){
        cout<< "INFO     Caught error -- " << e.what() << endl;
    }
}//t_classMembers

void UsingQhullLib_test::
t_globalPoints()
{
    const coordT *r10PointsBegin;
    {
        RboxPoints r10("10");
        Qhull q(r10,"v");  // voronoi diagram of 10 points
        UsingQhullLib::unsetGlobalPoints();
        int dimension;
        const coordT *pointsEnd;
        const coordT *pointsBegin= UsingQhullLib::globalPoints(&dimension, &pointsEnd);
        cout << "pointsBegin " << pointsBegin
            << " pointsEnd " << pointsEnd
            << " dimension " << dimension
            << endl;
        int dimension2;
        const coordT *pointsEnd2;
        const coordT *pointsBegin2= UsingQhullLib::currentPoints(&dimension2, &pointsEnd2);
        QCOMPARE(pointsBegin2, pointsBegin);
        QCOMPARE(pointsEnd2, pointsEnd);
        QCOMPARE(dimension2, dimension);
        coordT c[]= { 1.0,2.0, 3.0,4.0, 5.0,6.0 };
        UsingQhullLib::setGlobalPoints(2, c, c+3*2);
        pointsBegin= UsingQhullLib::globalPoints(&dimension, &pointsEnd);
        QCOMPARE(pointsBegin, c);
        QCOMPARE(pointsEnd[-1], 6.0);
        QCOMPARE(dimension, 2);
        UsingQhullLib::unsetGlobalPoints();
        pointsBegin= UsingQhullLib::globalPoints(&dimension, &pointsEnd);
        QCOMPARE(pointsBegin, pointsBegin2);
        QCOMPARE(pointsEnd, pointsEnd2);
        QCOMPARE(dimension, dimension2);
        UsingQhullLib::setGlobals();
        r10PointsBegin= pointsBegin;
    }
    int dimension3;
    const coordT *pointsEnd3;
    const coordT *pointsBegin3= UsingQhullLib::currentPoints(&dimension3, &pointsEnd3);
    QCOMPARE(pointsBegin3, r10PointsBegin); // Memory was freed
    QCOMPARE(pointsEnd3, r10PointsBegin+10*4);
    QCOMPARE(dimension3, 4);
    UsingQhullLib::unsetGlobals();
    try{
        pointsBegin3= UsingQhullLib::globalPoints(&dimension3, &pointsEnd3);
        QFAIL("Did not throw error for undefined global points.");
    }catch(const std::exception &e){
        cout<< "INFO     Caught error -- " << e.what() << endl;
    }
}//t_globalPoints

void UsingQhullLib_test::
t_UsingQhullLib()
{
    {
        Qhull q;
        UsingQhullLib uq(&q); // Normally created in a method using 'this'

        try{
            Qhull q2; // If qh_QHpointer, QhullQh() calls usinQhullLib()
            UsingQhullLib uq2(&q2);
            QFAIL("UsingQhullLib did not fail.");
        }catch (const std::exception &e) {
            cout<< "INFO   : Caught " << e.what();
        }
    }
    Qhull q3;
    UsingQhullLib uq3(&q3);
}//t_UsingQhullLib

void UsingQhullLib_test::
t_methods()
{
    Qhull q;
    UsingQhullLib u(&q); // Normally created in a method using 'this'
    QVERIFY(u.defined());
    u.maybeThrowQhullMessage(0);  // Nothing thrown
    try{
        u.maybeThrowQhullMessage(1);
        QFAIL("maybeThrowQhullMessage(1) did not fail.");
    }catch (const std::exception &e) {
        cout<< "INFO   : Caught " << e.what();
    }
    // Can not check checkRunId() in maybeThrowQhullMessage().  Requires another thread.
    u.maybeThrowQhullMessage(2, UsingQhullLib::NOthrow);
    try{
        throw QhullError(10054, "Report previous NOthrow error");
    }catch (const std::exception &e) {
        cout<< "INFO   : " << e.what();
    }
}//t_methods

// Executed after last test
void UsingQhullLib_test::
t_cleanuptestcase()
{
    UsingQhullLib::unsetGlobals();
}//t_cleanuptestcase



}//orgQhull

#include "moc/UsingQhullLib_test.moc"

