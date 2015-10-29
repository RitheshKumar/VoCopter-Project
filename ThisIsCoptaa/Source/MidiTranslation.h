//
//  MidiTranslation.h
//  ThisIsCoptaa
//
//  Created by Rithesh Kumar Ravikumar on 10/15/15.
//
//

#ifndef __ThisIsCoptaa__MidiTranslation__
#define __ThisIsCoptaa__MidiTranslation__

#include "../JuceLibraryCode/JuceHeader.h"

class MidiTranslation {
public:
    MidiTranslation();
    ~MidiTranslation();

protected:
    std::vector<float> noteNumber;

private:
    File* filePtr;
    //ScopedPointer<FileInputStream> fileInputStream;
    FileInputStream* fileInputStream;
    MidiFile fileMIDI;
    const MidiMessageSequence *midiSequence;
    MidiMessageSequence::MidiEventHolder *midiEvent;
    MidiMessage midiVal;
    
    void readMidiData();
};

#endif /* defined(__ThisIsCoptaa__MidiTranslation__) */
