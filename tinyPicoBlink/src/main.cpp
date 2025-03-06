/*
  TinyPico RGB Color Cycling demo

  https://wokwi.com/arduino/projects/308012505806930496
*/

#include <TinyPICO.h>
#include <iostream>

#define LED_PIN 25 // Pin connected to the LED anode

TinyPICO tp = TinyPICO();

void setup()
{
  Serial.begin(115200);

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

  tp.DotStar_CycleColor(25);
  Serial.println("ducoup");
  std::cout << "ducoup cout\n";
}
