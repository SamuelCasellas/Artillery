//
//  TestPhysics.h
//  Lab07
//
//  Created by Samuel on 3/8/23.
//

#ifndef TestPhysics_h
#define TestPhysics_h

#include <map>
#include <tuple>

class TestPhysics {
public:
    void run();
private:
    bool determineIfApprox(double expected, double actual, double error);

    void testMach();
    
    void testInterpolateDragCoefficient();
    void testInterpolateDragCoefficient1();
    void testInterpolateDensity();
    void testInterpolateDensity1();
    void testInterpolateSpeedOfSound();
    void testInterpolateSpeedOfSound1();
    void testInterpolateGravity();
    void testInterpolateGravity1();
    
    void testCalculateDragForce(); 
    void testCalculateAcceleration();
    void testCalculateForce();
    void testCalculateHorizontalComponentVel();
    void testCalculateHorizontalComponentAcc();
    void testCalculateVerticalComponentVel();
    void testCalculateVerticalComponentAcc();
    
    void testCalculateAngleFromComponents();
    void testCalculateTotalVelocity();
    void testCalculateDistanceX();
    void testCalculateDistanceY();
    
    void testKinematicsEquationX();
    void testKinematicsEquationY();
    
    void testLinearInterpolation();
    void testRetrieveD01R01();
};

#endif /* TestPhysics_h */
