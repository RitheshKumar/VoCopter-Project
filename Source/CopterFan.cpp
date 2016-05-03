//
//  CopterFan.cpp
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 10/8/15.
//
//

#include "CopterFan.h"

CopterFan::CopterFan() {
    
}

CopterFan::~CopterFan() {
    
}

void CopterFan::paint(Graphics &g) {
    g.setColour(Colours::red);
    const float lineThickness = getWidth()*4/100;
    //we need to find the distance from the edge, so that
    //the fan is a complete rectangle
    g.drawLine(0,0,getWidth(),getHeight(),lineThickness);
    g.drawLine(0,getHeight(),getWidth(),0,lineThickness);
}
