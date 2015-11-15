//
//  SimpleCorrelation.h
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 11/2/15.
//
//

#ifndef __RecordingTry__SimpleCorrelation__
#define __RecordingTry__SimpleCorrelation__

#include <stdio.h>
#include <fstream>
#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"

class SimpleCorrelation  : public AudioIODeviceCallback
{
public:
    SimpleCorrelation ();
    ~SimpleCorrelation();
    
    //==============================================================================
    void startTracking ();
    
    void stopTracking();
    
    
    //==============================================================================
    void audioDeviceAboutToStart (AudioIODevice* device);
    
    void audioDeviceStopped() override;
    
    void audioDeviceIOCallback (const float** inputChannelData, int /*numInputChannels*/,
                                float** outputChannelData, int numOutputChannels,
                                int numSamples) override ;

    void writeTheFile(std::vector<float>* vect,const char *fileName,int numSamples);
    //void writeFile(std::vector<float>* vect,const char *fileName);
    float frequency;
    
    
private:
    double sampleRate;
    int64 nextSampleNum;
    std::vector<float> delayBuffer,aucorr,x1,x2,myTestVec;
    int startIndex,endIndex,minIndex;
    bool isTracking;

};

#endif /* defined(__RecordingTry__SimpleCorrelation__) */
