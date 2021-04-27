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
    numBytes = firstB + (nextB << 8);
    Serial.print("Num Bytes ");
    Serial.println(numBytes);
    int numByte_selected = 80;
    Serial.print("numByte_selected");
    Serial.println(numByte_selected);
    s_File.seek(0); 
    char waveheader[44];
    for (int h = 0; h < 44; h++){
      //waveheader[h] = s_File.read() ;
      //Serial.println(s_File.read(),HEX);
      sprintf(waveheader, "%02X ", s_File.read());
      //Serial.println(waveheader[h],HEX);
      }
    s_File.seek(44); 
    // storing the data
    byte wavecontents[numByte_selected];
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
//    for (int i = 0; i < numByte_selected; i++){
//          Serial.println(filteredwave[i]);
//    }
    Serial.println("Creating ...");

    File myFile = SD.open("filter.wav", FILE_WRITE);

    myFile.close();

  // Check to see if the file exists:

    if (SD.exists("filter.wav")) {

      Serial.println("filter.wav exists.");

     } else {

        Serial.println("filter.wav doesn't exist.");

      }     
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
        sFilter.println(finalfiltereddata[m]);
        //sprintf(finalfiltereddata, "%02X ",waveheader[m] );
      }
      else
      {
       finalfiltereddata[m] = filteredwave[m - 44];
        sFilter.println(finalfiltereddata[m]); 
        //sprintf(finalfiltereddata, "%02X ",filteredwave[m - 44] );
      }
    }
    sFilter.close();
    Serial.println("done");
    } else {
    // if the file didn't open, print an error:
    Serial.println("error opening");
  } 
  //Serial.print(sizeof(finalfiltereddata));      
}
