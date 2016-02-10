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
#include <string.h>
#include <fstream>
#include <iostream>
#include <numeric>
#include "../JuceLibraryCode/JuceHeader.h"

class SimpleCorrelation  
{
public:
    SimpleCorrelation ();
    ~SimpleCorrelation();
    
    //==============================================================================
    
    void correlate ( const float** inputData, float &freq, int numSamples, int numChannels, int sampleRate );
    //==============================================================================
    float getFrequency() { return frequency;  }

    void writeTheFile( std::vector<float>* vect, const char *fileName );
    
private:
    int64 nextSampleNum;
    std::vector<float> maxima,aucorr,myTestVec;
    std::vector<int>   peakIdx;
    int startIndex,endIndex,minIndex, iter;

    float frequency;

};

#endif /* defined(__RecordingTry__SimpleCorrelation__) */



