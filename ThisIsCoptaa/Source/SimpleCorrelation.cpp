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
                                                                               _fFrequency(0.0f),
                                                                               curFreq(0),
                                                                               prevFreq(0)
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
    _ppfAucorr = 0;

}



void SimpleCorrelation::correlate ( const float** inputData, float &freq, int &midiNote, int numSamples )
{

    int acfSize = 2*numSamples-1;
    startIndex = numSamples;

    for (int c = 0; c< _iNumChannels; c++) {


        for ( int i=numSamples-1,cnt = 0; cnt<numSamples; i--, cnt++ ) {
            for( int j=0; j<numSamples; j++ ) {
                _ppfAucorr[c][cnt+j] += inputData[c][i]*inputData[c][j];
            }
        }

        float maxVal=0.0;


        for ( int i = startIndex; i < acfSize - 1; i++ ) {
            if ( _ppfAucorr[c][i-1] < _ppfAucorr[c][i] && _ppfAucorr[c][i] >= _ppfAucorr[c][i+1] ) {
                if ( _ppfAucorr[c][i] >= maxVal ) {
                        maxVal   = _ppfAucorr[c][i];
                        endIndex = i;
                }
            }
//            _ppfAucorr[c][i-1] = 0.0f; //Instead do the resetting here!
        }

        if (startIndex != endIndex && endIndex != 0) {
            freq = _fSampleRate/(endIndex+1-numSamples); //since indexing starts from 0
        }

        
    }

//    FileRW::fileWrite( _ppfAucorr, _iAcfBufLen, 1, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/CorrelationOutput.txt" );
//    std::cout<< freq <<", ";
    midiNote = roundFloatToInt( 69 + 12*log2f(freq/440.f) ); //std::cout<<midiNote<<std::endl;
    midiNote = midiNote%12; //std::cout<<midiNote<<std::endl;
//    if (midiNote == 7) {
//        std::cout<<"G";
//    }
//    else if( midiNote == 5) {
//        std::cout<<"F";
//    }
//    else if (midiNote < 9){
//        std::cout<<(char) ( 67 + midiNote/2);
//        if (midiNote == 1 || midiNote == 3 || midiNote == 6 || midiNote == 8) {
//            std::cout<<"#";
//        }
//        
//    }
//    else  {
//        std::cout<< (char) ( 65 + (midiNote%3)/2 );
//        if (midiNote == 10) {
//            std::cout<<"#";
//        }
//    }
   
//    std::cout<<", "<<midiNote<<std::endl;

    //if ( freq> 1500) { freq =  0.0f;  }

//    reset(); //This function uses a lot of CPU!!

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
                               _numSamples(4096),
                               _numChannels(3)
    {
    
        testObj = new SimpleCorrelation(_numSamples, _numChannels, _sampleRate);
        setVal( _ppfInputData,"init");
        
    }
    
    ~SimpleCorrelationTests() { delete testObj; testObj = 0; }
    
    void runTest() override
    {
        beginTest ("ZeroCheck"); {

            testObj->correlate( (const float**) _ppfInputData, _freq, _numSamples );
            
            expect(_freq == 0);
        }
        

        beginTest ("DC Check"); {
        
            setVal( _ppfInputData, "set", 1.5f );
            
            testObj->correlate( (const float**) _ppfInputData, _freq, _numSamples );
            
            expect(_freq == 0 );
        }
        

        beginTest("Write Audio Correlated Output"); {
 
            FileRW::fileRead( _ppfAudioFile, _numSamples, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/audioIn.txt");

            testObj -> correlate( (const float**) _ppfAudioFile, _freq, _numSamples);

            expect(_freq == 441);

        }

    }
private:
    float **_ppfInputData, _freq, **_ppfAudioFile;
    int _sampleRate,_numSamples,_numChannels;
    
    SimpleCorrelation *testObj;
    
    //private Function
    void setVal( float **input, const char *string, float setValue = 0) {
        
        
        if( strcmp("init",string) == 0 ){
            
            for( int c = 0; c<_numChannels; c++ ) {
                _ppfInputData[c] = new float[_numSamples];
                std::fill(_ppfInputData[c],_ppfInputData[c]+_numSamples, setValue);
            }
            
        }
        else if( strcmp("set",string) == 0 ){
            
            for( int c = 0; c<_numChannels; c++ ) {
                std::fill(_ppfInputData[c],_ppfInputData[c]+_numSamples, setValue);
            }
        }
    }
};

static SimpleCorrelationTests simpleCorrelationTest;

#endif
