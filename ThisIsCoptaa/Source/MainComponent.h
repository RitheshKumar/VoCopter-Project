/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CopterComponent.h"
#include "AudioProcess.h"
#include "NuObstacleComponent.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
                               public ButtonListener,
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
    bool keyStateChanged(bool isKeyDown) override;
    void timerCallback() override;
   
private:
    TextButton startButton, stopButton;
    
    NuObstacleComponent *myObstacle;
    CopterComponent Copter;
    
    AudioProcess *processingAudio;
    AudioDeviceManager deviceManager;
    
    int winWidth = 600, winHeight = 400, cnt = 0, currentHeight;
    float xpos, ypos,obsX;
    bool keyRelease;
    
    Label hitLabel,gameOverLabel;
    
    //Private Functions
    void buttonClicked (Button *button) override;
    void gameOver();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
