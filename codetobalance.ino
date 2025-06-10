#include "Arduino.h"
#include <Wire.h>
#include "MPU6050.h"

MPU6050 mpu(0x68);
int ENA = 19;
int IN1 = 18;
int IN2 = 5;

double speed;
unsigned long previousTime = 0;

void getAngle(float *z) {
  static float roll = 0;
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);
  unsigned long currentTime = micros();
  float dt = (currentTime - previousTime) / 1000000.0;
  previousTime = currentTime;
  roll = 0.98 * (roll + gz * dt / 131.0) + 0.02 * (atan2(ay, az) * 180.0 / PI);
  *z = roll;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  previousTime = micros();
}

void loop() {
  float z;
  getAngle(&z);
  if (z < 0) z += 360;
  Serial.print("Z angle: "); Serial.println(z);
  int zInt = (int)z;

if (zInt >=5)
  speed = 255;  // forward zone
 // reverse zone
else
  speed = 0;


  Serial.print("Speed: "); Serial.println(speed);

  if (z > 0 && z<180) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } else if ( z>180) {
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, HIGH);
  }

  
  analogWrite(ENA, (int)speed);  // cast it to int if needed
}
