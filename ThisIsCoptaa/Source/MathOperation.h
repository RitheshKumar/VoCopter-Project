//
//  MathOperation.h
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 2/19/16.
//
//

#ifndef ThisIsCoptaa_MathOperation_h
#define ThisIsCoptaa_MathOperation_h

#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>
#include <string.h>

class MathOperation {
public:
    MathOperation(){}
    ~MathOperation(){}

    static void normalize( float *pfInput, int iInputLen );
    static float filterOutliers( float *pfInput, int &iInputLen );
    static float findMedian( float *pfInput, int iInputLen );
    static float findMeanAbsDev( float *pfInput, int iInputLen );
    static float findMeanAbsDev( float *pfInput, int iInputLen, float median );

private:
    static void insertionSort ( float *pfInput, int iInputLen );
};

#endif
