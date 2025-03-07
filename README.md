# Simple Gain Plugin

A minimalist audio plugin developed using the JUCE framework. This project represents my first venture into audio plugin development, programming with C++, and building programs in Xcode.


## Overview

This simple gain plugin features a single slider that controls the volume of the audio signal. Built as a learning project to understand the fundamentals of audio plugin development with JUCE, and building in Xcode.

## Features

- Simple gain control with a responsive slider
- Available in VST3 and AU formats
- Cross-platform compatibility

## Development

This plugin was developed using:
- JUCE Framework
- Xcode IDE
- C++ programming language

The core functionality is implemented in `.h` and `.cpp` files, following JUCE's component-based architecture.

## How to Use

### Requirements
- Compatible DAW that supports VST3 or AU plugins
- optional: macOS, if using Xcode to build from files

### Install Steps
1. Locate the plugin vst3 and/or AU at 'SimpleGainPlugin/Builds/MacOSX/build/Debug'
1. Copy the `.vst3` file to your vst3 directory
2. Copy the `.component` file to your AU directory
3. Restart your DAW or rescan for plugins
5. The plugin should now be available in your DAW's plugin list

## Usage

1. Add the plugin to an audio track in your DAW
2. Adjust the gain slider to control the volume


## Future Improvements

While this plugin was created as a learning exercise, potential improvements could include:
- Adding a VU meter for visual feedback
- Implementing preset management
- Adding additional audio processing features

## License

MIT License

## Acknowledgements

- Thanks to the JUCE team for making audio plugin development accessible
