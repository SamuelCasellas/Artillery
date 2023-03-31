//
//  TestHowitzer.h
//  Lab07
//
//  Created by Samuel on 3/8/23.
//

#ifndef TestHowitzer_h
#define TestHowitzer_h

#include "uiInteract.h"
#include "howitzer.h"
#include "angle.h"

class TestHowitzer
{
public:
    void run();

private:
    bool determineIfApprox(double expected, double actual);
    void testGetAngle();
    void testUpdateAngle();
};

#endif /* TestHowitzer_h */
