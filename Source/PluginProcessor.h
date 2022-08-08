

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MySamplerSound.h"
#include "MySamplerVoice.h"
#include "MYSampler.h"
#include <vector>



//==============================================================================
/**
*/
class NewProjectAudioProcessor  : public AudioProcessor
{
    
    StringArray instruments;
    
public:
    //==============================================================================
    NewProjectAudioProcessor();
    ~NewProjectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //=====================================================
    
    
    
//    void loadFile();
    void loadFile(const String& path,int index);
    
    int getSamplerSounds(){return mySampler.getNumSounds();}

    void updateADSR(const float attack, const float decay, const float sustain, const float release);
    void setType(const int filtertype, const float cutoff, const float res);
    void updateADSRParams();
    void updateFilterParams();
    void updateParams();
    void SampleCount(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,int index);
    
    
   
    AudioBuffer<float>&getWaveForm(int index);
//    AudioProcessorValueTreeState& getValueTree(){return APVTS;}
//    juce::AudioProcessorValueTreeState APVTS;
    bool renameFile (const File& f, String& newName)  { return f.moveFileTo (f.getSiblingFile(newName));}
    std::atomic<bool>& isNotePlayed(int index) {
        if(index ==0){
        return myIsNotePlayed; }
        if(index ==1){
        return myIsNotePlayed2; }
        if(index ==2){
        return myIsNotePlayed3; }
        if(index ==3){
        return myIsNotePlayed4; }
    }

    std::atomic<int>& getSampleCount(int index) {
        if(index == 0){
            return mySampleCount;}
        if(index == 1){
            return mySampleCount2;}
        if(index == 2){
            return mySampleCount3;}
        if(index == 3){
           return mySampleCount4;
        }
        }

    std::atomic<int>& getSampleCount2() { return mySampleCount2;}
    std::atomic<int>& getSampleCount3() { return mySampleCount3;}
    std::atomic<int>& getSampleCount4() { return mySampleCount4;}
    
     AudioProcessorValueTreeState& getValueTree(){return APVTS;}
//     std::unique_ptr<UndoManager> undoManager;
//     std::unique_ptr<AudioProcessorValueTreeState> APVTS;
       
   
    
private:
    
    MYSampler mySampler;
    MYSampler mySampler2;
    MYSampler mySampler3;
    MYSampler mySampler4;
    
    const int NumVoices {4};
    ADSRdata adsrData;
    ADSRdata adsrData2;
    FilterData filterData;
//    std::unique_ptr<UndoManager> undoManager;
//    int index;
    
//    AudioFormatManager FormatManager;
//   AudioFormatReader* FormatReader{nullptr};
    
    typedef enum Sounds {Sample_1 = 0, Sample_2, Sample_3,Sample_4} Sounds_t;
    AudioProcessorValueTreeState APVTS;
    AudioProcessorValueTreeState::ParameterLayout ParamLayout();
    void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged,const Identifier& property);
    std::atomic<bool> myIsNotePlayed { false };
    std::atomic<bool> myIsNotePlayed2 { false };
    std::atomic<bool> myIsNotePlayed3 { false };
    std::atomic<bool> myIsNotePlayed4 { false };
    std::atomic<bool> ShouldUpdate {false};
    std::atomic<int> mySampleCount { 0 };
    std::atomic<int> mySampleCount2 { 0 };
    std::atomic<int> mySampleCount3 { 0 };
    std::atomic<int> mySampleCount4 { 0 };




    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessor)
    
};
