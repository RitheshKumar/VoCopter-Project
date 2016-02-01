//
//  ObstacleComponent.cpp
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 10/8/15.
//
//

#include "ObstacleComponent.h"


ObstacleCreate::ObstacleCreate (/*int offset*/ ):obstacleLength(noteNumber.size()),pathWidth(280.00),
                                             xOffset(/*offset*/)
{

    //paint Parameters
    widthPartition = floorf(1000/(float)obstacleLength)/1000;
    //std::cout<<"Le TotalLength est: "<<floorf(obstacleLength*widthPartition*600)<<"\n";

    obstacleHeight.resize(obstacleLength);
    instantObstacleHeight.resize(floorf(obstacleLength*widthPartition*600));

    //std::ostream_iterator<float> outputStream (std::cout,"\n");
    //std::copy (noteNumber.begin(), noteNumber.end(), outputStream);

    //normalize your range of input to the range of heights in the GUI.
    normalize (&noteNumber);

    //output the contents of the 'normalized' notes.
    //std::copy (noteNumber.begin(), noteNumber.end(), outputStream);

    for (int i=0; i<obstacleLength; i++) {
        obstacleHeight[i]=( noteNumber.at(i) )*0.8;///obstacleLength;//This is to generate the obstacle height.A ramp is called.
                                                   //This is where we must getheight information.
        std::fill(instantObstacleHeight.begin()+i*widthPartition,instantObstacleHeight.begin()+i*widthPartition+widthPartition,obstacleHeight[i]);
        //std::cout<<obstacleHeight[i]<<std::endl;
    }

    //std::ostream_iterator<float> out_it (std::cout, ",");
    //std::copy(instantObstacleHeight.begin(), instantObstacleHeight.end(), out_it);
    //std::copy(obstacleHeight.begin(), obstacleHeight.end(), out_it);
    /*for (int i = 0; i<obstacleHeight.size(); i++) {
        std::cout<<obstacleHeight.at(i)<<std::endl;
    }*/
    
    //This array is to store all the coordinate values of heights.
    heightValues = new float*[2];
    for (int i=0; i<2; i++ ) {
        heightValues[i] = new float[obstacleLength];
    }
    
    width = getWidth(); height = getHeight();
    for (int i=0; i<obstacleLength; i++) {
        
       heightValues[0][i] = height*obstacleHeight[i];
        
       float floorThickness = 2*height - obstacleHeight[i]*height - pathWidth;
       heightValues[1][i] = floorThickness;
    }
}
    
ObstacleCreate::~ObstacleCreate () {
    
}
    
void ObstacleCreate::paint (Graphics &g) { //Called everytime the timer callback is called
    
    width = getWidth(); height = getHeight();
    obstacleWidth = width*widthPartition; 
    
    for (int i=0; i<obstacleLength; i++) {
        

            g.drawLine( i*obstacleWidth,       0*(height-height*0.2),
                        (i+1)*obstacleWidth,   0*(height-height*0.2),
                        height*obstacleHeight[i]);
            heightValues[0][i] = height*obstacleHeight[i];

            float floorThickness = 2*height - obstacleHeight[i]*height - pathWidth; //we calculate this by solving for x,
                                                                                    //obstacleHeight[i]*height/2 + pathWidth 
                                                                                    //                        + height*x/2 = height

            g.drawLine( i*obstacleWidth,       1*(height),
                        (i+1)*obstacleWidth,   1*(height),
                        floorThickness);
            heightValues[1][i] = floorThickness;

            
    }
}

void ObstacleCreate::normalize(std::vector<float> *myVector) {

    float max = *std::max_element(myVector->begin(),myVector->end());
    float min = *std::min_element(myVector->begin(),myVector->end());
    
    for (int i=0; i<myVector->size(); i++) {
        myVector->at(i) = (myVector->at(i)-min)/(max-min);
    }
}

/*int ObstacleCreate::getObstacleHeight() {
    xOffset += 5;
    if ((int)xOffset%(int)obstacleWidth == 0) {
        count++;
    }
    if ( count <= obstacleHeight.size() ) {
        return obstacleHeight.at(count);
    }
    else {
        return 0;
    }
}*/

ObstacleComponent::ObstacleComponent (/*int offset*/) : ObstacleCourse(/*offset*/) {
    startTimer(50);
    addAndMakeVisible(ObstacleCourse);
}
    
ObstacleComponent::~ObstacleComponent() {
    
}

void ObstacleComponent::paint (Graphics &g) {
    
}

void ObstacleComponent::timerCallback () {
    ObstacleCourse.setBounds(xpos-=5, 0, getWidth(), getHeight());
    
}

