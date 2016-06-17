/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include <string.h>


//==============================================================================
MainContentComponent::MainContentComponent(): myObstacle(0),
                                              fileFilter(("*.mid"), ("*"), ("Midi files")),
                                              chooseMidi(0)
{
    
    reset();
    
    //Notice that the order is important
    addAndMakeVisible(startButton);
    addAndMakeVisible(gameLogo);
    addAndMakeVisible(chooseMidi);
    
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
    
    processingAudio = new AudioProcess(myObstacle->getStartNote()+12);
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
    
    gameLogo.setInterceptsMouseClicks(true, true);
    
    
    //Add lives imagery
    for (int i = 0; i < 5; ++i)
    {
        CopterComponent* d = new CopterComponent();
        livesLeft.add (d);
    }
    
    
    setSize (winWidth, winHeight);
    setWantsKeyboardFocus(true);
    
}

void MainContentComponent::reset() {

    xpos = winWidth*0.15;
    keyRelease = 0;
    obsX = winWidth*0.95;
    gameStartTime = 0.0f;
    newlifeTime = 0.0f;
    copterHits = 0;
    lifeIdx = 0;

    
    if (myObstacle!= nullptr) {
        delete myObstacle;
    }
    myObstacle = 0;
    
    if (chooseMidi!=nullptr){
        delete chooseMidi;
    }
    chooseMidi = 0;

    chooseMidi = new FileBrowserComponent( FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles,
                                           File::getSpecialLocation(File::userDesktopDirectory),
                                          &fileFilter, NULL);
    

    myObstacle = new ObstacleComponent((char *)"../stairwayToHeaven.mid") ;
    ypos       = myObstacle->getInitialHeight()-35;
    
    isjBMode = false;
    
}

MainContentComponent::~MainContentComponent()
{
//    deviceManager.removeAudioCallback(processingAudio);
    delete myObstacle;
    myObstacle = 0;
    
    delete chooseMidi;
    chooseMidi = 0;
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
    
    startButton.setBounds(getWidth()/2-50, getHeight()/2+25, 100, 40);
    gameLogo.setBounds(-125, getHeight()/2-175, 1000, 204);
    chooseMidi->setBounds(getWidth()/2-150, getHeight()/2+75, 300, 150);
    
    
    myObstacle->setBounds(obsX, 0, getWidth(), getHeight());

    
    stopButton.setBounds(getWidth()-45, 20, 40, 20);
    hitLabel.setBounds(round(getWidth()/2)-40,round(getHeight()/2),80,50);
    numHitsLabel.setBounds(0,0,150,70);
    
    gameOverLabel.setBounds(getWidth()/2-95,getHeight()/2-120, 200, 60 );
    scoreLabel.setBounds(getWidth()/2-180,getHeight()/2-70, 400, 60);
    restartButton.setBounds(getWidth()/2-50,getHeight()/2+20, 100, 60 );
    
    noteLabel.setBounds(getWidth()/2-50, getHeight()/2+25, 100, 40);
    jBModeLabel.setBounds(150, getHeight()/2-50, 1000, 60);
    
//    CopterComponent* d = livesLeft.getUnchecked(0);
//    livesLeft.getUnchecked(0)->setBoundsToFit(20, 20, 80, 60, Justification::centred, true);
    
}

bool MainContentComponent::keyPressed(const KeyPress& key)
{
    switch (key.getTextCharacter()) {
        case 'w':
            Copter->setBounds(xpos,ypos-=8,/*getWidth()*0.3,getHeight()*0.3*/80,60);
            return true;
            break;
            
        case 's':
            Copter->setBounds(xpos,ypos+=5,/*getWidth()*0.3,getHeight()*0.3*/80,60);
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
    
    if (isjBMode) {
        noteLabel.setText(std::to_string(processingAudio->getMidiIn()), dontSendNotification);
    }
    else {
//        myObstacle->setBounds(0, 0, myObstacle->getObstacleLength(), getHeight());
        myObstacle->setBounds(obsX-=10.5, 0, myObstacle->getObstacleLength(), getHeight());
        myObstacle->setCurTime( 10.5 );

        copterPlacement();
        
        collisionDetection();

        //if ( keyRelease == true ) {
        //    ypos += 5;
        //    Copter.setBounds((int)xpos,(int)ypos,80,60);
        //}
        gamePlayEvents();
    }
    
}

int height1, height2,
    height1Dev, height2Dev;
float noteIn;
void MainContentComponent::copterPlacement() {
    //It takes 3.2xx seconds for the copter to enter the obstacles from gameStart
    //Basically you can temporally shift here.
    float curTime = processingAudio->getTimeElapsed() - gameStartTime - 3.20;
    curObsPos = (int)myObstacle->getObstacleHeight( curTime );
    
    noteIn = processingAudio->getMidiIn();
    ypos = winHeight - 12.5 - noteIn*25;
    Copter->setBounds(xpos, ypos-35, 80, 60); //Fine Tuning copter's position.

    //Copter placement
    //25 is the no. of pixels for a note
//    if ( curObsPos > 0 ) {
//        noteIn = processingAudio->getMidiIn();
//        
//        height1 = winHeight - 12.5 - noteIn*25; ypos = height1;
//        height1Dev = height1 - curObsPos;
//        height1Dev = (height1Dev>0)? height1Dev : -height1Dev;
//        
//        height2 = winHeight - 12.5 - noteIn*25 - winHeight/2;
//        height2Dev = height2 - curObsPos;
//        height2Dev = (height2Dev>0)? height2Dev : -height2Dev;
//        
//        ypos = (height1Dev <= height2Dev )? height1 : height2;
//        //        std::cout<<noteIn<<", "<<curObsPos<<", "<<ypos<<"     "<<height1Dev<<", "<<height2Dev<<"     ";
//        //        std::cout<<height1<<", "<<height2<<std::endl;
//        Copter.setBounds(xpos, ypos-35, 80, 60); //Fine Tuning copter's position.
//    }
}

void MainContentComponent::collisionDetection() {
    if (  obsX < (0.15*winWidth + 80)    ) {
        
        if ( (  curObsPos + 50 < ypos   ||   (curObsPos -50) > ypos  ) && curObsPos > 0 ){ //Within one semitone difference
//            std::cout<<curObsPos<<std::endl;
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
    
    if(copterHits > 50) {
        gameOver();
    }
    
    if( copterHits%10 == 0 && copterHits > 0 && (processingAudio->getTimeElapsed() - newlifeTime) > 1.0f){
        newLife();
    }
 
}


void MainContentComponent::newLife() {
    newlifeTime = processingAudio->getTimeElapsed();
    if (lifeIdx>=0 && lifeIdx<4){
        removeChildComponent(livesLeft.getUnchecked(lifeIdx++));
        Copter = livesLeft.getUnchecked(lifeIdx);
    }
}

void MainContentComponent::gamePlayEvents() {
    if ( roundf( processingAudio->getTimeElapsed() - gameStartTime ) == 5 ) {
        removeChildComponent(&gameLogo);
    }
    
    if ( roundf( processingAudio->getTimeElapsed() - gameStartTime ) == 4 ) {
        processingAudio->setNotePlay(false);
    }
    
    if ( roundf( processingAudio->getTimeElapsed() - gameStartTime )
        == roundf(myObstacle->getEndTime() + 5) ) { //5 seconds overhead in scrolling
        gameOver();
    }
}


void MainContentComponent::buttonClicked (Button *button) {
    
    if (button == &startButton) {
        removeChildComponent(&startButton);
        
//        String myString = (chooseMidi->getSelectedFile(1)).getFullPathName();
//        std::cout<<myString<<std::endl;
//        myObstacle  = new ObstacleComponent((myString.toStdString()).c_str());
//         ypos       = myObstacle->getInitialHeight()-35;
        
        gameStart();
    }
    if (button == &stopButton) {
        gameOver();
    }
    if (button == &restartButton) {
        removeAllChildren();
        stopTimer();
        reset();
        gameStart();
        
    }

}

void MainContentComponent::gameStart() {
    
    resized();

    addAndMakeVisible(myObstacle);
    removeChildComponent(chooseMidi);
    
    livesLeft.getUnchecked(1)->setBounds(20,20,80,60);addAndMakeVisible(livesLeft.getUnchecked(1));
    livesLeft.getUnchecked(2)->setBounds(45,20,80,60);addAndMakeVisible(livesLeft.getUnchecked(2));
    livesLeft.getUnchecked(3)->setBounds(20,45,80,60);addAndMakeVisible(livesLeft.getUnchecked(3));
    livesLeft.getUnchecked(4)->setBounds(45,45,80,60);addAndMakeVisible(livesLeft.getUnchecked(4));
    Copter = livesLeft.getUnchecked(0);
    addAndMakeVisible(Copter);
    Copter->setBounds(xpos,ypos,80,60);
    addAndMakeVisible(stopButton);
    hitsDisplay = "Number of hits: ";
    hitsDisplay += copterHits;
    numHitsLabel.setText(hitsDisplay, dontSendNotification);
    addAndMakeVisible(numHitsLabel);
    gameStartTime = processingAudio->getTimeElapsed();
    processingAudio->setNotePlay(true);
    myObstacle->resetTime();
    startTimer(50);
}

void MainContentComponent::gameOver() {
    stopTimer();
    isjBMode = false;
    removeAllChildren();
    
    addAndMakeVisible(&gameOverLabel);
    
    
    hitsDisplay = "You scored ";
    if (  obsX < (0.15*winWidth + 80)    ) {
        int completionScore = (int)(myObstacle->getPercentComplete()*100.f);
        if ( completionScore > 94.f ) {
//            std::cout<<(int)((1.0f - (copterHits*1.0f/50.f) )*100.0f)<<std::endl;
            hitsDisplay += completionScore + (int)((1.0f - (copterHits*1.0f/50.f) )*100.0f);
        }
        else {
            hitsDisplay += completionScore;
        }
        
    }
    else {
        hitsDisplay += 0;
    }
    hitsDisplay += " points!";
    scoreLabel.setFont(Font(40));
    scoreLabel.setText(hitsDisplay, dontSendNotification);
    scoreLabel.setColour(Label::textColourId, Colours::green);
    addAndMakeVisible(&scoreLabel);
    
    
    addAndMakeVisible(restartButton);
}


void MainContentComponent::mouseDown(const MouseEvent & event) {
    isjBMode = true;
//    jawKneeBoyMode();
}


void MainContentComponent::jawKneeBoyMode() {
    removeAllChildren();
    
    jBModeLabel.setFont(Font(40));
    jBModeLabel.setColour(Label::textColourId, Colours::green);
    addAndMakeVisible(jBModeLabel);
    jBModeLabel.setText("Welcome to JawKnee Boy mode!! :)", dontSendNotification);
    
    noteLabel.setFont(Font(40));
    noteLabel.setColour(Label::textColourId, Colours::red);
    addAndMakeVisible(noteLabel);
    
    addAndMakeVisible(stopButton);
    
    startTimer(50);
}

