//
//  ObstacleComponent.h
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 9/30/15.
//
//

#ifndef ThisIsCoptaa_ObstacleComponent_h
#define ThisIsCoptaa_ObstacleComponent_h


#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiTranslation.h"


class ObstacleCreate : public Component,
                       protected MidiTranslation
{
public:
    
    ObstacleCreate (/*int offset*/);
    ~ObstacleCreate ();
    
    void paint (Graphics &g);
    //int getObstacleHeight();

    int obstacleLength;
    float ** getHeightValue() const { return heightValues; }

private:
    std::vector<float> obstacleHeight,instantObstacleHeight;
    float widthPartition,pathWidth,obstacleWidth;
    int width,height,xOffset,count=0;

    void normalize(std::vector<float> *myVector);

    float **heightValues;
};
  
class ObstacleComponent: private Timer,
                         public Component
{
public:
    
    ObstacleComponent (/*int offset*/);    
    ~ObstacleComponent();   

    void paint (Graphics &g);  

    void timerCallback () override;

    int getObstacleLength() { return obstacleLength;} 
    float** getHeightCoord() const { return ObstacleCourse.getHeightValue(); }

private:
    ObstacleCreate ObstacleCourse;
    int xpos=0;
    
    //int width,height;
    int obstacleLength = ObstacleCourse.obstacleLength;
    
};

#endif
