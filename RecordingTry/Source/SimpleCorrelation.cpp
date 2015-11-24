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
                                       _numChannels ( numChannels ), frequency (0.0)             {
    peakIdx.resize(0);
    maxima.resize(0);
    aucorr.resize(_numSamples);   //myTestVec.resize(_numSamples);
}

SimpleCorrelation::~SimpleCorrelation() {}


void SimpleCorrelation::correlate ( const float** inputData ) 
{
    //std::cout<<"_numSamples: "<<_numSamples<<std::endl;

    for (int j = 0; j< _numChannels; j++) {

        for (int i = 0; i < _numSamples; i++ ) {

                int iter = _numSamples - i;
                for ( int k = iter; k < _numSamples; k++ ) {

                    aucorr.at ( i ) += inputData[ j ][ k - iter ] * inputData[ j ][ k ];

                }
            
        }

        writeTheFile(&aucorr,"./aucorr.txt");

        startIndex            = std::distance(aucorr.begin(),std::max_element(aucorr.begin(),aucorr.end()));
        //myTestVec.resize( startIndex );
        //std::copy ( aucorr.begin(), aucorr.begin() + startIndex , myTestVec.begin() );
        //writeTheFile ( &myTestVec, "./x1.txt", startIndex);
        
        //std::cout<<"\naucorr.size() - startIndex - 1 = "<< aucorr.size() - startIndex - 1<< std::endl;

        /*//moving average filter of windowSize
        int windowSize = 5;
        int windowIdx  = (int) windowSize/2;

        for ( int i = windowIdx; i < _numSamples - windowIdx; i++ ) {
            
            aucorr.at(i) = std::accumulate ( &aucorr.at( i-windowIdx ), &aucorr.at( i+windowIdx ), 0.0 ) / windowSize;
        }*/

        /*diffVec.resize( aucorr.size() - startIndex ); //store differences of the aucorr sub-vector formed from the middle

        for ( int i = startIndex; i < aucorr.size() - 1; i++ ) {
            diffVec.at( i - startIndex ) = aucorr.at(i+1) - aucorr.at(i);
        }

        for ( int i = 0; i < diffVec.size() - 1; i++ ) {
            if ( ( diffVec[i] <= 0 && diffVec[i+1] <= 0 ) || ( diffVec[i] >= 0 && diffVec[i+1] >= 0 ) || ( diffVec[i] <= 0 && diffVec[i+1] >= 0 ) ) {
                continue;
            }
            else {
                peakIdx.push_back( i+ startIndex + 1);
                break;
            }
        }

        endIndex = *std::max_element ( peakIdx.begin(), peakIdx.end());*/
        
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
            frequency = _sampleRate/(startIndex-endIndex);
        }
    
        std::cout<<"startIndex ="<<startIndex<<"\nendIndex ="<<endIndex<<std::endl;
        //std::cout<<"\nFrequency: "<<frequency<<std::endl;
        
    }

}


void SimpleCorrelation::writeTheFile(std::vector<float>* vect,const char *fileName) {
    std::ofstream outputFile(fileName);
    std::ostream_iterator<float> outputStream(outputFile,"\n");
    std::copy(vect->begin(),vect->end(),outputStream);
}
