//
//  howitzer.cpp
//  Lab07
//
//  Created by Samuel on 3/8/23.
//

#include "howitzer.h"

Howitzer::Howitzer() : ptHowitzer() {}

void Howitzer::userInput(const Interface *pUI)
{
    double currentR = this->aHowitzer.getRadians();
    // move a large amount
    if (pUI->isRight())
        this->aHowitzer.setRadians(currentR + 0.05);
    if (pUI->isLeft())
        this->aHowitzer.setRadians(currentR - 0.05);

    // move by a little
    if (pUI->isUp())
        this->aHowitzer.setRadians(currentR + (currentR >= 0 ? -0.003 : 0.003));
    if (pUI->isDown())
        this->aHowitzer.setRadians(currentR + (currentR >= 0 ? 0.003 : -0.003));
}

void Howitzer::updateAngle(Angle &a)
{
    this->aHowitzer = a;
}

Angle &Howitzer::getAngle()
{
    return this->aHowitzer;
}

Position &Howitzer::getPt()
{
    return this->ptHowitzer;
}
