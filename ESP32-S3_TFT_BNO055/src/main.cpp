#define WOKWI 1

#if WOKWI
// only required for wokwi
#define TFT_CS 7
#define TFT_RST 40
#define TFT_DC 39
#define TFT_BACKLITE 45
#define esp32s3_SDA 42
#define esp32s3_SCL 41

#include <Adafruit_MPU6050.h>
Adafruit_MPU6050 mpu;
#else
// ======== tft screen ========
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
GFXcanvas16 canvas(240, 135);

// ======== BNO IMU ========
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <utility/imumaths.h>
Adafruit_BNO055 bno = Adafruit_BNO055();
#endif

// the setup routine runs once when you press reset:
void setup()
{
  Serial.begin(115200);

#if WOKWI
  Wire.setPins(esp32s3_SDA, esp32s3_SCL);
  Wire.begin();
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
      delay(10);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
#else
  //=== turn on and init the tft screen ===
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
  tft.init(135, 240); // Init ST7789 240x135
  tft.setRotation(3); // rotates the screen

  //=== init BNO IMU ===
  if (!bno.begin(OPERATION_MODE_IMUPLUS))
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.println("No BNO055 detected... Check your wiring or I2C ADDR!");
    while (1)
      ;
  }
  bno.setExtCrystalUse(true);

  delay(1000);
#endif

  Serial.println("setup completed successfully");
}

void loop()
{
  /* Get a new sensor event */
#if WOKWI
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("X: ");
  Serial.print(a.acceleration.x);
  Serial.print("\nY: ");
  Serial.print(a.acceleration.y);
  Serial.print("\nZ: ");
  Serial.print(a.acceleration.z);
  Serial.println("");
#else
  sensors_event_t event;
  bno.getEvent(&event);

  /* Display the floating point data */
  canvas.fillScreen(ST77XX_BLACK);
  canvas.setCursor(0, 10);
  canvas.setTextColor(ST77XX_MAGENTA);
  canvas.setTextSize(3);
  canvas.print("X: ");
  canvas.print(event.orientation.x, 4);
  canvas.setTextColor(ST77XX_WHITE);
  canvas.print("\nY: ");
  canvas.print(event.orientation.y, 4);
  canvas.setTextColor(ST77XX_CYAN);
  canvas.print("\nZ: ");
  canvas.print(event.orientation.z, 4);
  canvas.println("");

  tft.drawRGBBitmap(0, 0, canvas.getBuffer(), 240, 135);
#endif
  delay(10);
}
