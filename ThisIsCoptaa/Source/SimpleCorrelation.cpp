//
//  SimpleCorrelation.cpp
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 9/8/15.
//
//

#include "SimpleCorrelation.h"

SimpleCorrelation::SimpleCorrelation( int sampleRate, int numSamples, int numChannels )
                                    :  _sampleRate  ( sampleRate ),  _numSamples ( numSamples ),
                                       _numChannels ( numChannels ),  frequency (0.0)            {

    iter   = 0;
    peakIdx.resize(0);
    maxima.resize(0);
    aucorr.resize(_numSamples);   //myTestVec.resize(_numSamples);
}

SimpleCorrelation::~SimpleCorrelation() {}


float SimpleCorrelation::correlate ( const float** inputData )
{

    aucorr.resize(_numSamples);
    for (int j = 0; j< _numChannels; j++) {

        for (int i = 0; i < _numSamples; i++ ) {

                iter = _numSamples - i;
                for ( int k = iter; k < _numSamples; k++ ) {

                    aucorr.at ( i ) += inputData[ j ][ k - iter ] * inputData[ j ][ k ];

                }
            
        }

        //writeTheFile(&aucorr,"./aucorr.txt");
        
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
            frequency = _sampleRate/(_numSamples-endIndex);
        }
    
        //std::cout<<"\nendIndex ="<<endIndex<<std::endl;
        //std::cout<<"\nFrequency: "<<frequency<<std::endl;
        
    }
    aucorr.clear();

    if ( frequency> 1500) { return 0.0f;      }
    else                  { return frequency; }

}


void SimpleCorrelation::writeTheFile(std::vector<float>* vect,const char *fileName) {
    std::ofstream outputFile(fileName);
    std::ostream_iterator<float> outputStream(outputFile,"\n");
    std::copy(vect->begin(),vect->end(),outputStream);
}
