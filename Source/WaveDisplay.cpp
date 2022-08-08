/*
  ==============================================================================

    WaveDisplay.cpp
    Created: 13 Apr 2022 11:42:39pm
    Author:  Rhys William Buckham

  ==============================================================================
*/

#include "WaveDisplay.h"

//==============================================================================
WaveDisplay::WaveDisplay(NewProjectAudioProcessor& p,int i): audioProcessor(p),index(i)
{
   
    
}

WaveDisplay ::~WaveDisplay ()
{
    
    
}

//==============================================================================


void WaveDisplay::drawWaveform(juce::Graphics& g){
    
    if(index == 0){
        drawW(g, 0);
    }
    if(index == 1){
        drawW(g, 1);
    }
    if(index == 2){
        drawW(g, 2);
    }
    if(index == 3){
        drawW(g, 3);
    }

  
    
    
}
        
void WaveDisplay::drawW(juce::Graphics& g,int index){
            
     
    g.fillAll(Colours::azure.darker());
    
   
    auto waveform = audioProcessor.getWaveForm(index);
    
    
    if(waveform.getNumSamples() > 0)
    {
            Path p;
            AudioPoints.clear();
        
            auto ratio = waveform.getNumSamples() / getWidth();
            auto buffer = waveform.getReadPointer(0);
            //scale on x axis
        
            for(int i = 0; i < waveform.getNumSamples();i+=ratio){
                AudioPoints.push_back(buffer[i]);
            }
        
            g.setColour(Colours::yellow);
        
        
            p.startNewSubPath(0, getHeight()/2);
            
            
            // scale on y axis
            for(int i = 0; i < AudioPoints.size();++ i){
                auto point = jmap<float>(AudioPoints[i], -1.0f, 1.0f, getHeight(), 0);
                //scaled and connects the lines
                p.lineTo(i, point);
//                AudioPoints.clear();
            }

            //actually draws the connected lines
        g.strokePath(p, PathStrokeType(6));
            
        g.setColour(Colours::white);
        g.setFont(15.0f);
        auto txtBounds = getLocalBounds().reduced(10, 10);
        g.drawFittedText(FileName + String(index), txtBounds, Justification::topRight, 1);
        
     
        if (index == 0){
        auto playHeadPosition=jmap<int>(audioProcessor.getSampleCount(0), 0, audioProcessor.getWaveForm(0).getNumSamples(), 0, getWidth());
                
                g.setColour (Colours::white);
                g.drawLine (playHeadPosition, 0, playHeadPosition, getHeight(), 2.0f);
                
                g.setColour (Colours::black.withAlpha (0.2f));
                g.fillRect (0, 0, playHeadPosition, getHeight());
            }
        if (index == 1){
        auto playHeadPosition=jmap<int>(audioProcessor.getSampleCount(1), 0, audioProcessor.getWaveForm(1).getNumSamples(), 0, getWidth());
                
                g.setColour (Colours::white);
                g.drawLine (playHeadPosition, 0, playHeadPosition, getHeight(), 2.0f);
                
                g.setColour (Colours::black.withAlpha (0.2f));
                g.fillRect (0, 0, playHeadPosition, getHeight());
            }
        if (index == 2){
        auto playHeadPosition=jmap<int>(audioProcessor.getSampleCount(2), 0, audioProcessor.getWaveForm(2).getNumSamples(), 0, getWidth());
                
                g.setColour (Colours::white);
                g.drawLine (playHeadPosition, 0, playHeadPosition, getHeight(), 2.0f);
                
                g.setColour (Colours::black.withAlpha (0.2f));
                g.fillRect (0, 0, playHeadPosition, getHeight());
            }
        if (index == 3){
        auto playHeadPosition=jmap<int>(audioProcessor.getSampleCount(3), 0, audioProcessor.getWaveForm(3).getNumSamples(), 0, getWidth());
                
                g.setColour (Colours::white);
                g.drawLine (playHeadPosition, 0, playHeadPosition, getHeight(), 2.0f);
                
                g.setColour (Colours::black.withAlpha (0.2f));
                g.fillRect (0, 0, playHeadPosition, getHeight());
            }
    }

        
        
        
        
        
        
        
    else
    {
        g.setColour(Colours::white);
        g.setFont(40.0f);
        g.drawFittedText("Drop an Audio File", getLocalBounds(), Justification::centred, 1);
    }
    
    
    
    
    
    
    
    
    
    
    
        }
        
        
        
        
        
        
        
        
        
        




void WaveDisplay ::paint (juce::Graphics& g)
{
//    if(index == 0){
//    drawWaveform(g);
//    }
//    if(index == 1){
//    drawWaveform2(g);
//    }
//    if(index == 2){
//    drawWaveform3(g);
//    }
//    if(index == 3){
//    drawWaveform4(g);
//    }
    
    drawWaveform(g);
    
    

   
}


void WaveDisplay ::resized()
{
  
    
}

bool WaveDisplay::isInterestedInFileDrag(const StringArray& files){
    // is it an audio file?
    for(auto file : files){
        if(file.contains(".wav") || file.contains("mp3")||file.contains(".aif")){
        
            //if yes go
            return true;
        }
    }
    return false;
    

    
}

void WaveDisplay::filesDropped(const StringArray& files,
                                                  int x, int y){
    
    for(auto file:files){

        if(isInterestedInFileDrag(file)){
            
            auto myFile = std::make_unique<File>(file);
//            String name = ("Sample_" + std::to_string(index));
//            renameFile(file,name);
            FileName = myFile->getFileNameWithoutExtension();
            if(index == 0){
//            auto myFile = std::make_unique<File>(file);
            audioProcessor.loadFile(file,0);
                repaint();
            }
            else
            if(index == 1 ){
//            auto myFile2 = std::make_unique<File>(file);
            audioProcessor.loadFile(file,1);
                repaint();
             }
                
            else
            if(index == 2){
//                auto myFile3 = std::make_unique<File>(file);
            audioProcessor.loadFile(file,2);
                repaint();

            }
            else
            if(index == 3 ){
//                auto myFile4 = std::make_unique<File>(file);
            audioProcessor.loadFile(file,3);
                repaint();
                
            }
//          }
    }
    repaint();
}

}
