//
//  angle.cpp
//  Lab07
//
//  Created by Samuel on 3/8/23.
//

#include "angle.h"

#include <iostream>
#include <cmath>

using namespace std;

Angle::Angle() : pi{2 * asin(1.0)}, fullRevolutionRad{2 * pi}, fullRevolutionDeg{360.0}
{
    radians = 0.0;
    degrees = 0.0;
}

Angle::Angle(Angle &a) : pi{2 * asin(1.0)}, fullRevolutionRad{2 * pi}, fullRevolutionDeg{360.0}
{
    radians = a.radians;
    degrees = a.degrees;
}

Angle::Angle(Angle &&other) : pi(other.pi), fullRevolutionRad(other.fullRevolutionRad), fullRevolutionDeg(other.fullRevolutionDeg), radians(other.radians), degrees(other.degrees) {}

double Angle::convertToDegrees(double r)
{
    return r * 180 / pi;
}

double Angle::convertToRadians(double d)
{
    return d * pi / 180;
}

void Angle::normalize()
{
    while (radians < fullRevolutionRad)
    {
        radians += fullRevolutionRad;
    }

    while (radians > fullRevolutionRad)
    {
        radians -= fullRevolutionRad;
    }

    while (degrees < fullRevolutionDeg)
    {
        degrees += fullRevolutionDeg;
    }

    while (degrees > fullRevolutionDeg)
    {
        degrees -= fullRevolutionDeg;
    }
}

// setters
void Angle::setDegrees(double d)
{
    degrees = d;
    radians = convertToRadians(d);
    normalize();
}
void Angle::setRadians(double r)
{
    radians = r;
    degrees = convertToDegrees(r);
    normalize();
}

void Angle::reverseRadianAngle()
{
    this->radians = this->radians + M_PI;
    this->degrees = this->degrees + 180.0;
    this->normalize();
}

Angle &Angle::operator=(const Angle &a)
{
    radians = a.radians;
    degrees = a.degrees;
    normalize();
    return *this;
}
