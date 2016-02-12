//
//  FileRW.h
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 2/11/16.
//
//

#ifndef __ThisIsCoptaa__FileRW__
#define __ThisIsCoptaa__FileRW__

#include <stdio.h>
#include <fstream>

class FileRW {

public:
    static void fileWrite( float  *inFile, int &fileSize,  char  *fileName ) const {

        std::ofstream outputFile(fileName);

        for(int i=0; i<fileSize; i++ ) {
            outputFile<<inFile[i]<<"\n";
        }

    }
};




#endif /* defined(__ThisIsCoptaa__FileRW__) */
