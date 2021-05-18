#include <SPI.h>
#include <SD.h>
#include <MCP_DAC.h>
MCP4921 myDAC;
File recFile;
#define CS_pin 10;
int sampledata[81];
int sampledatacopy[101];
int fastdata[4];
int i=0;
int j=0;
String line;
int line_;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  recFile = SD.open("test.txt", FILE_READ);
  if (recFile) {
      Serial.println("File opened sucessfully");
  } else {
      Serial.println("error opening REC.txt");
  }
  for(int k=0;k<50;k++){
      sampledatacopy[k]=0;
    }
      while(recFile.available()){
      line = recFile.readStringUntil('\n');
      line_=line.toInt();
      Serial.println(line_);
      
      //change amplitude
//      int CA=change_amplitude(line.toInt());
//      Serial.println(CA);

      //faster
      //Serial.println(j);
      if (j<2){
        fastdata[j]=line_;
        j++;
      }
      else if (j == 2){
//        int FS=faster();
//        Serial.println(FS);
        j=0;
      }
      
       //echo
      if (i<80){
      sampledata[i] = line_;
      sampledatacopy[i+20] = line_;
      i++;
      }
      else if (i==80){
        i=0;
      }
//      int EH=echo();
//      Serial.println(EH);
  }
    recFile.close();
}

void loop() {
  // put your main code here, to run repeatedly:

}

int change_amplitude(int data){
  int val = 0.8*data;
  return val;
}

int faster(){
  int fd = 0.5*(fastdata[0]+fastdata[1]);
  return fd;
}

int echo(){
  int echodata = sampledata[i] + (0.5*sampledatacopy[i]);
   if (echodata>255) {
    echodata=255;
  }
  return echodata;
}
