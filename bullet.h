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
#include "ground.h"

#include "TestBullet.h"
#include "TestPhysics.h"

class Bullet
{
    friend TestPhysics;
    friend TestBullet;

public:
    int framesSinceLanded = 0;
    // Constructor for move method
    Bullet();
    
    // Constructor for testing
    Bullet(double mass, double radius, double initVel, Angle a, Position pos);
    
    // Constructor for simulation (hilly terrain)
    Bullet(double mass, double radius, double initVel, Angle a, Position pos, Ground & ground);

    // Move constructor (for push_back method in main)
    Bullet(Bullet &&other);

    const double surfaceArea;
    const double mass;

    Position projectilePath[20];

    bool hasLanded();
    void calculateNextFramesPos();

    double getAge() const { return age; }
    Position getPtBullet() const { return ptBullet; }
    
    double finalDistanceFromOrigin;
    double hangTime;

private:
    Position ptBullet;

    Angle aBullet;
    Angle aDrag;
    
    Ground ground;

    const double originX;
    
    // time since firing
    double age;

    double mach;
    double dragCoefficient;

    double density;
    double speedOfSound;
    double gravity;

    double dragAcceleration;

    // velocity
    double dx;
    double dy;
    
    // acceleration
    double ddx;
    double ddy;
    
    double totalVelocity;

    // Time interval
    static inline const int t = 1;
};

#endif /* bullet_h */
