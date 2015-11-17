//
//  SimpleCorrelation.cpp
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 9/8/15.
//
//

#include "SimpleCorrelation.h"

SimpleCorrelation::SimpleCorrelation() : frequency(0.0) 
{
    delayBuffer.resize(88200);
}

SimpleCorrelation::~SimpleCorrelation() {}


void SimpleCorrelation::correlate ( float** inputData, int numSamples ) 
{
    myTestVec.resize(numSamples);

    for (int i = 0; i < numSamples; i++ ) {
        myTestVec.at(i) = inputData[0][i];
    }

    std::ostream_iterator<float> myOut ( std::cout, "\n" );
    std::copy ( myTestVec.begin(), myTestVec.end(), myOut);  //Yes, I do receive the audioFile here fully.
    /*aucorr.resize(2*numSamples-1);
    x1.resize(2*numSamples-1); x2.resize(2*numSamples-1);
    myTestVec.resize(numSamples);


    for (int i = 0; inputData[i] != nullptr; i++) {

            for (int j=0; j < numSamples; j++) {
                x1.at(j) = 10.0f*inputData[i][j];
                myTestVec.at(j) = 10.0f*inputData[i][j];
            }

            std::copy ( x1.begin(), x1.begin()+numSamples, x2.begin()+numSamples );

            writeTheFile ( &x1, "./x1.txt", 2*numSamples-1 );
            writeTheFile ( &x2, "./x2.txt", 2*numSamples-1 );

            for (int ii=0; ii<x2.size(); ii++)
            {
                for (int kk=0; kk<=x2.size(); kk++) {
                    aucorr[ii]+=x1[kk]*x2[kk];
                }
                std::rotate(x2.begin(),x2.end()-1,x2.end());
            }
            writeTheFile(&myTestVec,"./inputChannel.txt",numSamples);
            writeTheFile(&aucorr,"./aucorr.txt",numSamples);

            startIndex            = std::distance(aucorr.begin(),std::max_element(aucorr.begin(),aucorr.end()));
            aucorr [ startIndex ] = 0.0f;
            std::cout<<"Aucorr [startIndex] : "<<aucorr[startIndex]<<std::endl;
            //minIndex =  std::distance(aucorr.begin(),std::min_element(aucorr.begin()+startIndex,aucorr.end())); //error is here
            endIndex              =  std::distance ( aucorr.begin()+startIndex, 
                                                     std::max_element ( aucorr.begin()+startIndex, aucorr.end() ) );
            endIndex              += startIndex;
            std::cout << startIndex << "," << endIndex;

            if (startIndex != endIndex) {
                frequency = 44100/(endIndex-startIndex);
            }
        
            std::cout<<"\nFrequency: "<<frequency<<std::endl;

            /*std::copy( &inputData[numInputChannels-1][0], &inputData[numInputChannels-1][0]+numSamples, x2.begin()+numSamples );
            std::copy(x2.end()-numSamples, x2.end(), x1.begin());
            std::copy( &inputData[numInputChannels-1][0], &inputData[numInputChannels-1][0]+numSamples, myTestVec.begin()+numSamples );
            
            //writeTheFile(&myTestVec,"./inputChannel.txt",numSamples);
            writeTheFile(&aucorr,"./x1.txt",2*numSamples-1);
            writeTheFile(&aucorr,"./x2.txt",2*numSamples-1);

    }*/
}


void SimpleCorrelation::writeTheFile(std::vector<float>* vect,const char *fileName,int numSamples=0) {
    std::ofstream outputFile(fileName);
    std::ostream_iterator<float> outputStream(outputFile,"\n");
    std::copy(vect->begin(),vect->end(),outputStream);
}
