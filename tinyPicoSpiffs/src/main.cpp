#include "SPIFFS.h"

String fileContent;
#include <iostream>

void setup()
{
  Serial.begin(115200);
  delay(10000);
  Serial.println("delay done!");

  if (!SPIFFS.begin())
  {
    Serial.println("SPIFFS.begin() failed");
    return;
  }

  File file = SPIFFS.open("/text.txt");
  if (!file)
  {
    Serial.println("Failed to open text.txt");
    return;
  }

  while (file.available())
    fileContent += (char)file.read();

  file.close();
}

void loop()
{
  if (!fileContent.isEmpty())
    Serial.println(fileContent);
  else
    Serial.println("could not read file");
}
