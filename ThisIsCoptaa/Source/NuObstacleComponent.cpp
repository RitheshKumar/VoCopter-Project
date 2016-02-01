//
//  NuObstacleComponent.cpp
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 1/31/16.
//
//

#include "NuObstacleComponent.h"

NuObstacleComponent::NuObstacleComponent( ) : obstacleHeight( new int[3]/*noteNumber.size()*/ ), cnt(0) {
    
    //normalize noteValues
    normalize(&noteNumber);
    
    int height = 400;//, width = 600;

    obstacleHeight[0] = round(height/2) - 130/2;
    obstacleHeight[1] = round(height/2) - 130/2 + 40;
    obstacleHeight[2] =  -1;
            
}

NuObstacleComponent::~NuObstacleComponent( ) {
}

void NuObstacleComponent::normalize(std::vector<float> *myVector) {
    
    float max = *std::max_element(myVector->begin(),myVector->end());
    float min = *std::min_element(myVector->begin(),myVector->end());
    
    for (int i=0; i<myVector->size(); i++) {
        myVector->at(i) = (myVector->at(i)-min)/(max-min);
    }
}


void NuObstacleComponent::paint(Graphics &g) {

    g.fillAll(Colours::black);
    g.setColour(Colours::cornflowerblue);
    g.drawLine( 0, round(getHeight()/2), 400, round(getHeight()/2), 130 );
    g.drawLine(400, round(getHeight()/2)+40, 800, round(getHeight()/2)+40, 130 );
    

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
        std::cout<<temp<<std::endl;
        return temp;
    }
    else {
        std::cout<<*obstacleHeight<<std::endl;
        return *obstacleHeight;
    }
}

