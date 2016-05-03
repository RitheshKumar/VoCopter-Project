//
//  AudioProcess.cpp
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 9/8/15.
//
//

#include "AudioProcess.h"

AudioProcess::AudioProcess (int note )  {
    isNoteOn = false;
    freq = 0.0f;
    time = 0.0f;
    bpm  = 60.f/240.f; //Denominator is your tempo/bpm
    tick = bpm;
    currentAngle = 0.f;
    startFreq = std::pow(2.0f,(note-69)/12.f)*440.f;  
    sampleRate = 0;
    midiNote   = 0;
}


AudioProcess::~AudioProcess() {
    delete correlation;
}

//numSamples is 512 for a sample rate of 44100 which is 11.6ms a block
//This block is called
void AudioProcess::audioDeviceIOCallback (const float** inputChannelData,  int numInputChannels,
                                                float** outputChannelData, int numOutputChannels,
                                                                           int numSamples)        {


    if ( /*isTracking*/1 ) {

        correlation->correlate( (const float**) inputChannelData, freq, midiNote, numSamples );
        
             
     } 
    // We need to clear the output buffers, in case they're full of junk..
    
    if ( isNoteOn ) {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            const float currentSample = (float) std::sin (currentAngle);
            currentAngle += (startFreq/sampleRate) * 2.0 * double_Pi;
            for ( int c = 0; c < numOutputChannels; c++) {
                outputChannelData[c][sample] = currentSample * 0.3;
            }
        }
    }
    else {
        for (int i = 0; i < numOutputChannels; ++i) {
            if (outputChannelData[i] != nullptr) {
                FloatVectorOperations::clear (outputChannelData[i],numSamples);
            }
//                    if((time - tick) <= 0.0116f && (time - tick) > 0) {
//                        outputChannelData[i][(int)numSamples/2] = 0.5f;
//                        if (i == numOutputChannels-1) {
//                            tick+=bpm;
//                        }
//                    }
        }
        
    }
    time+=(numSamples*1.f)/sampleRate;
//    std::cout<<time<<std::endl;
    
//    tick+=tick;
//    float actTime = time/sampleRate;
//    if ( actTime - (int)actTime == 0.0f)
//        std::cout<<actTime<<std::endl;
}

void AudioProcess::audioDeviceAboutToStart (AudioIODevice* device){

    int   blockSize = 2*(int)device->getCurrentBufferSizeSamples(),
        numChannels = ( device->getActiveInputChannels() ).toInteger();  //getActiveInputChannels() returns a juce::BigInteger
    sampleRate  = (int) device->getCurrentSampleRate();
    correlation = new SimpleCorrelation( blockSize, numChannels, sampleRate );

}

void AudioProcess::audioDeviceStopped() {}



