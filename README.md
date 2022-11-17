# SIMPLE VOICE RECORDER

## Introduction

* The main objective of this project was to design and implement a voice/sound recorder capable of simple voice modulation. 
Hence, we have developed a simple voice recorder that can playback audio which is recorded by the user through a microphone. 
The user is also able to implement a low-pass filter effect to recorded audio and playback the modified sound as well. Up to 3 
recordings without any effects can be saved in the device and can be selectively played back, and we have made this using the 
ATmega328p microcontroller and various other inexpensive electronic components. Currently we have developed the physical prototype
as a breadboard implementation. Furthermore, we have been involved with the PCB and enclosure designing which will influence the 
production of the finished product as a commercially successful device. Problems, improvements and alternatives regarding this project 
were also discussed and evaluated.

* When designing the functionality of the prototype, many critical factors have to be considered. Firstly, this project is implemented 
using appropriate ADC and DAC with 8 bit PCM. Hence, aspects such as sampling rate, quantization and compression needed for the PCM should
be evaluated when doing so. Furthermore, the storage of recorded audio tracks in an SD card is another point of importance, with the number
of samples stored, the file format used for storage etc. needed to be considered as well. With regards to audio enhancement, the type of 
effects to be implemented are essential to be identified when developing the algorithm. Next, concerning the perspective of the user of the 
prototype, elements such as input device, UI and output device design should be executed. The use of an appropriate microphone module and any 
other required input devices, an LCD screen to act as a clean and simple UI and a speaker with an appropriate amplification setup are included 
in this. Thus, the aforementioned features were experimented with using various parameters and variables and weighing out the pros and cons 
before they were finalized for this project. Hence, this paper details the attempt to develop a working prototype (breadboard implementation) 
of a simple voice recorder using the ATmega 328p microcontroller alongside other affordable electronic components, in a suitable way that can 
be expanded for commercial use later on.

 ## List of components used
 
### Modules and External components
• 1 x KY-037 Microphone module
• 1 x 16x2 Alphanumeric LCD Display
• 1 x Micro SD Card Module
• 1 x PCF8574 LCD I2C
• 1 x 4x4 Keypad
• 1 x TPA3118 Amplifier module
• 1 x 8Ωspeaker
• 1 x 10 KΩ potentiometer
• 1 x 9V Battery

### Main PCB
• 1 x ATmega 328p microcontroller
• 1 x DAC0808 IC
• 1 x LM7805CV Power regulator
• 1 x 16 kHz crystal oscillator
• 3 x100 nF capacitors
• 2 x 22 pF capacitors
• 1 x Switch
• 3 x10 KΩ resistors
• 1 x 330 nF capacitor
• 1 x 330Ω resistor

## Matlab 

In this project for the effect to be induced in playback, lowpass filtering is used. For this effect, each sample is read one by one from 
the pre-recorded voice sample stored in the SD card,and the values corresponding to the filtered output are stored in a new file(effects file).
In the playback, the effects file is opened and played. For computing the values for the filtered output, the corresponding Matlab function is 
found using the first-order lowpass filter transfer function. the Matlab code and the calculation for the transfer function for lowpass first-order
filtering done for an audio sample in wave file. And the spectrum obtained from the Matlab. Here the audio sample is filtered using a lowpass filter
with a cutoff frequency of 1000Hz. Similarly, in Matlab we had tested adding echo effects for the recorded wave file. In this, each sample of the 
input signal is read and an empty array is created to store the set of past sample data and then combined to give the resultant output. The Matlab 
code done for the echo effects shows the original and resultant spectrum after the echo effects. However, the echo effects part of our testing was 
not implemented in the final product due to various limitations

### Low Pass Filter
![filterd sepectrum](https://user-images.githubusercontent.com/81348862/202334447-2ee18cca-3b6c-415f-8cc3-787bd2b0cd03.png)

### Echo effect
![echo](https://user-images.githubusercontent.com/81348862/202334333-031448db-a2fc-43ea-b38c-3995333025b0.png)

## Arduino 
With the physical implementation, the waveform obtained for the low pass filtering for a random signal

![effects](https://user-images.githubusercontent.com/81348862/202334676-b41c139d-98dd-46ec-bb25-c4f0abb8c70d.png)

## ALGORITHM DEVELOPMENT

 The following block diagram is shown in represents the basic functionality of a simple voice recorder. By following these basic steps, we develop 
 the related algorithms and appropriate functions in the Arduino platform and design and simulates in proteus software.
 
 ![flowchart](https://user-images.githubusercontent.com/81348862/202334923-cc5211b7-1e20-49e5-b3df-8a1888ea6246.jpeg)

## SIMULATIONS AND INPUT-OUTPUT WAVEFORMS 

The Arduino implementation is simulated through proteus professional software. The circuit design for the proteus simulation. As an audio sample here 
sinusoidal signal of a single frequency of 500Hz is used. Samples are taken at a rate of nearly 4000 samples per second and stored in a comma-separated 
value file format in the SD card.

![protues sim](https://user-images.githubusercontent.com/81348862/202335237-10854471-da3b-4835-b7bd-f30e3000c924.png)

## results

![inout_output](https://user-images.githubusercontent.com/81348862/202335319-a4e371c4-a801-40c3-a364-e3b05677f641.png)

![input and effects](https://user-images.githubusercontent.com/81348862/202335347-243e25de-8dd6-4653-91c6-5488e6262d95.png)

## SCHEMATIC AND PCB DESIGN 
The PCB design for the simple voice recorder circuit was made in Altium designer software. PCB design contains three main units they are power supply
unit, main microcontroller ATmega 328p, DAC IC.

### PCB Design

![pcb3D](https://user-images.githubusercontent.com/81348862/202335670-16caac5f-e9be-4b35-be93-1e8837f8a7e8.png)

![pcb](https://user-images.githubusercontent.com/81348862/202335701-79820b22-12b2-4036-94ac-974ce35d983f.png)

### ENCLOSURE DESIGN

 In designing the enclosure we considered several factors. Convenient usability was considered when deciding the placement of buttons, display and the 
 microphone. Unscrewing the two plates would reveal all the connections and the battery hostler for easy replacement of parts. Maintaining aesthetic look 
 and feel complementing the functionality, was also a concern. 
 
 ![enclosure](https://user-images.githubusercontent.com/81348862/202335995-4ed8cff1-af8e-4b65-9dce-ea5d036770e5.png)

##  USER INTERFACE 
For the user to interact with our product, we have included a keypad which can be used for selection of the recording option and selective playback of 
the different recorded files with or without effects. From the simulation stage we are developing the final product which will work as follows. When the 
user turns on the device first a greeting message will be shown, then the selective option will be displayed. Six selective buttons are present for recording, 
playing the original file, playing the filter file, and selecting the appropriate audio clip. In the simulation, we designed for our device to contain upto 
three recordings. If we try to go beyond three files, there will be a prompt to delete the files first. we implemented the user interface in the simulation.
To start recording, the user should press the record button (number 6) and after the subsequent press of the record button, the recording will be completed.
After that, to play the original file, the user should press the play button (number 4). Then they have to select the file number, whether it is one, two or three.
Similarly, for the play effects, the user should press the effect button (number 5) and choose the respective audio clip number.

![ui](https://user-images.githubusercontent.com/81348862/202336236-db33cb66-53bf-40cb-9479-073382f058c0.png)

## PHYSICAL PROTOTYPE 
The following image shows the physical circuit implementation using the breadboard. Using the aforementioned theories, simulations and components mentioned 
in the METHOD section, we have designed this circuit in a user-friendly way to achieve effective operation.

![bi](https://user-images.githubusercontent.com/81348862/202336419-ecff3cb8-0973-4a91-95b5-8be034e150a9.jpeg)





