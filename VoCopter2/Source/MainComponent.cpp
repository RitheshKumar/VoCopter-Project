/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent() : xpos(249), ypos(150), prevYPos(150)
{
    setSize (600, 400);
    addAndMakeVisible(Copter);
    setWantsKeyboardFocus(true);
    alpha.attack  = 0.5;
    alpha.release = 0.01;
    alpha.timerInterval_ms = 5;
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll(Colours::skyblue);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    Copter.setBounds(xpos,ypos,/*getWidth()*0.3,getHeight()*0.3*/80,60);
}

bool MainContentComponent::keyPressed(const KeyPress& key)
{
    //std::cout<<ypos<<",";
    switch (key.getTextCharacter()) {
        case 'w':
            stopTimer();
            Copter.setBounds(xpos,ypos-=20,/*getWidth()*0.3,getHeight()*0.3*/80,60);
            ypos  = ypos<0 ? alpha.release : ypos; //ensure that ypos is not negative
            return true;
            break;
            
        case 's':
            Copter.setBounds(xpos,ypos+=5,/*getWidth()*0.3,getHeight()*0.3*/80,60);
            return true;
            break;
            
    }
    return false;
}


bool MainContentComponent::keyStateChanged(bool isKeyDown) {
    
    if ( !isKeyDown ) {
        startTimer(alpha.timerInterval_ms);  //initiate timer callback
    }
    return false;
}

void MainContentComponent::timerCallback() {
    
    if ( ypos < getHeight()-60 ) {
        ypos += 5;
        Copter.setBounds((int)xpos,(int)ypos,80,60);
        //prevYPos = ypos;
        //ypos     = (1+alpha.release)*prevYPos ;
    }
    else {
        stopTimer();
    }
}
