constexpr int esp32s3_CS{7};
constexpr int esp32s3_DC{39};
constexpr int esp32s3_SCL{41};
constexpr int esp32s3_SDA{42};

//========================= setup screen =======================
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ILI9341.h> // Hardware-specific library for ST7789
#include <SPI.h>

Adafruit_ILI9341 tft = Adafruit_ILI9341(esp32s3_CS, esp32s3_DC);

//======================== setup MPU6050 =======================
#include <Adafruit_MPU6050.h>
Adafruit_MPU6050 mpu;

float prevAccelX = 0, prevAccelY = 0, prevAccelZ = 0;
float prevGyroX = 0, prevGyroY = 0, prevGyroZ = 0;
float prevTemp = 0;


void setup() {
  //general stuff
  Serial.begin(115200);
  Serial.println("Beginning setup");

  Wire.setPins(esp32s3_SDA, esp32s3_SCL);
  Wire.begin();

  //init screen
  tft.begin();
  Serial.println(F("Screen is Initialized"));

  //init IMU
  if (!mpu.begin())
    Serial.println("Failed to find MPU6050 chip");
  else
    Serial.println("MPU6050 chip is initialized");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("MPU6050 chip is setup");

  tft.setCursor(26, 120);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(3);
  tft.println("Hello, TFT!");

  tft.setCursor(20, 160);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  tft.println("I can has colors?");

  delay(2000);

  Serial.println("setup completed");
  tft.fillScreen(ILI9341_BLACK);
}

void printSensorData()
{
    // Clear the area and update the screen
    tft.fillRect(0, 0, 240, 60, ILI9341_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(1);
    tft.print("Accel X: ");
    tft.print(prevAccelX);
    tft.print(" m/s^2\n");
    tft.print("Accel Y: ");
    tft.print(prevAccelY);
    tft.print(" m/s^2\n");
    tft.print("Accel Z: ");
    tft.print(prevAccelZ);
    tft.print(" m/s^2\n");

    tft.print("Gyro X: ");
    tft.print(prevGyroX);
    tft.print(" rad/s\n");
    tft.print("Gyro Y: ");
    tft.print(prevGyroY);
    tft.print(" rad/s\n");
    tft.print("Gyro Z: ");
    tft.print(prevGyroZ);
    tft.print(" rad/s\n");

    tft.print("Temp: ");
    tft.print(prevTemp);
    tft.print(" C\n");
}

void updateSensorData()
{
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Check if the sensor data has changed
    if (a.acceleration.x != prevAccelX || a.acceleration.y != prevAccelY || a.acceleration.z != prevAccelZ ||
        g.gyro.x != prevGyroX || g.gyro.y != prevGyroY || g.gyro.z != prevGyroZ ||
        temp.temperature != prevTemp)
    {
        // Update cached values
        prevAccelX = a.acceleration.x;
        prevAccelY = a.acceleration.y;
        prevAccelZ = a.acceleration.z;
        prevGyroX = g.gyro.x;
        prevGyroY = g.gyro.y;
        prevGyroZ = g.gyro.z;
        prevTemp = temp.temperature;

        printSensorData();
    }
}


void loop()
{
  updateSensorData();
}
