#include <Arduino.h>

#define LED 5

void setup()
{
  pinMode(LED, OUTPUT);

  Serial.begin(115200);
  Serial.println("Hello, Wokwi!");
}

void loop()
{
  digitalWrite(LED, LOW);
  delay(1000);
  digitalWrite(LED, HIGH);
  delay(1000);
  Serial.println("ducoup");
}
