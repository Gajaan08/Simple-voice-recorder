#include <TMRpcm.h>
#include <SD.h>
#include <SPI.h>
TMRpcm audio;
// push button for start and stop recording

char filename[50] = "test.wav";
const int mic_pin = A0;
const int sample_rate = 44100;
#define SD_CSPin 10

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  //Sets up the pins
  pinMode(mic_pin, INPUT);
  //audio.speakerPin=9;
  Serial.println("loading... SD card");
  if (!SD.begin(SD_CSPin)) {
    Serial.println("An Error has occurred while mounting SD");
  }
  while (!SD.begin(SD_CSPin)) {
    Serial.print(".");
    delay(500);
  }
  audio.CSPin = SD_CSPin;
  Serial.println(file_name);
  audio.startRecording(file_name, sample_rate, mic_pin);
  Serial.println("startRecording ");
  delay(10000);
  audio.stopRecording(file_name);
  Serial.println("stopRecording");
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
 
}
//void play(){
//  audio.stopPlayback();
//  audio.play("test.wav");
//  delay(100);
//  return;
//}
