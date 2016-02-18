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
#include "FileRW.h"
#include "../JuceLibraryCode/JuceHeader.h"

class SimpleCorrelation  
{
public:
    SimpleCorrelation ( int iMaxBlockSize, int iNumChannels, float fSampleRate );
    ~SimpleCorrelation();
    
    //==============================================================================
    
    void correlate ( const float** inputData, float &freq, int numSamples );

    //==============================================================================
    
private:
    int64 nextSampleNum;
    std::vector<float> maxima,aucorr,myTestVec;
    std::vector<int>   peakIdx;
    int startIndex,endIndex,minIndex, iter;

    float frequency;
    int _iNumChannels,
        _iAcfBufLen;
    float **_ppfAucorr,
          _fSampleRate,
          _fFrequency;

    //Private Functions
    void reset();

};

#endif /* defined(__RecordingTry__SimpleCorrelation__) */



