#include <Arduino_LSM9DS1.h>

float x, y, z, ledValue;

void setup() {
  Serial.begin(9600);
  IMU.begin();
}

void loop() {
  IMU.readMagneticField(x, y, z);

  Serial.print("x: ");
  Serial.println(x);
  Serial.print("y: ");
  Serial.println(y);
  Serial.print("z: ");
  Serial.println(z);

  analogWrite(LED_BUILTIN, abs(x));
  delay(500);
}
