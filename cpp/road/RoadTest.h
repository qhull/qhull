/****************************************************************************
**
** Copyright (C) 2008-2010 C.B. Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/road/RoadTest.h#15 $$Change: 1164 $
** $DateTime: 2010/01/07 21:52:00 $$Author: bbarber $
**
****************************************************************************/

#ifndef ROADTEST_H
#define ROADTEST_H

//pre-compiled with RoadTest.h
#include <QObject>
#include <QtTest/QtTest>

//FIXUP -- test that compiler sets QHULL_USES_QT.
#define QHULL_USES_QT 1

namespace orgQhull {

#//Types
    //! RoadTest -- Generic test for Qt's QTest
    class RoadTest;
    //! TESTadd_(t) -- Add a RoadTest

/** Test Name objects using Qt's QTestLib

Template:

class Name_test : public RoadTest
{
    Q_OBJECT
#//Test slot
private slots:
    void t_name();
    //Executed before any test
    void initTestCase();
    void init();          // Each test
    //Executed after each test
    void cleanup(); //RoadTest::cleanup();
    // Executed after last test
    void cleanupTestCase();
};

void
add_Name_test()
{
    new Name_test();
}

Send additional output to cout
*/

class RoadTest : public QObject
{
    Q_OBJECT

protected:
#//class variable
    static QList<RoadTest*>
                        s_testcases; ///! List of testcases to execute.  Initialized via add_...()
    static int          s_test_count; ///! Total number of tests executed
    static int          s_test_fail; ///! Number of failed tests
    static QStringList  s_failed_tests; ///! List of failed tests

#//Test slots
public slots:
    void cleanup();

public:
#//constructor, destructor
    RoadTest()  { s_testcases.append(this); };
    ~RoadTest() { s_testcases.removeAll(this); };

#//Helper
    void                recordFailedTest();


#//class function
    static int          runTests(QStringList arguments);

};//RoadTest

#define TESTadd_(t) extern void t(); t();


}//orgQhull

namespace QTest {

template<>
inline char *
toString(const std::string &s)
{
    return qstrdup(s.c_str());
}

}//namespace QTest

#endif //ROADTEST_H

