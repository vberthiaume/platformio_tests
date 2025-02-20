#define USE_SPIFFS 0

#if USE_SPIFFS
#include "SPIFFS.h"
String fileContent;
#else
#include <Arduino.h>
#endif

#include <iostream>

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    // wait for serial monitoring
  }

#if USE_SPIFFS
  if (!SPIFFS.begin())
  {
    std::cout << "An Error has occurred while mounting SPIFFS, printed using std::cout" << std::endl;
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
#endif
}

void loop()
{
#if USE_SPIFFS
  if (!fileContent.isEmpty())
  {
    std::cout << "fileContent printed with std::cout: " << fileContent.c_str() << std::endl;
    Serial.println(fileContent);
  }
  else
  {
    std::cout << "couldn't open the file";
  }
#else
  Serial.println("printing from Serial.println");
  std::cout << "printing from std::cout\n";
#endif
}
