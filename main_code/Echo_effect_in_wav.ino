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
  
  read_write();
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

    // filling empty....
    byte wavecontents[numByte_selected];
    byte wavecontentscopy[numByte_selected+30];
    // storing the data
    s_File.seek(44);
    for (int i = 0; i < numByte_selected; i++){
      sprintf(wavecontents, "%02X ", s_File.read());  
    } 
    //storing copy data
    for (int k = 0; k < numByte_selected+30; k++){
      if (k<30){
        wavecontentscopy[k] = 0b00000000; // 0x00
        //sprintf(wavecontentscopy, "%02X ",0b00000000 );
      }
      else{
        wavecontentscopy[k] = wavecontents[k-30];
        //sprintf(wavecontentscopy, "%02X ", wavecontents[k-30]);
      }
    }
     
    // echo....
    byte wavecontentsprocess[numByte_selected];
    for (int j = 0; j < numByte_selected; j++){
         wavecontentsprocess[j]  = wavecontentscopy[j] + wavecontents[j];
    }
    s_File.close();


  Serial.println("Creating ...");

  File myFile = SD.open("echo.wav", FILE_WRITE);

  myFile.close();

  // Check to see if the file exists:

  if (SD.exists("echo.wav")) {

    Serial.println("echo.wav exists.");

  } else {

    Serial.println("echo.wav doesn't exist.");

  }
    
    byte finalechodata[numByte_selected + 44];
    File sEcho = SD.open("echo.wav",FILE_WRITE);
//    for (int m = 0; m < numByte_selected + 44; m++)
//    {
//      sEcho.seek(m);
//      if (m < 44)
//      {
//        finalechodata[m] = waveheader[m];
//        sEcho.println(finalechodata[m]);
//        //sprintf(finalechodata, "%02X ",waveheader[m] );
//      }
//      else
//      {
//        finalechodata[m] = wavecontentsprocess[m - 44];
//        sEcho.println(finalechodata[m]);
//        //sprintf(finalechodata, "%02X ",wavecontentsprocess[m - 44] );
//      }
//    }
//    Serial.println("done");
//    //sEcho.println(finalechodata);
//    sEcho.close();  
    
      // if the file opened okay, write to it:
  if (sEcho) {
    Serial.print("Writing ...");
    for (int m = 0; m < numByte_selected + 44; m++)
    {
      sEcho.seek(m);
      if (m < 44)
      {
        finalechodata[m] = waveheader[m];
        sEcho.println(finalechodata[m]);
        //sprintf(finalechodata, "%02X ",waveheader[m] );
      }
      else
      {
        finalechodata[m] = wavecontentsprocess[m - 44];
        sEcho.println(finalechodata[m]);
        //sprintf(finalechodata, "%02X ",wavecontentsprocess[m - 44] );
      }
    }
    // close the file:
    sEcho.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening");
  }

  
    for (int i = 0; i < numByte_selected; i++){
      //Serial.println(wavecontents[i]);
      //Serial.println(wavecontentscopy[i]);
      //Serial.println(wavecontentsprocess[i]);
      //Serial.println(finalechodata[i],HEX);
    }
    //Serial.print(sizeof(finalechodata));     
}
