//
//  howitzer.h
//  Lab07
//
//  Created by Samuel on 3/8/23.
//

#ifndef howitzer_h
#define howitzer_h

#include <stdio.h>
#include "position.h"
#include "angle.h"
#include "uiInteract.h"

#include "TestHowitzer.h"

class Howitzer
{
public:
    Howitzer();
    void userInput(const Interface * pUI);
    void draw();
    void updateAngle(Angle & a);
    
    Position getPt()const;

    // Needs to be public to pass directly to reset method in ground
    Position ptHowitzer;
    
private:
    Angle aHowitzer;
};

#endif /* howitzer_h */
