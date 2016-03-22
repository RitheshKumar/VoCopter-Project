//
//  CopterComponent.cpp
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 10/8/15.
//
//

#include "CopterComponent.h"

CopterComponent::CopterComponent() {
    addAndMakeVisible(Body);
    addAndMakeVisible(Fan);
}

CopterComponent::~CopterComponent() {
    
}

void CopterComponent::resized() {
//    Fan.setBounds (0,0,getWidth(),getHeight()*40/100);
    Body.setBounds(0,getHeight()*20/100,getWidth(),getHeight()*80/100);
    //Fan.setBounds(<#int x#>, <#int y#>, <#int width#>, <#int height#>)
}

