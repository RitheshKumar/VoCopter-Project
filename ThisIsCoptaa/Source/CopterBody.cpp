//
//  CopterBody.cpp
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 10/8/15.
//
//

#include "CopterBody.h"

CopterBody::CopterBody() {
    copterImage = ImageCache::getFromMemory(BinaryData::copterFoto_png, BinaryData::copterFoto_pngSize);
 
}

CopterBody::~CopterBody() {
    
}

void CopterBody::paint(Graphics &g) {  //this function is continuously called. That's how GUI's work
    
//    const float lineThickness = getHeight()*10/100;
//    g.setColour(Colours::white);
//    g.drawLine(getWidth()*0.17, getHeight()*0.8, getWidth(),getHeight()*0.8,lineThickness);
//    g.drawLine(0, getHeight()-lineThickness/2, getWidth()*0.83,getHeight()-lineThickness/2,lineThickness);
//    g.setColour(Colours::yellow);
//    g.fillEllipse(0+getWidth()*0.06,2,getWidth()*0.88, getHeight()*0.9);
    g.drawImageAt(copterImage, 0, 0);
    
}
