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

void TestBullet::run()
{
    testConstructor();
    testHasLanded();
    testCalculateNextFramesPos();
    testGetAge();
}

void TestBullet::testConstructor()
{
    Angle a;
    a.setDegrees(180.0);
    Bullet b(0.1, 1, 100.0, a, Position(0.0, 0.0));

    // Verify
    assert(b.mass == 0.1);
    assert(b.surfaceArea > 3.14 && b.surfaceArea < 3.1416);
    assert(b.totalVelocity == 100.0);
    assert(b.ptBullet.getMetersY() == 0.0 && b.ptBullet.getMetersX() == 0.0);
} // Teardown

void TestBullet::testHasLanded()
{

    Angle a;
    a.setDegrees(45.00);
    // Test case for hasLanded when bullet hasn't landed yet

    Bullet b1(46.7, .15489 / 2, 827.0, a, Position(0.0, 0.0));
    for (int i = 0; i < 10; i++)
    {
        b1.calculateNextFramesPos();
    }

    assert(!b1.hasLanded());
    // Test case for hasLanded when bullet has landed

    Bullet b2(46.7, .15489 / 2, 827.0, a, Position(0.0, 0.0));
    for (int i = 0; i < 100; i++)
    {
        b2.calculateNextFramesPos();
    }
    assert(b2.hasLanded());
}

void TestBullet::testCalculateNextFramesPos()
{
    Angle a;
    a.setDegrees(10.0);

    // Test case for calculateNextFramesPos with initial velocity

    Bullet b3(46.7, .15489 / 2, 827.0, a, Position(0.0, 0.0));

    do
    {
        b3.calculateNextFramesPos();
    } while (!b3.hasLanded());

    assert(b3.ptBullet.getMetersX() > 8700 && b3.ptBullet.getMetersX() < 8800);
}

void TestBullet::testGetAge()
{
    Angle a;
    a.setDegrees(45.00);

    // Test case for getAge with no elapsed time
    Bullet b5(0.1, 0.05, 100.0, a, Position(0.0, 0.0));
    assert(b5.getAge() == 0.0);

    // Test case for getAge with elapsed time
    for (int i = 0; i < 10; i++)
    {
        b5.calculateNextFramesPos();
    }
    assert(b5.getAge() == 10.0);
}
