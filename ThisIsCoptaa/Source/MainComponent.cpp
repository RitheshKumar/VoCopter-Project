/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent() : currentHeight(0),
                                               xpos(winWidth*0.15),
                                               ypos(winHeight*0.5-25),
                                               keyRelease(0)
{


    obsX = winWidth*0.95;

    //Notice that the order is important
    addAndMakeVisible(startButton);
    startButton.setButtonText("Start!");
    startButton.addListener(this);
    stopButton.setButtonText("Stop");
    stopButton.addListener(this);
    
    startButton.setColour(TextButton::buttonColourId, Colours::green);
    startButton.setColour(TextButton::textColourOnId, Colours::black);
    stopButton.setColour(TextButton::buttonColourId, Colours::red);
    stopButton.setColour(TextButton::textColourOnId, Colours::black);
    
    
    myObstacle = new ObstacleComponent((char *)"~/Documents/Fall_2015/VoCopter Project/ThisIsCoptaa/MidiFiles/OnlyTime.mid") ;
//    addAndMakeVisible(myObstacle); //NuObstacleComponent class
//    addAndMakeVisible(Copter);    //CopterComponent Class
    
    
    processingAudio = new AudioProcess();
    deviceManager.initialise( 1, 2, 0, true, String::empty, 0 );
    deviceManager.addAudioCallback(processingAudio);
    
    hitLabel.setText("Copter Hit!", dontSendNotification);
    hitLabel.setColour(Label::textColourId, Colours::red);
    gameOverLabel.setFont(Font(40));
    gameOverLabel.setText("Game Over", dontSendNotification);
    gameOverLabel.setColour(Label::textColourId, Colours::red);

    setSize (winWidth, winHeight);
    setWantsKeyboardFocus(true);
}

MainContentComponent::~MainContentComponent()
{
//    deviceManager.removeAudioCallback(processingAudio);
    delete myObstacle;
    myObstacle = 0;
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
    
    startButton.setBounds(getWidth()/2-50, getHeight()/2-20, 100, 40);
    
    Copter.setBounds(xpos,ypos,/*getWidth()*0.3,getHeight()*0.3*/80,60);
    myObstacle->setBounds(obsX, 0, getWidth(), getHeight());
    stopButton.setBounds(getWidth()-45, 20, 40, 20);
    hitLabel.setBounds(round(getWidth()/2)-40,round(getHeight()/2),80,50);
    
    gameOverLabel.setBounds(getWidth()/2-100,getHeight()/2-30, 200, 60 );
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
    float freq  = processingAudio->getFreq() - 200;
    if (freq < 322 && freq > 5) {
        Copter.setBounds(xpos, ypos = 300 - freq, 80,60);
//        std::cout<<freq<<",";
    }
//    std::cout<<processingAudio->getFreq()<<std::endl;
    myObstacle->setBounds(obsX-=10, 0, myObstacle->getObstacleLength(), getHeight());
//    myObstacle->setBounds(obsX-=10, 0, getWidth()*20, getHeight());
//    std::cout<<obsX<<std::endl;
//    currentHeight = myObstacle->getObstacleHeight() + 135;
//    if( ( (currentHeight >= ypos) || (currentHeight+75 <= ypos) ) && Copter.isShowing() ){
//        addAndMakeVisible(hitLabel);
//    }
//    else {
//        removeChildComponent(&hitLabel);
//    }
    
    if ( keyRelease == true ) {
        ypos += 5;
        Copter.setBounds((int)xpos,(int)ypos,80,60);
    }
   // int localTime = (int)(processingAudio->getTime()*100.f);
   // int intTime   = (int)(processingAudio->getTime())*100;

   // if( (localTime-intTime < 6) && (localTime-intTime >= 0) ) {
        //myObstacle->setBounds(obsX-=5, 0, getWidth()*20, getHeight());
   // }

   // std::cout<<localTime<<std::endl;
//    std::cout<<processingAudio->getTime()<<std::endl;
    
}


void MainContentComponent::buttonClicked (Button *button) {
    
    if (button == &startButton) {
        removeChildComponent(&startButton);
        addAndMakeVisible(myObstacle);
        addAndMakeVisible(Copter);
        addAndMakeVisible(stopButton);
        startTimer(50);
    }
    if (button == &stopButton) {
        gameOver();
    }
}

void MainContentComponent::gameOver() {
    stopTimer();
    removeAllChildren();
    addAndMakeVisible(&gameOverLabel);
}
