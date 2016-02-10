//
//  SimpleCorrelation.cpp
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 9/8/15.
//
//

#include "SimpleCorrelation.h"

SimpleCorrelation::SimpleCorrelation()  : frequency (0.0)  {

    iter   = 0;
    peakIdx.resize(0);

    maxima.resize(0);

}

SimpleCorrelation::~SimpleCorrelation() {}


void SimpleCorrelation::correlate ( const float** inputData, float &freq, int numSamples, int numChannels, int sampleRate )
{

    aucorr.resize(numSamples);
    for (int j = 0; j< numChannels; j++) {

        for (int i = 0; i < numSamples; i++ ) {

                iter = numSamples - i;
                for ( int k = iter; k < numSamples; k++ ) {

                    aucorr.at ( i ) += inputData[ j ][ k - iter ] * inputData[ j ][ k ];

                }
            
        }

        float maxVal=0.0;

        for ( int i = 1; i < aucorr.size() - 1; i++ ) {
            if ( aucorr[i-1] < aucorr[i] && aucorr[i] >= aucorr[i+1] ) {
                if ( aucorr[i] >= maxVal ) {
                        maxVal   = aucorr[i];
                        endIndex = i;
                }
            }
        }

        if (startIndex != endIndex) {
            frequency = sampleRate/(numSamples-endIndex);
        }
        
    }
    aucorr.clear();

    if ( frequency> 1500) { freq =  0.0f;      }
    else                  { freq = frequency; }

}


void SimpleCorrelation::writeTheFile(std::vector<float>* vect,const char *fileName) {
    std::ofstream outputFile(fileName);
    std::ostream_iterator<float> outputStream(outputFile,"\n");
    std::copy(vect->begin(),vect->end(),outputStream);
}


//____________________________________________________________________________________
//_____________________________**********************_________________________________


#if MY_UNIT_TESTS

class SimpleCorrelationTests  : public UnitTest
{
public:
    SimpleCorrelationTests() : UnitTest ("SimpleCorrelation"),
    _ppfInputData( new float*[3]),
    _freq(0),
    _sampleRate(44100),
    _numSamples(1000),
    _numChannels(3),
    testObj( new SimpleCorrelation() )
    {
        testObj = new SimpleCorrelation();
        
        setVal( _ppfInputData, 0, "init");
        
    }
    
    ~SimpleCorrelationTests() { delete testObj; }
    
    void runTest() override
    {
        beginTest ("ZeroCheck");
        
        testObj->correlate( (const float**) _ppfInputData, _freq,
                           _numSamples, _numChannels, _sampleRate );
        
        expect(_freq == 0);
        
        beginTest ("DC Check");
        
        setVal( _ppfInputData, 1.5, "set");
        
        testObj->correlate( (const float**) _ppfInputData, _freq,
                           _numSamples, _numChannels, _sampleRate );
        
        expect(_freq == 0 );
    }
private:
    float **_ppfInputData,_freq;
    int _sampleRate,_numSamples,_numChannels;
    
    SimpleCorrelation *testObj;
    
    //private Function
    void setVal( float **input, int setValue, const char *string) {
        
        
        if( strcmp("init",string) == 0 ){
            
            for( int c = 0; c<_numChannels; c++ ) {
                _ppfInputData[c] = new float[1000];
                std::fill(_ppfInputData[c],_ppfInputData[c]+1000,0);
            }
            
        }
        else if( strcmp("set",string) == 0 ){
            
            for( int c = 0; c<_numChannels; c++ ) {
                _ppfInputData[c] = new float[1000];
                std::fill(_ppfInputData[c],_ppfInputData[c]+1000,0);
            }
        }
    }
};

static SimpleCorrelationTests simpleCorrelationTest;

#endif
