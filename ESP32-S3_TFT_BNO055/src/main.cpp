// ======== tft screen ========
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// ======== BNO IMU ========
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
Adafruit_BNO055 bno = Adafruit_BNO055();

// the setup routine runs once when you press reset:
void setup()
{
  Serial.begin(115200);

  //=== turn on and init the tft screen ===
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
  tft.init(135, 240);               // Init ST7789 240x135
  tft.fillScreen(ST77XX_BLACK);     // Clear the screen
  tft.setRotation(3);               // rotates the screen
  tft.setTextColor(ST77XX_MAGENTA); // text colour to white you can use hex codes like 0xDAB420 too
  tft.setTextSize(3);               // sets font size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc

  //=== init BNO IMU ===
  if (!bno.begin(OPERATION_MODE_IMUPLUS))
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.println("No BNO055 detected... Check your wiring or I2C ADDR!");
    while (1)
      ;
  }

  delay(1000);

  bno.setExtCrystalUse(true);
  Serial.println("setup completed successfully");
}

void loop()
{
  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  /* Display the floating point data */
  tft.fillScreen(ST77XX_BLACK); // Clear the screen
  tft.setCursor(0, 10);
  tft.print("X: ");
  tft.print(event.orientation.x, 4);
  tft.print("\nY: ");
  tft.print(event.orientation.y, 4);
  tft.print("\nZ: ");
  tft.print(event.orientation.z, 4);
  tft.println("");
  delay(200);
}
