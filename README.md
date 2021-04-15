# Arduino_IR

This is a personal project that I've been working on periodically since January 2021. The goal was to create a software defined infrared tool that would teach me about building electronics, and could act as a foundation for any future, more complicated projects. 

## The Project
![Le Projekt](https://cdn.discordapp.com/attachments/522123076037640197/832021320748630027/image0.jpg)
The project itself consists of 3 main parts - The input, output, and controls. In its current state, the Arduino records a signal from a remote, saves it to an array, and replays that signal on command. 

### Input
![](https://cdn.discordapp.com/attachments/522123076037640197/832021324024905758/image2.jpg)
Before anything else, the Arduino has to receive a signal. This is received as a sequence of high and low pulses. These pulses are very quick (in the microseconds), so recording the signals is a time-sensitive operation. Because of this, Arduino built-in commands are too slow to accurately read the signals. Instead, a [register](https://www.arduino.cc/en/Reference/PortManipulation) which constantly has the state of the pins stored, is used to read the pin. This allowed for accurate measurement of IR signals, which were verified by reading the same signals on an oscilloscope.

### Output
![](https://cdn.discordapp.com/attachments/522123076037640197/832021323633917972/image1.jpg)
The IR LED more or less plays back exactly what was recorded by the receiver. However, the logical high state, rather than constantly on, modulates the LED on and off at around 38kHz. This tells the receiving device to listen to the signal, rather than ignoring it as background noise. It also helps keep the LED from burning out. The pulses on the output LED were also adjusted according to readings on an oscilloscope. 

### Controls
![](https://cdn.discordapp.com/attachments/522123076037640197/832021324452462642/image3.jpg)
Currently, there are three buttons to control what function to execute. The red button controls whether or not to record a new signal, and the green buttons select which signal will be either recorded or replayed. After learning about floating pins the hard way, I wired up every button with [pull down resistors](https://en.wikipedia.org/wiki/Pull-up_resistor), creating a clear logical difference between low and high voltage. 

## The Future
Moving forward, I will likely condense everything into a smaller form factor using an Arduino Nano, as well as creating some sort of permanent housing for it. I may also add some more features like an IR jammer, or macros so it can do multiple operations in succession.
