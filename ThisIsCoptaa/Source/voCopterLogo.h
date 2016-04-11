//
//  voCopterLogo.h
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 4/10/16.
//
//

#ifndef __ThisIsCoptaa__voCopterLogo__
#define __ThisIsCoptaa__voCopterLogo__


#include "../JuceLibraryCode/JuceHeader.h"

class voCopterLogo : public Component {
public:
    voCopterLogo();
    ~voCopterLogo();
    
    void paint(Graphics &g);
private:
    juce::Image logoImage;
};
#endif
