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


    static void fileRead( float ** &outFile, int numSamples, char *fileName ) {

        std::ifstream inputFile( fileName );
        //numSamples = inputFile.gcount();
        outFile = new float*[3];
        for (int c=0; c<3; c++ ) {
            outFile[c] = new float[ numSamples ];
        }

        int curIdx = 0;
        while ( curIdx<numSamples ) {
            inputFile>>outFile[0][curIdx];
            curIdx++;
        }

        for ( int c=1; c<3; c++ ) {
            for ( int sample = 0; sample<curIdx; sample++ ) {
                outFile[c][sample]  = outFile[0][sample];
            }
        }
        
    }
};




#endif /* defined(__ThisIsCoptaa__FileRW__) */
