#include <TMRpcm.h>
#include <SD.h>
#include <SPI.h>

TMRpcm audio; // make instance variable
int file_number = 0;
char filePrefixname[50] = "recording";
char exten[10] = ".wav";

const int recordLed = 2;
const int mic_pin = A0;
const int sample_rate = 8000;

#define SD_CSPin 10 

void setup() {
  // put your setup code here, to run once:
  //initializes the serial connection between the Arduino and any connected serial device(e.g. computer, phone, raspberry pi...)
  Serial.begin(9600);
  //Sets up the pins
  pinMode(mic_pin, INPUT);
  pinMode(recordLed, OUTPUT);
  Serial.println("loading... SD card");
  if (!SD.begin(SD_CSPin)) {
            Serial.println("An Error has occurred while mounting SD");
  }
  while (!SD.begin(SD_CSPin)) {
            Serial.print(".");
            delay(500);
  }
  audio.CSPin = SD_CSPin;
}

// delay function for serial log.
void wait_min(int mins) {
  int count = 0;
  int secs = mins * 60;
  while (1) {
            Serial.print('.');
            delay(1000);
            count++;
            if (count == secs) {
            count = 0;
            break;
            }
  }
  Serial.println();
  return ;
}

void loop() {
Serial.println("##");
  char fileSlNum[20] = "";
  itoa(file_number, fileSlNum, 10);
  char file_name[50] = "";
  strcat(file_name, filePrefixname);
  strcat(file_name, fileSlNum);
  strcat(file_name, exten);
  Serial.print("New File Name: ");
  Serial.println(file_name);
  digitalWrite(recordLed, HIGH);
  audio.startRecording(file_name, sample_rate, mic_pin);
  Serial.println("startRecording ");
  // record audio for 2mins. means, in this loop process record 2mins of audio.
  // if you need more time duration recording audio then
  // pass higher value into the wait_min(int mins) function.
  wait_min(2); // This is the length of the audio file which is set to 2 minutes
  digitalWrite(recordLed, LOW);
  audio.stopRecording(file_name);
  Serial.println("stopRecording");
  file_number++;
  Serial.println("##");

  
  // open wave file from sdcard
  File myFile = SD.open("test.wav");
  if (!myFile) {
    // if the file didn't open, print an error and stop
    Serial.println("error opening test.wav");
    while (true);
  }
}
