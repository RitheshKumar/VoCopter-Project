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
    AudioProcess ();
    ~AudioProcess();
    
    //==============================================================================

    void startTracking ();
    void stopTracking  ();
   
    //==============================================================================
    void audioDeviceAboutToStart (AudioIODevice* device);
    
    void audioDeviceStopped() override;
    
    void audioDeviceIOCallback (const float** inputChannelData, int /*numInputChannels*/,
                                float** outputChannelData, int numOutputChannels,
                                int numSamples) override ;

    float getFreq() { return freq; }

private:
    SimpleCorrelation *correlation;
    bool isTracking;
    float freq;

};

#endif /* defined(__RecordingTry__AudioProcess__) */
