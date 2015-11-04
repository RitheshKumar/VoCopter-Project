//
//  AudioRecorder.h
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 9/8/15.
//
//

#ifndef __RecordingTry__AudioRecorder__
#define __RecordingTry__AudioRecorder__

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"

class AudioRecorder  : public AudioIODeviceCallback
{
public:
    AudioRecorder ();
    ~AudioRecorder();
    
    //==============================================================================
    void startRecording (const File& file);
    
    void stop();
    
    bool isRecording() const;
    
    //==============================================================================
    void audioDeviceAboutToStart (AudioIODevice* device) override;
    
    void audioDeviceStopped() override;
    
    void audioDeviceIOCallback (const float** inputChannelData, int /*numInputChannels*/,
                                float** outputChannelData, int numOutputChannels,
                                int numSamples) override ;
    
    
private:
    //AudioThumbnail& thumbnail;
    TimeSliceThread backgroundThread; // the thread that will write our audio data to disk
    ScopedPointer<AudioFormatWriter::ThreadedWriter> threadedWriter; // the FIFO used to buffer the incoming data
    double sampleRate;
    int64 nextSampleNum;
    
    CriticalSection writerLock;
    AudioFormatWriter::ThreadedWriter* volatile activeWriter;
};

#endif /* defined(__RecordingTry__AudioRecorder__) */
