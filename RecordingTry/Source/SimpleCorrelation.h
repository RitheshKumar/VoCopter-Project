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

class SimpleCorrelation  
{
public:
    SimpleCorrelation ();
    ~SimpleCorrelation();
    
    //==============================================================================
    void startTracking ();
    
    void stopTracking();
    
    void correlate ( float** inputData, int numSamples, int numChannels ); 
    //==============================================================================
    float getFrequency() { return frequency;  }

    void writeTheFile( std::vector<float>* vect, const char *fileName, int numSamples );
    
private:
    double sampleRate;
    int64 nextSampleNum;
    std::vector<float> diffVec,aucorr,x1,x2,myTestVec;
    int startIndex,endIndex,minIndex;
    //bool ifTracking;
    float frequency;

};

#endif /* defined(__RecordingTry__SimpleCorrelation__) */
