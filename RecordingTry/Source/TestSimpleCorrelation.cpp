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
    correlationObject = new SimpleCorrelation(  44100, 1024, 1 );
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

    const float *ptr     = &( *( audioFile.begin() ) );
    const float **audioPointer = &ptr;

    correlationObject->correlate ( audioPointer );   //correlate expects a pointer to a pointer and
                                                     //this is not the same as a pointer to a 2D array!!

    std::cout<<"The frequency is: "<<correlationObject->getFrequency()<< std::endl;
}



void TestSimpleCorrelation::writeFile( std::vector<float>* vect, const char *fileName ) {

    std::ofstream outputFile(fileName);

    std::ostream_iterator<float> outputStream(outputFile,"\n");
    std::copy(vect->begin(),vect->end(),outputStream);

}
