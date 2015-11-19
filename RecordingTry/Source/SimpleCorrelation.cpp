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
}

SimpleCorrelation::~SimpleCorrelation() {}


void SimpleCorrelation::correlate ( const float** inputData ) 
{
    //std::cout<<"_numSamples: "<<_numSamples<<std::endl;
    x1.resize(2*_numSamples-1);
    x2.resize(2*_numSamples-1);
    aucorr.resize(2*_numSamples-1);   //myTestVec.resize(_numSamples);


    for (int j = 0; j< _numChannels; j++) {

        for (int i = 0; i < _numSamples; i++ ) {

            x1.at(i)              = inputData[j][i];
            x2.at(i+_numSamples-1) = inputData[j][i];
            //myTestVec.at(i)       = inputData[j][i];
            
        }

        //writeTheFile(&myTestVec, "writtenAudio.txt", _numSamples );

        //std::cout<< "size of x1 : "<< x1.size() <<"\nsize of x2 : "<< x2.size() << std::endl;
        //std::cout<< "size of aucorr: "<<aucorr.size() << std::endl;

        for (int ii=0; ii<x2.size(); ii++)
        {
            for (int kk=0; kk<x2.size(); kk++) {
                aucorr[ii]+=x1[kk]*x2[kk];
            }
            std::rotate(x2.begin(),x2.end()-1,x2.end());
        }

        writeTheFile(&aucorr,"./aucorr.txt");

        startIndex            = std::distance(aucorr.begin(),std::max_element(aucorr.begin(),aucorr.end()));
        //myTestVec.resize( startIndex );
        //std::copy ( aucorr.begin(), aucorr.begin() + startIndex , myTestVec.begin() );
        //writeTheFile ( &myTestVec, "./x1.txt", startIndex);
        
        //std::cout<<"\naucorr.size() - startIndex - 1 = "<< aucorr.size() - startIndex - 1<< std::endl;

        diffVec.resize( aucorr.size() - startIndex ); //store differences of the aucorr sub-vector formed from the middle

        for ( int i = startIndex; i < aucorr.size() - 1; i++ ) {
            diffVec.at( i - startIndex ) = aucorr.at(i+1) - aucorr.at(i);
        }

        for ( int i = 0; i < diffVec.size() - 1; i++ ) {
            if ( ( diffVec[i] <= 0 && diffVec[i+1] <= 0 ) || ( diffVec[i] >= 0 && diffVec[i+1] >= 0 ) || ( diffVec[i] <= 0 && diffVec[i+1] >= 0 ) ) {
                continue;
            }
            else {
                endIndex = i+ startIndex + 1;
                break;
            }
        }


        if (startIndex != endIndex) {
            frequency = _sampleRate/(endIndex-startIndex);
        }
    
        //std::cout<<"\nFrequency: "<<frequency<<std::endl;
        
    }

}


void SimpleCorrelation::writeTheFile(std::vector<float>* vect,const char *fileName) {
    std::ofstream outputFile(fileName);
    std::ostream_iterator<float> outputStream(outputFile,"\n");
    std::copy(vect->begin(),vect->end(),outputStream);
}
