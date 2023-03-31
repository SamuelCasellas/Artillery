//
//  Physics.h
//  Lab07
//
//  Created by Samuel on 2/16/23.
//

#ifndef Physics_h
#define Physics_h

#include "position.h"
#include <map>
#include <tuple>
#include "TestPhysics.h"
/**************************************************
 *
 *                 PHYSICS CLASS
 *
 * All functions are static since there are no member variables.
 *********************************************************************************/
class Physics
{
    friend TestPhysics;

public:
    static double calculateMach(double speed, double speedOfSound);

    static double interpolateDragCoefficient(double mach);
    static double interpolateDensity(double y);
    static double interpolateSpeedOfSound(double y);
    static double interpolateGravity(double y);

    static double calculateDragForce(double coefficient, double p, double v, double a);
    static double calculateAcceleration(double f, double m);
    static double calculateForce(double m, double a);
    static double calculateHorizontalComponent(double a, double s);
    static double calculateVerticalComponent(double a, double s);
    static double calculateAngleFromComponents(double dx, double dy);
    static double calculateTotalVelocity(double dx, double dy);
    static double calculateDistance(double s, double v, double a, double t);

    static double kinematicsEquation(double s, double a, double t);

    static double linearInterpolation(double r0, double r1, double d0, double d1, double d);

private:
    static const std::map<double, double> dragMap;
    static const std::map<int, double> gravityMap;
    static const std::map<int, double> densityMap;
    static const std::map<int, int> speedOfSoundMap;

    template <typename map_T, typename T1, typename T2>
    static std::tuple<T1, T1, T2, T2> retrieveD01R01(double d /* mach || altitude */, map_T &map);
};

#endif /* Physics_h */
