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
#include "TestPhysics.h"

class Bullet
{
    friend TestPhysics;
    friend TestBullet;

public:
    int framesSinceLanded = 0;
    // Constructor for move method
    Bullet();
    Bullet(double mass, double radius, double initVel, Angle a, Position pos);

    // Move constructor (for push_back method in main)
    Bullet(Bullet &&other);

    const double surfaceArea;
    const double mass;

    Position projectilePath[20];

    // void draw();
    bool hasLanded();
    void calculateNextFramesPos();

    double getAge() const;
    
    Position getPtBullet()const;

private:
    Position ptBullet;

    Angle aBullet;
    Angle aDrag;

    double age; // time since firing

    double mach;
    double dragCoefficient;

    double density;
    double speedOfSound;
    double gravity;

    double dragAcceleration;

    // dx and dy are the x and y components of the bullet's velocity
    double dx;
    double dy;
    // ddx and ddy are the x and y components of the bullet's acceleration
    double ddx;
    double ddy;
    // totalVelocity is the total velocity of the bullet
    double totalVelocity;

    // Time interval
    static inline const int t = 1;
};

#endif /* bullet_h */
