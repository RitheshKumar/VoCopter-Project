 //
//  AudioListener.cpp
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 9/8/15.
//
//

#include "AudioListener.h"

void AudioListener::audioDeviceIOCallback (const float** inputChannelData, int numInputChannels,
        float** outputChannelData, int numOutputChannels,
        int numSamples)
{
    //generating a sine wave
    float sineWave[numSamples];
    for (int i=0; i<numSamples; i++)
        sineWave[i]=(float) std::sin(2*double_Pi*50*i);
    int delay = 256*100;
    aucorr.resize(2*numSamples-1);
    x1.resize(2*numSamples-1); x2.resize(2*numSamples-1);


    if (isListening) {
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

                writeTheFile(&aucorr,"./aucorr.txt",numSamples);//*/

                if(delay>numSamples) {
                    std::copy(delayBuffer.end()-delay,delayBuffer.end()-delay+numSamples,outputChannelData[i]);
                    delay-=numSamples; }
                else {
                    std::copy(delayBuffer.end()-numSamples,delayBuffer.end(),outputChannelData[i]);  }
            } 
        } }
    else
    {
        // We need to clear the output buffers, in case they're full of junk..
        for (int i = 0; i < numOutputChannels; ++i)
            if (outputChannelData[i] != nullptr)
                FloatVectorOperations::clear (outputChannelData[i],numSamples);
    }
}

AudioListener::AudioListener() : frequency(0.0), backgroundThread ("Audio Recorder Thread"),activeWriter (nullptr)
{
    isListening = false;
    delayBuffer.resize(88200);
}

AudioListener::~AudioListener()
{
    stopListening();
}

void AudioListener::stopListening()
{
    // First, clear this pointer to stop the audio callback from using our writer object..
    {
        const ScopedLock sl (writerLock);
        AudioListener::activeWriter = nullptr;
    }

    // Now we can delete the writer object. It's done in this order because the deletion could
    // take a little time while remaining data gets flushed to disk, so it's best to avoid blocking
    // the audio callback while this happens.
    threadedWriter = nullptr;
    isListening = false;

}

void AudioListener::startListening()
{
    AudioListener::stopListening();
    isListening = true;
}

void AudioListener::audioDeviceAboutToStart (AudioIODevice* device){}

void AudioListener::audioDeviceStopped() {}

void AudioListener::writeTheFile(std::vector<float>* vect,const char *fileName,int numSamples=0) {
    std::ofstream outputFile(fileName);
    std::ostream_iterator<float> outputStream(outputFile,"\n");
    //if (numSamples) {
    //    std::copy(vect,vect+numSamples,outputStream);
    //    //memcpy(&outputStream, vect, numSamples);
    //}
    //else
        std::copy(vect->begin(),vect->end(),outputStream);
}

/*void AudioListener::writeFile(std::vector<float>* vect,const char *fileName) {
    File fileOut(fileName);
    FileOutputStream fileStream(fileOut,vect->size()*sizeof(float));
    fileStream.write(vect,vect->size()*sizeof(float));
}*/


