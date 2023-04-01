#include <iostream>
#include <iomanip>
#include <cmath>
#include "physics.h"

double Physics::interpolateDragCoefficient(double mach)
{
    auto [d0, d1, r0, r1] = Physics::retrieveD01R01<const std::map<double, double>, double, double>(mach, Physics::dragMap);

    return Physics::linearInterpolation(r0, r1, d0, d1, mach);
}

double Physics::interpolateDensity(double y)
{
    auto [d0, d1, r0, r1] = Physics::retrieveD01R01<const std::map<int, double>, int, double>(y, Physics::densityMap);

    return Physics::linearInterpolation(r0, r1, d0, d1, y);
}

double Physics::interpolateSpeedOfSound(double y)
{
    auto [d0, d1, r0, r1] = Physics::retrieveD01R01<const std::map<int, int>, int, int>(y, Physics::speedOfSoundMap);

    return Physics::linearInterpolation(r0, r1, d0, d1, y);
}

double Physics::interpolateGravity(double y)
{
    auto [d0, d1, r0, r1] = Physics::retrieveD01R01<const std::map<int, double>, int, double>(y, Physics::gravityMap);

    return Physics::linearInterpolation(r0, r1, d0, d1, y);
}

double Physics::calculateMach(double speed, double speedOfSound)
{
    return speed / speedOfSound;
}

// Drag Force Equation
// d = 1/2 c * p * v^2 * a

double Physics::calculateDragForce(double coefficient, double p /*air density*/, double v, double a)
{
    return (coefficient / 2.0) * p * (pow(v, 2)) * a;
}

// Newton's Second Law of Motion
// F = m * a

double Physics::calculateForce(double m, double a)
{
    return m * a;
}

double Physics::calculateAcceleration(double f, double m)
{
    return f / m;
}

double Physics::calculateHorizontalComponent(double a, double s)
{
    return s * sin(a);
}

double Physics::calculateVerticalComponent(double a, double s)
{
    return s * cos(a);
}

double Physics::calculateAngleFromComponents(double dx, double dy)
{
    return atan(dx / dy);
}

// pythagorean theorem
// s^2 = dx^2 + dy^2

double Physics::calculateTotalVelocity(double dx, double dy)
{
    return sqrt((dx * dx) + (dy * dy));
}

double Physics::calculateDistance(double s /*x || y*/, double v /*  */, double a /*acceleration*/, double t /*time*/)
{
    return s + v * t + 0.5 * a * t * t;
}

double Physics::kinematicsEquation(double s, double a, double t)
{
    // s1
    return s + (a * t);
}

// Private members

const std::map<double, double> Physics::dragMap = {
    {0.300, 0.1629},
    {0.500, 0.1659},
    {0.700, 0.2031},
    {0.890, 0.2597},
    {0.920, 0.3010},
    {0.960, 0.3287},
    {0.980, 0.4002},
    {1.000, 0.4258},
    {1.020, 0.4335},
    {1.060, 0.4483},
    {1.240, 0.4064},
    {1.530, 0.3663},
    {1.990, 0.2897},
    {2.870, 0.2297},
    {2.890, 0.2306},
    {5.000, 0.2656}};

const std::map<int, double> Physics::densityMap = {
    {0, 1.2250000},
    {1000, 1.1120000},
    {2000, 1.0070000},
    {3000, 0.9093000},
    {4000, 0.8194000},
    {5000, 0.7364000},
    {6000, 0.6601000},
    {7000, 0.5900000},
    {8000, 0.5258000},
    {9000, 0.4671000},
    {10000, 0.4135000},
    {15000, 0.1948000},
    {20000, 0.0889100},
    {25000, 0.0400800},
    {30000, 0.0184100},
    {40000, 0.0039960},
    {50000, 0.0010270},
    {60000, 0.0003097},
    {70000, 0.0000828},
    {80000, 0.0000185}};

const std::map<int, int> Physics::speedOfSoundMap = {
    {0, 340},
    {1000, 336},
    {2000, 332},
    {3000, 328},
    {4000, 324},
    {5000, 320},
    {6000, 316},
    {7000, 312},
    {8000, 308},
    {9000, 303},
    {10000, 299},
    {15000, 295},
    {20000, 295},
    {25000, 295},
    {30000, 305},
    {40000, 324}};

const std::map<int, double> Physics::gravityMap = {
    {0, 9.807},
    {1000, 9.804},
    {2000, 9.801},
    {3000, 9.797},
    {4000, 9.794},
    {5000, 9.791},
    {6000, 9.788},
    {7000, 9.785},
    {8000, 9.782},
    {9000, 9.779},
    {10000, 9.776},
    {15000, 9.761},
    {20000, 9.745},
    {25000, 9.730}};

template <typename map_T, typename T1, typename T2>
std::tuple<T1, T1, T2, T2> Physics::retrieveD01R01(double d /* altitude || mach */, map_T &map)
{
    std::tuple<T1, T1, T2, T2> d01R01Tuple;

    bool withinRange = false;

    // Projectile hit the ground
    if (d < 0)
    {
        auto it = map.begin();
        // Lower bound (d0, r0)
        std::get<0>(d01R01Tuple) = it->first;
        std::get<2>(d01R01Tuple) = it->second;
        it++;
        // Upper bound (d1, r1)
        std::get<1>(d01R01Tuple) = it->first;
        std::get<3>(d01R01Tuple) = it->second;
        return d01R01Tuple;
    }

    for (auto it = map.begin(); it != map.end(); ++it)
    {
        // first == altitude / mach
        // second == var in question
        if (it->first <= d)
            continue;

        // Upper bound (d1, r1)
        std::get<1>(d01R01Tuple) = it->first;
        std::get<3>(d01R01Tuple) = it->second;

        it--;
        // Lower bound (d0, r0)
        std::get<0>(d01R01Tuple) = it->first;
        std::get<2>(d01R01Tuple) = it->second;

        withinRange = true;
        break;
    }

    if (!withinRange)
    {
        auto it = map.end();
        it--;
        std::get<1>(d01R01Tuple) = std::get<0>(d01R01Tuple) = it->first;
        std::get<3>(d01R01Tuple) = std::get<2>(d01R01Tuple) = it->second;
    }

    return d01R01Tuple;
}

// d == v ; r == c
double Physics::linearInterpolation(double r0, double r1, double d0, double d1, double d)
{
    if (d0 == d1)
    {
        // Handle case where d0 and d1 are equal
        return (r0 + r1) / 2.0;
    }
    else
    {
        return (r0 + ((d - d0) * (r1 - r0) / (d1 - d0)));
    }
}
