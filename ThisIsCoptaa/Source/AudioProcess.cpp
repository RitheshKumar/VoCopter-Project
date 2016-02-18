//
//  AudioProcess.cpp
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 9/8/15.
//
//

#include "AudioProcess.h"

AudioProcess::AudioProcess ()  {
    isTracking = false;
    freq = 0.0f;
}


AudioProcess::~AudioProcess() {
    AudioProcess::stopTracking();
    delete correlation;
}

void AudioProcess::audioDeviceIOCallback (const float** inputChannelData,  int numInputChannels,
                                                float** outputChannelData, int numOutputChannels,
                                                                           int numSamples)        {


    if ( /*isTracking*/1 ) {

        correlation->correlate( (const float**) inputChannelData, freq, numSamples ); 
        
             
     } 
    // We need to clear the output buffers, in case they're full of junk..
    for (int i = 0; i < numOutputChannels; ++i) {
        if (outputChannelData[i] != nullptr) {
            FloatVectorOperations::clear (outputChannelData[i],numSamples);
            //memcpy( outputChannelData[i], inputChannelData[0], sizeof(float)*numSamples );
        }
    }
}

void AudioProcess::audioDeviceAboutToStart (AudioIODevice* device){

    int   blockSize = 2*(int)device->getCurrentBufferSizeSamples(),
        numChannels = ( device->getActiveInputChannels() ).toInteger();  //getActiveInputChannels() returns a juce::BigInteger
    float sampleRate  = (int) device->getCurrentSampleRate();
    correlation = new SimpleCorrelation( blockSize, numChannels, sampleRate );

}

void AudioProcess::audioDeviceStopped() {}

void AudioProcess::startTracking () {
    AudioProcess::stopTracking();
    isTracking = true;
}

void AudioProcess::stopTracking ()  {
    isTracking = false;
}


