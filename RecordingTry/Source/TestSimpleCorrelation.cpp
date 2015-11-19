//
//  TestSimpleCorrelation.cpp
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 17/11/15.
//
//

#include "TestSimpleCorrelation.h"

TestSimpleCorrelation::TestSimpleCorrelation()  
{
    audioFile = readFile  ( "./ACFAudio.txt" );
    //std::ostream_iterator<float> vectorOut (std::cout, "\n");
    //std::copy(audioFile.begin(), audioFile.end(), vectorOut);
    writeFile ( &audioFile, "./writtenAudio.txt" );
}

TestSimpleCorrelation::~TestSimpleCorrelation() {}


std::vector<float> TestSimpleCorrelation::readFile (const char *fileName ) {
    
    //File Handle String Constructed
    //std::string fileHandle;
    //fileHandle.append(_filePath);
    //fileHandle.append(fileName);
    
    //Read the file into a vector
    inputFile.open(fileName);
    
    if ( !inputFile) {
        
        std::cout<<"Given File doesn't exist/ wrong path"<< std::endl;
        return std::vector<float>();             //empty vector!!

    }
    else {

        std::istream_iterator<float> start( inputFile ), end;
        std::vector<float> inputVec ( start, end );
        //std::ostream_iterator<float> vectorOut (std::cout, "\n");
        //std::copy(inputVec.begin(), inputVec.end(), vectorOut);
        return inputVec;
    }
    
    inputFile.close();inputFile.clear();
    //start=inputFile;
}

void TestSimpleCorrelation::testFunction () {

    const int numSamples = 512*5; //audioFile.size();
    
    float **audioPointer = new float*[1];
    audioPointer[0]      = new float [numSamples];
    
    std::vector<float> testVec(numSamples);

    for (int i = 0; i < numSamples; i++ ) {

        audioPointer[0][i] = audioFile.at(i);
        testVec.at(i)      = audioPointer[0][i];

    }
    
    //std::ostream_iterator<float> myOut (std::cout, ",");
    //std::copy(testVec.begin(), testVec.end(), myOut);

    correlationObject.correlate ( audioPointer, numSamples, 1 );   //correlate expects a pointer to a pointer and
                                                                //this is not the same as a pointer to a 2D array!!

    std::cout<<"The frequency is: "<<correlationObject.getFrequency()<< std::endl;
}



void TestSimpleCorrelation::writeFile( std::vector<float>* vect, const char *fileName ) {

    std::ofstream outputFile(fileName);

    std::ostream_iterator<float> outputStream(outputFile,"\n");
    std::copy(vect->begin(),vect->end(),outputStream);

}
