/**********************************************************************
 * Apollo 11
 * Benjamin Pratt and Tyler Elms
 **********************************************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "lander.h"
#include <iomanip>


using namespace std;

/*************************************************************************
 * Program
 * Holds all the values for everything that exists in the program
 *************************************************************************/
class Program
{
public:
    Program(const Point& ptUpperRight) :
        ground(ptUpperRight),
        lm(random(0.0, ptUpperRight.getX()), 350.0) //give the LM a random x value when the game starts
    { 
        //set the values of the stars and their phases
        for (int i = 0; i < 50; i++)
        {
            stars[i] = Point(random(0.0, ptUpperRight.getX()), random(0.0, ptUpperRight.getY()));
            phases[i] = random(0, 255);
        }
    }

   // getters
    Lander getLM() {
        return this->lm;
    }
    Point getPTUpperRight() {
        return this->ptUpperRight;
    }
    unsigned char * getPhases() {
        return this->phases;
    }
    Ground getGround()
    {
        return this->ground;
    }
    Point* getStars()
    {
        return this->stars;
    }

    //Setter, operator, and moveLander methods
    Program& operator-= (double amount) { lm -= amount; return *this; };
    void setAngle(double amount) {
        lm.setAngle(amount);
    }
    void moveLander(bool isThrusting)
    {
        lm.moveLander(isThrusting);
    }

private:
    Lander lm;         // lander object
    Point ptUpperRight;   // size of the screen
    unsigned char phases[50];  //each star's phase of blinking
    Ground ground; //ground
    Point stars[50]; //each star's point
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void * p)
{
   //Lets us draw stuff to the screen
   ogstream gout;

   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Program * pProgram = (Program *)p;  

   //Check if the lander has hit the ground or landed on the platform
   bool gameEnded = false;
   bool won = false;
   if (pProgram->getGround().hitGround(pProgram->getLM().getPoint(), 20) ||
       (pProgram->getGround().onPlatform(pProgram->getLM().getPoint(), 20)))
   {
       //Check if the landing was successful
       if (pProgram->getGround().onPlatform(pProgram->getLM().getPoint(), 20) && pProgram->getLM().getVelocity() < 4)
       {
           won = true;
       }
       gameEnded = true;
   }
   //Logic for the lander's movement
   bool isThrusting = false;
   bool isRight = false;
   bool isLeft = false;
   //Only allow the lander to move if it has fuel
   if (pProgram->getLM().getFuel() > 0)
   {
       // move the ship around and lower the fuel
       if (pUI->isRight()) //Rotate the ship clockwise if the right key is pressed
       {
           isRight = true;
           if (!gameEnded)
           {
               pProgram->setAngle(0.1);
           }
           //decrease the fuel by 1 each frame
           *pProgram -= 1.0;
       }
       if (pUI->isLeft()) //Rotate the ship counter-clockwise if the right key is pressed
       {
           isLeft = true;
           if (!gameEnded)
           {
               pProgram->setAngle(-0.1);
           }
           //decrease the fuel by 1 each frame
           *pProgram -= 1.0;
       }
       if (pUI->isDown()) //Set isThrusting to true so that the moveLander method knows that 
                          //the lander is thrusting
       {
           isThrusting = true;

           //decrease the fuel by 10 each frame
           *pProgram -= 10.0;
       }
   }
   else {
       //Brings the fuel back to 0 if it goes negative
       *pProgram -= pProgram->getLM().getFuel();
   }

   //Only allow the lander to move if the game is still going
   if (!gameEnded)
   {
       pProgram->moveLander(isThrusting);
   }

   // draw stars
   for (int i = 0; i < 50; i++)
   {
       gout.drawStar(pProgram->getStars()[i], pProgram->getPhases()[i]++);
   }

   // draw the ground
   pProgram->getGround().draw(gout);

   // draw the lander and its flames
   gout.drawLander(pProgram->getLM().getPoint() /*position*/, -pProgram->getLM().getAngleRad() /*angle*/);

   gout.drawLanderFlames(pProgram->getLM().getPoint(), -pProgram->getLM().getAngleRad(), /*angle*/
                   isThrusting, isLeft,isRight);
   
   
   //Information
   gout.setPosition(Point(20.0, 370.0));
   gout << "Fuel: " << (int)pProgram->getLM().getFuel() << "\n";
   gout << "Altitude: " << (int)pProgram->getLM().getPoint().getY() << " meters\n";
   gout << fixed << setprecision(2) << "Speed: " << pProgram->getLM().getVelocity() << " m/s\n";

   //If the game ends, display a message to the screen
   if (!won && gameEnded)
   {
       gout.setPosition(Point(pProgram->getLM().getPoint().getX() - 35.0, pProgram->getLM().getPoint().getY() + 25.0));
       gout << "You Crashed!";
   }
   else if (won && gameEnded)
   {
       gout.setPosition(Point(pProgram->getLM().getPoint().getX() - 25.0, pProgram->getLM().getPoint().getY() + 25.0));
       gout << "You Win!";
   }
   
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * the window size and the program object and
 * call the run method.
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance, 
   _In_opt_ HINSTANCE hPrevInstance, 
   _In_ PWSTR pCmdLine, 
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char ** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Point ptUpperRight(400.0, 400.0);
   Interface ui(0, NULL, 
                "Open GL Demo", 
                 ptUpperRight);

   // Initialize the game class
   Program program(ptUpperRight);

   // set everything into actions
   ui.run(callBack, &program);             

   return 0;
}
