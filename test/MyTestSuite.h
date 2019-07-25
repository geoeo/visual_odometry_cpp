//
// Created by Marc Haubenstock on 2019-07-22.
//

#ifndef VISUAL_ODOMETRY_TEST_MYTESTSUITE_H
#define VISUAL_ODOMETRY_TEST_MYTESTSUITE_H

// MyTestSuite1.h
#include <cxxtest/TestSuite.h>


class MyTestSuite1 : public CxxTest::TestSuite
{
public:
    void testAddition(void)
    {
        TS_ASSERT(1 + 1 > 1);
        TS_ASSERT_EQUALS(1 + 1, 2);
    }
};

#endif //VISUAL_ODOMETRY_TEST_MYTESTSUITE_H
