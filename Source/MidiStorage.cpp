//
//  MidiStorage.cpp
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 10/15/15.
//
//

#include "MidiStorage.h"
#include "MathOperation.h"
#include "FileRW.h"

MidiStorage::MidiStorage(const char *filePath) : noteNumber(0),
                                                 timeStamps(0),
                                                 cnt(0),
                                                 midiLen(0)

{
    readMidiData(filePath);
}

MidiStorage::~MidiStorage() {
//    delete midiSequence; //You don't need this! The array in MidiMessage class uses the Array class, which deletes itself!
    delete [] noteNumber;
    delete [] timeStamps;
}

void MidiStorage::readMidiData(const char *filePath) {
    
    File *filePtr = new File (filePath);
    bool fileExists = filePtr->existsAsFile();
    int NumEvents;

    if (fileExists) {

        ScopedPointer<FileInputStream> fileInputStream = filePtr->createInputStream(); //delete the stream!
        MidiFile fileMIDI;
        const MidiMessageSequence *midiSequence;
        MidiMessageSequence::MidiEventHolder *midiEvent;

        
        fileMIDI.readFrom(*fileInputStream); // read the MIDI file
        fileMIDI.convertTimestampTicksToSeconds();
   
        midiSequence = fileMIDI.getTrack(1);    //Track indices start from 1; Also we want only one track to exist

        NumEvents = midiSequence->getNumEvents();

        noteNumber = new float[NumEvents];
        timeStamps = new float[NumEvents];

        for (int i=0; i<NumEvents; i++) {
            midiEvent =  midiSequence->getEventPointer(i); //Make sure the index doesn't exceed your no. of timeStamps. It starts from 0.

            if ( midiEvent->message.isNoteOn() ) {
                noteNumber[i] =  midiEvent->message.getNoteNumber();
                timeStamps[i] =  midiEvent->message.getTimeStamp();

            }
            else {
                noteNumber[i] =  -1.f;
                timeStamps[i] =  midiEvent->message.getTimeStamp();
            }
        }
        

    }
    else {
        Logger::writeToLog("Error in Reading Midi File - It doesn't exist");
    }

    midiLen = NumEvents; //std::cout<<"noteNumber: "<<midiLen<<std::endl;

    FileRW::fileWrite( noteNumber, NumEvents, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/midiIn.txt");
    FileRW::fileWrite( timeStamps, NumEvents, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/tStmpIn.txt");

    
    
}

//void MidiStorage::filterTimeStamps() {
//    float *tempStmp = new float[(tStampLen-3)/2];
//    for (int i = 3,cnt = 0; i<tStampLen; i+=2, cnt++) {
//        tempStmp[cnt] = timeStamps[i];
//    }
//    delete [] timeStamps; timeStamps = 0;
//    timeStamps = tempStmp;
//}

bool MidiStorage::getMidiData(float *note) {
    if( cnt != midiLen ) {
        *note = noteNumber[cnt];
        cnt++;
        return true;
    }
    else if( cnt == midiLen ) {
        return false;
    }
    else {
        Logger::writeToLog("getMidiData function error");
        return false;
    }
}

float MidiStorage::getStartNote() {
    int i=0;
    while (noteNumber[i] == -1) {
        i++;
    }
    return noteNumber[i];
}
