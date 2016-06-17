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
#include "ObstacleComponent.h"
#include "voCopterLogo.h"


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
    void mouseDown(const MouseEvent & event) override;
   
private:
    TextButton startButton, stopButton, restartButton;
    
    ObstacleComponent *myObstacle;
    CopterComponent *Copter;
    voCopterLogo gameLogo;
    OwnedArray<CopterComponent> livesLeft;
    
    AudioProcess *processingAudio;
    AudioDeviceManager deviceManager;
    
    int winWidth = 900, winHeight = 600, cnt = 0, currentHeight,
        copterHits, curObsPos, lifeIdx;
    float xpos, ypos;
    float obsX, gameStartTime, newlifeTime;
    bool keyRelease, isjBMode;
    
    String hitsDisplay;
    
    Label hitLabel,gameOverLabel, numHitsLabel,
          noteLabel,jBModeLabel, scoreLabel;
    
    WildcardFileFilter fileFilter;
    FileBrowserComponent *chooseMidi;
    

    
    //Private Functions
    void buttonClicked (Button *button) override;
    void gameStart();
    void gameOver();
    void newLife();
    void reset();
    void jawKneeBoyMode();
    
    void collisionDetection();
    void gamePlayEvents();
    void copterPlacement();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
