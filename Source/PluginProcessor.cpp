#include "PluginProcessor.h"
#include "PluginEditor.h"

SimpleGainAudioProcessor::SimpleGainAudioProcessor()
    : AudioProcessor (BusesProperties()
                     .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                     .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     ),
      parameters (*this, nullptr, "Parameters", createParameterLayout())
{
    // Get a pointer to the gain parameter
    gainParameter = parameters.getRawParameterValue("gain");
}

SimpleGainAudioProcessor::~SimpleGainAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout SimpleGainAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    // Add gain parameter
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "gain",                  // Parameter ID
        "Gain",                  // Parameter name
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),  // Range (0 to 1, step size 0.01)
        0.5f));                  // Default value
    
    return layout;
}

const juce::String SimpleGainAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleGainAudioProcessor::acceptsMidi() const
{
    return false;
}

bool SimpleGainAudioProcessor::producesMidi() const
{
    return false;
}

bool SimpleGainAudioProcessor::isMidiEffect() const
{
    return false;
}

double SimpleGainAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleGainAudioProcessor::getNumPrograms()
{
    return 1;
}

int SimpleGainAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleGainAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SimpleGainAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleGainAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void SimpleGainAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Prepare for playback
}

void SimpleGainAudioProcessor::releaseResources()
{
    // Release resources when not playing
}

bool SimpleGainAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // Accept mono or stereo for input and output
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

void SimpleGainAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear any output channels that don't contain input data
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Get the current gain value from the parameter
    float currentGain = gainParameter->load();

    // Apply gain to all channels
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // Apply gain to each sample
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            channelData[sample] *= currentGain;
    }
}

bool SimpleGainAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* SimpleGainAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor (*this);
}

void SimpleGainAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // Save the current plugin state
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void SimpleGainAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Restore the plugin state
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
}

// This creates new instances of the plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleGainAudioProcessor();
}
