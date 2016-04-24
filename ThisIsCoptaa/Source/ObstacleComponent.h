//
//  ObstacleComponent.h
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 1/31/16.
//
//

#ifndef __ThisIsCoptaa__ObstacleComponent__
#define __ThisIsCoptaa__ObstacleComponent__

#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiStorage.h"

class ObstacleComponent : public Component
{
public:

    ObstacleComponent ( char *midiFilePath );
    ~ObstacleComponent( );

    void paint(Graphics &g);

    float getObstacleHeight(float curTime);
    float getInitialHeight(); 
//    int getObstacleLength(){ return midiData.getTime(obstacleLength-1)*pathWidth + 2*0.95*900 ; }
    int getObstacleLength(){ return midiData.getTime(obstacleLength-1)*pathWidth; }
    float getEndTime(){ return midiData.getTime(obstacleLength-1); }
    int getCurNote(){ return midiData.getNote(timeIdx); }
    int getStartNote(){ return midiData.getStartNote(); }
    
    void setCurTime(float curTime){ time += curTime; }

private:
    MidiStorage midiData;
    
    int obstacleLength,
               timeIdx;
    const int pathWidth,
              pathHeight,
              pathPosition;
    float *obstacleHeight,
           time;
    
    void noteToPixels(float *myArray);
    
};
    


#endif /* defined(__ThisIsCoptaa__ObstacleComponent__) */
