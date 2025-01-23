//======================== setup pins =======================
#include <TinyPICO.h>
constexpr int pico_SDA{25};
constexpr int pico_SCL{26};

TinyPICO tp;

//======================== setup MPU6050 =======================
#include <Adafruit_BNO055.h>
#include <Adafruit_BMP280.h>

Adafruit_BNO055 bno;
Adafruit_BMP280 bmp;

float prevAccelX = 0, prevAccelY = 0, prevAccelZ = 0;
float prevGyroX = 0, prevGyroY = 0, prevGyroZ = 0;

//======================== main code =======================
void setup(void)
{
  tp.DotStar_Clear();
  tp.DotStar_SetBrightness(255);

  Serial.begin(115200);
  Serial.println(F("beginning setup"));

  Wire.setPins(pico_SDA, pico_SCL);
  Wire.begin();

  // bmp = Adafruit_BMP280();

  if (!bmp.begin())
    Serial.println("Failed to start bmp");
  else
    Serial.println("bmp is initialized");

  if (!bmp.begin())
    Serial.println("Failed to start bmp");
  else
    Serial.println("bmp is initialized");

  // mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  // mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  // mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("MPU6050 chip is setup");
}

void printSensorData()
{
  Serial.print("\nX: ");
  Serial.print(prevAccelX);
  Serial.print("\tY: ");
  Serial.print(prevAccelY);
  Serial.print("\tZ: ");
  Serial.print(prevAccelZ);

  Serial.print("\tGX: ");
  Serial.print(prevGyroX);
  Serial.print("\tGY: ");
  Serial.print(prevGyroY);
  Serial.print("\tGZ: ");
  Serial.print(prevGyroZ);
}

void updateSensorData()
{
  sensors_event_t a, g;
  bno.getEvent(&a, Adafruit_BNO055::VECTOR_EULER);
  bno.getEvent(&g, Adafruit_BNO055::VECTOR_LINEARACCEL);

  // Check if the sensor data has changed
  if (a.acceleration.x != prevAccelX || a.acceleration.y != prevAccelY || a.acceleration.z != prevAccelZ ||
      g.gyro.x != prevGyroX || g.gyro.y != prevGyroY || g.gyro.z != prevGyroZ)
  {
    // Update cached values
    prevAccelX = a.acceleration.x;
    prevAccelY = a.acceleration.y;
    prevAccelZ = a.acceleration.z;
    prevGyroX = g.gyro.x;
    prevGyroY = g.gyro.y;
    prevGyroZ = g.gyro.z;
    printSensorData();
    return;
  }

  Serial.println("nothing yet bro");
}

void loop()
{
  updateSensorData();

  tp.DotStar_CycleColor(25);
  delay(10);
}
