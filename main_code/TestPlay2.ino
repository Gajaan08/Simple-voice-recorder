// simple Uno program to play sound data from an SD Card using Timer2
// surprisingly it works !

// it is assumed that the user will study the Atmel Atmega328 datasheet
// and the Arduino Pin Mapping for the Uno/

/*
 The circuit: (based directly on the SD Card library examples)
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

 * the sound output is on Pin3 which is OC2B
 * Note that OC2A is pin 11 which is needed by the SD Card.
 
*/

#include <SPI.h>
#include <SD.h>
#define SD_ChipSelectPin 4 

File sFile;
char filename[] = "steam8b.wav";

const byte soundPin = 3; // OC2B
int dataCount = 0;
unsigned int numBytes;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting simple WAV demo\n");
  
  pinMode(soundPin, OUTPUT);

  
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");  
    return;
  }
  sFile = SD.open(filename);
  if( !sFile ){ 
    Serial.println("File not opened"); 
  }
  else {
//      // first show the data at the start of the WAV file
//    Serial.println("RIFF section");
//    for (byte i = 0; i < 12; i++){
//      Serial.print(sFile.read(), HEX);
//      Serial.print(' ');
//    }
//    Serial.println();
//    Serial.println();
//    
//    Serial.println("Format section");
//    for (byte i = 12; i < 36; i++){
//      Serial.print(sFile.read(), HEX);
//      Serial.print(' ');
//    }
//    Serial.println();
//    Serial.println();
//    
//    Serial.println("Data Header");
//    for (byte i = 36; i < 44; i++){
//      Serial.print(sFile.read(), HEX);
//      Serial.print(' ');
//    }
//    Serial.println();
//    Serial.println();
//    
//    Serial.println("First 32 data bytes");
//    for (int i = 0; i < 32; i++){
//      Serial.print("0x");
//      Serial.print(sFile.read(), HEX);
//      Serial.print(',');
//    }
//    Serial.println();
//    Serial.println();
//    
      // Now prepare to play the sound

      // move the pointer back to the start of the data size
    sFile.seek(40);
      // this assumes the data size fits in 2 bytes. There are 4 bytes to read if necessary
    byte firstB = sFile.read();
    byte nextB = sFile.read();
    // firstB = 11101110
    // nextB = 10101101
    // size = 101011011110110
    // numBytes = 10101101000000000 + 11101110
    numBytes = firstB + (nextB << 8);
    Serial.print("Num Bytes ");
    Serial.print(numBytes);
    Serial.println();
    
      // move the pointer back to the start of the data
    sFile.seek(44); 
    
//      // set up Timer2 to run at 11025 Hz (or near it)
//    TCCR2A = 0b00100011; // fast PWM mode with OC2B changed
//    TCCR2B = 0b00000010; // last 3 bits 010 select clock/8 or 16MHz/8 = 2MHz
//    OCR2A = 179; // should give 11025 Hz, might need tweaking
//    OCR2B = 80;
//      // set the interrupt last thing so other stuff is not affected
//    TIMSK2 = 0b00000001; // Overflow interrupt enabled

    process(sFile)
    
  }

}

void process(File sFile)
{
    // filling empty....
    byte wavecontents[numBytes];
    byte wavecontentscopy[numBytes+30];
    for (int k = 0; k < 30; k++){
      wavecontentscopy[k] = 0b00000000 // 0x00
    }

    // storing the data
    for (int i = 0; i < numBytes; i++){
      byte data = sFile.read();
      wavecontents[i] = data
      wavecontentscopy[i+30] = data

    }

    // echo....
    byte wavecontentsprocess[numBytes];
    for (int j = 0; j < numBytes; j++){
         wavecontentsprocess[j]  = wavecontentscopy[j] + wavecontents[j];
    }

    // filtering
    byte threshold = 0x40;
    byte filteredwave[numBytes];
    for (int p = 0; p < numBytes; p++)
    {
       if (wavecontent[p] < threshold)
        {
          filteredwave[p] = wavecontent[p]
        }
        else
        {
          filteredwave[p] = 0x00;
        }
    }

    
}



void loop() {
}

//ISR (TIMER2_OVF_vect) {
//  OCR2B = sFile.read(); // this represents the amplitude of each sample
//  dataCount ++;
//  if (dataCount >= numBytes) { // go back to the start of the file
//    dataCount = 0;
//    sFile.seek(44);
//  }
//}
