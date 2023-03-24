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
    
    Bullet(double mass, double radius, double initVel, Angle a);
    Bullet(double mass, double radius, double initVel, Angle a, Position pos);
    
    // Move constructor (for push_back method in main)
    Bullet(Bullet&& other);
    
    const double surfaceArea;
    const double mass;
    
    Position projectilePath[20];
    
    // void draw();
    bool hasLanded();
    void calculateNewPosition();
    
    double getAge()const;
    
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
    
    // dragForce is the force of drag on the bullet
    double dragForce;
    // projectileForce is the force of the bullet's projectile
    double projectileForce;
    
    // dx and dy are the x and y components of the bullet's velocity
    double dx;
    double dy;
    // ddx and ddy are the x and y components of the bullet's acceleration
    double ddx;
    double ddy;
    // totalVelocity is the total velocity of the bullet
    double totalVelocity;
    // totalAcceleration is the total acceleration of the bullet
    double totalAcceleration;
};



#endif /* bullet_h */
