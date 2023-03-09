//
//  TestBullet.h
//  Lab07
//
//  Created by Samuel on 3/8/23.
//

#ifndef TestBullet_h
#define TestBullet_h

#include <stdio.h>

class TestBullet {
public:
    void run();
private:
    bool determineIfApprox(double expected, double actual);

    void testMach();
    void testRetrieveD01R01();
    void testLinearInterpolation();
};

#endif /* TestPhysics_h */

