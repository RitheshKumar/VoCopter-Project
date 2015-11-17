/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
//#include "AudioRecorder.h"
//#include "AudioListener.h"
//#include "SimpleCorrelation.h"
#include "AudioProcess.h"
//#include "juce_Timer.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/




class MainContentComponent   : public AudioAppComponent,
                               private Button::Listener
                               //private Timer

{
public:
    //==============================================================================
    MainContentComponent()
    {
        setSize (800, 600);

        // specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);

        /*addAndMakeVisible (recordButton);
        recordButton.setButtonText ("Record");
        recordButton.addListener (this);
        recordButton.setColour (TextButton::buttonColourId, Colour (0xffff5c5c));
        recordButton.setColour (TextButton::textColourOnId, Colours::black);
        
        
        
        addAndMakeVisible(listenButton);
        listenButton.setButtonText("Listen");
        listenButton.addListener(this);
        listenButton.setColour(TextButton::buttonColourId, Colours::yellow);
        listenButton.setColour(TextButton::textColourOnId, Colours::black);*/

        addAndMakeVisible(pitchButton);
        pitchButton.setButtonText("Track Pitch");
        pitchButton.addListener(this);
        pitchButton.setColour(TextButton::buttonColourId, Colours::yellow);
        pitchButton.setColour(TextButton::textColourOnId, Colours::black);

        //addAndMakeVisible(pitchLabel);
        ////pitchLabel.setText(std::to_string(listen.frequency), dontSendNotification);
        //pitchLabel.setColour(Label::textColourId, Colours::yellow);
        
        ////deviceManager is used to manage the soundcard
        deviceManager.initialise (1, 2, 0, true, String::empty, 0);
        ////deviceManager.addAudioCallback(&listen);
        deviceManager.addAudioCallback(&processingAudio);
        ////deviceManager.addAudioCallback (&recorder);
        
    }

    ~MainContentComponent()
    {
        shutdownAudio();
        //deviceManager.removeAudioCallback (&recorder);
        deviceManager.removeAudioCallback (&processingAudio);
    }

    //=======================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        // This function will be called when the audio device is started, or when
        // its settings (i.e. sample rate, block size, etc) are changed.

        // You can use this function to initialise any resources you might need,
        // but be careful - it will be called on the audio thread, not the GUI thread.

        // For more details, see the help for AudioProcessor::prepareToPlay()
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        // Your audio-processing code goes here!

        // For more details, see the help for AudioProcessor::getNextAudioBlock()

        // Right now we are not producing any data, in which case we need to clear the buffer
        // (to prevent the output of random noise)
        bufferToFill.clearActiveBufferRegion();
        
    }

    void releaseResources() override
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.

        // For more details, see the help for AudioProcessor::releaseResources()
    }

    //=======================================================================
    void paint (Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (Colours::black);
        //g.setColour(Colours::yellow);
        //g.fillRect(60,60+(int)listen.frequency,90,75); //The first is the axis,width,height,cornersize

        // You can add your drawing code here!
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        //recordButton.setBounds(round(getWidth()/2)-80,round(getHeight()/2)-190,80,20);
        //listenButton.setBounds(round(getWidth()/2)+20,round(getHeight()/2)-190,80,20);
        //pitchLabel.setBounds(round(getWidth()/2)-30,round(getHeight()/2)-150,80,20);
        //pitchButton.setBounds(round(getWidth()/2)-25,round(getHeight()/2)-120,80,20);
    }

   //void timerCallback() override {
        //pitchLabel.setText(std::to_string(pitchTrack.frequency),dontSendNotification);
    //}

private:
    //==============================================================================

    // Your private member variables go here...
    TextButton /*recordButton,listenButton,*/pitchButton;
    ////AudioRecorder recorder;
    ////AudioListener listen;
    //SimpleCorrelation pitchTrack;
    AudioProcess processingAudio;
    //Label pitchLabel;
    int isOn=1;
    //AudioDeviceManager deviceManager;
    
    
    /*void startRecording()
    {
        const File file (File::getSpecialLocation (File::userDocumentsDirectory)
                         .getNonexistentChildFile ("MyRecording", ".wav"));
        //recorder.startRecording (file);
        
        recordButton.setButtonText ("Stop");
    
    }
    
    void stopRecording()
    {
        //recorder.stop();
        recordButton.setButtonText ("Record");
        
    }
    
    void startListening()
    {
        listen.startListening();
        listenButton.setButtonText("StopListening");
        startTimer(20);
    }
    
    void stopListening()
    {
        listen.stopListening();
        listenButton.setButtonText("Listen");
        stopTimer();
    }*/

    /*void startTracking()
    {
        pitchTrack.startTracking();
        pitchButton.setButtonText("StopTracking");
        startTimer(20);
    }
    
    void stopTracking()
    {
        pitchTrack.stopTracking();
        pitchButton.setButtonText("Track Pitch");
        stopTimer();
    }*/
    
    void buttonClicked (Button* button) override
    {
        /*if (button == &recordButton)
        {
            if (recorder.isRecording())
                stopRecording();
            else
                startRecording();
        }
        if (button == &listenButton)
        {
            
            if (isOn==1)
            {   startListening();
                isOn=0;
            }
            else
            {   stopListening();
                isOn=1;
            }
        }*/
        if (button == &pitchButton)
        {
            
            if (isOn==1)
            {
                //startTracking();
                processingAudio.startTracking();
                pitchButton.setButtonText("StopTracking");
                //startTimer(20);
                isOn=0;
            }
            else
            {
                //stopTracking();
                processingAudio.stopTracking();
                pitchButton.setButtonText("Track Pitch");
                //stopTimer();
                isOn=1;
            }
        }
    }
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};



// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); } //Why can't it return a reference?


#endif  // MAINCOMPONENT_H_INCLUDED
