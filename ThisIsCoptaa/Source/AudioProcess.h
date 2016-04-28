//
//  AudioProcess.h
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 11/2/15.
//
//

#ifndef __RecordingTry__AudioProcess__
#define __RecordingTry__AudioProcess__

#include <stdio.h>
#include <fstream>
#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"
#include "SimpleCorrelation.h"

class AudioProcess  : public AudioIODeviceCallback
{
public:
    AudioProcess (int note);
    ~AudioProcess();
    
    //==============================================================================
   
    //==============================================================================
    void audioDeviceAboutToStart (AudioIODevice* device);
    
    void audioDeviceStopped() override;
    
    void audioDeviceIOCallback (const float** inputChannelData, int /*numInputChannels*/,
                                float** outputChannelData, int numOutputChannels,
                                int numSamples) override ;

    float getFreqIn() { return freq; }
    float getTimeElapsed() { return time; }
    float getMidiIn() { return midiNote; }

    void setNotePlay(bool toggle) { isNoteOn = toggle; }

private:
    SimpleCorrelation *correlation;
    bool isNoteOn;
    float freq,
          time,
          tick,
          bpm;
    float currentAngle, startFreq,
          midiNote;
    int sampleRate;

};

#endif /* defined(__RecordingTry__AudioProcess__) */
