//
//  NuObstacleComponent.cpp
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 1/31/16.
//
//

#include "NuObstacleComponent.h"
#include "fileRW.h"

NuObstacleComponent::NuObstacleComponent(std::string midiFilePath) : midiData(midiFilePath),
                                              cnt(0),
                                              obstacleLength(midiData.getMidiLen()),
                                              obstacleHeight( new float[midiData.getMidiLen()+1] )
{
//    int count = 0;
//    for (int i=0; i< midiData.getMidiLen(); i++) {
//        if( midiData.getMidiData(<#float *note#>)
//        count++;
//    }

    for (int i = 0; i<obstacleLength; i++) {
        midiData.getMidiData(&obstacleHeight[i]);
        obstacleHeight[i] = ( obstacleHeight[i] );//*100;//*0.8;
    }
    obstacleHeight[obstacleLength] =  -2;

    
    FileRW::fileWrite( obstacleHeight, obstacleLength, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/broomba.txt");


    //normalize noteValues
    normalizeRange(obstacleHeight);
    
    //The Value received from midiStorage and normalized range all tally with Matlab results
//    FileRW::fileWrite( obstacleHeight, obstacleLength, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/glissandoOut.txt");

    
}

NuObstacleComponent::~NuObstacleComponent( ) {
    delete [] obstacleHeight;
}

void NuObstacleComponent::normalizeRange(float *myArray) {
    
    float max = 0.0f, min = 127.0f;
    
    for (int i=0; i<obstacleLength; i++) {
        if ( myArray[i]>max) {
            max = myArray[i];
        }
        else if(myArray[i]<min && myArray[i] > 0) {
            min = myArray[i];
        }
    }
    
    //std::cout<<"Max: "<<max<<", Min: "<<min<<std::endl;
    
    for (int i=0; i<obstacleLength; i++) {
        myArray[i] = (myArray[i]-min)/(max-min);
        //std::cout<<myArray[i]<<std::endl;
    }
}


void NuObstacleComponent::paint(Graphics &g) {

    g.fillAll(Colours::black);
    g.setColour(Colours::cornflowerblue);
    
    for (int i=0; i<obstacleLength; i++) {
        if ( obstacleHeight[i] == -1 ) {
            continue;
        }

        //if ( obstacleHeight[i] < 0.5f ) {
        //    g.drawLine( i*400,       round(getHeight()/2)-obstacleHeight[i],
        //               (i+1)*400,    round(getHeight()/2)-obstacleHeight[i],
        //               130);
        //}
        //else {
        //    g.drawLine( i*400,       round(getHeight()/2)+obstacleHeight[i],
        //               (i+1)*400,    round(getHeight()/2)+obstacleHeight[i],
        //               130);
         //}
        if ( obstacleHeight[i] < 0.5f ) {
            g.drawLine( i*20,       round(getHeight()/2)-30*obstacleHeight[i],
                       (i+1)*20,    round(getHeight()/2)-30*obstacleHeight[i],
                       75);
            //std::cout<<round(getHeight()/2)-obstacleHeight[i];
        }
        else {
            g.drawLine( i*20,       round(getHeight()/2)+30*obstacleHeight[i],
                       (i+1)*20,    round(getHeight()/2)+30*obstacleHeight[i],
                       75);
            //std::cout<<round(getHeight()/2)+obstacleHeight[i];
        }

        std::cout<<std::endl;

    }

}


int NuObstacleComponent::getObstacleHeight() {
    if( *obstacleHeight!= -2) { //if ptr has not reached end of stream
        int temp = *obstacleHeight;
        if ( (cnt%400 == 0) && (cnt != 0)) {
            obstacleHeight++;
            cnt++;
        }
        else {
            cnt++;
        }
        return temp;
    }
    else {
        return *obstacleHeight;
    }
}

