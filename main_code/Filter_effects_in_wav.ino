#include <SD.h>
#include <SPI.h>
char filename[50] = "test.wav";
#define SD_CSPin 10
unsigned int numBytes;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("loading... SD card");
  if (!SD.begin(SD_CSPin)) {
    Serial.println("An Error has occurred while mounting SD");
  }
  while (!SD.begin(SD_CSPin)) {
    Serial.print(".");
    delay(500);
  }
  read_write() ;  
}
void loop(){  
}
void read_write(){
     File s_File = SD.open("test.wav");
    s_File.seek(40);
    byte firstB = s_File.read();
    byte nextB = s_File.read();
    byte next1B = s_File.read();
    byte next2B = s_File.read();
    numBytes = firstB + (nextB << 8)+(next1B << 16)+(next2B << 24);
    Serial.print("Num Bytes ");
    Serial.println(numBytes);
    //int numByte_selected = numBytes;
    int numByte_selected = 100;
    Serial.print("numByte_selected");
    Serial.println(numByte_selected);
    byte waveheader[44];
    s_File.seek(0); 
    for (int h = 0; h < 44; h++){
      waveheader[h] = s_File.read() ;
    }
    // filling empty....
    byte wavecontents[numByte_selected];
    // storing the data
    s_File.seek(44);
    for (int i = 0; i < numByte_selected; i++){
      sprintf(wavecontents, "%02X ", s_File.read());  
    } 

     // filtering
    byte threshold = 0x10;
    byte filteredwave[numByte_selected];
    for (int p = 0; p < numByte_selected; p++)
    {
       if (wavecontents[p] < threshold)
        {
          //filteredwave[p] = wavecontents[p];
          sprintf(filteredwave , "%02X ", wavecontents[p]);
        }
        else
        {
          //filteredwave[p] = 0x00;
          sprintf(filteredwave , "%02X ", 0x10);
        }
    }
    
    s_File.close();
    
    Serial.println("Creating ...");
    File myFile = SD.open("filter.wav", FILE_WRITE);
    myFile.close();
    
    byte finalfiltereddata[numByte_selected + 44];
    File sFilter = SD.open("filter.wav",FILE_WRITE);
    if (sFilter){
      Serial.print("Writing ...");
    for (int m = 0; m < numByte_selected + 44; m++)
    {
      sFilter.seek(m);
      if (m < 44)
      {
        finalfiltereddata[m] = waveheader[m];
      }
      else
      {
       finalfiltereddata[m] = filteredwave[m - 44];
      }
    }
    sFilter.write((byte *)&finalfiltereddata,numByte_selected + 44);
    sFilter.close();
    Serial.println("done");
    } else {
    // if the file didn't open, print an error:
    Serial.println("error opening");
  } 
//  for (int i = 0; i < numByte_selected; i++){
//          Serial.println(filteredwave[i]);
//    }
    
    File sFile = SD.open("filter.wav");
    if( !sFile ){ 
        Serial.println("File not opened"); 
    }
    else {
        for (byte i = 0; i <numByte_selected+44 ; i++){
        
            Serial.println(sFile.read());
        }
    }
}
