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

Bullet::Bullet(double mass, double radius, double initVel, Angle a) : mass(mass), surfaceArea(M_PI * radius * radius) {
    
    this->age = 0.0;
    
    this->ptBullet.setMetersX(0.0);
    this->ptBullet.setMetersY(0.0);
    
    this->totalVelocity = this->totalAcceleration = initVel;
    
    this->aBullet = a;
    
    // Environmental factors at ground level.
    this->density = Physics::interpolateDensity(0.0); // 1.225 if y = 0
    this->speedOfSound = Physics::interpolateSpeedOfSound(0.0); // 340.0
    this->gravity = Physics::interpolateGravity(0.0); // 9.807 = 0
}

Bullet::Bullet(double mass, double radius, double initVel, Angle a, Position pos) : mass(mass), surfaceArea(M_PI * radius * radius) {
    
    this->age = 0.0;
    
    this->ptBullet = pos;
    
    this->totalVelocity = this->totalAcceleration = initVel;
    
    this->aBullet = a;
    
    // Environmental factors at ground level.
    double y = pos.getMetersY();
    this->density = Physics::interpolateDensity(y); // 1.225 if y = 0
    this->speedOfSound = Physics::interpolateSpeedOfSound(y); // 340.0
    this->gravity = Physics::interpolateGravity(y); // 9.807 = 0
}

Bullet::Bullet(Bullet&& other)
    : surfaceArea(other.surfaceArea), mass(other.mass), ptBullet(std::move(other.ptBullet)),
      aBullet(std::move(other.aBullet)), age(other.age), mach(other.mach),
      dragCoefficient(other.dragCoefficient), density(other.density), speedOfSound(other.speedOfSound),
      gravity(other.gravity), dragForce(other.dragForce), projectileForce(other.projectileForce),
      dx(other.dx), dy(other.dy), ddx(other.ddx), ddy(other.ddy),
      totalVelocity(other.totalVelocity), totalAcceleration(other.totalAcceleration)
{
    // Move the projectilePath array
    for (int i = 0; i < 20; i++) {
        projectilePath[i] = std::move(other.projectilePath[i]);
    }
    
    // Destroy other object after move
}


bool Bullet::hasLanded() {
    return (this->ptBullet.getMetersY() <= 0);
}

void Bullet::calculateNewPosition() {
    
    // t was half a second according to simulation
    const double t = 0.5;

    // initial force
    this->projectileForce = Physics::calculateForce(this->mass, this->totalVelocity); // The velocity is the acceleration at the first frame

    double finalDistanceFromOrigin = 0.0;
    double hangTime = 0.0;

    while (this->ptBullet.getMetersY() >= 0) {
        // Collect all data from tables
        // 2. Update to mach required for drag coefficient
        this->mach = Physics::calculateMach(this->totalVelocity, this->speedOfSound);
        this->dragCoefficient = Physics::interpolateDragCoefficient(this->mach);
        
        double y = this->ptBullet.getMetersY();
        this->density = Physics::interpolateDensity(y);
        this->speedOfSound = Physics::interpolateSpeedOfSound(y);
        this->gravity = Physics::interpolateGravity(y);

        // 3. Apply necessary data to drag coefficient equation
        // TOTAL ACCELERATION
        this->dragForce = Physics::calculateDragForce(this->dragCoefficient, this->density, this->totalVelocity, this->surfaceArea);

        // 4. Compute new angle (optional)

        this->totalAcceleration = Physics::calculateAcceleration(this->dragForce, this->mass);

        // Velocity horizontal and vertical components
        // double revAngle = this->reverseRadianAngle(this->aRadians);
        double dx0 = Physics::calculateHorizontalComponent(this->aBullet.getRadians(), this->totalVelocity);
        double dy0 = Physics::calculateVerticalComponent(this->aBullet.getRadians(), this->totalVelocity);

        // Acceleration horizontal and vertical components
        this->ddx = -Physics::calculateHorizontalComponent(this->aBullet.getRadians(), this->totalAcceleration);
        this->ddy = -this->gravity - Physics::calculateVerticalComponent(this->aBullet.getRadians(), this->totalAcceleration);

        // New position

        double oldX = this->ptBullet.getMetersX();
        double oldY = this->ptBullet.getMetersY();

        this->ptBullet.setMetersX(Physics::calculateDistance(this->ptBullet.getMetersX(), dx0, this->ddx, t));
        this->ptBullet.setMetersY(Physics::calculateDistance(this->ptBullet.getMetersY(), dy0, this->ddy, t));

        if (this->ptBullet.getMetersY() < 0) {
            finalDistanceFromOrigin = Physics::linearInterpolation(oldX, this->ptBullet.getMetersX(), oldY, this->ptBullet.getMetersY(), 0);
            hangTime = Physics::linearInterpolation(t, t+1, oldY, this->ptBullet.getMetersY(), 0);
        }

        // New horizontal and vertical components
        this->dx = Physics::kinematicsEquation(dx0, this->ddx, t);
        this->dy = Physics::kinematicsEquation(dy0, this->ddy, t);

        // Compute new angle (Wasn't in vid)
        this->aBullet.setRadians(Physics::calculateAngleFromComponents(this->dx, this->dy));

        // New velocity

        this->totalVelocity = Physics::calculateTotalVelocity(this->dx, this->dy); // don't use initial?

        // Include this??? (Wasn't in vid)
        this->projectileForce = Physics::calculateForce(this->mass, this->totalAcceleration);
        // cout << projectileForce << ' ' << dForce << '\n';

        // s = s1 + (a * t) // where s is speed, s1 is initial speed, a is acceleration and t is time.
        // Compute the new velocity
//        dx = this->pythagorean(dx, ddx); // This is the wrong equation
//        dy = this->pythagorean(dy, ddy);
//
        // cout << position.getMetersY() << endl;

        this->age += t;
   }
}

double Bullet::getAge()const{
    return this->age;
}

