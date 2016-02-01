/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent() : Obstacle(/*600*/), xpos(winWidth*0.15), ypos(winHeight*0.5-25), obsX(winWidth*0.15)
{

    //Obstacle(xpos);

    setSize (winWidth, winHeight);
    setWantsKeyboardFocus(true);
    
    //Notice that the order is important
    addAndMakeVisible(myObstacle);
    addAndMakeVisible(Obstacle);  //ObstacleComponent class
    addAndMakeVisible(Copter);    //CopterComponent Class
    //viewport.setViewedComponent(Copter,true);
    hitLabel.setText("Copter Hit!", dontSendNotification);
    hitLabel.setColour(Label::textColourId, Colours::red);
    
    startTimer(50);
    
    //xpos = getWidth()*0.15; ypos = getHeight()*0.6;
    //Rectangle<int> r (0,0,100,100);
    //Animation.animateComponent(&Obstacle, r, 1.0f, 3000, false, 0.0, 0.0);
    processingAudio = new AudioProcess;
    deviceManager.initialise( 1, 2, 0, true, String::empty, 0 );
    deviceManager.addAudioCallback(processingAudio);
}

MainContentComponent::~MainContentComponent()
{
    deviceManager.removeAudioCallback(processingAudio);
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
//    Obstacle.setBounds(0, 0, getWidth()*Obstacle.getObstacleLength()/2, getHeight());   //divided by 2 to represent 2 notes at a time in a window.
    myObstacle.setBounds(obsX, 0, getWidth(), getHeight());
    hitLabel.setBounds(round(getWidth()/2)-40,round(getHeight()/2),80,50);
}

bool MainContentComponent::keyPressed(const KeyPress& key)
{
    //std::cout<<ypos<<",";
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

bool MainContentComponent::keyStateChanged(bool isKeyDown) {
    
    if ( !isKeyDown ) {
        keyRelease = true;  //initiate timer callback
    }
    else {
        keyRelease = false;
    }
    return false;
}

void MainContentComponent::timerCallback() {
    /*float freq  = processingAudio->getFreq() - 200;
    if (freq < 322 && freq > 5) {
        Copter.setBounds(xpos, ypos = 300 - freq, 80, 60);
        std::cout<<freq<<",";
    }*/
    myObstacle.setBounds(obsX-=1, 0, getWidth()*20, getHeight());
    int currentHeight = myObstacle.getObstacleHeight();
//    std::cout<<currentHeight<<std::endl;
    if( (currentHeight >= ypos) || (currentHeight+75 <= ypos) ){
        addAndMakeVisible(hitLabel);
    }
    else {
        removeChildComponent(&hitLabel);
    }
    
    if ( keyRelease == true ) {
        ypos += 5;
        Copter.setBounds((int)xpos,(int)ypos,80,60);
    }
    
}

