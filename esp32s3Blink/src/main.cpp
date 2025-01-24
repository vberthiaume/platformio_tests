#define PRINT_TO_TFT 1

// ======== neopixel led ========
#if !PRINT_TO_TFT
#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

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

int curColor = -1;
#endif

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
#if !PRINT_TO_TFT
  while (! Serial)
    delay(10);//wait for serial monitor to open

  //=== init the neopixel led ===
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
  pixels.begin();
  pixels.setBrightness(20);
#endif

  //=== turn on and init the tft screen ===
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
  tft.init(135, 240);               // Init ST7789 240x135
  tft.setRotation(3);               // rotates the screen
  tft.setTextColor(ST77XX_MAGENTA); // text colour to white you can use hex codes like 0xDAB420 too
  tft.setTextSize(3);               // sets font size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc

#if !PRINT_TO_TFT 
  //greet the world
  tft.fillScreen(ST77XX_BLACK);     // fills the screen with black colour
  tft.setCursor(10, 10);            // starts to write text at y10 x10
  tft.setTextWrap(true);
  tft.print("Hello World!\n");
#endif

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
#if !PRINT_TO_TFT
  //have the led cycle through the colors
  if (++curColor == 8)
    curColor = 0;

  pixels.fill(colors[curColor]);
  pixels.show();
#endif

  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  /* Display the floating point data */
#if PRINT_TO_TFT
  tft.fillScreen(ST77XX_BLACK); // Clear the screen
  tft.setCursor(10, 10);
  tft.print("X: ");
  tft.print(event.orientation.x, 4);
  tft.print("\nY: ");
  tft.print(event.orientation.y, 4);
  tft.print("\nZ: ");
  tft.print(event.orientation.z, 4);
  tft.println("");
  delay(200);
#else
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");
  delay(100);
#endif
}
