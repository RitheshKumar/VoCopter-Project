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
#include "MidiTranslation.h"

class NuObstacleComponent : public Component,
                            public MidiTranslation
{
public:

    NuObstacleComponent ( );
    ~NuObstacleComponent( );

    void paint(Graphics &g);

    int getObstacleHeight(); 

private:
    int *obstacleHeight,cnt;
    
    void normalize(std::vector<float> *myVector);
    
};
    


#endif /* defined(__ThisIsCoptaa__NuObstacleComponent__) */
