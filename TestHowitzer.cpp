//
//  TestHowitzer.cpp
//  Lab07
//
//  Created by Samuel on 3/8/23.
//

#include <cassert>

#include "TestHowitzer.h"
#include "howitzer.h"
#include "angle.h"


void TestHowitzer::run() {
    testGetAngle();
    testUpdateAngle();
}

bool TestHowitzer::determineIfApprox(double expected, double actual) {
    double low = expected - 0.0001;
    double high = expected + 0.0001;
    return (actual > low && actual < high);
}

void TestHowitzer::testGetAngle() {
    Howitzer h;
    Angle a;
    a.setDegrees(45.0);
    h.updateAngle(a);
    assert(determineIfApprox(a.getDegrees(), h.getAngle().getDegrees()));
}

void TestHowitzer::testUpdateAngle() {
    Howitzer h;
    Angle a;
    a.setDegrees(45.0);
    h.updateAngle(a);
    Angle newAngle;
    newAngle.setDegrees(30.0);
    h.updateAngle(newAngle);
    assert(determineIfApprox(newAngle.getDegrees(), h.getAngle().getDegrees()));
}



