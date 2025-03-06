#include "SPIFFS.h"

String fileContent;
#include <iostream>

void setup()
{
  Serial.begin(115200);
  delay(10000);

  Serial.println("delay done, attempting to begin spiffs");
  if (!SPIFFS.begin())
  {
    Serial.println("SPIFFS.begin() failed");
    return;
  }
  else
  {
    Serial.println("SPIFFS.begin() success");
  }

  File file = SPIFFS.open("/text.txt");
  if (!file)
  {
    Serial.println("Failed to open text.txt");
    return;
  }
  else
    Serial.println("text.txt opened");

  while (file.available())
    fileContent += (char)file.read();

  Serial.println("closing file");
  file.close();

  Serial.println("all done");
}

void loop()
{
  if (!fileContent.isEmpty())
    Serial.println(fileContent);
  else
    Serial.println("could not read file");

  delay(1000);
}