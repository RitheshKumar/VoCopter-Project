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
#include <numeric>
#include "../JuceLibraryCode/JuceHeader.h"

class SimpleCorrelation  
{
public:
    SimpleCorrelation ( int sampleRate, int numSamples, int numChannels );
    ~SimpleCorrelation();
    
    //==============================================================================
    void startTracking ();
    
    void stopTracking();
    
    void correlate ( const float** inputData ); 
    //==============================================================================
    float getFrequency() { return frequency;  }

    void writeTheFile( std::vector<float>* vect, const char *fileName );
    
private:
    double sampleRate;
    int64 nextSampleNum;
    std::vector<float> maxima,aucorr,myTestVec;
    std::vector<int>   peakIdx;
    int startIndex,endIndex,minIndex, _sampleRate, _numSamples, _numChannels;
    //bool ifTracking;
    float frequency;

};

#endif /* defined(__RecordingTry__SimpleCorrelation__) */
