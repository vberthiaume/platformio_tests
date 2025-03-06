#define USE_SPIFFS 1
#define REDIRECT 0

#include <Arduino.h>
#include <iostream>

#if REDIRECT
class SerialOut : public std::streambuf {
public:
    int overflow(int c) override {
        if (c != EOF) {
            Serial.write(c);
        }
        return c;
    }
};

SerialOut serialOut;
std::ostream serialStream(&serialOut);
#endif

//=====================================================

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
  #if REDIRECT
  std::cout.rdbuf(&serialOut);  // Redirect std::cout to Serial
  #endif
  while (!Serial)
  {
    // wait for serial monitoring
  }

#if USE_SPIFFS
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
#endif
}

void loop()
{
#if USE_SPIFFS
  if (!fileContent.isEmpty())
  {
    // std::cout << "fileContent printed with std::cout: " << fileContent.c_str() << std::endl;
    Serial.println(fileContent);
  }
  else
  {
    // std::cout << "couldn't open the file";
    Serial.println("couldn't open the file");
  }
#else
  Serial.println("printing from Serial.println");
  // std::cout << "printing from std::cout\n";
  // printf("Hello from printf!\n");
#endif
}
