#include <Arduino.h>
#include <iostream>
#include "SPIFFS.h"

String fileContent;

int led = LED_BUILTIN;

void setup()
{
  pinMode(led, OUTPUT);

  Serial.begin(115200);
  delay(10000); // wait for 10 seconds

  if (!SPIFFS.begin())
  {
    // std::cout << "An Error has occurred while mounting SPIFFS, printed using std::cout" << std::endl;
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
  if (!fileContent.isEmpty())
    Serial.println("file contains: " + fileContent);
  else
    Serial.println("could not read file");

  // blink the led
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(500);
}
