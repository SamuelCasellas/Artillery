//
//  TestPhysics.cpp
//  Lab07
//
//  Created by Samuel on 3/4/23.
//

#include "physics.h"

void TestPhysics::run() {
    this->testMach();
    this->testRetrieveD01R01();
    this->testLinearInterpolation();
}

bool TestPhysics::determineIfApprox(double expected, double actual) {
    double low = expected - 0.0001;
    double high = expected + 0.0001;
    return (actual > low && actual < high);
}

void TestPhysics::testMach()
{
    // Exercise
    double mach = Physics::calculateMach(827.0, 340.0);
    
    // Verify
    assert(this->determineIfApprox(2.4323, mach));
} // Teardown

void TestPhysics::testRetrieveD01R01()
{
    // Setup
    double mach = 2.4323;
    
    // Exercise
    auto [d0,d1,r0,r1] = Physics::retrieveD01R01<const std::map<double, double>, double, double>(mach, Physics::dragMap);
    
    // Verify
    assert(this->determineIfApprox(1.99, d0));
    assert(this->determineIfApprox(2.870, d1));
    assert(this->determineIfApprox(0.2897, r0));
    assert(this->determineIfApprox(0.2297, r1));
} // Teardown

void TestPhysics::testLinearInterpolation()
{
    // Setup / Exercise
    double mach = 2.4323;
    double d0 = 1.99;
    double d1 = 2.870;
    double r0 = 0.2897;
    double r1 = 0.2297;
    
    // Exercise
    
    double dragCoefficient = Physics::linearInterpolation(r0, r1, d0, d1, mach);
    
    // Verify
    assert(this->determineIfApprox(.25953, dragCoefficient));
} // Teardown
