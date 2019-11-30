# CPPKeys
Functional programming for key events

Nice little tool to read keys, mouse event in background in C++.

## Platform

Currently only supported on Windows, but in the future it may be possible to add Mac and Linux Distros since I made a good abtsraction layer.

## Usage

Import MouseInput for mouse
Import KeyboardInput for keyboard

Create object of those
Link events to the objects
If you want to go background mode use the method background
If you want to run it in your process on the main thread use mainthread
