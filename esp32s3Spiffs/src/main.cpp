#include "SPIFFS.h"

String fileContent;

void setup()
{
  Serial.begin(115200);
  while (! Serial)
  {
    //wait for serial monitoring
  }

  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  File file = SPIFFS.open("/text.txt");
  if (!file)
  {
    Serial.println("Failed to open file for reading");
    return;
  }

  while (file.available())
    fileContent += (char)file.read();

  file.close();
}

void loop()
{
  if (! fileContent.isEmpty())
    Serial.println(fileContent);
  else
    Serial.println("couldn't read the file!!");
}
