// ======== neopixel led ========
#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

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
  while (! Serial)
    delay(10);//wait for serial monitor to open

  //=== init the neopixel led ===
#if defined(NEOPIXEL_POWER)
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
#endif

  pixels.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(20); // not so bright

  //=== turn on and init the tft screen ===
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  tft.init(135, 240);               // Init ST7789 240x135
  tft.setRotation(3);               // rotates the screen
  tft.fillScreen(ST77XX_BLACK);     // fills the screen with black colour
  tft.setCursor(10, 10);            // starts to write text at y10 x10
  tft.setTextColor(ST77XX_MAGENTA); // text colour to white you can use hex codes like 0xDAB420 too
  tft.setTextSize(3);               // sets font size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc
  tft.setTextWrap(true);
  tft.print("Hello World!\n");

  //=== init BNO IMU ===
  if (!bno.begin())
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

// array of colors to cycle through
uint32_t colors[] = {
    pixels.Color(255, 0, 0),     // Red
    pixels.Color(0, 255, 0),     // Green
    pixels.Color(0, 0, 255),     // Blue
    pixels.Color(255, 255, 0),   // Yellow
    pixels.Color(0, 255, 255),   // Cyan
    pixels.Color(255, 0, 255),   // Magenta
    pixels.Color(255, 255, 255), // White
    pixels.Color(128, 0, 128)    // Purple
};

int i = -1;
void loop()
{
  //have the led cycle through the colors
  if (++i == 8)
    i = 0;

  pixels.fill(colors[i]);
  pixels.show();

  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");

  delay(100);
}
