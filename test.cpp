/***********************************************************************
 * Source File:
 *    Test : Test runner
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The test runner for all the unit tests
 ************************************************************************/

#include "test.h"

#include "testPosition.h"
#include "testGround.h"

#include "TestPhysics.h"
#include "TestBullet.h"
#include "TestHowitzer.h"

/*****************************************************************
 * TEST RUNNER
 * Runs all the unit tests
 ****************************************************************/
void Test::testRunner()
{
   TestPosition().run();
   TestGround().run();
    
   // Our unit tests //
   TestPhysics().run();
   TestBullet().run();
   TestHowitzer().run();
}
