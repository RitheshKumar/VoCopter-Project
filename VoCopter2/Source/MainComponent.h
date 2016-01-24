/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CopterComponent.h"
#include "MidiTranslation.h"
#include "ObstacleComponent.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
                               private Timer
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&);
    void resized();
    
    //my Functions
    bool keyPressed(const KeyPress& key) override;
    bool keyStateChanged(bool isKeyDown) override;
    void timerCallback() override;
    
    //public DataMembers
    struct ppmPara {  //co-efficient for ppm implementation
        float  release,
               attack;
        int    timerInterval_ms;
    };

    
private:
    CopterComponent Copter;
    float xpos, ypos; float prevYPos;
    const KeyPress key;
    ppmPara alpha;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
