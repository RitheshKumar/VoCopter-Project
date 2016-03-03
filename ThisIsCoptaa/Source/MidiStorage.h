//
//  MidiStorage.h
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 10/15/15.
//
//

#ifndef __ThisIsCoptaa__MidiStorage__
#define __ThisIsCoptaa__MidiStorage__

#include "../JuceLibraryCode/JuceHeader.h"
#include "MathOperation.h"
#include "FileRW.h"

class MidiStorage {
public:
    MidiStorage(std::string fileName);
    ~MidiStorage();

    bool getMidiData( float * note );
    int  getMidiLen() { return midiLen; }

private:
    //File* filePtr;
    ////ScopedPointer<FileInputStream> fileInputStream;
    //FileInputStream* fileInputStream;
    //MidiFile fileMIDI;
    //const MidiMessageSequence *midiSequence;
    //MidiMessageSequence::MidiEventHolder *midiEvent;
    //MidiMessage midiVal;
    
    std::vector<float> noteNumber;
    std::string filePath;
    int cnt, midiLen;

    void readMidiData();
};

#endif /* defined(__ThisIsCoptaa__MidiStorage__) */
