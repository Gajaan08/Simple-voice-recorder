#include <SD.h>
#include <SPI.h>

int sdpin=10;

void setup()
{
  Serial.begin(9600);
  pinMode(sdpin, OUTPUT);
  if (SD.begin())
  {
    File root = SD.open("/");
    printFiles(root,0);
  }
}

void loop()
{

}

void printFiles(File dir, int numTabs)
{
  while (true)
  {
    File entry =  dir.openNextFile();
    if (! entry)
    {
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++)
    {
      Serial.print('\t');
    }
    Serial.println(entry.name());
    entry.close();
  }
}
