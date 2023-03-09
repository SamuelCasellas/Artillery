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
    bool determineIfApprox(double expected, double actual);  

    void testMach();
    void testInterpolateDragCoefficient();
    void testInterpolateDensity();
    void testInterpolateSpeedOfSound();
    void testInterpolateGravity();
    
    void testCalculateDragForce();
    void testCalculateAcceleration();
    void testCalculateForce();
    void testCalculateHorizontalComponent();
    void testCalculateVerticalComponent();
    void testCalculateAngleFromComponents();
    void testCalculateTotalVelocity();
    void testCalculateDistance();
    
    void testKinematicsEquation();
    
    void testLinearInterpolation();
    
    void testRetrieveD01R01();
};

#endif /* TestPhysics_h */
