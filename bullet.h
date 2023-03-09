//
//  bullet.h
//  Lab07
//
//  Created by Samuel on 3/8/23.
//

#ifndef bullet_h
#define bullet_h

#include "position.h"
#include "angle.h"

#include "TestBullet.h"

class Bullet
{
public:
    Bullet(double mass, double radius, double initVel);
    
    const double surfaceArea;
    const double mass;
    
    Position projectilePath[20];
    
    // void draw();
    bool hasLanded();
    void calculateNewPosition();
    
private:
    Position ptBullet;
    
    Angle aBullet;
    
    double age; // time since firing
    
    double mach;
    double dragCoefficient;
    
    double density;
    double speedOfSound;
    double gravity;
    
    double dragForce;
    double projectileForce;
    
    double dx;
    double dy;
    double ddx;
    double ddy;
    double totalVelocity;
    double totalAcceleration;
};



#endif /* bullet_h */
