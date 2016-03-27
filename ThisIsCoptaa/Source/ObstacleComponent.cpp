//
//  ObstacleComponent.cpp
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 1/31/16.
//
//

#include "ObstacleComponent.h"
#include "fileRW.h"


ObstacleComponent::ObstacleComponent( char *midiFilePath ) : midiData( midiFilePath ),
                                          pathWidth( 100 ),
                                          pathHeight( 75 ),
                                          pathPosition( 60 )
{
    obstacleLength = midiData.getMidiLen();

    obstacleHeight = new float[obstacleLength];
    for (int i = 0; i<obstacleLength; i++) {
        obstacleHeight[i] = midiData.getNote( i );
    }

    //Normalize noteValues
    normalizeRange( obstacleHeight );
}


ObstacleComponent::~ObstacleComponent( ) {

}

void ObstacleComponent::paint(Graphics &g) {

    g.fillAll(Colours::black);
    g.setColour(Colours::cornflowerblue);
    
    for ( int noteIdx=0; noteIdx < obstacleLength-1; noteIdx++ ) {
        if ( midiData.getNote(noteIdx) == -1 ) {
            continue;
//            g.drawLine( midiData.getTime( noteIdx )*pathWidth,      round(getHeight()/2)+pathPosition*(1-obstacleHeight[noteIdx]),
//                       midiData.getTime( noteIdx+1 )*pathWidth,    round(getHeight()/2)+pathPosition*(1-obstacleHeight[noteIdx]),
//                       getHeight());
        }
        else {
            
            g.drawLine( midiData.getTime( noteIdx )*pathWidth,      round(getHeight()/2)+pathPosition*(1-obstacleHeight[noteIdx]),
                        midiData.getTime( noteIdx+1 )*pathWidth,    round(getHeight()/2)+pathPosition*(1-obstacleHeight[noteIdx]),
                        pathHeight);

        }
    }

}


void ObstacleComponent::normalizeRange(float *myArray) {
    
    float max = 0.0f, min = 127.0f;
    
    for (int i=0; i<obstacleLength; i++) {
        if ( myArray[i]>max) {
            max = myArray[i];
        }
        if(myArray[i]<min && myArray[i] > 0) {
            min = myArray[i];
        }
    }
    
    
    for (int i=0; i<obstacleLength; i++) {
        myArray[i] = (myArray[i]-min)/(max-min);
    }

}
