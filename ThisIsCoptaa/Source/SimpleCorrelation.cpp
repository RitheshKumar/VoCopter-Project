//
//  SimpleCorrelation.cpp
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 9/8/15.
//
//

#include "SimpleCorrelation.h"

SimpleCorrelation::SimpleCorrelation( int iMaxBlockSize, int iNumChannels, float fSampleRate )  :
                                                                                frequency (0.0),
                                                                               _iNumChannels(iNumChannels),
                                                                               _iAcfBufLen(2* iMaxBlockSize - 1),
                                                                               _ppfAucorr( new float*[iNumChannels] ),
                                                                               _fSampleRate( fSampleRate ),
                                                                               _fFrequency(0.0f)
{

    iter   = 0;
    peakIdx.resize(0);

    maxima.resize(0);

    for( int c=0; c<iNumChannels; c++ ) {
        _ppfAucorr[c] = new float[ _iAcfBufLen ];
    }

}

SimpleCorrelation::~SimpleCorrelation() {

    for( int c=0; c<_iNumChannels; c++ ) {
        delete [] _ppfAucorr[c];
    }
    delete [] _ppfAucorr;

}



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

void SimpleCorrelation::correlate2 ( const float** inputData, float &freq, int numSamples )
{

    int acfSize = 2*numSamples-1;
    for (int c = 0; c< _iNumChannels; c++) {


        for ( int i=numSamples-1,cnt = 0; cnt<numSamples; i--, cnt++ ) {
            for( int j=0; j<numSamples; j++ ) {
                _ppfAucorr[c][cnt+j] += inputData[c][i]*inputData[c][j];
            }
        }

        float maxVal=0.0;

        for ( int i = 1; i < acfSize - 1; i++ ) {
            if ( _ppfAucorr[c][i-1] < _ppfAucorr[c][i] && _ppfAucorr[c][i] >= _ppfAucorr[c][i+1] ) {
                if ( _ppfAucorr[c][i] >= maxVal ) {
                        maxVal   = _ppfAucorr[c][i];
                        endIndex = i;
                }
            }
        }

        if (startIndex != endIndex) {
            freq = _fSampleRate/(numSamples-endIndex);
        }
        
    }

    FileRW::fileWrite( _ppfAucorr, _iAcfBufLen, 1, (char *)"CorrelationOutput.txt" );

    if ( freq> 1500) { freq =  0.0f;  }

    reset();

}


void SimpleCorrelation::reset() {
    for ( int c = 0; c < _iNumChannels; c++ ) {
        for ( int sample = 0; sample < _iAcfBufLen; sample++ ) {
            _ppfAucorr[c][sample] = 0.0f;
        }
    }
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
                               _numChannels(3)
    {
    
        testObj = new SimpleCorrelation(_numSamples, _numChannels, _sampleRate);
        setVal( _ppfInputData,"init");
        
    }
    
    ~SimpleCorrelationTests() { delete testObj; }
    
    void runTest() override
    {
        beginTest ("ZeroCheck");
        
        testObj->correlate2( (const float**) _ppfInputData, _freq, _numSamples );
        
        expect(_freq == 0);
        
        beginTest ("DC Check");
        
        setVal( _ppfInputData, "set", 1.5f );
        
        testObj->correlate2( (const float**) _ppfInputData, _freq, _numSamples );
        
        expect(_freq == 0 );
        
        
        beginTest("Write Correlated Output");
        FileRW::fileWrite( _ppfInputData, _numSamples, 1, (char *)"inputSample.txt" );
        testObj -> correlate2( (const float**) _ppfInputData, _freq, _numSamples);

        beginTest("Write Audio Correlated Output");
        int numAudioSamples = 0;

        FileRW::fileRead( _ppfAudioFile, numAudioSamples, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/audioIn.txt");
        FileRW::fileWrite( _ppfAudioFile, numAudioSamples, 1, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/audioOut.txt");


        //testObj -> correlate2( (const float**) _pfAudioFile, _freq, numAudioSamples);
    }
private:
    float **_ppfInputData, _freq, **_ppfAudioFile;
    int _sampleRate,_numSamples,_numChannels;
    
    SimpleCorrelation *testObj;
    
    //private Function
    void setVal( float **input, const char *string, float setValue = 0) {
        
        
        if( strcmp("init",string) == 0 ){
            
            for( int c = 0; c<_numChannels; c++ ) {
                _ppfInputData[c] = new float[1000];
                std::fill(_ppfInputData[c],_ppfInputData[c]+1000, setValue);
            }
            
        }
        else if( strcmp("set",string) == 0 ){
            
            for( int c = 0; c<_numChannels; c++ ) {
                std::fill(_ppfInputData[c],_ppfInputData[c]+1000, setValue);
            }
        }
    }
};

static SimpleCorrelationTests simpleCorrelationTest;

#endif
