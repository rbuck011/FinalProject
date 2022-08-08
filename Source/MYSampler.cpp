/*
  ==============================================================================

    Sampler.cpp
    Created: 1 Jul 2022 12:27:38am
    Author:  Rhys William Buckham

  ==============================================================================
*/

#include "MYSampler.h"

void MYSampler::setup(int _voice){
    
      for (int i = 0; i < NumVoices; i++)
          {
              auto* voice = new MySamplerVoice();
              voice->setMidiNote(_voice);
              addVoice(voice);
          }
      FormatManager.registerBasicFormats();
      FormatManager2.registerBasicFormats();
      FormatManager3.registerBasicFormats();
      FormatManager4.registerBasicFormats();
}

void MYSampler::_addSound(const String& path){
    
    
    
    
}

void MYSampler::loadFile(const String &path){
//    index = Sample_1;

    String inst;
    File* file = new File(path);
  
    String FileName =  file->getFileName();

    //the reader can be a local variable here since it's not needed by the other classes after this
    
    std::unique_ptr<AudioFormatReader> reader{FormatManager.createReaderFor(*file)};

    BigInteger note;
    note.setBit(midiNote);
    double attackTimeSec = 0.1;
    double releaseTimeSec = 0.1;
    double maxSampleLength = 10.0;
    
    addSound(new MySamplerSound(path, *reader, note, midiNote, attackTimeSec, releaseTimeSec, maxSampleLength));
 
}
void MYSampler::SampleCount(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages){
    
    MidiMessage m;
    MidiBuffer::Iterator it { midiMessages };
    int sample;
    while (it.getNextEvent (m, sample))
    {
        if (m.isNoteOn())
            myIsNotePlayed = true;
        else if (m.isNoteOff())
            myIsNotePlayed = false;
    }
    mySampleCount = myIsNotePlayed ? mySampleCount += buffer.getNumSamples() : 0;
    
}


AudioBuffer<float>& MYSampler::getWaveForm(int& index)
{
    auto sound = dynamic_cast<MySamplerSound*>(getSound(index).get());
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



void MYSampler::noteOn(int midiChannel,
    int midiNoteNumber,
    float velocity)
{
    
    midiNote = midiNoteNumber;
    
    const ScopedLock sl (lock);

    
    for(int j = 0; j < getNumSounds(); j++)
        {
            auto* sound = getSound(j).get();
            if(sound->appliesToNote(midiNoteNumber) && sound->appliesToChannel(midiChannel))
            {
                for(int i = 0; i < getNumVoices(); i++)
                {
                    if(auto* voice = dynamic_cast<MySamplerVoice*>(getVoice(i)))
                    {
                        if(voice->playSound(midiNoteNumber) && voice->getCurrentlyPlayingSound())
                        {
                            stopVoice(voice, 0.0f, false);
                        }
                    }
                }

                for(int i = 0; i < getNumVoices(); i++)
                {
                    if(auto* voice = dynamic_cast<MySamplerVoice*> (getVoice(i)))
                    {
                        if(voice->playSound(midiNoteNumber) && !voice->getCurrentlyPlayingSound())
                        {

//                            Logger::outputDebugString("Start Voice: " + std::to_string(i) + " with Sound: " + std::to_string(j));

                            if(midiNoteNumber == 41 ||
                               midiNoteNumber == 42
                               )
                            {
                                    switch(midiNoteNumber)
                                    {
                                        case 41:
                                            for(int i = 0; i < getNumVoices(); i++)
                                            {
                                                if(auto* voice = dynamic_cast<MySamplerVoice*>(getVoice(i)))
                                                {
                                                    if(voice->playSound(42))
                                                    {
                                                        stopVoice(voice, 0.0f, false);
                                                        break;
                                                    }
                                                }
                                            }
                                    case 42:
                                        for(int i = 0; i < getNumVoices(); i++)
                                        {
                                            if(auto* voice = dynamic_cast<MySamplerVoice*>(getVoice(i)))
                                            {
                                                if(voice->playSound(43))
                                                {
                                                    stopVoice(voice, 0.0f, false);
                                                    break;
                                                }
                                            }
                                        }
//
                                    default:
                                        break;
                                    }
                            }

                            startVoice(voice, sound, midiChannel, midiNoteNumber, velocity);
                        }
                    }
                }
            }
        }

            
}
