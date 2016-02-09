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
    
    float correlate ( const float** inputData );
    //==============================================================================
    float getFrequency() { return frequency;  }

    void writeTheFile( std::vector<float>* vect, const char *fileName );
    
private:
    double sampleRate;
    int64 nextSampleNum;
    std::vector<float> maxima,aucorr,myTestVec;
    std::vector<int>   peakIdx;
    int startIndex,endIndex,minIndex, iter,
        _sampleRate, _numSamples, _numChannels;
    //bool ifTracking;
    float frequency;

};


class SimpleCorrelationTests  : public UnitTest
{
public:
    SimpleCorrelationTests() : UnitTest ("SimpleCorrelation"),
                               _ppfInputData( new float*[3])
    {
        testObj = new SimpleCorrelation( 44100, 1000, 3 );
    
        for( int i = 0; i<3; i++ ) {
            _ppfInputData[i] = new float[1000];
            std::fill(_ppfInputData[i],_ppfInputData[i]+1000,0);
        }
    }
    
    ~SimpleCorrelationTests() { delete testObj; }
    
    void runTest() override
    {
        beginTest ("ZeroCheck");
        
        const float **tmp = (const float**) _ppfInputData;
        
        float freq = testObj->correlate( tmp );

        expect(freq == 0);
        
    }
private:
    SimpleCorrelation *testObj;
    float **_ppfInputData;
};

static SimpleCorrelationTests simpleCorrelationTest;

#endif /* defined(__RecordingTry__SimpleCorrelation__) */
