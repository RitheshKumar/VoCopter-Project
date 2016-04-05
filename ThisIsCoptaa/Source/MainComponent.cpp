/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include <string.h>


//==============================================================================
MainContentComponent::MainContentComponent(): myObstacle(0){
    
    reset();
    
    //Notice that the order is important
    addAndMakeVisible(startButton);
    
    startButton.setButtonText("Start!");
    startButton.addListener(this);
    stopButton.setButtonText("Stop");
    stopButton.addListener(this);
    restartButton.setButtonText("Restart");
    restartButton.addListener(this);
    
    startButton.setColour(TextButton::buttonColourId, Colours::green);
    startButton.setColour(TextButton::textColourOnId, Colours::black);
    stopButton.setColour(TextButton::buttonColourId, Colours::red);
    stopButton.setColour(TextButton::textColourOnId, Colours::black);
    restartButton.setColour(TextButton::buttonColourId, Colours::yellow);
    restartButton.setColour(TextButton::textColourOnId, Colours::black);
    
    processingAudio = new AudioProcess();
    deviceManager.initialise( 1, 2, 0, true, String::empty, 0 );
    deviceManager.addAudioCallback(processingAudio);
    
    hitLabel.setText("Copter Hit!", dontSendNotification);
    hitLabel.setColour(Label::textColourId, Colours::red);
    gameOverLabel.setFont(Font(40));
    gameOverLabel.setText("Game Over", dontSendNotification);
    gameOverLabel.setColour(Label::textColourId, Colours::red);
    
    hitsDisplay = "Number of hits: ";
    hitsDisplay += copterHits;
    numHitsLabel.setText(hitsDisplay, dontSendNotification);
    numHitsLabel.setColour(Label::textColourId, Colours::red);


    setSize (winWidth, winHeight);
    setWantsKeyboardFocus(true);
}

void MainContentComponent::reset() {
    
    xpos = winWidth*0.15;
    keyRelease = 0;
    obsX = winWidth*0.95;
    gameStartTime = 0.f;
    copterHits = 0;

    
    if (myObstacle!= nullptr) {
        delete myObstacle;
    }
    myObstacle = 0;
    
    myObstacle = new ObstacleComponent((char *)"~/Documents/Fall_2015/VoCopter Project/ThisIsCoptaa/MidiFiles/allNotes.mid") ;
    ypos       = myObstacle->getInitialHeight()-35;
    
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
    
    
    myObstacle->setBounds(obsX, 0, getWidth(), getHeight());
    stopButton.setBounds(getWidth()-45, 20, 40, 20);
    hitLabel.setBounds(round(getWidth()/2)-40,round(getHeight()/2),80,50);
//    numHitsLabel.setBounds(0, 0, 40, 50);
    numHitsLabel.setBounds(0,0,150,70);
    
    gameOverLabel.setBounds(getWidth()/2-95,getHeight()/2-60, 200, 60 );
    restartButton.setBounds(getWidth()/2-50,getHeight()/2+30, 100, 60 );
}

bool MainContentComponent::keyPressed(const KeyPress& key)
{
    switch (key.getTextCharacter()) {
        case 'w':
            Copter.setBounds(xpos,ypos-=8,/*getWidth()*0.3,getHeight()*0.3*/80,60);
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

int noteIn, height1, height2,
            height1Dev, height2Dev;

void MainContentComponent::timerCallback() {
    
    myObstacle->setBounds(obsX-=10, 0, myObstacle->getObstacleLength(), getHeight());
    
    //It takes 3.2xx seconds for the copter to enter the obstacles from gameStart
    //Basically you can temporally shift here.
    int curObsPos = (int)myObstacle->getObstacleHeight( processingAudio->getTimeElapsed() - gameStartTime - 3.20 );
    std::cout<<curObsPos<<std::endl;

    //Copter placement
    //25 is the no. of pixels for a note
//    if ( curObsPos > 0 ) {
//        noteIn = 2;//processingAudio->getMidiIn();
//        
//        height1 = winHeight - 12.5 - noteIn*25;
//        height1Dev = height1 - curObsPos;
//        height1Dev = (height1Dev>0)? height1Dev : -height1Dev;
//        
//        height2 = winHeight - 12.5 - noteIn*25 - winHeight/2;
//        height2Dev = height2 - curObsPos;
//        height2Dev = (height2Dev>0)? height2Dev : -height2Dev;
//
//        ypos = (height1Dev <= height2Dev )? height1 : height2;
////        std::cout<<noteIn<<", "<<curObsPos<<", "<<ypos<<"     "<<height1Dev<<", "<<height2Dev<<"     ";
////        std::cout<<height1<<", "<<height2<<std::endl;
//        Copter.setBounds(xpos, ypos-35, 80, 60); //Fine Tuning copter's position.
//    }

    //Collision Detection
    
    if (  obsX < (0.15*winWidth + 80)    ) {

        if ( (  curObsPos + 12.5 < ypos   ||   (curObsPos -12.5) > ypos  ) && curObsPos > 0 ){ //Within one semitone difference
            addAndMakeVisible(hitLabel);
            copterHits++;
            hitsDisplay = "Number of hits: ";
            hitsDisplay += copterHits;
            numHitsLabel.setText(hitsDisplay, dontSendNotification);
        }
        else if( curObsPos != -1 ){
            removeChildComponent(&hitLabel);
        }

    }
    
    //if ( keyRelease == true ) {
    //    ypos += 5;
    //    Copter.setBounds((int)xpos,(int)ypos,80,60);
    //}

    if ( roundf( processingAudio->getTimeElapsed() - gameStartTime )
                                   == roundf(myObstacle->getEndTime() + 5) ) { //5 seconds overhead in scrolling
        gameOver();
    }
    
}


void MainContentComponent::buttonClicked (Button *button) {
    
    if (button == &startButton) {
        removeChildComponent(&startButton);
        gameStart();
    }
    if (button == &stopButton) {
        gameOver();
    }
    if (button == &restartButton) {
        removeAllChildren();
        reset();
        gameStart();
        
    }

}

void MainContentComponent::gameStart() {
    addAndMakeVisible(myObstacle);
    addAndMakeVisible(Copter);
    Copter.setBounds(xpos,ypos,/*getWidth()*0.3,getHeight()*0.3*/80,60);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(numHitsLabel);
    gameStartTime = processingAudio->getTimeElapsed();
    startTimer(50);
}

void MainContentComponent::gameOver() {
    stopTimer();
    removeAllChildren();
    addAndMakeVisible(&gameOverLabel);
    addAndMakeVisible(restartButton);
}
