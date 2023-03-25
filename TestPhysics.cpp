//
//  TestPhysics.cpp
//  Lab07
//
//  Created by Samuel on 3/4/23.
//

#include "physics.h"
#include "bullet.h"
#include <cassert>

void TestPhysics::run() {
    this->testMach();
    
    this->testInterpolateDragCoefficient();
    this->testInterpolateDragCoefficient1();
    this->testInterpolateDensity();
    this->testInterpolateDensity1();
    this->testInterpolateSpeedOfSound();
    this->testInterpolateSpeedOfSound1();
    this->testInterpolateGravity();
    this->testInterpolateGravity1();
    
    this->testCalculateDragForce();
    this->testCalculateAcceleration();
    this->testCalculateForce();
    this->testCalculateHorizontalComponentVel();
    this->testCalculateHorizontalComponentAcc();
    this->testCalculateVerticalComponentVel();
    this->testCalculateVerticalComponentAcc();
    this->testCalculateAngleFromComponents();
    this->testCalculateTotalVelocity();
    this->testCalculateDistanceX();
    this->testCalculateDistanceY();
    
    this->testKinematicsEquationX();
    this->testKinematicsEquationY();
    
    this->testLinearInterpolation();
    this->testRetrieveD01R01();
}

bool TestPhysics::determineIfApprox(double expected, double actual, double error) {
    double low = expected - error;
    double high = expected + error;
    return (actual > low && actual < high);
}

void TestPhysics::testMach()
{
    // Exercise
    double mach = Physics::calculateMach(827.0, 340.0);
    
    // Verify
    assert(this->determineIfApprox(2.4323, mach, 0.001));
} // Teardown

//

void TestPhysics::testInterpolateDragCoefficient() {
    // Setup
    double mach = 0.3;
    
    // Exercise
    double coefficient = Physics::interpolateDragCoefficient(mach);
    
    // Verify
    assert(this->determineIfApprox(0.1629, coefficient, 0.001));
}

void TestPhysics::testInterpolateDragCoefficient1() {
    // Setup
    double mach = 2.4323;
    
    // Exercise
    double coefficient = Physics::interpolateDragCoefficient(mach);
    
    // Verify
    assert(this->determineIfApprox(.25953, coefficient, 0.001));
}

void TestPhysics::testInterpolateDensity() {
    // Setup
    double y = 0;
    
    // Exercise
    double dens = Physics::interpolateDensity(y);
    
    // Verify
    assert(this->determineIfApprox(1.225, dens, 0.001));
}

void TestPhysics::testInterpolateDensity1() {
    // Setup
    double y = 1435;
    
    // Exercise
    double dens = Physics::interpolateDensity(y);
    
    // Verify
    assert(this->determineIfApprox(1.0653250, dens, 0.01));
}

void TestPhysics::testInterpolateSpeedOfSound() {
    // Setup
    double y = 0;
    
    // Exercise
    double sOfS = Physics::interpolateSpeedOfSound(y);
    
    // Verify
    assert(this->determineIfApprox(340, sOfS, 0.01));
}

void TestPhysics::testInterpolateSpeedOfSound1() {
    // Setup
    double y = 2322.23;
    
    // Exercise
    double sOfS = Physics::interpolateSpeedOfSound(y);
    
    // Verify
    assert(this->determineIfApprox(330.71, sOfS, 0.01));
}

void TestPhysics::testInterpolateGravity() {
    // Setup
    double y = 0;
    
    // Exercise
    double grav = Physics::interpolateGravity(y);
    
    // Verify
    assert(this->determineIfApprox(9.807, grav, 0.01));
}

void TestPhysics::testInterpolateGravity1() {
    // Setup
    double y = 573.0;
    
    // Exercise
    double grav = Physics::interpolateGravity(y);
    
    // Verify
    assert(this->determineIfApprox(9.805281, grav, 0.01));
}

//

void TestPhysics::testCalculateDragForce() {
    // Setup
    Angle ang;
    ang.setDegrees(30);
    Bullet b(46.7 /*mass of projectile*/, .15489 / 2.0 /*Radius for calculating surface area*/, 827.0 /* initial velocity */, ang, Position());
    double coefficient = 0.25953957219251339;
    double p = 1.225;
    double v = 827.0;
    double a = b.surfaceArea;
    
    // Exercise
     double dragForce = Physics::calculateDragForce(coefficient, p,
                                                v, a);
    // Verify
     assert(this->determineIfApprox(2048.6292, dragForce, 0.1));
}

void TestPhysics::testCalculateAcceleration() {
    // Setup
    double f = 2048.6292;
    double m = 46.7;
    
    // Exercise
    double acc = Physics::calculateAcceleration(f, m);
    // Verify
    assert(this->determineIfApprox(43.867, acc, 0.001));
}

void TestPhysics::testCalculateForce() {
    // Setup
    double a = 43.867;
    double m = 46.7;
    
    // Exercise
    double f = Physics::calculateForce(m, a);
    // Verify
    assert(this->determineIfApprox(2048.6292, f, 0.3));
}

//

void TestPhysics::testCalculateHorizontalComponentVel() {
    // Setup
    Angle a;
    a.setDegrees(30);
    Bullet b(46.7 /*mass of projectile*/, .15489 / 2.0 /*Radius for calculating surface area*/, 827.0 /* initial velocity */, a, Position());
    
    // Exercise
    double dx = Physics::calculateHorizontalComponent(a.getRadians(), b.totalVelocity);
    // Verify
    assert(this->determineIfApprox(413.5, dx, 0.001));
}

void TestPhysics::testCalculateVerticalComponentVel() {
    // Setup
    Angle a;
    a.setDegrees(30);
    Bullet b(46.7 /*mass of projectile*/, .15489 / 2.0 /*Radius for calculating surface area*/, 827.0 /* initial velocity */, a, Position());
    
    // Exercise
    double dy = Physics::calculateVerticalComponent(a.getRadians(), b.totalVelocity);
    // Verify
    assert(this->determineIfApprox(716.2, dy, 0.01));
}

void TestPhysics::testCalculateHorizontalComponentAcc() {
    // Setup
    Angle a;
    a.setDegrees(30);
    Bullet b(46.7 /*mass of projectile*/, .15489 / 2.0 /*Radius for calculating surface area*/, 827.0 /* initial velocity */, a, Position());
    double acc = 43.867;
    // Exercise
    double ddx = -Physics::calculateHorizontalComponent(a.getRadians(), acc);
    // Verify
    assert(this->determineIfApprox(-21.93, ddx, 0.01));
}

void TestPhysics::testCalculateVerticalComponentAcc() {
    // Setup
    Angle a;
    a.setDegrees(30);
    Bullet b(46.7 /*mass of projectile*/, .15489 / 2.0 /*Radius for calculating surface area*/, 827.0 /* initial velocity */, a, Position());
    double acc = 43.867;
    // Exercise
    double ddy = -b.gravity-Physics::calculateVerticalComponent(a.getRadians(), acc);
    // Verify
    assert(this->determineIfApprox(-47.79, ddy, 0.01));
}

//

void TestPhysics::testCalculateAngleFromComponents() {
    // Setup
    double dx = 413.5;
    double dy = 716.2;
    // Exercise
    double newAngle = Physics::calculateAngleFromComponents(dx, dy);
    // Verify
    assert(this->determineIfApprox(0.5201290587991238, newAngle, 0.01));
}

void TestPhysics::testCalculateTotalVelocity() {
    // Setup
    double dx = 413.5;
    double dy = 716.2;
    // Exercise
    double totalVel = Physics::calculateTotalVelocity(dx, dy);
    // Verify
    assert(this->determineIfApprox(827.7915367159061, totalVel, 1));
}

void TestPhysics::testCalculateDistanceX() {
    // Setup
    double x = 0.0;
    double dx = 413.5;
    double ddx = -21.935;
    double t = 1;
    // Exercise
    double newX = Physics::calculateDistance(x, dx, ddx, t);
    // Verify
    assert(this->determineIfApprox(403.53, newX, 1.1));
}

void TestPhysics::testCalculateDistanceY() {
    // Setup
    double y = 0.0;
    double dy = 716.2;
    double ddy = -47.79;
    double t = 1;
    // Exercise
    double newY = Physics::calculateDistance(y, dy, ddy, t);
    // Verify
    assert(this->determineIfApprox(692.31, newY, 0.1));
}

//

void TestPhysics::testKinematicsEquationX() {
    // Setup
    double dx0 = 413.5;
    double ddx = -21.935;
    double t = 1;
    // Exercise
    double dx = Physics::kinematicsEquation(dx0, ddx, t);
    // Verify
    assert(this->determineIfApprox(391.56, dx, 0.1));
}

void TestPhysics::testKinematicsEquationY() {
    // Setup
    double dy0 = 716.2;
    double ddy = -47.79;
    double t = 1;
    // Exercise
    double dx = Physics::kinematicsEquation(dy0, ddy, t);
    // Verify
    assert(this->determineIfApprox(668.40, dx, 0.1));
}

//

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
    assert(this->determineIfApprox(.25953, dragCoefficient, 0.001));
} // Teardown

void TestPhysics::testRetrieveD01R01()
{
    // Setup
    double mach = 2.4323;
    
    // Exercise
    auto [d0,d1,r0,r1] = Physics::retrieveD01R01<const std::map<double, double>, double, double>(mach, Physics::dragMap);
    
    // Verify
    assert(this->determineIfApprox(1.99, d0, 0.001));
    assert(this->determineIfApprox(2.870, d1, 0.001));
    assert(this->determineIfApprox(0.2897, r0, 0.001));
    assert(this->determineIfApprox(0.2297, r1, 0.001));
} // Teardown
