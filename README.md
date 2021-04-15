# Arduino_IR

This is a personal project of mine that I've been working on periodically since January 2021. The goal was to create a software defined infrared tool that would teach me about building electronics, and could act as a foundation for any future, more complicated projects. 

## The Project
The project itself consists of 3 main parts - The input, output, and controls. In its current state, the Arduino records a signal from a remote, saves it to an array, and replays that signal on command. 

### Input
Before anything else, the Arduino has to receive a signal this is received by the arduino as a sequence of high and low pulses. These pulses are very quick (in the microseconds), so recording the signals is a time-sensitive operation. Because of this, Arduino built in commands were too slow for to read the signals. Instead, a [register](https://www.arduino.cc/en/Reference/PortManipulation) was used to read the pin, which constantly has the state of the pins stored. This allowed for accurate measurement of IR signals, which were verified with an oscilloscope.

### Output
The IR LED more or less plays back exactly what was received by the receiver. However, the logical high state, rather than constantly on, modulates the LED on and off at around 38kHz. This tells the receiving device to listen to the signal, rather than ignoring it as background noise. It also helps keep the LED from burning out. The pulses on the output LED were also adjusted according to redings on the oscilloscope. 

### Controls
Currently, there are three buttons to control what function to execute. The red button controls whether or not to record a new signal, and the green buttons select which signal will be either recorded or replayed. After learning about floating pins the hard way, I wired up every button with [pull down resistors](https://en.wikipedia.org/wiki/Pull-up_resistor), creating a clear difference between low and high voltage. 

## The Future
Moving forward, I will likely condense everything onto a smaller form factor using an Arduino Nano, as well as creating some sort of permanent housing for it. I may also add some more features like an IR jammer, or macros so it can do multiple operations in succession. 
