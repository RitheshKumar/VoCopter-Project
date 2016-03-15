//
//  NuObstacleComponent.cpp
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 1/31/16.
//
//

#include "NuObstacleComponent.h"
#include "fileRW.h"



NuObstacleComponent::NuObstacleComponent(char *midiFilePath) : midiData(midiFilePath),
                                                               pathWidth(140),
                                                               pathHeight(75),
                                                               pathPosition(60)
{
//    int count = 0;
//    for (int i=0; i< midiData.getMidiLen(); i++) {
//        if( midiData.getMidiData(<#float *note#>)
//        count++;
//    }

    obstacleLength = midiData.getMidiLen();
    int midiLen = midiData.getMidiLen() + 1;
//    float *randomVar  = new float[ midiLen ];
    obstacleHeight =  new float[ midiLen ];

    for (int i = 0; i<obstacleLength; i++) {
        midiData.getMidiData(&obstacleHeight[i]);
        obstacleHeight[i] = ( obstacleHeight[i] );//*100;//*0.8;
    }
    obstacleHeight[obstacleLength] =  -2;

    
//    FileRW::fileWrite( obstacleHeight, obstacleLength, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/broomba.txt");


    //normalize noteValues
    normalizeRange(obstacleHeight);
    
    //The Value received from midiStorage and normalized range all tally with Matlab results
    for (int i = 0; i<obstacleLength; i++) {
        std::cout<<obstacleHeight[i]<<std::endl;
    }
//    FileRW::fileWrite( obstacleHeight, obstacleLength, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/glissandoOut.txt");

    
}

NuObstacleComponent::~NuObstacleComponent( ) {
    delete [] obstacleHeight;
    obstacleHeight = 0;
}

void NuObstacleComponent::normalizeRange(float *myArray) {
    
    float max = 0.0f, min = 127.0f;
    
    for (int i=0; i<obstacleLength; i++) {
        if ( myArray[i]>max) {
            max = myArray[i];
        }
        if(myArray[i]<min && myArray[i] > 0) {
            min = myArray[i];
        }
    }
    
    std::cout<<"Max: "<<max<<", Min: "<<min<<std::endl;
    
    for (int i=0; i<obstacleLength; i++) {
        myArray[i] = (myArray[i]-min)/(max-min);
        //std::cout<<myArray[i]<<std::endl;
    }
}

float prevHeight;


void NuObstacleComponent::paint(Graphics &g) {

    g.fillAll(Colours::black);
    g.setColour(Colours::cornflowerblue);
    
    prevHeight = 0.f;
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
        //    g.drawLine( i*400,       round(getHeight()/2)+[i],
        //               (i+1)*400,    round(getHeight()/2)+obstacleHeight[i],
        //               130);
         //}
//        if ( obstacleHeight[i] < 0.5f ) {
            g.drawLine( i*pathWidth,       round(getHeight()/2)+pathPosition*(1-obstacleHeight[i]),
                       (i+1)*pathWidth,    round(getHeight()/2)+pathPosition*(1-obstacleHeight[i]),
                       pathHeight);
//            g.drawLine(i*(1.f*pathWidth/2.f),      prevHeight,
//                       (i+1)*(1.f*pathWidth/2.f), round(getHeight()/2)+pathPosition*(1-obstacleHeight[i]),
//                       pathHeight);
//            prevHeight = round(getHeight()/2)+pathPosition*(1-obstacleHeight[i]);
//            //std::cout<<round(getHeight()/2)-obstacleHeight[i];
//        }
//        else {
//            g.drawLine( i*pathWidth,       round(getHeight()/2)-pathPosition*obstacleHeight[i],
//                       (i+1)*pathWidth,    round(getHeight()/2)-pathPosition*obstacleHeight[i],
//                       pathHeight);
//            g.drawLine(i*(pathWidth/2.f),      prevHeight,
//                       (i+1)*(pathWidth/2.f), round(getHeight()/2)-pathPosition*obstacleHeight[i],
//                       pathHeight);
//            prevHeight =round(getHeight()/2)-pathPosition*obstacleHeight[i];
//            //std::cout<<round(getHeight()/2)+obstacleHeight[i];
//        }

//        std::cout<<std::endl;

    }

}

int nthNote = 0,cnt=0;

int NuObstacleComponent::getObstacleHeight() {
    std::cout<<obstacleHeight[nthNote]<<std::endl;
    if( *obstacleHeight!= -2) { //if ptr has not reached end of stream
        if ( (cnt%(pathWidth/5) == 0) && (cnt != 0)) { //pathWidth
            nthNote++;
            cnt++;
        }
        else {
            cnt++;
        }
        return obstacleHeight[nthNote];
    }
    else {
        return obstacleHeight[nthNote];
    }
}

