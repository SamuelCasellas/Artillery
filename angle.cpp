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

Angle::Angle():pi{2 * asin(1.0)}, fullRevolutionRad{2 * pi}, fullRevolutionDeg{360.0} {
    radians = 0.0;
    degrees = 0.0;
}

Angle::Angle(Angle & a):pi{2 * asin(1.0)}, fullRevolutionRad{2 * pi}, fullRevolutionDeg{360.0} {
    radians = a.radians;
    degrees = a.degrees;
}
    
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
    while (radians < fullRevolutionRad) {
        radians += fullRevolutionRad;
    }
    
    while (radians > fullRevolutionRad) {
        radians -= fullRevolutionRad;
    }
    while (degrees < fullRevolutionDeg) {
        degrees += fullRevolutionDeg;
    }
    
    while (degrees > fullRevolutionDeg) {
        degrees -= fullRevolutionDeg;
    }
}

// getters
double Angle::getDegrees()const
{
    return degrees;
}
double Angle::getRadians()const
{
    return radians;
}
// setters
void Angle::setDegrees(double d)
{
    degrees = d;
    radians = convertToRadians(d);
}
void Angle::setRadians(double r)
{
    radians = r;
    degrees = convertToDegrees(r);
}

double Angle::reverseRadianAngle(double aRadians)
{
    return aRadians + M_PI;
}

Angle &Angle::operator=(const Angle &a)
{
   radians = a.radians;
   degrees = a.degrees;
   this->normalize();
   return *this;
}
