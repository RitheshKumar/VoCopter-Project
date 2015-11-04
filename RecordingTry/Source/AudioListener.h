//
//  AudioListener.h
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 9/8/15.
//
//

#ifndef __RecordingTry__AudioListener__
#define __RecordingTry__AudioListener__

#include <stdio.h>
#include <fstream>
#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"

class AudioListener  : public AudioIODeviceCallback
{
public:
    AudioListener ();
    ~AudioListener();
    
    //==============================================================================
    void startListening ();
    
    void stopListening();
    
    
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
    TimeSliceThread backgroundThread; // the thread that will write our audio data to disk
    ScopedPointer<AudioFormatWriter::ThreadedWriter> threadedWriter; // the FIFO used to buffer the incoming data
    double sampleRate;
    int64 nextSampleNum;
    std::vector<float> delayBuffer,aucorr,x1,x2;
    int startIndex,endIndex,minIndex;
    bool isListening;
    
    CriticalSection writerLock;
    AudioFormatWriter::ThreadedWriter* volatile activeWriter;
    

};

#endif /* defined(__RecordingTry__AudioListener__) */
