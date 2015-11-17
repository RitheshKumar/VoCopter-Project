//
//  AudioProcess.cpp
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 9/8/15.
//
//

#include "AudioProcess.h"

AudioProcess::AudioProcess()  {
    isTracking = false;
}


AudioProcess::~AudioProcess() {
    AudioProcess::stopTracking();
}

void AudioProcess::audioDeviceIOCallback (const float** inputChannelData, int numInputChannels,
        float** outputChannelData, int numOutputChannels,
        int numSamples)
{

    if ( isTracking ) {

        float **inputData = new float*[numInputChannels];

        for (int i = 0; i < numInputChannels; i++ ) {
            inputData[i] = new float[numSamples];
        }

        for (int i = 0; i < numInputChannels; i++) {

            for ( int j = 0; j < numSamples; j++ ) {
                
                inputData[i][j] =  inputChannelData[i][j];

            }
        }

        correlation.correlate( inputData, numSamples);
             
     } 
    else
    {
        // We need to clear the output buffers, in case they're full of junk..
        for (int i = 0; i < numOutputChannels; ++i) {
            if (outputChannelData[i] != nullptr) {
                FloatVectorOperations::clear (outputChannelData[i],numSamples);
                memcpy( outputChannelData[i], inputChannelData[0], sizeof(float)*numSamples );
            }
        }
    }//*/
}

void AudioProcess::audioDeviceAboutToStart (AudioIODevice* device){}

void AudioProcess::audioDeviceStopped() {}

void AudioProcess::startTracking () {
    AudioProcess::stopTracking();
    isTracking = true;
}

void AudioProcess::stopTracking ()  {
    isTracking = false;
}


