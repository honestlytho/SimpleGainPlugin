#include "PluginProcessor.h"
#include "PluginEditor.h"

SimpleGainAudioProcessorEditor::SimpleGainAudioProcessorEditor (SimpleGainAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Set up the gain slider
    gainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    addAndMakeVisible(gainSlider);
    
    // Set up the gain label
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(gainLabel);
    
    // Connect the slider to the parameter
    gainAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(
        audioProcessor.parameters, "gain", gainSlider));
    
    // Set the plugin window size
    setSize (300, 200);
}

SimpleGainAudioProcessorEditor::~SimpleGainAudioProcessorEditor()
{
}

void SimpleGainAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Fill the background
    g.fillAll (juce::Colours::darkgrey);
}

void SimpleGainAudioProcessorEditor::resized()
{
    // Layout the components
    auto area = getLocalBounds().reduced(20);
    
    gainLabel.setBounds(area.removeFromTop(20));
    gainSlider.setBounds(area);
}
