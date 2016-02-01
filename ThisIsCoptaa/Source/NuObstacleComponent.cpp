//
//  NuObstacleComponent.cpp
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 1/31/16.
//
//

#include "NuObstacleComponent.h"

NuObstacleComponent::NuObstacleComponent( ) : obstacleHeight( new int[801]/*noteNumber.size()*/ ) {
    
    int height = 400, width = 600;
    for(int i=0; i<800; i++) {
        if( i<round(width/2)) {
            obstacleHeight[i] = round(height/2) - 130/2;
        }
        else {
            obstacleHeight[i] = round(height/2) - 130/2 + 40;
        }
    }
    obstacleHeight[800] = -1;
        
}

NuObstacleComponent::~NuObstacleComponent( ) {
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
        obstacleHeight++;
        return temp;
    }
    else {
        return *obstacleHeight;
    }
}

