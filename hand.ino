/* Get tilt angles on X and Y, and rotation angle on Z
 * Angles are given in degrees
 * 
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>
#include <SoftwareSerial.h>

#define MIN_ANGLE -90
#define MAX_ANGLE 90
#define ANGLE_DEAD_ZONE 20
#define POSITIVE_ANGLE_ACTIVE_ZONE 0 + ANGLE_DEAD_ZONE
#define NEGATIVE_ANGLE_ACTIVE_ZONE 0 - ANGLE_DEAD_ZONE
#define MIN_SPEED 90
#define MAX_SPEED 255

SoftwareSerial bluetooth(4, 5);
MPU6050 mpu(Wire);
unsigned long timer = 0;
float y_angle, x_angle;
byte speed = 0;
void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  Wire.begin();

  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) {}  // stop everything if could not connect to MPU6050

  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets();  // gyro and accelero
  Serial.println("Done!\n");
}

void loop() {
  mpu.update();
  if ((millis() - timer) > 10) {  // print data every 10ms
    Serial.print("X : ");
    Serial.print(mpu.getAngleX());
    Serial.print("\tY : ");
    Serial.print(mpu.getAngleY());
    Serial.print("\tZ : ");
    Serial.println(mpu.getAngleZ());
    timer = millis();
  }
  if (bluetooth.available()) {
    Serial.write(bluetooth.read());
  }
  if (Serial.available()) {
    bluetooth.write(Serial.read());
  }
  y_angle = mpu.getAngleY();
  x_angle = mpu.getAngleX();
  //keep the angles within a desired range
  y_angle = constrain(y_angle, MIN_ANGLE, MAX_ANGLE);
  x_angle = constrain(x_angle, MIN_ANGLE, MAX_ANGLE);

  if (y_angle > POSITIVE_ANGLE_ACTIVE_ZONE) {
    //turn left
    speed = map(y_angle, POSITIVE_ANGLE_ACTIVE_ZONE, MAX_ANGLE, MIN_SPEED, MAX_SPEED);
    bluetooth.write('L');
  } 
  else if (y_angle < NEGATIVE_ANGLE_ACTIVE_ZONE) {
    //turn right
    speed = map(y_angle, NEGATIVE_ANGLE_ACTIVE_ZONE, MIN_ANGLE, MIN_SPEED, MAX_SPEED);
    bluetooth.write('R');
  } 
  else if (x_angle > POSITIVE_ANGLE_ACTIVE_ZONE) {
    // go backward
    speed = map(x_angle, POSITIVE_ANGLE_ACTIVE_ZONE, MAX_ANGLE, MIN_SPEED, MAX_SPEED);
    bluetooth.write('B');
  } 
  else if (x_angle < NEGATIVE_ANGLE_ACTIVE_ZONE) {
    // go forward
    speed = map(x_angle, NEGATIVE_ANGLE_ACTIVE_ZONE, MIN_ANGLE, MIN_SPEED, MAX_SPEED);
    bluetooth.write('F');
  } 
  else {
    speed = 0;
    bluetooth.write('S');
  }
  bluetooth.write(speed);
}