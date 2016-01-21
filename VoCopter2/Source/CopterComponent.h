//
//  CopterComponent.h
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 9/29/15.
//
//

#ifndef ThisIsCoptaa_CopterComponent_h
#define ThisIsCoptaa_CopterComponent_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "CopterFan.h"
#include "CopterBody.h"

class CopterComponent : public Component
{
public:
    CopterComponent();
    ~CopterComponent();
    
    void resized();
    
private:
    CopterFan Fan;
    CopterBody Body;
};
#endif
