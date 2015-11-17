//
//  TestSimpleCorrelation.h
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 11/2/15.
//
//

#ifndef __RecordingTry__TestSimpleCorrelation__
#define __RecordingTry__TestSimpleCorrelation__

#include "../JuceLibraryCode/JuceHeader.h"
#include "SimpleCorrelation.h"

class TestSimpleCorrelation  
{
public:
    TestSimpleCorrelation ();
    ~TestSimpleCorrelation();

    //==============================================================================
    std::vector<float> readFile (const char *fileName ); //Function to read a file

    void testFunction ();

    void writeFile (std::vector<float>* vect, const char *fileName );

    //==============================================================================

private:
    std::vector<float> audioFile, frequency;
    std::ifstream inputFile;
    
    SimpleCorrelation correlationObject;

};

#endif /* defined(__RecordingTry__TestSimpleCorrelation__) */
