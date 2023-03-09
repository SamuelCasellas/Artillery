/*************************************************************
 * 1. Name:
 *      Samuel Casellas, Andrew Swayze, Isaac Radford
 * 2. Assignment Name:
 *      Lab 07: M777 Howitzer Prototype
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *           Trying to get the bullet to hit the ground. Didn't fully complete the assignment.
 * 5. How long did it take for you to complete the assignment?
 *      4 hours and counting...
 *****************************************************************/

#include <cassert>      // for ASSERT

#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*

#include "ground.h"   // for GROUND
#include "bullet.h"
#include "howitzer.h"
#include "position.h" // for POSITION
#include <cmath>
#include "physics.h"

// For testing
#include "test.h"

using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
   Demo(Position ptUpperRight) : ptUpperRight(ptUpperRight),
                                 ground(ptUpperRight),
                                 time(0.0),
                                 angle(0.0),
                                 bullet(46.7 /*mass of projectile*/, .15489 / 2.0 /*Radius for calculating surface area*/, 827.0 /* initial velocity */)
   {
      // Set the horizontal position of the howitzer. This should be random.
      howitzer.getPt().setPixelsX(Position(ptUpperRight).getPixelsX() / 2.0);

      // Generate the ground and set the vertical position of the howitzer.
      ground.reset(howitzer.ptHowitzer);

      // This is to make the bullet travel across the screen. Notice how there are
      // 20 pixels, each with a different age. This gives the appearance
      // of a trail that fades off in the distance.
      for (int i = 0; i < 20; i++)
      {
         bullet.projectilePath[i].setPixelsX((double)i * 2.0);
         bullet.projectilePath[i].setPixelsY(ptUpperRight.getPixelsY() / 1.5);
      }
   }

   Ground ground;
   Howitzer howitzer;
   Bullet bullet;
    
   // Position projectilePath[20]; // path of the projectile

   Position ptUpperRight;       // size of the screen
   double angle;                // angle of the howitzer
   double time;                 // amount of time since the last firing
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL.
   Demo *pDemo = (Demo *)p;

   //
   // accept input
   //

   pDemo->howitzer.userInput(pUI);
    
   // fire that gun
   if (pUI->isSpace())
      pDemo->time = 0.0;

   //
   // perform all the game logic
   //

   // advance time by half a second.
   pDemo->time += 0.5;

   // move the projectile across the screen
   for (int i = 0; i < 20; i++)
   {
      // this bullet is moving left at 1 pixel per frame
      double x = pDemo->bullet.projectilePath[i].getPixelsX();
      x -= 1.0;
      if (x < 0)
         x = pDemo->ptUpperRight.getPixelsX();
      pDemo->bullet.projectilePath[i].setPixelsX(x);
   }

   //
   // draw everything
   //

   ogstream gout(Position(10.0, pDemo->ptUpperRight.getPixelsY() - 20.0));

   // draw the ground first
   pDemo->ground.draw(gout);

   // draw the howitzer
   gout.drawHowitzer(pDemo->howitzer.getPt(), pDemo->angle, pDemo->time);

   // draw the projectile
   for (int i = 0; i < 20; i++)
      gout.drawProjectile(pDemo->bullet.projectilePath[i], 0.5 * (double)i);

   // draw some text on the screen
   gout.setf(ios::fixed | ios::showpoint);
   gout.precision(1);
   gout << "Time since the bullet was fired: "
        << pDemo->time << "s\n";
}

double Position::metersFromPixels = 40.0;

double prompt(string message)
{
   double response;
   cout << message;
   cin >> response;
   return response;
}

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ PWSTR pCmdLine,
    _In_ int nCmdShow)
#else  // !_WIN32
int main(int argc, char **argv)
#endif // !_WIN32
{

    testRunner();
    
    std::cout << "All tests passed" << std::endl;
    return 0;
    
//
//
//    cout << "Distance:\t"
//         << finalDistanceFromOrigin
//         << "\n"
//         << "Hang Time:\t"
//         << hangTime;
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////   // Initialize OpenGL
////   Position ptUpperRight;
////   ptUpperRight.setPixelsX(700.0);
////   ptUpperRight.setPixelsY(500.0);
////   Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
////   Interface ui(0, NULL,
////      "Demo",   /* name on the window */
////      ptUpperRight);
////
////   // Initialize the demo
////   Demo demo(ptUpperRight);
////
////   // set everything into action
////   ui.run(callBack, &demo);
//
//
//   return 0;
}
