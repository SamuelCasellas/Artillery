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

class physics
{
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
    double aDegrees; // User input on the angle
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

    //    // getters
    double getAltitude() const;
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

    void calculateNewPosition();

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

    template <typename func_T, typename map_T, typename T1, typename T2>
    std::tuple<T1, T1, T2, T2> retrieveD01R01(double altitude, func_T func);

    // Including Mach
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
