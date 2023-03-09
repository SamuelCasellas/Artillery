//
//  TestBullet.cpp
//  Lab07
//
//  Created by Samuel on 3/8/23.
//

#include "bullet.h"


void TestBullet::run() {
//    this->testMach();
//    this->testRetrieveD01R01();
//    this->testLinearInterpolation();
}

bool TestBullet::determineIfApprox(double expected, double actual) {
    double low = expected - 0.0001;
    double high = expected + 0.0001;
    return (actual > low && actual < high);
}

//
//void TestBullet::testConstructor()
//{
//    // Verify
//    assert(p.mass == 46.7);
//    assert(p.surfaceArea > 0.0188 && p.surfaceArea < 0.0189);
//    assert(p.getAltitude() == p.y && p.y == 0.0);
//} // Teardown
