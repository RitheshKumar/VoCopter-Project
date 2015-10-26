/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CopterComponent.h"
#include "ObstacleComponent.h"
#include "juce_Timer.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
                               //private Viewport,
                               private Timer
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();
    
    void paint (Graphics&);
    void resized();

    bool keyPressed(const KeyPress& key) override;
    void timerCallback() override;
   
private:
    CopterComponent Copter;
    ObstacleComponent Obstacle;
    ComponentAnimator Animation;
    Viewport viewport;
    
    int winWidth = 600, winHeight = 400;
    float xpos, ypos;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
