//
//  TestBullet.cpp
//  Lab07
//
//  Created by Samuel on 3/8/23.
//

#include "bullet.h"
#include "TestBullet.h"
#include "physics.h"
#include <cassert>

//testHaslanded
//testCalculateNewPosition
//testGetH

void TestBullet::testConstructor()
{
    Bullet b;

    // Verify
    assert(b.mass == 46.7);
    assert(b.surfaceArea > 0.0188 && b.surfaceArea < 0.0189);
} // Teardown

void TestBullet::run() {
    // testHasLanded();
    testCalculateNewPosition();
    testGetAge();
}

void TestBullet::testHasLanded() {

    Angle a;
    a.setDegrees(45.00);
    // Test case for hasLanded when bullet hasn't landed yet
    
    Bullet b1(0.1, 0.05, 100.0, a);
    for (int i = 0; i < 10; i++) {
        b1.calculateNewPosition();
    }
    
    assert(b1.hasLanded() == false);
    // Test case for hasLanded when bullet has landed
    
    Bullet b2(0.1, 0.05, 100.0, a);
    for (int i = 0; i < 100; i++) {
        b2.calculateNewPosition();
    }
    assert(b2.hasLanded() == true);
}

void TestBullet::testCalculateNewPosition() {
    Angle a;
    a.setDegrees(30.0);
        
    // Test case for calculateNewPosition with initial velocity
    
    Bullet b3(46.7, 0.077445, 827.0, a, Position(0.0, 0.0));
    
    b3.calculateNewPosition();
    
    
    // Test case for calculateNewPosition with no initial velocity
    Bullet b4(0.1, 0.05, 0.0, a, Position(0.0, 0.0));
    b4.calculateNewPosition();
    assert(b4.ptBullet.getPixelsX() == 0.0 && b4.ptBullet.getPixelsY() == 0.0);
}

void TestBullet::testGetAge() {
    Angle a;
    a.setDegrees(45.00);
        
    // Test case for getAge with no elapsed time
    Bullet b5(0.1, 0.05, 100.0, a, Position(0.0, 0.0));
    assert(b5.getAge() == 0.0);
    
    // Test case for getAge with elapsed time
    Bullet b6(0.1, 0.05, 100.0, a, Position(0.0, 0.0));
    for (int i = 0; i < 10; i++) {
        b6.calculateNewPosition();
    }
    assert(b6.getAge() == 0.1);
}





