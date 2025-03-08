#include "LittleFS.h"

String fileContent = ""; // Global string to store file content

int led = LED_BUILTIN;

void setup()
{
  pinMode(led, OUTPUT);

  Serial.begin(115200);
  delay(10000); // wait for 10 seconds

  Serial.println("attempting to begin little fs");
  if (!LittleFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  File file = LittleFS.open("/text.txt", "r");
  if (!file)
  {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.println("Reading file content...");
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

  //blink the led
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
}
