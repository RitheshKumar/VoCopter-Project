/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


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


    setSize (winWidth, winHeight);
    setWantsKeyboardFocus(true);
}

void MainContentComponent::reset() {
    
    xpos = winWidth*0.15;
    keyRelease = 0;
    obsX = winWidth*0.95;
    gameStartTime = 0.f;

    
    if (myObstacle!= nullptr) {
        delete myObstacle;
    }
    myObstacle = 0;
    
    myObstacle = new ObstacleComponent((char *)"~/Documents/Fall_2015/VoCopter Project/ThisIsCoptaa/MidiFiles/altNotesC.mid") ;
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
    
    gameOverLabel.setBounds(getWidth()/2-95,getHeight()/2-60, 200, 60 );
    restartButton.setBounds(getWidth()/2-50,getHeight()/2+30, 100, 60 );
}

bool MainContentComponent::keyPressed(const KeyPress& key)
{
    //std::cout<<ypos<<",";
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

void MainContentComponent::timerCallback() {
    
//    std::cout<<myObstacle->getObstacleLength()<<std::endl;
    myObstacle->setBounds(obsX-=10, 0, myObstacle->getObstacleLength(), getHeight());
    
    //It takes 3.2xx seconds for the copter to enter the obstacles from gameStart
    //Basically you can temporally shift here.
    int curObsPos = (int)myObstacle->getObstacleHeight( processingAudio->getTimeElapsed() - gameStartTime - 3.5 );
//    std::cout<<curObsPos<<std::endl;
//    //if ( curObsPos!= -1 ) {
    int noteIn = 0;//processingAudio->getMidiIn(); //std::cout<<noteIn<<std::endl;
    int heightDev = curObsPos - ypos;
    heightDev = (heightDev>0)? heightDev : -heightDev;
    
    //Copter placement
    //25 is the no. of pixels for a note
//    ypos = winHeight - 12.5 - noteIn*25;
    if ( curObsPos > 0 ) {
        ypos = (heightDev >= 300 )? (winHeight - 12.5 - noteIn*25 - winHeight/2) : (winHeight - 12.5 - noteIn*25) ;
        std::cout<<heightDev/*<<", "<<curObsPos<<", "<<ypos*/<<std::endl;
//        ypos = curObsPos - 35;
//        ypos -= 35;
        Copter.setBounds(xpos, ypos-35, 80, 60); //Fine Tuning copter's position.
    }
//    std::cout<<noteIn<<", "<<processingAudio->getFreqIn()<<", "<<ypos<<std::endl;
//    std::cout<<processingAudio->getMidiIn()<<std::endl;
//    }

    //Collision Detection
    
    if (  obsX < (0.15*winWidth + 80)    ) {
        
        curObsPos -= 35;

        if ( (  curObsPos + 12.5 < ypos   ||   (curObsPos -12.5) > ypos  ) && curObsPos >= 0 ){ //Within one semitone difference
            addAndMakeVisible(hitLabel);
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
//        removeChildComponent(&gameOverLabel);
//        removeChildComponent(&restartButton);
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
    gameStartTime = processingAudio->getTimeElapsed();
    startTimer(50);
}

void MainContentComponent::gameOver() {
    stopTimer();
    removeAllChildren();
    addAndMakeVisible(&gameOverLabel);
    addAndMakeVisible(restartButton);
}
