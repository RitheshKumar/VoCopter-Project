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
    MidiStorage(char *filePath);
    ~MidiStorage();

    bool getMidiData( float * note );
    int  getMidiLen() { return midiLen; }
    float getNote(int index){ return noteNumber[index]; }
    float getTime(int index){ return timeStamps[index]; }

private:
    
    float *noteNumber,
          *timeStamps;
    int cnt, midiLen;

    void readMidiData(char *filePath);
    void filterTimeStamps();
};

#endif /* defined(__ThisIsCoptaa__MidiStorage__) */
