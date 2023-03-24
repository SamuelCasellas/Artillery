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
    
    // How long the
    this->age = 0.0;
    
    this->ptBullet.setMetersX(0.0);
    this->ptBullet.setMetersY(0.0);
    
    this->totalVelocity = this->totalAcceleration = initVel;
    
    this->aBullet = a;
    
    // Environmental factors at ground level.
                                                                // if y = 0...
    this->density = Physics::interpolateDensity(0.0);           // 1.225
    this->speedOfSound = Physics::interpolateSpeedOfSound(0.0); // 340.0
    this->gravity = Physics::interpolateGravity(0.0);           // 9.807
}

Bullet::Bullet(double mass, double radius, double initVel, Angle a, Position pos) : mass(mass), surfaceArea(M_PI * radius * radius) {
    
    this->age = 0.0;
    
    this->ptBullet = pos;
    
    this->totalVelocity = this->totalAcceleration = initVel;
    
    this->aBullet = a;
    this->aDrag = Angle(a);
    this->aDrag.reverseRadianAngle();
    
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
    const double t = 1.0;
    
    // initial projectile force
    this->mach = Physics::calculateMach(this->totalVelocity, this->speedOfSound);
    this->dragCoefficient = Physics::interpolateDragCoefficient(this->mach);
    
//    this->projectileForce = Physics::calculateForce(this->mass, this->totalVelocity); // The velocity is the acceleration at the first frame

    double finalDistanceFromOrigin = 0.0;
    double hangTime = 0.0;

    while (this->ptBullet.getMetersY() >= 0) {
        // Collect all data from tables
        // 2. Update to mach required for drag coefficient
        
        double y = this->ptBullet.getMetersY();
        this->density = Physics::interpolateDensity(y);
        this->speedOfSound = Physics::interpolateSpeedOfSound(y);
        this->gravity = Physics::interpolateGravity(y);

        // 3. Apply necessary data to drag coefficient equation
        // TOTAL ACCELERATION
        
        this->dragForce = Physics::calculateDragForce(this->dragCoefficient, this->density, this->totalVelocity, this->surfaceArea);

        // 4. Compute new angle (optional)
        
        // Horizontal and verticle of drag force
        double dragDx = Physics::calculateHorizontalComponent(this->aDrag.getRadians(), -(this->dx));
        double dragDy = Physics::calculateVerticalComponent(this->aDrag.getRadians(), -(this->dy));
        
        /** TODO: Make sure that we use horizontal, vertical, and total formulas
             
          -Make a while loop to loop while your y value is over 0 that:
            - Collect all of the data from your tables using a table reading method and your linear interpolation methods
            - Apply the necessary data to your  drag coefficient equation
                - This drag force is the total acceleration being applied to the projectile
            -  Calculate the angle of the projectile using the angle from components equation
            -  Calculate the inverse of the projectile (the inverse of 90 is 270)
            -  Apply the inverse angle of your drag force to get its vertical and horizontal components (sin and cos equations)
            -  Apply the sin and cos to your projectile's velocity
            -  Apply your horizontal and vertical drag accelerations to your horizontal and vertical velocities
            -  Apply gravity to your vertical velocity
            -  Apply your velocities to your x/y position to update your position
            -  Recombine your velocities into your total velocity using the pythagorean theorem
            -  Output your data
        */
        
        
        // Physics::calculateT
        
        
        // ?? Do we need this ??
//        this->totalAcceleration = Physics::calculateAcceleration(this->dragForce /*FIX*/, this->mass);

        // Velocity horizontal and vertical components
        // double revAngle = this->reverseRadianAngle(this->aRadians);
        double dx0 = Physics::calculateHorizontalComponent(this->aBullet.getRadians(), this->totalVelocity);
        double dy0 = Physics::calculateVerticalComponent(this->aBullet.getRadians(), this->totalVelocity);

        // Acceleration horizontal and vertical components
        this->ddx = -(Physics::calculateHorizontalComponent(this->aBullet.getRadians(), this->totalAcceleration));
        this->ddy = -(this->gravity) - Physics::calculateVerticalComponent(this->aBullet.getRadians(), this->totalAcceleration);

        // New position

        double oldX = this->ptBullet.getMetersX();
        double oldY = this->ptBullet.getMetersY();

        this->ptBullet.setMetersX(Physics::calculateDistance(oldX, dx0, this->ddx, t));
        this->ptBullet.setMetersY(Physics::calculateDistance(oldY, dy0, this->ddy, t));

        // Check if it hit the ground
        // If so, determine where exactly
        if (this->ptBullet.getMetersY() <= 0.0) {
            finalDistanceFromOrigin = Physics::linearInterpolation(oldX, this->ptBullet.getMetersX(), oldY, this->ptBullet.getMetersY(), 0);
            hangTime = Physics::linearInterpolation(t, t+1, oldY, this->ptBullet.getMetersY(), 0);
            break;
        }

        // New horizontal and vertical components
        this->dx = Physics::kinematicsEquation(dx0, this->ddx, t);
        this->dy = Physics::kinematicsEquation(dy0, this->ddy, t);

        // Compute new angle (Wasn't in vid)
        this->aBullet.setRadians(Physics::calculateAngleFromComponents(this->dx, this->dy));
        
        this->aDrag = Angle(this->aBullet);
        this->aDrag.reverseRadianAngle();

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
        
        this->mach = Physics::calculateMach(this->totalVelocity, this->speedOfSound);
        this->dragCoefficient = Physics::interpolateDragCoefficient(this->mach);
   }
}

double Bullet::getAge()const{
    return this->age;
}

