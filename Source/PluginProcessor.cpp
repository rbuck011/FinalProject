
/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/



#include "PluginProcessor.h"
#include "PluginEditor.h"

//
//static String doubleToString(double val) { return String(val); }
//static double stringToDouble(String s){return std::stod(s.toStdString());}

//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations  //init list
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),APVTS(*this, nullptr, "Parameters", ParamLayout())
                        
#endif
{
    mySampler.setup(41);
    mySampler2.setup(42);
    mySampler3.setup(43);
    mySampler4.setup(44);
    

        if(auto* voice = dynamic_cast<MySamplerVoice*>(mySampler.getVoice(0))){
                APVTS.addParameterListener(String("ATTACK" + String("0")),voice);
                APVTS.addParameterListener(String("DECAY" + String("0")),voice);
                APVTS.addParameterListener(String("SUSTAIN" + String("0")),voice);
                APVTS.addParameterListener(String("RELEASE" + String("0")),voice);
//                APVTS.addParameterListener(String("FILTERCHOICE" + String(i)),voice);
//                APVTS.addParameterListener(String("CUTOFF" + String(i)),voice);
//                APVTS.addParameterListener(String("RESONANCE" + String(i)),voice);
                }
        
        if(auto* voice = dynamic_cast<MySamplerVoice*>(mySampler2.getVoice(1))){
                    APVTS.addParameterListener(String("ATTACK" + String("1")),voice);
                    APVTS.addParameterListener(String("DECAY" + String("1")),voice);
                    APVTS.addParameterListener(String("SUSTAIN" + String("1")),voice);
                    APVTS.addParameterListener(String("RELEASE" + String("1")),voice);
    //                APVTS.addParameterListener(String("FILTERCHOICE" + String(i)),voice);
    //                APVTS.addParameterListener(String("CUTOFF" + String(i)),voice);
    //                APVTS.addParameterListener(String("RESONANCE" + String(i)),voice);
                    }
        if(auto* voice = dynamic_cast<MySamplerVoice*>(mySampler3.getVoice(2))){
                    APVTS.addParameterListener(String("ATTACK" + String("2")),voice);
                    APVTS.addParameterListener(String("DECAY" + String("2")),voice);
                    APVTS.addParameterListener(String("SUSTAIN" + String("2")),voice);
                    APVTS.addParameterListener(String("RELEASE" + String("2")),voice);
    //                APVTS.addParameterListener(String("FILTERCHOICE" + String(i)),voice);
    //                APVTS.addParameterListener(String("CUTOFF" + String(i)),voice);
    //                APVTS.addParameterListener(String("RESONANCE" + String(i)),voice);
                    }
        if(auto* voice = dynamic_cast<MySamplerVoice*>(mySampler4.getVoice(3))){
                    APVTS.addParameterListener(String("ATTACK" + String("3")),voice);
                    APVTS.addParameterListener(String("DECAY" + String("3")),voice);
                    APVTS.addParameterListener(String("SUSTAIN" + String("3")),voice);
                    APVTS.addParameterListener(String("RELEASE" + String("3")),voice);
    //                APVTS.addParameterListener(String("FILTERCHOICE" + String(i)),voice);
    //                APVTS.addParameterListener(String("CUTOFF" + String(i)),voice);
    //                APVTS.addParameterListener(String("RESONANCE" + String(i)),voice);
                    }
    
//    }
}


NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
    //    APVTS.state.removeListener(this);
}

//==============================================================================
const juce::String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;  
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    
    mySampler.setCurrentPlaybackSampleRate(sampleRate);
    mySampler2.setCurrentPlaybackSampleRate(sampleRate);
    mySampler3.setCurrentPlaybackSampleRate(sampleRate);
    mySampler4.setCurrentPlaybackSampleRate(sampleRate);
    updateParams();

}


void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NewProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
 
    SampleCount(buffer, midiMessages, 0);
    SampleCount(buffer, midiMessages, 1);
    SampleCount(buffer, midiMessages, 2);
    SampleCount(buffer, midiMessages, 3);
    
    if(ShouldUpdate){
        updateParams();
    }
    
    mySampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    mySampler2.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    mySampler3.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    mySampler4.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

}

void NewProjectAudioProcessor::SampleCount(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages, int index){
    
    MidiMessage m;
    MidiBuffer::Iterator it {midiMessages};

//        int sample;
    if(index == 0){
        int sample;
        while (it.getNextEvent (m, sample))
        {
            if (m.isNoteOn() && (m.getNoteNumber() == 41))
                myIsNotePlayed = true;
            else if (m.isNoteOff())
                myIsNotePlayed = false;
        }
        mySampleCount = myIsNotePlayed ? mySampleCount += buffer.getNumSamples() : 0;
    }
    else
    if(index == 1){
        int sample;
        while (it.getNextEvent (m, sample))
        {
            if (m.isNoteOn() && (m.getNoteNumber() == 42))
                myIsNotePlayed2 = true;
            else if (m.isNoteOff())
                myIsNotePlayed2 = false;
        }
        mySampleCount2 = myIsNotePlayed2 ? mySampleCount2 += buffer.getNumSamples() : 0;
    }
    else
    if(index == 2){
        int sample;
        while (it.getNextEvent (m, sample))
        {
            if (m.isNoteOn() && (m.getNoteNumber() == 43))
                myIsNotePlayed3 = true;
            else if (m.isNoteOff())
                myIsNotePlayed3 = false;
        }
        mySampleCount3 = myIsNotePlayed3 ? mySampleCount3 += buffer.getNumSamples() : 0;
    }
    else
    if(index == 3){
        int sample;
        while (it.getNextEvent (m, sample))
        {
            if (m.isNoteOn() && (m.getNoteNumber() == 44))
                myIsNotePlayed4 = true;
            else if (m.isNoteOff())
                myIsNotePlayed4 = false;
        }
        mySampleCount4 = myIsNotePlayed4 ? mySampleCount4 += buffer.getNumSamples() : 0;
    }
    
    updateParams();
    
}




//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor(*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
       MemoryOutputStream stream(destData, false);
        APVTS.state.writeToStream(stream);
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
   
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);

    if(tree.isValid())
    {
        if(tree.hasType("PARAMETERS"))
        {
            APVTS.state = tree;
        }
    }
    
}


void NewProjectAudioProcessor::updateParams(){
    updateADSRParams();
//    updateFilterParams();
}


void NewProjectAudioProcessor::updateADSRParams()
{


    ShouldUpdate = false;


     for(int i = 0; i < mySampler.getNumSounds();++i){

         if(auto voice = dynamic_cast<MySamplerVoice*>(mySampler.getVoice(i))){

             auto& attack = *APVTS.getRawParameterValue("ATTACK0");
             auto& decay = *APVTS.getRawParameterValue("DECAY0");
             auto& sustain = *APVTS.getRawParameterValue("SUSTAIN0");
             auto& release = *APVTS.getRawParameterValue("RELEASE0");

             voice->updateAttack(attack.load());
             voice->updateDecay(decay.load());
             voice->updateSustain(sustain.load());
             voice->updateRelease(release.load());

           }

     }
     
     for(int i = 0; i < mySampler2.getNumSounds();++i){

         if(auto voice = dynamic_cast<MySamplerVoice*>(mySampler2.getVoice(i))){

             auto& attack = *APVTS.getRawParameterValue("ATTACK1");
             auto& decay = *APVTS.getRawParameterValue("DECAY1");
             auto& sustain = *APVTS.getRawParameterValue("SUSTAIN1");
             auto& release = *APVTS.getRawParameterValue("RELEASE1");

             voice->updateAttack(attack.load());
             voice->updateDecay(decay.load());
             voice->updateSustain(sustain.load());
             voice->updateRelease(release.load());

           }

     }
     
     for(int i = 0; i < mySampler3.getNumSounds();++i){

         if(auto voice = dynamic_cast<MySamplerVoice*>(mySampler3.getVoice(i))){

             auto& attack = *APVTS.getRawParameterValue("ATTACK2");
             auto& decay = *APVTS.getRawParameterValue("DECAY2");
             auto& sustain = *APVTS.getRawParameterValue("SUSTAIN2");
             auto& release = *APVTS.getRawParameterValue("RELEASE2");

             voice->updateAttack(attack.load());
             voice->updateDecay(decay.load());
             voice->updateSustain(sustain.load());
             voice->updateRelease(release.load());

           }

     }
     
     for(int i = 0; i < mySampler4.getNumSounds();++i){

         if(auto voice = dynamic_cast<MySamplerVoice*>(mySampler4.getVoice(i))){

             auto& attack = *APVTS.getRawParameterValue("ATTACK3");
             auto& decay = *APVTS.getRawParameterValue("DECAY3");
             auto& sustain = *APVTS.getRawParameterValue("SUSTAIN3");
             auto& release = *APVTS.getRawParameterValue("RELEASE3");

             voice->updateAttack(attack.load());
             voice->updateDecay(decay.load());
             voice->updateSustain(sustain.load());
             voice->updateRelease(release.load());

           }

     }
     
    
    
    
}

void NewProjectAudioProcessor::updateFilterParams(){
    
    ShouldUpdate = false;
    
//    for(int i = 0; i < mySampler.getNumSounds();++i){
//
//        if(auto voice = dynamic_cast<MySamplerVoice*>(mySampler.getVoice(i))){
//
//           auto& filterchoice = *APVTS->getRawParameterValue("FILTERCHOICE"+String(i));
//            auto& freq = *APVTS->getRawParameterValue("CUTOFF"+String(i));
//            auto& res = *APVTS->getRawParameterValue("RESONANCE"+String(i));
//
//            voice->updateType(filterchoice.load());
//            voice->updateCutoff(freq.load());
//            voice->updateRes(res.load());
//
//        }
//
//  }
//
//
//    for(int i = 0; i < mySampler2.getNumSounds();++i){
//
//        if(auto voice = dynamic_cast<MySamplerVoice*>(mySampler.getVoice(i))){
//
//           auto& filterchoice = *APVTS->getRawParameterValue("FILTERCHOICE"+String(i));
//            auto& freq = *APVTS->getRawParameterValue("CUTOFF"+String(i));
//            auto& res = *APVTS->getRawParameterValue("RESONANCE"+String(i));
//
//            voice->updateType(filterchoice.load());
//            voice->updateCutoff(freq.load());
//            voice->updateRes(res.load());
//
//        }
//
//  }
            
}


AudioBuffer<float>& NewProjectAudioProcessor::getWaveForm(int index)
{
//    auto sound = dynamic_cast<MySamplerSound*>(mySampler.getSound(index).get());
    if(index == 0){
    auto sound = dynamic_cast<MySamplerSound*>(mySampler.getSound(mySampler.getNumSounds() - 1).get());
    if (sound)
    {
        return *sound->getAudioData();
    }
    // just in case it somehow happens that the sound doesn't exist or isn't a SamplerSound,
    // return a static instance of an empty AudioBuffer here...
//    }
    static AudioBuffer<float> dummybuffer;
    return dummybuffer;
    }
    
    if(index == 1){
    auto sound2 = dynamic_cast<MySamplerSound*>(mySampler2.getSound(mySampler2.getNumSounds() - 1).get());
    if (sound2)
    {
        return *sound2->getAudioData();
    }
    // just in case it somehow happens that the sound doesn't exist or isn't a SamplerSound,
    // return a static instance of an empty AudioBuffer here...
//    }
    static AudioBuffer<float> dummybuffer2;
    return dummybuffer2;
    }
    
    if(index == 2){
        
        auto sound3 = dynamic_cast<MySamplerSound*>(mySampler3.getSound(mySampler3.getNumSounds() - 1).get());
        if (sound3)
        {
            return *sound3->getAudioData();
        }
        // just in case it somehow happens that the sound doesn't exist or isn't a SamplerSound,
        // return a static instance of an empty AudioBuffer here...
    //    }
        static AudioBuffer<float> dummybuffer3;
        return dummybuffer3;
        
        
        
    }
    
    if(index == 3){
        
        
        auto sound4 = dynamic_cast<MySamplerSound*>(mySampler4.getSound(mySampler4.getNumSounds() - 1).get());
        if (sound4)
        {
            return *sound4->getAudioData();
        }
        // just in case it somehow happens that the sound doesn't exist or isn't a SamplerSound,
        // return a static instance of an empty AudioBuffer here...
    //    }
        static AudioBuffer<float> dummybuffer4;
        return dummybuffer4;
        
        
        
    }

}


AudioProcessorValueTreeState::ParameterLayout NewProjectAudioProcessor::ParamLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    params.push_back (std::make_unique<juce::AudioParameterFloat>("ATTACK0", "Attack0", juce::NormalisableRange<float> { 0.1f, 5.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DECAY0", "Decay0", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("SUSTAIN0", "Sustain0", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("RELEASE0", "Release0", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));
    
    params.push_back (std::make_unique<juce::AudioParameterFloat>("ATTACK1", "Attack1", juce::NormalisableRange<float> { 0.1f, 5.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DECAY1", "Decay1", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("SUSTAIN1", "Sustain1", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("RELEASE1", "Release1", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));
    
    params.push_back (std::make_unique<juce::AudioParameterFloat>("ATTACK2", "Attack2", juce::NormalisableRange<float> { 0.1f, 5.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DECAY2", "Decay2", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("SUSTAIN2", "Sustain2", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("RELEASE2", "Release2", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));
    
    
    params.push_back (std::make_unique<juce::AudioParameterFloat>("ATTACK3", "Attack3", juce::NormalisableRange<float> { 0.1f, 5.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DECAY3", "Decay3", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("SUSTAIN3", "Sustain3", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("RELEASE3", "Release3", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));
    
    
    
    return { params.begin(), params.end() };
    
//
}

void NewProjectAudioProcessor::loadFile(const String& path,int index)
{
    if(index == 0){
    mySampler.loadFile(path);
    updateParams();
    }
    if(index == 1){
    mySampler2.loadFile(path);
    updateParams();
    }
    if(index == 2){
        mySampler3.loadFile(path);
        updateParams();
    }
    if(index == 3){
        mySampler4.loadFile(path);
        updateParams();
    }

}



void NewProjectAudioProcessor::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
    ShouldUpdate = true;
}


void NewProjectAudioProcessor::updateADSR(const float attack, const float decay, const float sustain, const float release){
    adsrData.updateAttack(attack);
    adsrData.updateDecay(decay);
    adsrData.updateSustain(sustain);
    adsrData.updateRelease(release);
    
    adsrData2.updateAttack(attack);
    adsrData2.updateDecay(decay);
    adsrData2.updateSustain(sustain);
    adsrData2.updateRelease(release);
}



void NewProjectAudioProcessor::setType(const int filtertype, const float cutoff, const float res){
     
    filterData.SetType(filtertype);
    filterData.setCutoff(cutoff);
    filterData.setRes(res);
  
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}


