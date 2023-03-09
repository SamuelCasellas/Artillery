//
//  TestAngle.h
//  Lab07
//
//  Created by Samuel on 3/8/23.
//

#ifndef TestAngle_h
#define TestAngle_h

#include <stdio.h>

class TestAngle {
public:
    void run();
private:
    bool determineIfApprox(double expected, double actual);

    void testMach();
    void testAreaOfCircle();
    void testAreaOfCircle2();
    void testRetrieveD01R01();
    void testLinearInterpolation();
};

#endif /* TestAngle_h */
