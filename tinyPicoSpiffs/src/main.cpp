#include <TinyPICO.h>
#include "SPIFFS.h"

#define LED_PIN 25 // Pin connected to the LED anode

TinyPICO tp;
String fileContent;

void setup()
{
  Serial.begin(115200);

  if (!SPIFFS.begin(true))
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

  // Initialize LED pin as output
  pinMode(LED_PIN, OUTPUT);

  tp.DotStar_Clear();
  tp.DotStar_SetBrightness(255);
}

void loop()
{
  // Turn the LED on (full brightness)
  analogWrite(LED_PIN, 255);
  delay(250); // Keep it on for 1 second

  // Turn the LED off
  analogWrite(LED_PIN, 0);
  delay(250); // Keep it off for 1 second

  tp.DotStar_CycleColor(10);
  Serial.println(fileContent);
}
