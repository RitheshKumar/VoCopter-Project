#include "SimpleCorrelation.h"

void SimpleCorrelation::audioDeviceIOCallback (const float** inputChannelData, int numInputChannels,
        float** outputChannelData, int numOutputChannels,
        int numSamples)
{
    aucorr.resize(2*numSamples-1);
    x1.resize(2*numSamples-1); x2.resize(2*numSamples-1);


    if (isTracking) {
        for (int i = 0; i < numOutputChannels; ++i) {
            if (inputChannelData[i] != nullptr) {
                std::copy( &inputChannelData[numInputChannels-1][0], &inputChannelData[numInputChannels-1][0]+numSamples, outputChannelData[i]);
                
                for (int ii=0; ii<x2.size(); ii++)
                {
                    for (int kk=0; kk<=x2.size(); kk++) {
                        aucorr[ii]+=x1[kk]*x2[kk];
                    }
                    std::rotate(x2.begin(),x2.end()-1,x2.end());
                }

                startIndex            = std::distance(aucorr.begin(),std::max_element(aucorr.begin(),aucorr.end()));
                aucorr [ startIndex ] = 0.0f;
                //minIndex =  std::distance(aucorr.begin(),std::min_element(aucorr.begin()+startIndex,aucorr.end())); //error is here
                endIndex              =  std::distance(aucorr.begin()+startIndex,std::max_element(aucorr.begin(),aucorr.end()));
                std::cout << startIndex << "," << endIndex;
                frequency = 44100/(endIndex-startIndex);
            
                Logger::writeToLog(std::to_string(frequency)+"\n");

                writeTheFile(&aucorr,"./aucorr.txt",numSamples);

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

SimpleCorrelation::SimpleCorrelation() : frequency(0.0), backgroundThread ("Audio Listener Thread"), activeWriter (nullptr)
{
    isTracking = false;
    delayBuffer.resize(88200);
}

SimpleCorrelation::~SimpleCorrelation()
{
    stopTracking();
}

void SimpleCorrelation::stopTracking()
{
    // First, clear this pointer to stop the audio callback from using our writer object..
    {
        const ScopedLock sl (writerLock);
        SimpleCorrelation::activeWriter = nullptr;
    }

    // Now we can delete the writer object. It's done in this order because the deletion could
    // take a little time while remaining data gets flushed to disk, so it's best to avoid blocking
    // the audio callback while this happens.
    threadedWriter = nullptr;
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



