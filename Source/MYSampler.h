/*
  ==============================================================================

    Sampler.h
    Created: 1 Jul 2022 12:27:38am
    Author:  Rhys William Buckham

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MySamplerSound.h"
#include "MySamplerVoice.h"




class MYSampler : public Synthesiser

{
StringArray instruments;

public:
    void setup(int _voice);
    AudioBuffer<float>&getWaveForm(int& index);
//    void loadFile();
    void loadFile(const String& path);
//    void addMySound(const String& path);
    void noteOn(int midiChannel,
                int midiNoteNumber,
                float velocity)override;
    bool isChokeGroupActive;
    bool renameFile (const File& f,String& newName)  { return f.moveFileTo (f.getSiblingFile(newName));}
    void _addSound(const String& path);
    void SampleCount(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessage);
    int getIndex(){return _index;}
    int getMidiNotePlayed(){return midiNote;}
    
    std::atomic<bool>& isNotePlayed() { return myIsNotePlayed; }
    std::atomic<int>& getSampleCount() { return mySampleCount;}
    
private:
    const int NumVoices {1};
    int _index;
    AudioFormatManager FormatManager;
    AudioFormatReader* FormatReader{nullptr};
    AudioFormatManager FormatManager2;
    AudioFormatReader* FormatReader2{nullptr};
    AudioFormatManager FormatManager3;
    AudioFormatReader* FormatReader3{nullptr};
    AudioFormatManager FormatManager4;
    AudioFormatReader* FormatReader4{nullptr};
    
    int midiNote;
    std::atomic<bool> myIsNotePlayed { false };
    std::atomic<bool> ShouldUpdate {false};
    std::atomic<int> mySampleCount { 0 };
 
    typedef enum Sounds {Sample_1 = 0, Sample_2, Sample_3,Sample_4} Sounds_t;
    
};
