/* Get tilt angles on X and Y, and rotation angle on Z off two MPU's
 * Angles are given in degrees
 * 
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>

#define UPDATE_TIME 10

MPU6050 mpu1(Wire, 0x68);
MPU6050 mpu2(Wire, 0x69);
unsigned long timer = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  byte status1 = mpu1.begin();
  Serial.print(F("MPU6050 1 status: "));
  Serial.println(status1 ? "ERROR " + String(status1) : "initialized successfully");
  while(status1!=0){ } // stop everything if could not connect to MPU6050 1

  byte status2 = mpu2.begin();
  Serial.print(F("MPU6050 2 status: "));
  Serial.println(status2 ? "ERROR " + String(status2) : "initialized successfully");
  while(status2!=0){ } // stop everything if could not connect to MPU6050 2
  
  Serial.println(F("Calculating offsets, do not move MPU6050 1"));
  delay(500);
  mpu1.calcOffsets(); // gyro and accelero

  Serial.println(F("Calculating offsets, do not move MPU6050 2"));
  delay(500);
  mpu2.calcOffsets(); // gyro and accelero

  Serial.println("All done!\n");
}

void loop() {
  mpu1.update();
  mpu2.update();
  
  if((millis() - timer) > UPDATE_TIME){
    //MPU 1
    Serial.print("X:");
    Serial.print(mpu1.getAngleX());
    Serial.print(" Y:");
    Serial.print(mpu1.getAngleY());
    Serial.print(" Z:");
    Serial.print(mpu1.getAngleZ());

    //MPU 2
    Serial.print("\tX:");
    Serial.print(mpu2.getAngleX());
    Serial.print(" Y:");
    Serial.print(mpu2.getAngleY());
    Serial.print(" Z:");
    Serial.print(mpu2.getAngleZ());
    
    timer = millis();  
  }
}
