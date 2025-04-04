#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// How many internal neopixels do we have? some boards have more than one!
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// the setup routine runs once when you press reset:
void setup()
{
  Serial.begin(115200);
  // this is to wait for the serial monitor!
  // while (! Serial)
  //   delay(10);

  // turn on the led
#if defined(NEOPIXEL_POWER)
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
#endif

  pixels.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(20); // not so bright

  // turn on the tft backlight
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  tft.init(135, 240);               // Init ST7789 240x135
  tft.setRotation(3);               // rotates the screen
  tft.fillScreen(ST77XX_BLACK);     // fills the screen with black colour
  tft.setCursor(0, 10);            // starts to write text at y10 x10
  tft.setTextColor(ST77XX_MAGENTA); // text colour to white you can use hex codes like 0xDAB420 too
  tft.setTextSize(3);               // sets font size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc
  tft.setTextWrap(true);
  tft.print("HELLO WORLD!\n");
  tft.setTextSize(1); // sets font size
  tft.print("hello world but way smaller");
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

void loop()
{
  // cycle through colors
  for (int i = 0; i < 8; i++)
  {
    pixels.fill(colors[i]);
    pixels.show();
    delay(500); // wait half a second
  }

  // turn off
  pixels.fill(0x000000);
  pixels.show();
  delay(500); // wait half a second

  Serial.print(".");
}
