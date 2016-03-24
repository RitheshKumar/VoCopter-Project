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

MidiStorage::MidiStorage(char *filePath) : noteNumber(0),
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
void MidiStorage::readMidiData(char *filePath) {
    
    File *filePtr = new File (filePath);
    bool fileExists = filePtr->existsAsFile();
    int NumEvents;

    if (fileExists) {

        ScopedPointer<FileInputStream> fileInputStream = filePtr->createInputStream(); //delete the stream!
        MidiFile fileMIDI;
        const MidiMessageSequence *midiSequence;
        MidiMessageSequence::MidiEventHolder *midiEvent;
        MidiMessage midiVal;


        /*bool midiReadSuccessfully =*/ fileMIDI.readFrom(*fileInputStream); // note the *
//        //Logger::writeToLog("Successfully read midi file:"+std::to_string(midiReadSuccessfully));
//        //Logger::writeToLog("No. of Tracks in file: "+std::to_string(fileMIDI.getNumTracks()));

        midiSequence = fileMIDI.getTrack(1);    //Track indices start from 1; Also we want only one track to exist
//        //Logger::writeToLog("Total No. of events in the track is : "+ std::to_string( midiSequence->getNumEvents()));

        NumEvents = midiSequence->getNumEvents();
//        noteNumber.resize(NumEvents);
        noteNumber = new float[NumEvents];
        timeStamps = new float[NumEvents];

//        std::cout<<"The sequence of timeStamps are:\n";
        for (int i=0; i<midiSequence->getNumEvents(); i++) {
            midiEvent =  midiSequence->getEventPointer(i); //Make sure the index doesn't exceed your no. of timeStamps. It starts from 0.
            midiVal =  midiEvent->message;
            noteNumber[i] =  midiVal.getNoteNumber();
            timeStamps[i] =  midiVal.getTimeStamp();
//            std::cout<<timeStamps[i]<<std::endl;
            //std::cout<<noteNumber[i]<<" "<<midiVal.getMidiNoteName(noteNumber[i],true,true,4)<<std::endl;
        }
//        delete fileInputStream; fileInputStream = 0;//You don't need this! Juce does it for you. Also, you called a scopedPointer on it. Duh.

        //Logger::writeToLog("The Note no. is: " + std::to_string(noteNumber));
        //Logger::writeToLog("Therefore the note is: " + midiVal.getMidiNoteName(noteNumber,true,true,4)); //octave no. for middle C is 4
        //Logger::writeToLog("Further, its frequency in Hz is: "+ std::to_string(midiVal.getMidiNoteInHertz(noteNumber,440.0)));


    }
    else {
        Logger::writeToLog("Error in Reading Midi File - It doesn't exist");
    }

    tStampLen = NumEvents;
    //Filter Outliers Notes
    FileRW::fileWrite( noteNumber, NumEvents, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/midiIn.txt");
    MathOperation::filterOutliers(noteNumber, NumEvents) ;
    midiLen = NumEvents; //std::cout<<"noteNumber: "<<midiLen<<std::endl;
    FileRW::fileWrite( noteNumber, midiLen, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/midiOut.txt");
    
    //Filter Outliers TimeStamps
    FileRW::fileWrite( timeStamps, tStampLen, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/tStmpIn.txt");
    filterTimeStamps();
    //Do this after calling filterTimeStamps()
    tStampLen = NumEvents; //std::cout<<"timeStamps: "<<tStampLen<<std::endl;
    FileRW::fileWrite( timeStamps, tStampLen, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/tStmpOut.txt");
    
    
//    delete filePtr; filePtr = 0;
    
}

void MidiStorage::filterTimeStamps() {
    float *tempStmp = new float[(tStampLen-3)/2];
    for (int i = 3,cnt = 0; i<tStampLen; i+=2, cnt++) {
        tempStmp[cnt] = timeStamps[i];
    }
    delete [] timeStamps; timeStamps = 0;
    timeStamps = tempStmp;
}

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

