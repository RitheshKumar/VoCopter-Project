//
//  NuObstacleComponent.cpp
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 1/31/16.
//
//

#include "NuObstacleComponent.h"

NuObstacleComponent::NuObstacleComponent( ) : cnt(0),
                                              obstacleLength(midiData.getMidiLen()),
                                              obstacleHeight( new float[midiData.getMidiLen()+1] )
{
    
    
//    int height = 400;//, width = 600;

    for (int i = 0; i<obstacleLength; i++) {
        midiData.getMidiData(&obstacleHeight[i]);
        obstacleHeight[i] = ( obstacleHeight[i] );//*100;//*0.8;
        std::cout<<obstacleHeight[i]<<"\n";
    }
    std::cout<<std::endl;
//    obstacleHeight[0] = round(height/2) - 130/2;
//    obstacleHeight[1] = round(height/2) - 130/2 + 40;
//    obstacleHeight[obstacleLength] =  -1;
    
    //normalize noteValues
    normalizeRange(obstacleHeight);
    
}

NuObstacleComponent::~NuObstacleComponent( ) {
}

void NuObstacleComponent::normalizeRange(float *myArray) {
    
    float max = 0.0f,min = 20.0f;
    
    for (int i=0; i<obstacleLength; i++) {
        if ( myArray[i]>max) {
            max = myArray[i];
        }
        else if(myArray[i]<min) {
            min = myArray[i];
        }
    }
    
    std::cout<<"Max: "<<max<<", Min: "<<min<<std::endl;
    
    for (int i=0; i<obstacleLength; i++) {
        myArray[i] = (myArray[i]-min)*100/(max-min);
        std::cout<<myArray[i]<<std::endl;
    }
}


void NuObstacleComponent::paint(Graphics &g) {

    g.fillAll(Colours::black);
    g.setColour(Colours::cornflowerblue);
//    g.drawLine( 0, round(getHeight()/2), 400, round(getHeight()/2), 130 );
//    g.drawLine(400, round(getHeight()/2)+40, 800, round(getHeight()/2)+40, 130 );
    
    for (int i=0; i<obstacleLength; i++) {

        if ( obstacleHeight[i] < 0.5f ) {
            g.drawLine( i*400,       round(getHeight()/2)-obstacleHeight[i],
                       (i+1)*400,    round(getHeight()/2)-obstacleHeight[i],
                       130);
        }
        else {
            g.drawLine( i*400,       round(getHeight()/2)+obstacleHeight[i],
                       (i+1)*400,    round(getHeight()/2)+obstacleHeight[i],
                       130);
        }

    }

}


int NuObstacleComponent::getObstacleHeight() {
    if( *obstacleHeight!= -1) { //if ptr has not reached end of stream
        int temp = *obstacleHeight;
        if ( (cnt%400 == 0) && (cnt != 0)) {
            obstacleHeight++;
            cnt++;
        }
        else {
            cnt++;
        }
//        std::cout<<temp<<std::endl;
        return temp;
    }
    else {
//        std::cout<<*obstacleHeight<<std::endl;
        return *obstacleHeight;
    }
}

