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

MidiStorage::MidiStorage(char *filePath) : cnt(0), midiLen(0) {
    readMidiData(filePath);
}

MidiStorage::~MidiStorage() {
//    delete midiSequence; //You don't need this! The array in MidiMessage class uses the Array class, which deletes itself!
    delete [] noteNumber;
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

        //std::cout<<"The sequence of notes are:\n";
        for (int i=0; i<midiSequence->getNumEvents(); i++) {
            midiEvent =  midiSequence->getEventPointer(i); //Make sure the index doesn't exceed your no. of timeStamps. It starts from 0.
            midiVal =  midiEvent->message;
            noteNumber[i] =  midiVal.getNoteNumber();
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

    FileRW::fileWrite( noteNumber, NumEvents, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/midiIn.txt");
    //Filter Outliers
    MathOperation::filterOutliers(noteNumber, NumEvents) ;
    midiLen = NumEvents;
    FileRW::fileWrite( noteNumber, midiLen, (char *)"/Users/Rithesh/Documents/Learn C++/ASE/notes/Matlab_ASE/midiOut.txt");
    
    
//    delete filePtr; filePtr = 0;
    
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
        std::cout<<"getMidiData function error"<<std::endl;
        return false;
    }
}
