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
#include "AudioProcess.h"
#include "NuObstacleComponent.h"


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
    
    //these are things that i added
    //an audio app component has all these and extra audio related fns
    bool keyPressed(const KeyPress& key) override;
    void timerCallback() override;
   
private:
    NuObstacleComponent myObstacle;
    CopterComponent Copter;
    ObstacleComponent Obstacle;
    ComponentAnimator Animation;
    Viewport viewport;
    
    AudioProcess *processingAudio;
    AudioDeviceManager deviceManager;
    
    int winWidth = 600, winHeight = 400, cnt = 0;
    float xpos, ypos,obsX;
    
    Label hitLabel;
    //HeightValue Pointer
//    float **curHeightValue = Obstacle.getHeightCoord();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
