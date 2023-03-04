//
//  TestPhysics.cpp
//  Lab07
//
//  Created by Samuel on 3/4/23.
//

//
//  physics.hpp
//  Lab07
//
//  Created by Samuel on 2/16/23.
//

#ifndef physics_hpp
#define physics_hpp

#include <stdio.h>
#include "position.h"

#include <map>
#include <tuple>

class TestPhysics;

class physics {
    friend TestPhysics;
public:
    
    const double surfaceArea;
    const double mass;
    
    //    double timer;
    //    double accelerationThrust;  // Acceleration due to thrust
    //    double ddx;                 // Total horizontal acceleration
    //    double ddy;                 // Total vertical acceleration
    double dragCoefficient;
    double density;
    double speedOfSound;
    double gravity;
     
    double velocity;
    double acceleration;
    double aRadians;
    double aDegrees;            // User input on the angle
    double mach;
    double dragForce;
    double projectileForce;
    double dx;
    double dy;
    double ddx;
    double ddy;

    double x;
    double y; // altitude
    // Position pos;
    //    double v;                   // Total velocity
    //
    
    
    // constructor
    physics(double mass, double radius);
    physics();
    
//    // getters
    double getAltitude()const;
//    double getTimer();
//    double getRadians();
//    double getAccelerationThrust();
//    double getDdxThrust();
//
//    double getDdyThrust();
//    double getDdx();
//    double getDdy();
//    double getV();
//    double getDegrees();
//
//    // setters
//    void setTimer(double newTimer);
//    void setRadians(double r);
//    void setAccelerationThrust(double at);
//    void setDdxThrust(double dt);
//    void setDdyThrust(double dt);
//    void setDdx(double d);
//    void setDdy(double d);
//    void setV(double vel);
//    void setDegrees(double d);
//

// private:
    double radiansToDegrees(double radians);
    double degreesToRadians(double degrees);

    void normalize();
    double reverseRadianAngle(double a);
    double calculateMach(double speed, double speedOfSound);
    double areaOfCircle(double r);
    
    // Drag coefficient
    static std::map<double, double> createDragMap();

    // Environmental table methods
    
    static std::map<int, double> createGravityMap();
    static std::map<int, double> createDensityMap();
    static std::map<int, int> createSpeedOfSoundMap();
    
//    std::tuple<int, int, double, double> retrieveD01R01forDensity(double altitude);
//    std::tuple<int, int, double, double> retrieveD01R01ForGravity(double altitude);
//    std::tuple<int, int, int, int> retrieveD01R01ForSpeedOfSound(double altitude);

    template <typename func_T,typename map_T,typename T1,typename T2>
    std::tuple<T1,T1,T2,T2> retrieveD01R01(double altitude, func_T func);
    
    void interpolateEnviornmentalFunctions();
    void interpolateDragCoefficient();
  
    
    double caclulateDragCoefficient(double mach);
    double linearInterpolation(double r0, double r1, double d0, double d1, double d);
    double applyDragForce(double coefficient, double p, double v, double a);
    double calculateAcceleration(double f, double m);
    double calculateForce(double m, double a);
    double calculateHorizontalComponent(double a, double s);
    double calculateVerticalComponent(double a, double s);
    double angleFromComponents(double dx, double dy);
    double calculateTotalVelocity(double dx, double dy);
    double calculateDistance(double s, double v, double a, double t);
    
//     double dxtnearinterpolationR(double r0, double r1, double d0, double d1, double d);

    double kinematicsEquation(double s, double a, double t);
    
private:
    void interpolateDensity();
    void interpolateSpeedOfSound();
    void interpolateGravity();
};

#endif /* physics_hpp */


class TestPhysics {
    
public:
    void test_runner() {
        this->testConstructor();
        this->testDegreeToRadConversionBorder();
        this->testDegreeToRadConversionScenario();
        this->testNormalize();
        this->testRevAngle();
        this->testMach();
        this->testAreaOfCircle();
        this->testAreaOfCircle2();
        this->testRetrieveD01R01();
        this->testLinearInterpolation();
    }
    
private:
    bool determineIfApprox(double expected, double actual) {
        double low = expected - 0.0001;
        double high = expected + 0.0001;
        return (actual > low && actual < high);
    }
    
    void testConstructor()
    {
        // Setup / Exercise
        physics p(46.7 /*mass of projectile*/, .15489 / 2.0 /*Radius for calculating surface area*/);
        
        // Verify
        assert(p.mass == 46.7);
        assert(p.surfaceArea > 0.0188 && p.surfaceArea < 0.0189);
        assert(p.getAltitude() == p.y && p.y == 0.0);
    } // Teardown
    
    void testDegreeToRadConversionBorder()
    {
        // Setup
        physics p;
        p.aDegrees = 0.0;
        
        // Exercise
        p.aRadians = p.degreesToRadians(p.aDegrees);
        
        // Verify
        assert(p.aRadians == 0);
        assert(p.radiansToDegrees(p.aRadians) == p.aDegrees);
    } // Teardown
    
    void testDegreeToRadConversionScenario()
    {
        // Setup
        physics p;
        p.aDegrees = 30.0;
        
        // Exercise
        p.aRadians = p.degreesToRadians(p.aDegrees);
        
        // Verify
        assert(p.aRadians > 0.5234 && p.aRadians < 0.5236);
        assert(p.radiansToDegrees(p.aRadians) == 30.0);
        assert(p.aDegrees == 30);
        assert(p.radiansToDegrees(p.aRadians) == p.aDegrees);
    } // Teardown
    
    void testNormalize()
    {
        // Setup
        physics p;
        
        p.aDegrees = 360 * 8;
        p.aRadians = 2 * M_PI * 239;
        
        // Exercise
        p.normalize();
        
        // Verify
        assert(p.aDegrees == 360);
        assert(p.aRadians >= 0 && p.aRadians < 0.0001);
    } // Teardown

    void testRevAngle()
    {
        // Setup / Exercise
        physics p;
        p.aRadians = M_PI * 0.5;

        // Verify
        assert(p.reverseRadianAngle(p.aRadians) == M_PI * 1.5);
    } // Teardown

    void testMach()
    {
        // Setup
        physics p(46.7 /*mass of projectile*/, .15489 / 2.0 /*Radius for calculating surface area*/);
        p.velocity = 827.0;
        
        // Exercise
        p.mach = p.calculateMach(p.velocity, p.speedOfSound);
        
        // Verify
        assert(p.speedOfSound == 340.0);
        assert(p.mach > 2.4322 && p.mach < 2.4324);
    } // Teardown
    
    void testAreaOfCircle()
    {
        // Setup
        physics p;
        double radius = 1.0;
        
        // Exercise
        double area = p.areaOfCircle(radius);
        
        // Verify
        assert(area > 3.14158 && area < 3.14160);
    } // Teardown
    
    void testAreaOfCircle2()
    {
        // Setup
        physics p;
        double radius = 0.077445;
        
        // Exercise
        double area = p.areaOfCircle(radius);
        
        // Verify
        assert(area > 0.018841 && area < 0.018843);
    } // Teardown
    
    void testRetrieveD01R01()
    {
        // Setup / Exercise
        physics p(46.7 /*mass of projectile*/, .15489 / 2.0 /*Radius for calculating surface area*/);
        p.velocity = 827.0;
        p.mach = p.calculateMach(p.velocity, p.speedOfSound);
        
        //
        auto [d0,d1,r0,r1] = p.retrieveD01R01<decltype(&physics::createDragMap), std::map<double, double>, double, double>(p.mach, physics::createDragMap);
        
        // Verify
        assert(determineIfApprox(1.99, d0));
        assert(determineIfApprox(2.870, d1));
        assert(determineIfApprox(0.2897, r0));
        assert(determineIfApprox(0.2297, r1));
    } // Teardown
    void testLinearInterpolation()
    {
        // Setup / Exercise
        physics p(46.7 /*mass of projectile*/, .15489 / 2.0 /*Radius for calculating surface area*/);
        p.velocity = 827.0;
        p.mach = p.calculateMach(p.velocity, p.speedOfSound);
        auto [d0,d1,r0,r1] = p.retrieveD01R01<decltype(&physics::createDragMap), std::map<double, double>, double, double>(p.mach, physics::createDragMap);
        
        // Exercise
        
        p.dragCoefficient = p.linearInterpolation(r0, r1, d0, d1, p.mach);
        
        // Verify
        assert(determineIfApprox(.25953, p.dragCoefficient));
    } // Teardown
    
//
};
