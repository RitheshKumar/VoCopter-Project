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
    isTracking = false;
    delayBuffer.resize(88200);
}

SimpleCorrelation::~SimpleCorrelation()
{
    stopTracking();
}
void SimpleCorrelation::audioDeviceIOCallback (const float** inputChannelData, int numInputChannels,
        float** outputChannelData, int numOutputChannels,
        int numSamples)
{
    //std::cout<<"numSamples:"<<numSamples<<std::endl;
    aucorr.resize(2*numSamples-1);
    x1.resize(2*numSamples-1); x2.resize(2*numSamples-1);


    if (isTracking) {
        for (int i = 0; i < numOutputChannels; ++i) {
            if (inputChannelData[i] != nullptr) {
                std::copy( &inputChannelData[numInputChannels-1][0], &inputChannelData[numInputChannels-1][0]+numSamples, x2.begin()+numSamples-1 );
                std::copy(x2.end()-numSamples, x2.end(), x1.begin());
                
                writeTheFile(&aucorr,"./x1.txt",2*numSamples-1);
                writeTheFile(&aucorr,"./x2.txt",2*numSamples-1);
                
                for (int ii=0; ii<x2.size(); ii++)
                {
                    for (int kk=0; kk<=x2.size(); kk++) {
                        aucorr[ii]+=x1[kk]*x2[kk];
                    }
                    std::rotate(x2.begin(),x2.end()-1,x2.end());
                }

                writeTheFile(&aucorr,"./aucorr.txt",numSamples);

                startIndex            = std::distance(aucorr.begin(),std::max_element(aucorr.begin(),aucorr.end()));
                aucorr [ startIndex ] = 0.0f;
                std::cout<<"Aucorr [startIndex] : "<<aucorr[startIndex]<<std::endl;
                //minIndex =  std::distance(aucorr.begin(),std::min_element(aucorr.begin()+startIndex,aucorr.end())); //error is here
                endIndex              =  std::distance(aucorr.begin()+startIndex,std::max_element(aucorr.begin()+startIndex,aucorr.end()));
                endIndex              += startIndex;
                std::cout << startIndex << "," << endIndex;
                if (startIndex != endIndex) {
                    frequency = 44100/(endIndex-startIndex);
                }
            
                std::cout<<"\nFrequency: "<<frequency<<std::endl;

            } 
        } }
    else
    {
        // We need to clear the output buffers, in case they're full of junk..
        for (int i = 0; i < numOutputChannels; ++i)
            if (outputChannelData[i] != nullptr)
                FloatVectorOperations::clear (outputChannelData[i],numSamples);
    }//*/
    /*aucorr.resize(2*numSamples-1);
    x1.resize(2*numSamples-1); x2.resize(2*numSamples-1);


    if (isTracking) {
        for (int i = 0; i < numOutputChannels; ++i) {
            if (inputChannelData[i] != nullptr) {
                std::copy(&inputChannelData[numInputChannels-1][0],&inputChannelData[numInputChannels-1][0]+numSamples,back_inserter(delayBuffer));
                
                writeTheFile(&x1,"./x1.txt",numSamples);                
                writeTheFile(&x2,"./x2.txt",numSamples);                
                
                //writeTheFile(&delayBuffer+delayBuffer.size()-numSamples,"./inputData.txt",numSamples);
                std::vector<float> temp(delayBuffer.end()-numSamples,delayBuffer.end());
                writeTheFile(&temp,"./inputData.txt",numSamples);
                
                std::copy(temp.begin(),temp.end(),x1.begin()+temp.size()-1);
                std::copy(temp.begin(),temp.end(),x2.begin());
                
                ///*
                for (int ii=0; ii<x2.size(); ii++)
                {
                    for (int kk=0; kk<=x2.size(); kk++) {
                        aucorr[ii]+=x1[kk]*x2[kk];
                    }
                    //if (aucorr[ii]>0)
                    //    Logger::writeToLog(std::to_string(aucorr[ii]));
                    std::rotate(x2.begin(),x2.end()-1,x2.end());
                }
                startIndex = std::distance(aucorr.begin(),std::max_element(aucorr.begin(),aucorr.end()));
                minIndex =  std::distance(aucorr.begin(),std::min_element(aucorr.begin()+startIndex,aucorr.end()));
                endIndex =  std::distance(aucorr.begin(),std::max_element(aucorr.begin()+minIndex,aucorr.end()));
                frequency = 44100/(endIndex-startIndex);
            
                Logger::writeToLog(std::to_string(frequency)+"\n");

                writeTheFile(&aucorr,"./aucorr.txt",numSamples);

                std::copy(delayBuffer.end()-numSamples,delayBuffer.end(),outputChannelData[i]);  }
            } 
        } 
    else
    {
        // We need to clear the output buffers, in case they're full of junk..
        for (int i = 0; i < numOutputChannels; ++i)
            if (outputChannelData[i] != nullptr)
                FloatVectorOperations::clear (outputChannelData[i],numSamples);
    }//*/
}



void SimpleCorrelation::stopTracking()
{

    isTracking = false;

}

void SimpleCorrelation::startTracking()
{
    SimpleCorrelation::stopTracking();
    isTracking = true;
}

void SimpleCorrelation::audioDeviceAboutToStart (AudioIODevice* device){}

void SimpleCorrelation::audioDeviceStopped() {}

void SimpleCorrelation::writeTheFile(std::vector<float>* vect,const char *fileName,int numSamples=0) {
    std::ofstream outputFile(fileName);
    std::ostream_iterator<float> outputStream(outputFile,"\n");
    std::copy(vect->begin(),vect->end(),outputStream);
}



