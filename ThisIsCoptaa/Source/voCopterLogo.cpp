//
//  voCopterLogo.cpp
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 4/10/16.
//
//

#include "voCopterLogo.h"


voCopterLogo::voCopterLogo() {
    logoImage = ImageCache::getFromMemory(BinaryData::copterLogo_png, BinaryData::copterLogo_pngSize);
//    logoImage = ImageCache::getFromMemory(BinaryData::copterFoto2_png, BinaryData::copterFoto2_pngSize);
    
}

voCopterLogo::~voCopterLogo() {
    
}

void voCopterLogo::paint(Graphics &g) {  //this function is continuously called. That's how GUI's work
    
    g.drawImageAt(logoImage, 0, 0);
    
}
