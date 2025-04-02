#include <Arduino.h>
#include <iostream>
#include "SPIFFS.h"

String fileContent;

int led = LED_BUILTIN;

void setup()
{
  pinMode(led, OUTPUT);

  Serial.begin(115200);
  delay(5000); // wait for 1 seconds

  Serial.println("\n\n\n=============================================================");

  if (SPIFFS.begin())
  {
    Serial.println("Mounting SPIFFS succeeded!");
  }
  else
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
    Serial.println("SPIFFS: file contains: " + fileContent);
  else
    Serial.println("SPIFFS: could not read file");

  // blink the led
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(500);
}
