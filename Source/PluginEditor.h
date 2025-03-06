#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SimpleGainAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SimpleGainAudioProcessorEditor (SimpleGainAudioProcessor&);
    ~SimpleGainAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SimpleGainAudioProcessor& audioProcessor;
    
    juce::Slider gainSlider;
    juce::Label gainLabel;
    
    // This will handle the attachment of the slider to the parameter
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleGainAudioProcessorEditor)
};
