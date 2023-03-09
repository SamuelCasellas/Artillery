//
//  TestHowitzer.h
//  Lab07
//
//  Created by Samuel on 3/8/23.
//

#ifndef TestHowitzer_h
#define TestHowitzer_h

#include <stdio.h>

class TestHowitzer {
public:
    void run();
private:
    bool determineIfApprox(double expected, double actual);

    void testMach();
    void testRetrieveD01R01();
    void testLinearInterpolation();
};

#endif /* TestHowitzer_h */
