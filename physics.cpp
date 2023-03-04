#include <iostream>
#include <iomanip>
#include <cmath>
#include "physics.h"

physics::physics(double mass, double radius) : mass(mass), surfaceArea(this->areaOfCircle(radius))
{
    this->x = this->y = 0.0;
    this->dx = this->dy = 0.0;
    this->acceleration = 0.0;

    // Environment variables at ground level
    this->density = 1.225;
    this->speedOfSound = 340.0;
    this->gravity = 9.807;
}

physics::physics(): mass(0.0), surfaceArea(0.0) {}

double physics::getAltitude() const { return this->y; }

std::map<double, double> physics::createDragMap()
{
    return std::map<double, double>{
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
}

std::map<int, double> physics::createDensityMap()
{
    return std::map<int, double>{
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
}

std::map<int, int> physics::createSpeedOfSoundMap()
{
    return std::map<int, int>{
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
}

std::map<int, double> physics::createGravityMap()
{
    return std::map<int, double>{
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
}

template <typename func_T, typename map_T, typename T1, typename T2>
std::tuple<T1, T1, T2, T2> physics::retrieveD01R01(double d /* altitude || mach */, func_T mapFunc)
{

    map_T map = mapFunc();

    std::tuple<T1, T1, T2, T2> d01R01Tuple;

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
        // first == altitude
        // second == var in question
        if (it->first <= d)
            continue;

        // Upper bound (d1, r1)
        std::get<1>(d01R01Tuple) = it->first;
        std::get<3>(d01R01Tuple) = it->second;

        std::cout << it->second << std::endl;

        it--;
        // Lower bound (d0, r0)
        std::get<0>(d01R01Tuple) = it->first;
        std::get<2>(d01R01Tuple) = it->second;

        break;
    }

    return d01R01Tuple;
}

void physics::interpolateDragCoefficient()
{
    auto [d0, d1, r0, r1] = this->retrieveD01R01<decltype(&physics::createDragMap), std::map<double, double>, double, double>(this->mach, physics::createDragMap);

    this->dragCoefficient = this->linearInterpolation(r0, r1, d0, d1, this->mach);
}

//

/***
 Assuming we have updated y and mach
***/
void physics::interpolateEnviornmentalFunctions()
{
    this->interpolateDensity();
    this->interpolateSpeedOfSound();
    this->interpolateGravity();
}

void physics::interpolateDensity()
{
    auto [d0, d1, r0, r1] = this->retrieveD01R01<decltype(&physics::createDensityMap), std::map<int, double>, int, double>(this->y, physics::createDensityMap);

    this->density = this->linearInterpolation(r0, r1, d0, d1, this->y);
}

void physics::interpolateSpeedOfSound()
{
    auto [d0, d1, r0, r1] = this->retrieveD01R01<decltype(&physics::createSpeedOfSoundMap), std::map<int, int>, int, int>(this->y, physics::createSpeedOfSoundMap);

    this->speedOfSound = this->linearInterpolation(r0, r1, d0, d1, this->y);
}

void physics::interpolateGravity()
{
    auto [d0, d1, r0, r1] = this->retrieveD01R01<decltype(&physics::createGravityMap), std::map<int, double>, int, double>(this->y, physics::createGravityMap);

    this->gravity = this->linearInterpolation(r0, r1, d0, d1, this->y);
}

//

void physics::normalize()
{
    const double fullRevolututionRad = 2 * M_PI;
    const double fullRevolutionDeg = 360.0;

    while (aRadians < 0)
    {
        this->aRadians += fullRevolututionRad;
    }

    while (aRadians > fullRevolututionRad)
    {
        this->aRadians -= fullRevolututionRad;
    }

    while (aDegrees < 0)
    {
        this->aDegrees += fullRevolutionDeg;
    }

    while (aDegrees > fullRevolutionDeg)
    {
        this->aDegrees -= fullRevolutionDeg;
    }
}

double physics::reverseRadianAngle(double a)
{
    return aRadians + M_PI;
}

double physics::calculateMach(double speed, double speedOfSound)
{
    double mach = speed / speedOfSound;
    return mach;
}

// Drag Force Equation
// d = 1/2 c * p * v^2 * a
// This will need to be adjusted since Drag and coefficient are the variables we already have.

double physics::applyDragForce(double coefficient, double p /*air density*/, double v, double a)
{
    double drag = (coefficient / 2.0) * p * (pow(v, 2)) * a;
    return drag;
}

// Area of a Circle
// a = n * r^2

double physics::areaOfCircle(double r)
{
    double area = M_PI * pow(r, 2);
    return area;
}

// Degrees and Radians
// r / 2 pi = d / 360 degrees
// Because I wasn't sure which one we were going to be given, I did two basic functions, one to convert degrees to radians and one to convert radians to degrees.

double physics::radiansToDegrees(double radians)
{
    double degrees = radians * (180.0 / M_PI);
    return degrees;
}

double physics::degreesToRadians(double degrees)
{
    double radians = degrees * (M_PI / 180.0);
    return radians;
}

// Newton's Second Law of Motion
// F = m * a

double physics::calculateForce(double m, double a)
{
    double f = m * a;
    return f;
}

double physics::calculateAcceleration(double f, double m)
{
    double a = f / m;
    return a;
}

// vertical component of speed
// dy = s cos(a)

double physics::calculateHorizontalComponent(double a, double s)
{
    double dx = s * sin(a);
    return dx;
}

// horizontal component of speed
// dx = s sin(a)

double physics::calculateVerticalComponent(double a, double s)
{
    double dy = s * cos(a);
    return dy;
}

// angle from components
// a = atan(dx, dy)

double physics::angleFromComponents(double dx, double dy)
{
    double a = atan(dx / dy);
    return a;
}

// pythagorean theorem
// s^2 = dx^2 + dy^2

double physics::calculateTotalVelocity(double dx, double dy)
{
    double s = sqrt((dx * dx) + (dy * dy));
    return s;
}

double physics::calculateDistance(double s, double v, double a, double t)
{
    return s + v * t + 0.5 * a * t * t;
}

double physics::kinematicsEquation(double s, double a, double t)
{
    double s1 = s + (a * t);
    return s1;
}

// d == v ; r == c
double physics::linearInterpolation(double r0, double r1, double d0, double d1, double d)
{
    return (r0 + ((d - d0) * (r1 - r0) / (d1 - d0)));
    // 0.2897 + (2.432 - 1.99) * (.2296 - .289) / (2.87 - 1.99)
}
