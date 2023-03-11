//
//  TestAngle.cpp
//  Lab07
//
//  Created by Samuel on 3/8/23.
//

#include "angle.h"

void TestAngle::run() {
//    this->testMach();
//    this->testRetrieveD01R01();
//    this->testLinearInterpolation();
}

bool TestAngle::determineIfApprox(double expected, double actual) {
    double low = expected - 0.0001;
    double high = expected + 0.0001;
    return (actual > low && actual < high);
}

