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

    int getObstacleHeight(); 

private:
    MidiStorage midiData;
    
    int obstacleLength;
    const int pathWidth,
              pathHeight,
              pathPosition;
    float *obstacleHeight;
    
    void normalizeRange(float *myArray);
    
};
    


#endif /* defined(__ThisIsCoptaa__ObstacleComponent__) */
