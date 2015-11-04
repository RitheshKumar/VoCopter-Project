/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent() : Obstacle(/*600*/), xpos(winWidth*0.15), ypos(winHeight*0.2)
{

    //Obstacle(xpos);

    setSize (winWidth, winHeight);
    setWantsKeyboardFocus(true);
    addAndMakeVisible(Obstacle);
    addAndMakeVisible(Copter);
    //viewport.setViewedComponent(Copter,true);
    
    startTimer(50);
    
    //xpos = getWidth()*0.15; ypos = getHeight()*0.6;
    //Rectangle<int> r (0,0,100,100);
    //Animation.animateComponent(&Obstacle, r, 1.0f, 3000, false, 0.0, 0.0);
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
    // It is even called when you say setSize
    //xpos *= getWidth()*0.15; ypos *= getWidth()*0.15;
    Copter.setBounds(xpos,ypos,/*getWidth()*0.3,getHeight()*0.3*/80,60);
    Obstacle.setBounds(0, 0, getWidth()*Obstacle.getObstacleLength()/2, getHeight());
}

bool MainContentComponent::keyPressed(const KeyPress& key)
{
    switch (key.getTextCharacter()) {
        case 'w':
            Copter.setBounds(xpos,ypos-=5,/*getWidth()*0.3,getHeight()*0.3*/80,60);
            return true;
            break;
            
        case 's':
            Copter.setBounds(xpos,ypos+=5,/*getWidth()*0.3,getHeight()*0.3*/80,60);
            return true;
            break;
            
    }
    return false;
}

void MainContentComponent::timerCallback() {
    
}
