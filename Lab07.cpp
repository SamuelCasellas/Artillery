/*************************************************************
 * 1. Name:
 *      Samuel Casellas, Andrew Swayze, Isaac Radford
 * 2. Assignment Name:
 *      Lab 13: Artillery Final Submission
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece.
 * 4. What was the hardest part? Be as specific as possible.
 *      We ran into a lot of trouble with the projectilePath array. We had to
 *     figure out how to make the array work and follow the path of
 *    the projectile.
 * 5. How long did it take for you to complete the assignment?
 *      10+ hours
 *****************************************************************/
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*

#include <chrono>
#include <thread>

#include "ground.h" // for GROUND
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
                                  time(0.0)
    {
        // Set the horizontal position of the howitzer. This should be random.
        howitzer.getPt().setPixelsX(Position(ptUpperRight).getPixelsX() / 2.0);

        // Generate the ground and set the vertical position of the howitzer.
        ground.reset(howitzer.ptHowitzer);
    }

    Ground ground;
    Howitzer howitzer;
    Bullet *bullet = nullptr;
    
    bool hasWon = false;
    

    double time; // amount of time since began simulation (or last firing)
    
    double *finalDistanceFromOrigin = nullptr;
    double *hangTime = nullptr;

    Position ptUpperRight; // size of the screen

    void introduceBullet()
    {
        this->bullet = new Bullet(46.7 /*mass of projectile*/, .15489 / 2.0 /*Radius for calculating surface area*/, 827.0 /* initial velocity */, howitzer.getAngle(), Position(howitzer.getPt()), ground);

        // This is to make the bullet travel across the screen. Notice how there are
        // 20 pixels, each with a different age. This gives the appearance
        // of a trail that fades off in the distance.

        double howitzerX = this->howitzer.getPt().getPixelsX();
        double howitzerY = this->howitzer.getPt().getPixelsY();
        for (int i = 0; i < 20; i++)
        {
            bullet->projectilePath[i].setPixelsX(howitzerX);
            bullet->projectilePath[i].setPixelsY(howitzerY);
        }
    }
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
    
    // accept input
    pDemo->howitzer.userInput(pUI);
    
    // fire gun
    if (pUI->isSpace() && pDemo->bullet == nullptr)
    {
        delete pDemo->finalDistanceFromOrigin;
        delete pDemo->hangTime;
        pDemo->finalDistanceFromOrigin = pDemo->hangTime = nullptr;
        
        pDemo->time = 0;
        pDemo->introduceBullet();
    }


    //
    // perform all the game logic
    //

    pDemo->time += 1.0;

    // move the projectile across the screen

    if (pDemo->bullet != nullptr)
    {
        pDemo->bullet->calculateNextFramesPos();
        pDemo->bullet->projectilePath[0] = pDemo->bullet->getPtBullet();

        for (int i = 19; i > 0; i--)
        {
            pDemo->bullet->projectilePath[i] = pDemo->bullet->projectilePath[i - 1];
        }
    }


    //
    // draw everything
    //
    ogstream gout(Position(10.0, pDemo->ptUpperRight.getPixelsY() - 20.0));

    // draw the ground first
    pDemo->ground.draw(gout);

    // draw the howitzer
    gout.drawHowitzer(pDemo->howitzer.getPt(), pDemo->howitzer.getAngle().getRadians(), pDemo->time);

    // draw the projectile(s)
    if (pDemo->bullet != nullptr)
    {
        if(computeDistance(pDemo->bullet->getPtBullet(), pDemo->ground.getTarget()) > 0.0 and computeDistance(pDemo->bullet->getPtBullet(), pDemo->ground.getTarget()) < 550)
        {
            pDemo->hasWon = true;
        }
        
        for (int i = pDemo->bullet->framesSinceLanded; i < 20; i++)
        {
            gout.drawProjectile(pDemo->bullet->projectilePath[i], 0.5 * (double)i);
        }
        
        if (pDemo->bullet->hasLanded())
            pDemo->bullet->framesSinceLanded++;
        
        if (pDemo->bullet->framesSinceLanded >= 20)
        {
            // Save finalDistance and hangTime
            pDemo->finalDistanceFromOrigin = new double(pDemo->bullet->finalDistanceFromOrigin);
            pDemo->hangTime = new double(pDemo->bullet->hangTime);
            
            // Delete heap memory for bullet
            delete pDemo->bullet;
            pDemo->bullet = nullptr;
        }
    }

    if (pDemo->hasWon)
    {
        gout << "You win!";
    }

    // draw some text on the screen
    gout.setf(ios::fixed | ios::showpoint);
    gout.precision(1);
        
    gout << "    Angle: "
         << pDemo->howitzer.getAngle()
         << "\n\n";
    
    gout << "                 Elapsed time: "
         << pDemo->time << "s"
         << "\n\n";
    
    if (pDemo->hangTime != nullptr) {
        gout << "                 Final hang time: "
             << *(pDemo->hangTime) << "s"
             << "\n\n";
        gout << "                 Final distance from origin: "
             << *(pDemo->finalDistanceFromOrigin) << "m"
             << "\n\n";
    }
    
}

double Position::metersFromPixels = 40.0;

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
    // Initialize OpenGL
    Position ptUpperRight;
    ptUpperRight.setPixelsX(700.0);
    ptUpperRight.setPixelsY(500.0);
    Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
    Interface ui(0, NULL,
                 "Demo", /* name on the window */
                 ptUpperRight);

    // Initialize the demo
    Demo demo(ptUpperRight);

    // set everything into action
    ui.run(callBack, &demo);

    return 0;
};
