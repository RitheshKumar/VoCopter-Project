//
//  CopterBody.h
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 9/29/15.
//
//

#ifndef ThisIsCoptaa_CopterBody_h
#define ThisIsCoptaa_CopterBody_h

#include "../JuceLibraryCode/JuceHeader.h"

class CopterBody : public Component {
public:
    CopterBody();
    ~CopterBody();
    
    void paint(Graphics &g);
private:
    juce::Image copterImage;
};
#endif
