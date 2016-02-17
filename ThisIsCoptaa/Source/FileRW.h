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
    static void fileWrite( float  **inFile, int &fileSize, int numChannels,  char  *fileName ) {

        std::ofstream outputFile(fileName);

        for(int sample=0; sample<fileSize; sample++ ) {
            for ( int c =0; c < numChannels; c++ ) {
                outputFile<<inFile[c][sample]<<"  ";
            }
            outputFile<<"\n";
        }

        outputFile.close();

    }


    static void fileRead( float ** &outFile, int &numSamples, char *fileName ) {

        std::ifstream inputFile( fileName );
        //numSamples = inputFile.gcount();
        numSamples = 1000;
        outFile = new float*[1];
        outFile[0] = new float[ numSamples ];

        int curIdx = 0;
        while ( curIdx<numSamples ) {
            inputFile>>outFile[0][curIdx];
            std::cout<<outFile[0][curIdx]<<std::endl;
            curIdx++;
        }

    }
};




#endif /* defined(__ThisIsCoptaa__FileRW__) */
