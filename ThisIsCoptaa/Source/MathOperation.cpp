//
//  MathOperation.cpp
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 2/20/16.
//
//

#include "MathOperation.h"

float MathOperation::filterOutliers( float *pfInput, int iInputLen ) {
    float *pfInputCpy = new float[ iInputLen ] ;
    std::memcpy(pfInputCpy, pfInput, sizeof(float)*iInputLen);

    float      median = findMedian( pfInputCpy, iInputLen ),
          *pfCalcDiff = new float[iInputLen],
             tempDiff;

    for( int sample = 0; sample < iInputLen; sample++ ) {
        tempDiff = pfInput[sample] - median;
        if ( tempDiff >= 0 ) {
            pfCalcDiff[sample] = tempDiff;
        }
        else {
            pfCalcDiff[sample] = -tempDiff;
        }
    } 


    float meanAbsDev = findMedian( pfCalcDiff, iInputLen );
    for( int sample = 0; sample < iInputLen; sample++ ) {
        if( 5*meanAbsDev < pfCalcDiff[sample] ) {
            pfInput[sample] = -1;
        }
    }

    return meanAbsDev;

}

float MathOperation::findMeanAbsDev( float *pfInput, int iInputLen, float median ) {

    float *pfCalcDiff = new float[iInputLen],
          tempDiff;

    for( int sample = 0; sample < iInputLen; sample++ ) {
        tempDiff = pfInput[sample] - median;
        if ( tempDiff >= 0 ) {
            pfCalcDiff[sample] = tempDiff;
        }
        else {
            pfCalcDiff[sample] = -tempDiff;
        }
    }

    float meanAbsDev = findMedian( pfCalcDiff, iInputLen );
    return meanAbsDev;

}


float MathOperation::findMeanAbsDev( float *pfInput, int iInputLen ) {

    float *pfInputCpy = new float[ iInputLen ] ;
    std::memcpy(pfInputCpy, pfInput, sizeof(float)*iInputLen);

    float median = findMedian( pfInputCpy, iInputLen );
    float *pfCalcDiff = new float[iInputLen],
          tempDiff;

    for( int sample = 0; sample < iInputLen; sample++ ) {
        tempDiff = pfInput[sample] - median;
        if ( tempDiff >= 0 ) {
            pfCalcDiff[sample] = tempDiff;
        }
        else {
            pfCalcDiff[sample] = -tempDiff;
        }
    }

    float meanAbsDev = findMedian( pfCalcDiff, iInputLen );
    return meanAbsDev;

}

float MathOperation::findMedian( float *pfInput, int iInputLen ) {

    float *pfInputCpy = new float[ iInputLen ] ;
    std::memcpy(pfInputCpy, pfInput, sizeof(float)*iInputLen);

    float median;
    insertionSort( pfInputCpy, iInputLen );
    if ( iInputLen%2 == 0 ) {
       median = ( pfInputCpy[iInputLen/2] + pfInputCpy[iInputLen/2 - 1] ) / 2; 
    }
    else {
       median = pfInputCpy[ (int) iInputLen/2 ];
    }
    
    
    return median;
}


void MathOperation::insertionSort( float *pfInput, int iInputLen ) {
    //Insertion Sort!
    int temp = 0;
    for ( int i=1; i<iInputLen; i++ ) {

        for ( int j=0; j<i; j++ ) {

            if ( pfInput[i] < pfInput[j] ) {

                temp = pfInput[i];

                for ( int k=i; k>j; k--) {
                    pfInput[k] = pfInput[k-1];
                }
                pfInput[j] = temp;
                break;
                
            }

        }
    }
}


//____________________________________________________________________________________
//_____________________________**********************_________________________________


#if MY_UNIT_TESTS

class MathOperationTests  : public UnitTest
{
public:
    MathOperationTests() : UnitTest ("Math Operations"),
    testObj( new MathOperation )
    {
        
    }
    
    ~MathOperationTests() { 
        delete testObj; 
    }
    
    void runTest() override
    {
        float med;
        beginTest ("ZeroCheck"); {
            
            float inputVal[14] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            med = testObj->filterOutliers( inputVal, 14 );
            
            expect(med == 0);
        }
        
        
        beginTest ("Median Check"); {
            
            float inputVal[10] = { 4, 2, 3, 6, 9, 7, 10, 8, 5, 1 }; 
            med = testObj->findMedian( inputVal, 10 );
            expect(med == 5.5 );

            float inputVal2[7] = { 4, 2, 6, 1, 9, 2, 1 };
            
            med = testObj->findMedian( inputVal2, 7 );
            expect(med == 2.0 );
        

            med = testObj->filterOutliers( inputVal2, 7);
            expect(med == 1.0 );
            for ( int sample = 0; sample< 7; sample++ ) {
                std::cout<<inputVal2[sample]<<", ";
            } std::cout<<"\n";
        }
        
        
    }
private:
    
    MathOperation *testObj;
    
};

static MathOperationTests mathOperationTest;

#endif
    
