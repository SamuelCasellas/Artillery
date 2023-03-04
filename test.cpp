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


#include "TestPhysics.cpp"

/*****************************************************************
 * TEST RUNNER
 * Runs all the unit tests
 ****************************************************************/

class test {
    public : void testRunner()
    {
       TestPosition().run();
       TestGround().run();
       
       TestPhysics tP;
       tP.test_runner();
    }
};
