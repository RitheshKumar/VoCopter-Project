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
                                                             timeIdx(0),
                                                             pathWidth( 200 ),
                                                             pathHeight( 25 ),
                                                             pathPosition( 60 )
{
    obstacleLength = midiData.getMidiLen();

    //Get the notes from midiStorage class
    obstacleHeight = new float[obstacleLength];
    for (int i = 0; i<obstacleLength; i++) {
        obstacleHeight[i] = midiData.getNote( i );
    }

    //Normalize noteValues
    noteToPixels( obstacleHeight );

}

float ObstacleComponent::getInitialHeight() {
    for ( int i=0; i<obstacleLength; i++){
        if( obstacleHeight[i] != -1){
            return obstacleHeight[i];
        }
    }
    return 0;
}

ObstacleComponent::~ObstacleComponent( ) {

}

void ObstacleComponent::paint(Graphics &g) {

    g.fillAll(Colours::black);
    
    bool firstNoteDrawn = false;
    float curTime, curNextTime;
    int offset = 0.95*900;
    Path interNotePath;
    
    g.setColour(Colours::skyblue);
    g.fillRect(0, 0, offset, getHeight());
    
    
    for ( int noteIdx=0; noteIdx < obstacleLength-1; noteIdx++ ) {

        curTime     = midiData.getTime(noteIdx);
        curNextTime = midiData.getTime( noteIdx+1 );
        
        if ( curTime*pathWidth + offset < (100 + time) && curNextTime*pathWidth + offset > (-800 + time) ) {

            if ( midiData.getNote(noteIdx) == -1 ) {
                //DrawInterNotes
                if( noteIdx!= obstacleLength-2 && firstNoteDrawn && ( curNextTime - curTime < 0.20f ) ){
                    interNotePath.addQuadrilateral(curTime*pathWidth + offset,     obstacleHeight[noteIdx-1]-pathHeight,
                                                   curNextTime*pathWidth + offset, obstacleHeight[noteIdx+1]-pathHeight,
                                                   curNextTime*pathWidth + offset, obstacleHeight[noteIdx+1]+pathHeight,
                                                   curTime*pathWidth + offset,     obstacleHeight[noteIdx-1]+pathHeight);
                    g.setColour(Colours::lightslategrey);
                    g.fillPath(interNotePath);
                    g.strokePath (interNotePath, PathStrokeType (0.5f));
                    

                }
                else if( noteIdx!= obstacleLength-2 && firstNoteDrawn && ( curNextTime - curTime > 0.20f ) ) {
                    Rectangle<int> pauseFill(curTime*pathWidth + offset, 0, (curNextTime-curTime)*pathWidth, getHeight());
                    g.fillCheckerBoard(pauseFill, 50, 15, Colours::darkgrey, Colours::black);
                    
                }

            }
            else {
                
                g.setColour(Colours::cornflowerblue);
                g.drawLine( curTime*pathWidth + offset,     obstacleHeight[noteIdx],
                            curNextTime*pathWidth + offset, obstacleHeight[noteIdx],
                            pathHeight*2 );
                firstNoteDrawn  = true;
            }
            
        }
        
    }
    
//    for ( int noteIdx=0; noteIdx < obstacleLength-1; noteIdx++ ) {
    

//        int noteIdx = 0;
//        
//        while ( curTime*pathWidth + offset < (100 + time) && curNextTime*pathWidth + offset > (-800 + time) && noteIdx < obstacleLength-1) {
//            
//            curTime     = midiData.getTime(noteIdx);
//            curNextTime = midiData.getTime( noteIdx+1 );
//            
//            if ( midiData.getNote(noteIdx) == -1 ) {
//                //DrawInterNotes
//                if( noteIdx!= obstacleLength-2 && firstNoteDrawn && ( curNextTime - curTime < 0.20f ) ){
//                    interNotePath.addQuadrilateral(curTime*pathWidth + offset,     obstacleHeight[noteIdx-1]-pathHeight,
//                                                   curNextTime*pathWidth + offset, obstacleHeight[noteIdx+1]-pathHeight,
//                                                   curNextTime*pathWidth + offset, obstacleHeight[noteIdx+1]+pathHeight,
//                                                   curTime*pathWidth + offset,     obstacleHeight[noteIdx-1]+pathHeight);
//                    g.setColour(Colours::lightslategrey);
//                    g.fillPath(interNotePath);
//                    g.strokePath (interNotePath, PathStrokeType (0.5f));
//                    
//                    
//                }
//                else if( noteIdx!= obstacleLength-2 && firstNoteDrawn && ( curNextTime - curTime > 0.20f ) ) {
//                    Rectangle<int> pauseFill(curTime*pathWidth + offset, 0, (curNextTime-curTime)*pathWidth, getHeight());
//                    g.fillCheckerBoard(pauseFill, 50, 15, Colours::darkgrey, Colours::black);
//                    
//                }
//                
//            }
//            else {
//                
//                g.setColour(Colours::cornflowerblue);
//                g.drawLine( curTime*pathWidth + offset,     obstacleHeight[noteIdx],
//                           curNextTime*pathWidth + offset, obstacleHeight[noteIdx],
//                           pathHeight*2 );
//                firstNoteDrawn  = true;
//            }
//            
//            noteIdx += 1;
//            
//        }
    
//    }

    
    g.setColour(Colours::skyblue);
    g.fillRect( (int)curNextTime*pathWidth+offset, 0, offset+200, getHeight() );
    

}


void ObstacleComponent::noteToPixels(float *myArray) {
    
    int maxNoteNumber = 59;
    for (int noteIdx=0; noteIdx<obstacleLength; noteIdx++) {
        if( myArray[noteIdx] == -1) {
            continue;
        }
        else {
            myArray[noteIdx] = pathHeight/2.f + pathHeight*(maxNoteNumber - myArray[noteIdx]);
        }
    }

}


float ObstacleComponent::getObstacleHeight(float curTime) {
    if( timeIdx != obstacleLength-1) {
        if( curTime <= midiData.getTime(timeIdx) ) {
            return obstacleHeight[timeIdx];
        }
        else {
            return obstacleHeight[timeIdx++];
        }
  
    }
    else {
        return 0;
    }
}
