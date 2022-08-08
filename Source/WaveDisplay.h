/*
  ==============================================================================

    WaveDisplay.h
    Created: 13 Apr 2022 11:42:39pm
    Author:  Rhys William Buckham

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"





//==============================================================================
/**
*/
class WaveDisplay  : public Component,
                     public FileDragAndDropTarget,
                     public ValueTree::Listener
{
public:
    WaveDisplay(NewProjectAudioProcessor& p,int i);
    ~WaveDisplay() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void drawWaveform(juce::Graphics& g);
    void drawWaveform2(juce::Graphics& g);
    void drawWaveform3(juce::Graphics& g);
    void drawWaveform4(juce::Graphics& g);
    void drawW(juce::Graphics& g,int index);
    void resized() override;
    
    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;
    String getFileName(){return FileName;}
    bool renameFile (const File& f, String& newName)  { return f.moveFileTo (f.getSiblingFile(newName));}

private:

    
    std::vector<float>AudioPoints;
    bool ShouldbePaining{false};
    String FileName{""};
   
    
    NewProjectAudioProcessor& audioProcessor;
    int index;
    MYSampler mySampler;
    MYSampler mySampler2;
    MYSampler mySampler3;
    MYSampler mySampler4;

  
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveDisplay)
};
