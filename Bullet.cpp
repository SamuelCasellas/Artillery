//
//  bullet.cpp
//  Lab07
//
//  Created by Samuel on 3/8/23.
//

#include "bullet.h"
#include "physics.h"
#include "angle.h"

Bullet::Bullet() : surfaceArea(0.0), mass(0.0), age(0.0) {}

Bullet::Bullet(double mass, double radius, double initVel, Angle a, Position pos) : mass(mass), surfaceArea(M_PI * radius * radius)
{
    // USE THIS CONSTRUCTOR
    this->age = 0.0;

    this->aBullet = a;
    this->ptBullet = pos;

    this->totalVelocity = initVel;

    this->dx = this->dy = this->ddx = this->ddy = 0.0;

    // Environmental factors at ground level.
    double y = pos.getMetersY();
    this->density = Physics::interpolateDensity(y);           // 1.225 if y = 0
    this->speedOfSound = Physics::interpolateSpeedOfSound(y); // 340.0
    this->gravity = Physics::interpolateGravity(y);           // 9.807 = 0
}

Bullet::Bullet(Bullet &&other)
    : surfaceArea(other.surfaceArea), mass(other.mass), ptBullet(std::move(other.ptBullet)),
      aBullet(std::move(other.aBullet)), age(other.age), mach(other.mach),
      dragCoefficient(other.dragCoefficient), density(other.density), speedOfSound(other.speedOfSound),
      gravity(other.gravity), dragAcceleration(other.dragAcceleration),
      dx(other.dx), dy(other.dy), ddx(other.ddx), ddy(other.ddy),
      totalVelocity(other.totalVelocity)
{
    // Move the projectilePath array
    for (int i = 0; i < 20; i++)
    {
        projectilePath[i] = std::move(other.projectilePath[i]);
    }

    // Destroy other object after move
}

bool Bullet::hasLanded()
{
    return (this->ptBullet.getMetersY() <= 0);
}

void Bullet::calculateNextFramesPos()
{
    // Only calculate initial velocity at moment of firing
    if (age == 0)
    {
        // Break down the initial velocity to horizontal and vertical components
        dx = Physics::calculateHorizontalComponent(aBullet.getRadians(), totalVelocity);
        dy = Physics::calculateVerticalComponent(aBullet.getRadians(), totalVelocity);
    }
    else if (hasLanded())
    {
        age += t;
        return;
    }

    // Collect all of the data from your tables using a table reading method and your linear interpolation methods**
    double y = ptBullet.getMetersY();
    density = Physics::interpolateDensity(y);
    speedOfSound = Physics::interpolateSpeedOfSound(y);
    // Total acceleration due to gravity (negative)
    gravity = -(Physics::interpolateGravity(y));

    // Apply the necessary data to drag coefficient equation
    // This drag force is the total acceleration being applied to the projectile
    mach = Physics::calculateMach(totalVelocity, speedOfSound);
    dragCoefficient = Physics::interpolateDragCoefficient(mach);

    double dragForce = Physics::calculateDragForce(dragCoefficient, density, totalVelocity, surfaceArea);

    dragAcceleration = Physics::calculateAcceleration(dragForce, mass);

    ddx = -Physics::calculateHorizontalComponent(aBullet.getRadians(), dragAcceleration);
    ddy = gravity - Physics::calculateVerticalComponent(aBullet.getRadians(), dragAcceleration);

    // Keep record of old position (to calculate exact moment of hitting ground)
    Position oldPtBullet(ptBullet);

    // Apply your velocities to your x/y position to update your position
    ptBullet.setMetersX(Physics::calculateDistance(ptBullet.getMetersX(), dx, ddx, t));
    ptBullet.setMetersY(Physics::calculateDistance(ptBullet.getMetersY(), dy, ddy, t));

    // Use the kinematics equations to calculate the new horizontal and vertical
    dx = Physics::kinematicsEquation(dx, ddx, t);
    dy = Physics::kinematicsEquation(dy, ddy, t);

    // Calculate the new angle
    aBullet.setRadians(Physics::calculateAngleFromComponents(dx, dy));

    // Recombine  velocities into total velocity using the pythagorean theorem
    totalVelocity = Physics::calculateTotalVelocity(dx, dy);

    if (hasLanded())
    {
        double finalDistanceFromOrigin = Physics::linearInterpolation(oldPtBullet.getMetersX(), ptBullet.getMetersX(), oldPtBullet.getMetersY(), ptBullet.getMetersY(), 0.0 /*When y was 0.0*/);
        double hangTime = Physics::linearInterpolation(age, age + 1, oldPtBullet.getMetersY(), ptBullet.getMetersY(), 0.0 /*When y was 0.0*/);

        cout << "Final distance: " << finalDistanceFromOrigin << endl;
        cout << "Total hang time: " << hangTime << endl;
    }

    // Output your data
    cout << ptBullet << "\n";
    age += t;
}

double Bullet::getAge() const
{
    return this->age;
}

Position Bullet::getPtBullet() const
{
    return this->ptBullet;
}
