#include <SPI.h>
#include <SD.h>
File recFile;
File halffreq;
File fasterfile;
File echofile;
#define CS_pin 10;
int sampledata[100];
int fastdata[4];
int i,j,m,c=0;
String line;
int line_;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization.");
  SD.remove("halffreq.txt");
  SD.remove("faster.txt");
  SD.remove("echo.txt");
  recFile = SD.open("rec.txt", FILE_READ);
  halffreq = SD.open("halffreq.txt",FILE_WRITE);
  fasterfile = SD.open("faster.txt",FILE_WRITE);
  echofile = SD.open("echo.txt",FILE_WRITE);
  
  for(int k=0;k<20;k++){
      sampledata[k]=0;
    }
   while(recFile.available()){
      line = recFile.readStringUntil('\n');
      line_=line.toInt();
     // Serial.println(line_);
      m++;
      
      //half frequency
      if (m%2==1){
        halffreq.println(String(line_));  
      }

      //faster
      if (j<2){
        fastdata[j]=line_;
        j++;
      }
      else if (j == 2){
        int FS=faster();
        fasterfile.println(String(FS));
        j=0;
      }
      
       //echo
      if (i<80){
        sampledata[i+20] = line_;
        i++;
      } 
      if (i>59 && i<80){
        sampledata[c] = line_;
        c++;
      }
      if ((i==79) || (c==19)){
        i,c = 0;
      }
      int EH=echo();
      echofile.println(String(EH));
  }
    fasterfile.close();
    echofile.close();
    halffreq.close();
    recFile.close();
    Serial.println("Finished");
}

void loop() {
  // put your main code here, to run repeatedly:

}

int faster(){
  int fd = 0.5*(fastdata[0]+fastdata[1]);
  return fd;
}

int echo(){
  int echodata = sampledata[i+20] + (0.5*sampledata[i]);
  if (echodata>255) {
      echodata=255;
  }
  return echodata;
}


      //change amplitude
//      int CA=change_amplitude(line.toInt());
//      Serial.println(CA);


//int change_amplitude(int data){
//  int val = 0.8*data;
//  return val;
//}
