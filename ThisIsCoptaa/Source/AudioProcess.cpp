//
//  AudioProcess.cpp
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 9/8/15.
//
//

#include "AudioProcess.h"

AudioProcess::AudioProcess ( /*int sampleRate, int numSamples, int numChannels*/ )  {
    isTracking = false;
    correlation = new SimpleCorrelation (  );
    freq = 0.0f;
}


AudioProcess::~AudioProcess() {
    AudioProcess::stopTracking();
    delete correlation;
}

void AudioProcess::audioDeviceIOCallback (const float** inputChannelData,  int numInputChannels,
                                                float** outputChannelData, int numOutputChannels,
                                                                           int numSamples)        {

    //std::ofstream outputFile ( "./InputData.txt" );
    //std::ostream_iterator<float> outputStream( outputFile, "\n" );
    //std::copy( myData[0], myData[0] + numSamples, outputStream);

    if ( /*isTracking*/1 ) {

        correlation->correlate( (const float**) inputChannelData, freq,
                                    numSamples, numInputChannels, 44100 ); //How can I actually pass a const float** as a parameter??
                                                           //You can't!

             
     } 
    // We need to clear the output buffers, in case they're full of junk..
    for (int i = 0; i < numOutputChannels; ++i) {
        if (outputChannelData[i] != nullptr) {
            FloatVectorOperations::clear (outputChannelData[i],numSamples);
            //memcpy( outputChannelData[i], inputChannelData[0], sizeof(float)*numSamples );
        }
    }
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


