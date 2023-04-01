//
//  angle.h
//  Lab07
//
//  Created by Samuel on 3/8/23.
//

#ifndef angle_h
#define angle_h

#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

class Angle
{

    const double pi;
    const double fullRevolutionRad;
    const double fullRevolutionDeg;

private:
    double radians;
    double degrees;

    double convertToDegrees(double r);
    double convertToRadians(double d);
    void normalize();

public:
    Angle();
    Angle(Angle &a);

    Angle(Angle &&other);

    // getters
    double getDegrees() const { return degrees; }
    double getRadians() const { return radians; }
    
    void setDegrees(double d);
    void setRadians(double r);
    Angle &operator=(const Angle &a);
    
    friend std::ostream& operator<<(std::ostream& os, const Angle& ang) {
        os << ang.getDegrees();
        return os;
    }

    void reverseRadianAngle();
};

#endif /* angle_h */
