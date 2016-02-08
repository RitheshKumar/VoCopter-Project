//
//  NuObstacleComponent.h
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 1/31/16.
//
//

#ifndef __ThisIsCoptaa__NuObstacleComponent__
#define __ThisIsCoptaa__NuObstacleComponent__

#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiStorage.h"

class NuObstacleComponent : public Component
{
public:

    NuObstacleComponent ( );
    ~NuObstacleComponent( );

    void paint(Graphics &g);

    int getObstacleHeight(); 

private:
    MidiStorage midiData;
    
    int cnt,obstacleLength;
    float *obstacleHeight;
    
    void normalizeRange(float *myArray);
    
};
    


#endif /* defined(__ThisIsCoptaa__NuObstacleComponent__) */
