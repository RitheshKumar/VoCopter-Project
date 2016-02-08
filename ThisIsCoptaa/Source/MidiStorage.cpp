//
//  MidiStorage.cpp
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 10/15/15.
//
//

#include "MidiStorage.h"

MidiStorage::MidiStorage() : cnt(0), midiLen(0) {
    readMidiData();
    midiLen = noteNumber.size();
}

MidiStorage::~MidiStorage() {

}
void MidiStorage::readMidiData() {
    
    filePtr = new File ("~/Documents/Fall_2015/VoCopter Project/ThisIsCoptaa/MidiFiles/OnlyTime.mid");
    bool fileExists = filePtr->existsAsFile();

    if (fileExists) {

        FileInputStream* fileInputStream;
        fileInputStream = filePtr->createInputStream(); //delete the stream! 
        /*bool midiReadSuccessfully =*/ fileMIDI.readFrom(*fileInputStream); // note the *
        //Logger::writeToLog("Successfully read midi file:"+std::to_string(midiReadSuccessfully));
        //Logger::writeToLog("No. of Tracks in file: "+std::to_string(fileMIDI.getNumTracks()));

        midiSequence = fileMIDI.getTrack(1);    //Track indices start from 1; Also we want only one track to exist
        //Logger::writeToLog("Total No. of events in the track is : "+ std::to_string( midiSequence->getNumEvents()));

        int NumEvents = midiSequence->getNumEvents();
        noteNumber.resize(NumEvents);

        //std::cout<<"The sequence of notes are:\n";
        for (int i=0; i<midiSequence->getNumEvents(); i++) {
            midiEvent =  midiSequence->getEventPointer(i); //Make sure the index doesn't exceed your no. of timeStamps. It starts from 0.
            midiVal =  midiEvent->message;
            noteNumber[i] =  midiVal.getNoteNumber();
            //std::cout<<noteNumber[i]<<" "<<midiVal.getMidiNoteName(noteNumber[i],true,true,4)<<std::endl;
        }
        delete fileInputStream; 
 
        //Logger::writeToLog("The Note no. is: " + std::to_string(noteNumber));
        //Logger::writeToLog("Therefore the note is: " + midiVal.getMidiNoteName(noteNumber,true,true,4)); //octave no. for middle C is 4
        //Logger::writeToLog("Further, its frequency in Hz is: "+ std::to_string(midiVal.getMidiNoteInHertz(noteNumber,440.0)));

    }
    else {
        Logger::writeToLog("Error in Reading Midi File - It doesn't exist");
    }
    
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
